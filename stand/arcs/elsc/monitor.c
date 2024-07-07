//#pragma option v  
/* monitor.c */
/*
 * monitors data structure contain task status.  Calls appropriate routine for
 * any outstanding tasks.
 */
//#include <16c74.h>
//#include <elsc.h>
//#include <proto.h>

/* 
 * These global statements will be removed as soon as I can figure
 * out how to handle global varibles between modules.
 */
/* Global Structure Declarations */
//extern struct MONITOR tasks;		/* data structure containing task status */
//extern struct SYS_STATE reg_state;	/* data struct containing copies of reg. */
//extern struct TIMER TCB;			/* data structure containing task status */

/******************************************************************************
 *																										*
 *	monitor() - polls the task data sturcture for outstanding tasks, and			*
 *				calls the appropriate routing to handle the task.  The 				*
 *				individual task routines are responsible for resetting the			*
 *				data structure's bits.															*
 *																										*
 *				Upon entry the first job is to check for initial conditions			*
 *				that require task handling.  This is necessary because				*
 *				interrupts are generated by either a change in state or an			*
 *				edge transition.																	*
 *																										*
 ******************************************************************************/
void
monitor()
{
	 while (1) {
		/* Reset the Watch Dog Timer */
		CLRWDT();
#ifdef	SPEEDO
		/* keep sending a slave present command until the master responds */
		if (tasks.env2.ENV2_SPEEDO_SLAVE && !tasks.env2.ENV2_SPEEDO_MS_ENABLE) { 
			slave_cmd_param = SLAVE_PR;
			if (elscToElsc(SLAVE_CMD) == 0)
				tasks.env2.ENV2_SPEEDO_MS_ENABLE = 1;
		}
		
		/*
		 * keep trying to send the master a message if the MS is enabled and
		 * the slave_cmd_param is non zero.
		 */
		if (tasks.env2.ENV2_SPEEDO_SLAVE && (slave_cmd_param != 0)) {
			if (elscToElsc(SLAVE_CMD) == 0)
				slave_cmd_param = 0;
		}

		/*
		 * Send a slave ELSC a command.  First the bus must be granted and the
		 * master's slave I2C code must be idle to be able to send the command
		 */
		if (tasks.env2.ENV2_SPEEDO_MASTER && (master_cmd_param != 0)) {

				/* request the bus */
			if (!cmdp.cmd_intr.ELSC_I2C_GRANT)
				cmdp.cmd_intr.ELSC_I2C_REQ = 1;

			/* if the bus is granted and the slave code is idle send the command */
			if (cmdp.cmd_intr.ELSC_I2C_GRANT) {
				temp = elscToElsc(master_cmd_param);
				if (temp == 0) {
						i2c_retry = 5;
						master_cmd_param = 0;
				}
				else
					i2c_retry--;

				if (i2c_retry == 0) {
					master_cmd_param = 0;
					i2c_retry = 5;
				}
			}

		}
		 
#endif



		
#ifdef MODEM
		/* Modem flow control CTS & DCD Management */
		

#ifdef	SPEEDO
		/* Receiver buffers, Assert RTS if there is room to receive chars */
#ifdef RTS_CORRECTION
		if((reg_state.reg_out1.RTS == 1) && (i2c_outq.c_len <= LOWWATER)) {
			reg_state.reg_out1.RTS = 0;
			ext_ptr_store = OUTP1;
			extMemWt(reg_state.reg_out1);
		}
#else
		if((reg_state.reg_out1.RTS == 0) && (i2c_outq.c_len <= LOWWATER)) {
			reg_state.reg_out1.RTS = 1;
			ext_ptr_store = OUTP1;
			extMemWt(reg_state.reg_out1);
		}
#endif
		
#else	// SPEEDO

#ifdef RTS_CORRECTION
		/* Receiver buffers, Assert RTS if there is room to receive chars */
		if((reg_state.reg_out3.RTS == 1) && (i2c_outq.c_len <= LOWWATER)) {
			reg_state.reg_out3.RTS = 0;
			ext_ptr_store = OUTP3;
			extMemWt(reg_state.reg_out3);
		}
#else
		/* Receiver buffers, Assert RTS if there is room to receive chars */
		if((reg_state.reg_out3.RTS == 0) && (i2c_outq.c_len <= LOWWATER)) {
			reg_state.reg_out3.RTS = 1;
			ext_ptr_store = OUTP3;
			extMemWt(reg_state.reg_out3);
		}
#endif
#endif	// SPEEDO
		/* Xmit Buffer, Enable xmit interrupt if DCE ready to receive char */
		if (sci_outq.c_len > 0 && !reg_state.reg_in2.CTS)
			PIE.TXIE = 1;

#endif
		/* Check on Polled Inputs */
		if ((PORTA ^ reg_state.reg_ra))
			inputPortA();
			
		/* Check on Polled Inputs */
		if ((PORTB ^ reg_state.reg_rb) & PORTB_MASK)
			inputPortB();

		ext_ptr_store = INPT2;
		t_reg = extMemRd();
		
		if (t_reg ^ reg_state.reg_in2)
			inputIn2();
			
#ifndef	NO_PORTB_INT
		/* Now Check for outstanding Tasks*/
		if (tasks.env1 != 0 || (tasks.env2 & 0x7F) !=0 )
			tasks_env();
#endif
		if ((tasks.switches & 0x1F) != 0) /* do not respond to switch debounce */
			tasks_switch();
		if (tasks.fw_logical != 0)
			tasks_fw();
			
#ifdef	FAN_CHK
		if (fan_ptr.fan_stat_2.STAT2_CNT_CHK == 1 || fan_ptr.fan_stat_2.STAT2_FAN_LRTR)
			tasks_fan();
#endif

#ifdef	SPEEDO
			/* check for message recevied from Slave ELSC */
			if (slave_cmd_param &&	tasks.env2.ENV2_SPEEDO_MASTER) 
				tasks_SlaveElsc();

#endif
		/* Evaluate the environmental conditions and slow fans, if appropriate */
		if (tasks.fw_logical.FWL_FAN_SPEED)
			tasksFanSpeed();
			
	
		if (cmdp.cmd_intr.CMD_I2C) {
			cmdp.cmd_stat.SCI_I2C = 0;
			processCmd();
		}
		
		else if (cmdp.cmd_intr.CMD_SCI) {
			cmdp.cmd_stat.SCI_I2C = 1;
			processCmd();
		}
		
		/* Check for characters to be transferred from I2C in queue
		 * to SCI out queue.  These characters are discarded during
		 * Control-T commands; otherwise, output would interfere
		 * when the FFSC is using Control-T commands.
		 */

		if (slavep.sci_xfer_ct) {
			while (slavep.sci_xfer_ct > 2 && sci_outq.c_len < HIWATER) {

				CPUSTA.GLINTD = 1;
				INTSTA.INTIE = 0;
				INTSTA.PEIE = 0;
				CPUSTA.GLINTD = 0;
				
				temp = remq(I2C_IN);
				if (cmdp.cmd_intr.PASS_THRU &&
						(cmdp.cpu_see + 1 < 1 ||		/* Compiler bug WAR */
							cmdp.cpu_acp == cmdp.cpu_see))
					addq(SCI_OUT, temp);
					INTSTA.INTIE = 1;
					INTSTA.PEIE = 1;
				PIE.TXIE = 1;
				slavep.sci_xfer_ct--;
			}					
					
			/* after all characters have been transferred
			 * to out queue, send hub response */
			if (slavep.sci_xfer_ct == 2) {
				slavep.sci_xfer_ct = 0;

				/* remove the terminating CR from the queue */
				CPUSTA.GLINTD = 1;
				INTSTA.INTIE = 0;
				INTSTA.PEIE = 0;
				CPUSTA.GLINTD = 0;
				
				(void) remq(I2C_IN);
				
				INTSTA.INTIE = 1;
				INTSTA.PEIE = 1;

				param_val = slavep.bytes_used - 2;
				temp = putParam(&rsp_buf[4]);
					
				sendHubRsp();
			}
		}

		/* check for expired time out conditions */
		if (TCB.to_status || TCB.to_status_1) 
			tasks_to();
	}
}


/***************************************************************************
 *																									*
 *	inputPortA - 	Handles monitor inputs from Port A for the following 		*
 *						signals:																	*
 *							Key Switch Off														*
 *																									*
 ***************************************************************************/
void
inputPortA()
{
	t_reg = PORTA;

#ifndef	IGNORE_OT
	/* System Over Temperature */
	if (!t_reg.TMP_SYS_OT && reg_state.reg_ra.TMP_SYS_OT && tasks.env1.ENV1_TMP_EN) {
#ifdef	SPEEDO
		/* turn on RED LED */
		reg_state.reg_out1.LED_GREEN = 0;
		reg_state.reg_out1.LED_RED = 1;
		ext_ptr_store = OUTP1;
		extMemWt(reg_state.reg_out1);

		/*
		 * if a slave send a message to the master ELSC, and let the master
		 * signal when to power down.
		 */
		if (tasks.env2.ENV2_SPEEDO_SLAVE) {
			slave_cmd_param = SLAVE_OT;
			(void) elscToElsc(SLAVE_CMD);
		}

#else
		dspMsg(MSG_SYSOT);
		reg_state.reg_out3.SYS_OT_LED = 1;

		ext_ptr_store = OUTP3;
		extMemWt(reg_state.reg_out3);
		sendHubInt(INT_PD_TEMP);
		tasks.fw_logical.FWL_PWR_DN = 1;
#endif	// SPEEDO		
		reg_state.reg_ra.TMP_SYS_OT = 0;
	}
	/* reset the register copy of the over temperature bit */
	else if (t_reg.TMP_SYS_OT && !reg_state.reg_ra.TMP_SYS_OT)
		reg_state.reg_ra.TMP_SYS_OT = 1;
#endif	//IGNORE_OT
	
#ifndef	SPEEDO
#ifndef	_005
	/* key switch in a new position */
	if ((t_reg ^ reg_state.reg_ra) & KEY_SW_OFF_MASK) {
		if (!tasks.switches.FPS_KEY_BOUNCE) {
			tasks.switches.FPS_KEY_BOUNCE = 1;
			to_value = ONE_SEC;
			timeout(KEY_TO);
			reg_state.reg_ra.KEY_SW_OFF = t_reg.KEY_SW_OFF ? 0 : 1;
		}
	}
#endif
#endif

}

#ifdef	NO_PORTB_INT
/***************************************************************************
 *																									*
 *	inputPortB - 	Handles monitor inputs from Port B for the following 		*
 *						signals:																	*
 *																									*
 *																									*
 ***************************************************************************/
void
inputPortB()
{
	t_reg = PORTB;
	
#ifndef	SPEEDO
#ifdef	_005
#ifdef POK_CHK
	/* POK Failure */
	if (!t_reg.POKB && reg_state.reg_rb.POKB && !reg_state.reg_out3.PS_EN) {
		getPOKBId();
		tasks.fw_logical.FWL_PWR_DN = 1;
		reg_state.reg_rb.POKB = 0;

	}
#endif

	/* key switch in a new position */
	if ((t_reg ^ reg_state.reg_rb) & KEY_SW_OFF_MASK) {
		if (!tasks.switches.FPS_KEY_BOUNCE) {
			tasks.switches.FPS_KEY_BOUNCE = 1;
			to_value = ONE_SEC;
			timeout(KEY_TO);
		}
	}

#else
		/* Power Supply Failure */
	if (((t_reg ^ reg_state.reg_rb) & PS_OK_MASK) && !t_reg.PS_OK
		&& !reg_state.reg_out3.PS_EN) {

		dspMsg(MSG_PSFL);
		sendHubInt(INT_PD_PSFL);
		tasks.fw_logical.FWL_PWR_DN = 1;
		reg_state.reg_rb.PS_OK = 0;

	}
			
		/* Power Failure Warning */
	if (((t_reg ^ reg_state.reg_rb) & PWR_FAIL_MASK) &&
			!t_reg.PWR_FAIL && tasks.status.STAT_SYSPWR) {

		dspMsg(MSG_PFW);
		sendHubInt(INT_AC);
		tasks.fw_logical.FWL_PWR_DN = 1;
		reg_state.reg_rb.PWR_FAIL = 0;
	}
#endif

#endif	//SPEEDO
	
	/* System High Temperature */
	if (t_reg.TMP_FANS_HI && !reg_state.reg_rb.TMP_FANS_HI &&
			tasks.env1.ENV1_TMP_EN) {
#ifdef	SPEEDO
		/* if a slave send a message to the master ELSC. */
		if (tasks.env2.ENV2_SPEEDO_SLAVE) 
			slave_cmd_param = SLAVE_HT;
		
#endif	//SPEEDO
		tasks.status.STAT_SYSHT = 1;
		/* disable the pulse conunting status bit */
#ifdef FAN_CHK
		tasks.fw_logical.FWL_FAN_SPEED = 1;
#endif
		reg_state.reg_rb.TMP_FANS_HI = 1;

	}
		
	/* Temperature Normal */
	else if (!t_reg.TMP_FANS_HI && reg_state.reg_rb.TMP_FANS_HI &&
			tasks.env1.ENV1_TMP_EN) {
		tasks.status.STAT_SYSHT = 0;
		/* check the conditions and see if the fan speed can be lowered */
		tasks.fw_logical.FWL_FAN_SPEED = 1;
#ifdef	SPEEDO
		/*
		 * if a slave send a message to the master ELSC.
	 	*/
		if (tasks.env2.ENV2_SPEEDO_SLAVE) 
			slave_cmd_param = SLAVE_NT;
#endif
		reg_state.reg_rb.TMP_FANS_HI = 0;
}
		
#if 0
	/* Reset Button Pushed ? */
	if (((t_reg ^ reg_state.reg_rb) & RST_MASK) && !tasks.switches.FPS_RST_BOUNCE){
		/* change of state is a closed switch */
		if (!t_reg.RESET_SW ) 
			tasks.switches.FPS_RESET = 1;
		tasks.switches.FPS_RST_BOUNCE = 1;
		to_value = MSEC_250;
		timeout(RESET_TO); 
	}

	/* NMI Button Pushed ? */
	if (((t_reg ^ reg_state.reg_rb) & NMI_MASK) && !tasks.switches.FPS_NMI_BOUNCE){
		/* change of state is a closed switch */
		if (!t_reg.NMI_SW) 
			tasks.switches.FPS_NMI = 1;
		tasks.switches.FPS_NMI_BOUNCE = 1;
		to_value = MSEC_250;
		timeout(NMI_TO); 
	}
#endif
	/* Reset Button Pushed ? */
	if (!t_reg.RESET_SW && !tasks.switches.FPS_RST_BOUNCE){
		tasks.switches.FPS_RESET = 1;
		tasks.switches.FPS_RST_BOUNCE = 1;
		to_value = MSEC_250;
		timeout(RESET_TO); 
	}

	/* NMI Button Pushed ? */
	if (!t_reg.NMI_SW  && !tasks.switches.FPS_NMI_BOUNCE){
		tasks.switches.FPS_NMI = 1;
		tasks.switches.FPS_NMI_BOUNCE = 1;
		to_value = MSEC_250;
		timeout(NMI_TO); 
	}
}
#endif

/***************************************************************************
 *																									*
 *	inputIn2 - 	Handles monitor inputs from Input port at 0x5000 for the *
 *						following signals:													*
 *							Fan Hi Speed														*
 *							System Over Temperature											*
 *							Pwr Supply Over Temp (PS_OT2)									*
 *																									*
 ***************************************************************************/
void
inputIn2()
{

#ifdef	SPEEDO
	
		/* Power Supply Failure */
	if (((t_reg ^ reg_state.reg_in2) & PS_OK_MASK) && !t_reg.PS_OK
		&& !reg_state.reg_ra.POWERON_L) {
		speedoLED(RED, LED_BLINK);
		if (tasks.env2.ENV2_SPEEDO_SLAVE) {
			slave_cmd_param = SLAVE_PSF;
		}
		else {
			sendHubInt(INT_PD_PSFL);
			tasks.fw_logical.FWL_PWR_DN = 1;
		}
		to_value = TWO_SEC;
		delay();
	}

	/* Power Switch has been depressed */
	if (!t_reg.PWR_SW_L && tasks.env2.ENV2_SPEEDO_MASTER) {
		if (!tasks.switches.FPS_KEY_BOUNCE) {
			tasks.switches.FPS_KEY_BOUNCE = 1;
			to_value = MSEC_500;
			timeout(KEY_TO);
		}
	}


#elif		defined(_005)
	
	/* Power Supply Failure */
	if (((t_reg ^ reg_state.reg_in2) & PS_OK_MASK) && !t_reg.PS_OK
		&& !reg_state.reg_out3.PS_EN) {
			
		dspMsg(MSG_PSFL);
		sendHubInt(INT_PD_PSFL);
		tasks.fw_logical.FWL_PWR_DN = 1;
	}

	/* Power Failure Warning */
	if (((t_reg ^ reg_state.reg_in2) & PWR_FAIL_MASK) &&
		!t_reg.PWR_FAIL && tasks.status.STAT_SYSPWR) {
		dspMsg(MSG_PFW);
		sendHubInt(INT_AC);
		tasks.fw_logical.FWL_PWR_DN = 1;
	}


#else

#ifdef POK_CHK
	/* POK Failure */
	if (!t_reg.POKB && reg_state.reg_in2.POKB && !reg_state.reg_out3.PS_EN) {
		getPOKBId();
		tasks.fw_logical.FWL_PWR_DN = 1;
	}
#endif
#endif

#ifndef	SPEEDO
	/* Check for a change in the key switch position */
	if ((t_reg ^ reg_state.reg_in2) & DIAG_SW_MASK) {
		tasks.switches.FPS_KEY_BOUNCE = 1;
		to_value = ONE_SEC;
		timeout(KEY_TO);
	}

	/* Power Supply Over Temperature Failure */
	if (t_reg.PS_OT2 && !reg_state.reg_in2.PS_OT2) {
		dspMsg(MSG_PSOT2);
		sendHubInt(INT_PD_PSOT);
		tasks.fw_logical.FWL_PWR_DN = 1;
		tasks.fw_logical.FWL_PS_OT = 1;
		reg_state.reg_out3.SYS_OT_LED = 1;
		ext_ptr_store = OUTP3;
		extMemWt(reg_state.reg_out3);
	}
#endif
	reg_state.reg_in2 = t_reg;
}

#ifndef	NO_PORTB_INT
/***************************************************************************
 *																									*
 *	tasks_env - Executes outstanding tasks for the env1ironment monitoring	*
 *				duties of the firmware.  Tasks handled are:							*
 *					Power Fail																	*
 *					Power Supply Failures													*
 *					Board Power Failures (POK)												*
 *					Temperature Conditions													*
 *					Fan Conditions																*
 *																									*
 ***************************************************************************/
void
tasks_env()
{

	/* Power fail Warning */
	if (tasks.env1.ENV1_PF) {
		tasks.env1.ENV1_PF = 0;
#ifndef	SPEEDO
		dspMsg(MSG_PFW);
#endif
		
		sendHubInt(INT_AC);
		tasks.fw_logical.FWL_PWR_DN = 1;
	}
	
	/* Power Supply Failure */
	if (tasks.env1.ENV1_PS_FAIL) {
		tasks.env1.ENV1_PS_FAIL = 0;
#ifndef	SPEEDO
		dspMsg(MSG_PSFL);
#endif
		
		sendHubInt(INT_PD_PSFL);
		tasks.fw_logical.FWL_PWR_DN = 1;
	}
#ifndef	SPEEDO
#if defined(POK_CHK) && defined(_005)
	if (tasks.env1.ENV1_POK) {
		tasks.env1.ENV1_POK = 0;
		getPOKBId();
		tasks.fw_logical.FWL_PWR_DN = 1;
	}
#endif
#endif

		/* System High Temperature */
//	if (tasks.env1.ENV1_SYS_HT && tasks.env1.ENV1_TMP_EN) {
	if (tasks.env1.ENV1_SYS_HT) {
		tasks.env1.ENV1_SYS_HT = 0;
		if (!tasks.status.STAT_SYSHT) {
#ifdef	SPEEDO
		 	/* if a slave send a message to the master ELSC. */
			if (tasks.env2.ENV2_SPEEDO_SLAVE) 
				slave_cmd_param = SLAVE_HT;
#endif	//SPEEDO
				
			tasks.status.STAT_SYSHT = 1;
			/* disable the pulse conunting status bit */
#ifdef FAN_CHK
			tasks.fw_logical.FWL_FAN_SPEED = 1;
#endif

		}
	}

//	if ( tasks.env1.ENV1_TEMP_OK && tasks.env1.ENV1_TMP_EN) {
	if ( tasks.env1.ENV1_TEMP_OK) {
		tasks.env1.ENV1_TEMP_OK = 0;
		tasks.status.STAT_SYSHT = 0;
		/* check the conditions and see if the fan speed can be lowered */
		tasks.fw_logical.FWL_FAN_SPEED = 1;
#ifdef	SPEEDO
		/*
		 * if a slave send a message to the master ELSC.
		 */
		if (tasks.env2.ENV2_SPEEDO_SLAVE) 
			slave_cmd_param = SLAVE_NT;
#endif
	}
}
#endif	//NO_PORTB_INT

#ifdef FAN_CHK
/***************************************************************************
 *																									*
 *	tasks_fan -	Check for operation of fans with-in the correct tolerance	*
 *																									*
 ***************************************************************************/
void
tasks_fan()
{

long	pulse_cnt;

	/* set the expected RPM value */
#ifdef	SPEEDO
	if (!tasks.status.STAT_SYSHT)
		pulse_cnt = FAN_NM_CNT;
	else
		pulse_cnt = FAN_HI_CNT;

#else
#ifdef	KCAR_FAN_FULL_SPEED
	/* LEGO Blower Setting */
	if(mp_type != MP_KCAR) {
		if (!tasks.status.STAT_SYSHT)
			pulse_cnt = FAN_NM_CNT;
		else
			pulse_cnt = FAN_HI_CNT;
	}

	/* KCAR Setting */
	else 
		pulse_cnt = KCAR_FAN_HI_CNT;

#else
		
	/* LEGO Blower Setting */
	if(mp_type != MP_KCAR) {
		if (!tasks.status.STAT_SYSHT)
			pulse_cnt = FAN_NM_CNT;
		else
			pulse_cnt = FAN_HI_CNT;
	}

	/* KCAR Setting */
	else {
		if (!tasks.status.STAT_SYSHT)
			pulse_cnt = KCAR_FAN_NM_CNT;
		else
			pulse_cnt = KCAR_FAN_HI_CNT;
	}
#endif	//KCAR_FAN_FULL_SPEED
#endif	//SPEEDO
	
	/* Reset Monitor Flag */
	fan_ptr.fan_stat_2.STAT2_CNT_CHK = 0;


	/* check for out of tolerance conditions */
	// A fan failure is any fan operating below the lower tolerance and with no
	// high temperature condition present, or A fan operating below the high tolerance
	// with a high temperature present, or a locked rotar condition.

	if (fan_ptr.fan_stat_2.STAT2_FAN_LRTR) {
		/* adjust the multiplexer now to avoid unstable address lines, the lines
		 * are also adjusted in the interrupt capture routine.
		 */

		 /* set retry count to max to avoid retest a locked rotor fan if fan
		  * pulses are not being detected
		  */
		if (!tasks.env2.ENV2_FAN_RUNNING)
			fan_ptr.fan_retry = FAN_MAX_RETRY;

		fan_fail();
	}
		
	else if ((char)fan_ptr.fan_period > (char) pulse_cnt)
		fan_fail();

	else {
		fan_ptr.fan_retry = 0;
		next_fan();
	}
}
#endif


/***************************************************************************
 *																									*
 *	tasksFanSpeed:	This function evaluates the envrionment state of the  	*
 *					module and determines if the fan speed can be lowered  		*
 *					to the normal speed setting, or increased to the high 		*
 *					setting.																		*
 *																									*
 ***************************************************************************/
void
tasksFanSpeed() 
{

	int change;								/* flag indicating a change in fan speed */

	change = 0;
	
	/* Reset the request Flag */
	tasks.fw_logical.FWL_FAN_SPEED = 0;

#ifdef	FAN_CHK
	/* Raise the fan Speed? */

#ifdef	SPEEDO
	if (tasks.status.STAT_SYSHT || 
			fan_ptr.fan_stat_2.STAT2_FAN_HI || cmdp.cmd_stat.FAN_HI) {
		reg_state.reg_out1.FAN_HI_SPEED = 1;
		change = 1;
	}

	/* Lower the Fan Speed ? */
	else if (!tasks.status.STAT_SYSHT && 
			!fan_ptr.fan_stat_2.STAT2_FAN_HI && !cmdp.cmd_stat.FAN_HI) {
		reg_state.reg_out1.FAN_HI_SPEED = 0;
		change = 1;
	}
		
#else		//SPEEDO
		
	if (tasks.status.STAT_SYSHT || 
			fan_ptr.fan_stat_2.STAT2_FAN_HI || cmdp.cmd_stat.FAN_HI) {
		reg_state.reg_out3.FAN_HI_SPEED = 1;
		if (mp_type == MP_KCAR) 
			reg_state.reg_out1.KCAR_HI_FAN_SPEED = 1;
		change = 1;
	}

	/* Lower the Fan Speed ? */
	else if (!tasks.status.STAT_SYSHT && 
		!fan_ptr.fan_stat_2.STAT2_FAN_HI && !cmdp.cmd_stat.FAN_HI) {
		
		reg_state.reg_out3.FAN_HI_SPEED = 0;
		if (mp_type == MP_KCAR) 
			reg_state.reg_out1.KCAR_HI_FAN_SPEED = 0;
		change = 1;
	}
		
#endif	//SPEEDO
	/* shutdown the fan pulse monitoring */
	if (change) {
		PIE.CA1IE = 0;
		PIE.CA2IE = 0;
		TCON2.TMR3ON = 0;
		fan_ptr.fan_stat_2.STAT2_CNT_CHK = 0;
		fan_ptr.fan_stat_2.STAT2_FAN_CHK = 0;
		
		/* Set the Fan Speed */
#ifdef	SPEEDO
		ext_ptr_store = OUTP1;
		extMemWt(reg_state.reg_out1);
#else
		ext_ptr_store = OUTP3;
		extMemWt(reg_state.reg_out3);
		if (mp_type == MP_KCAR) {
			ext_ptr_store = OUTP1;
			extMemWt(reg_state.reg_out1);
		}

#endif

		/* Check the fans again in 10 Seconds if the system is powered up*/
		if (tasks.status.STAT_SYSPWR) {
			if(!mfg_tst)
				to_value = TEN_SEC;
			else
				to_value = MSEC_500;
			timeout(FAN_TO);

			/* disable temperature monitoring for the duration of the fan timeout,
		 	* due to noise on the rs-232 line in MMSC/MSC configuration
		 	*/
			tasks.env1.ENV1_TMP_EN = 0;
		}
	}
		

#else

#ifdef	SPEEDO
	/* Raise the fan Speed? */
	if (tasks.status.STAT_SYSHT || cmdp.cmd_stat.FAN_HI)
	
		reg_state.reg_out1.FAN_HI_SPEED = 1;

	/* Lower the Fan Speed ? */
	else if (!tasks.status.STAT_SYSHT &&  !cmdp.cmd_stat.FAN_HI)
	
		reg_state.reg_out1.FAN_HI_SPEED = 0;
		
		
	/* Set the Fan Speed */
	ext_ptr_store = OUTP1;
	extMemWt(reg_state.reg_out1);

#else		//SPEEDO
	
	/* Raise the fan Speed? */
	if (tasks.status.STAT_SYSHT || cmdp.cmd_stat.FAN_HI) {
		reg_state.reg_out3.FAN_HI_SPEED = 1;
		if (mp_type == MP_KCAR) 
			reg_state.reg_out1.KCAR_HI_FAN_SPEED = 1;
	}


	/* Lower the Fan Speed ? */
	else if (!tasks.status.STAT_SYSHT &&  !cmdp.cmd_stat.FAN_HI) {
	
		reg_state.reg_out3.FAN_HI_SPEED = 0;
		if (mp_type == MP_KCAR) 
			reg_state.reg_out1.KCAR_HI_FAN_SPEED = 0;
	}
		
		
		
	/* Set the Fan Speed */
	ext_ptr_store = OUTP3;
	extMemWt(reg_state.reg_out3);
	if (mp_type == MP_KCAR) {
		ext_ptr_store = OUTP1;
		extMemWt(reg_state.reg_out1);
	}


#endif	// SPEEDO
#endif	// FAN_CHK

}

#ifdef	SPEEDO
/***************************************************************************
 *																									*
 *	tasks_SlaveElsc:	Processes status information received from Slave ELSC	*
 *							in a Speedo Master / Slave confiuration.					*
 *																									*
 ***************************************************************************/
void
tasks_SlaveElsc()
{
	switch(slave_cmd_param) {
		case	SLAVE_NT:
			/* Slave Normal Temperature Restored */
			slave_temp_stat = SLAVE_NT;
			break;
		case	SLAVE_HT:
			/* Slave High Temperature */
			slave_temp_stat = SLAVE_HT;
			break;
		case	SLAVE_OT:
			/* Slave Over Temperature, initiate a shutdown */
			slave_temp_stat = SLAVE_OT;
			sendHubInt(INT_PD_TEMP);
			tasks.fw_logical.FWL_PWR_DN = 1;
			break;
		case	SLAVE_FF:
			/* Slave Fan Failed */
			sendHubInt(INT_FAN_OUT);
			break;
		case	SLAVE_MFF:
			/* Slave Multiple fan failure, must shut the system down */
			sendHubInt(INT_FAN_OUT);
			tasks.fw_logical.FWL_PWR_DN = 1;
			break;
		case	SLAVE_PSF:
			/* Slave Power Supply Failure, must shut the system down */
			sendHubInt(INT_PD_PSFL);
			tasks.fw_logical.FWL_PWR_DN = 1;
			break;
		case	SLAVE_PR:
			/* Slave Present */
			tasks.env2.ENV2_SPEEDO_MS_ENABLE = 1;
		default:
			break;
	}

	slave_cmd_param = 0;
}
#endif	//SPEEDO

/***************************************************************************
 *																									*
 *	tasks_switch:	This function is called as a result of the monitor    	*
 *					function detecting a positive bit in the monitor switch		*
 *					data structure.  The data structure is set by the 				*
 *					interrupt routine as a result of detecting a key swith		*
 *					movement, or push button switch closure.							*
 *																									*
 ***************************************************************************/
void
tasks_switch()
{

	bits	reg;

#ifndef	SPEEDO
	/* Key Switch Diag Position */
	if (tasks.switches.FPS_KEY_DIAG) {
		tasks.switches.FPS_KEY_DIAG = 0;
		if (!tasks.status.STAT_SYSPWR && !last_key_position.KEY_SW_OFF  &&
				!tasks.fw_logical.FWL_FFSC_PRESENT)
			tasks.fw_logical.FWL_PWR_UP = 1;
		cmdp.cmd_stat.SUP_MODE = 1;
	}
	/* Key Switch On */
	if (tasks.switches.FPS_KEY_ON) {
		tasks.switches.FPS_KEY_ON = 0;
		if (!tasks.status.STAT_SYSPWR  && !last_key_position.KEY_SW_OFF &&
				!tasks.fw_logical.FWL_FFSC_PRESENT)
			tasks.fw_logical.FWL_PWR_UP = 1;
			cmdp.cmd_stat.SUP_MODE = 0;
	}

	/* Key Switch OFF */
	/*
	 * send a message to the Hub if power up and then set a timeout
	 * period to wait before removing power.
	 */
	if (tasks.switches.FPS_KEY_OFF ) {
		tasks.switches.FPS_KEY_OFF = 0;
		cmdp.cmd_stat.SUP_MODE = 0;
		if ( tasks.status.STAT_SYSPWR) {
			dspMsg(MSG_FP_OFF);
			sendHubInt(INT_PD_OFF);
			tasks.fw_logical.FWL_PWR_DN = 1;
		}
	}

	/* store the position of the switch */
#ifdef	_005
	last_key_position = PORTB;
#else
	last_key_position = PORTA;
#endif
	
	ext_ptr_store = INPT2;
	reg = extMemRd();
	
#endif	//SPEEDO
	
	/* Reset Button Closure */
	if (tasks.switches.FPS_RESET) {
		tasks.switches.FPS_RESET = 0;
#ifdef	SPEEDO
		/* only issue an Reset if the ELSC is a master */
		if (tasks.env2.ENV2_SPEEDO_MASTER) 
			issueReset();
#else
		/* Active only when key is in Diag Position */
		if (!reg.DIAG_SW_ON) 
			issueReset();
#endif
	}

	/* NMI Button Closure */
	if (tasks.switches.FPS_NMI) {
		tasks.switches.FPS_NMI = 0;
#ifdef	SPEEDO
		/* only issue an NMI if the ELSC is a master */
		if (tasks.env2.ENV2_SPEEDO_MASTER) 
			issueNMI();
#else
		/* Active only when key is in Diag Position */
		if (!reg.DIAG_SW_ON && (mp_type == MP_LEGO)) 
				issueNMI();
#endif
	}
}

/***************************************************************************
 *																									*
 *	tasks_fw - 	Executes outstanding tasks logical firmware actions			*
 *				The tasks executed are:														*
 *					power up																		*
 *					power down																	*
 *					boot																			*
 *					heart beat																	*
 *																									*
 ***************************************************************************/
void
tasks_fw()
{


	if (tasks.fw_logical.FWL_REMOVE_PWR) {
#ifdef	SPEEDO
		if (tasks.env2.ENV2_SPEEDO_MASTER)
			master_cmd_param = SP_PWR_D;
#endif
		cancel_timeout(POWER_DN_TO);
		power_dn();
		tasks.fw_logical.FWL_REMOVE_PWR = 0;
	}

	if (tasks.fw_logical.FWL_PWR_UP) {
#ifdef	SPEEDO
		if (tasks.env2.ENV2_SPEEDO_MASTER)	
			master_cmd_param = SP_PWR_U;
#endif	//SPEEDO
		
		power_up();
		tasks.fw_logical.FWL_PWR_UP = 0;
	}
	
	else if (tasks.fw_logical.FWL_PWR_DN) {

		if (TCB.power_dn_delay > 0) {
			cancel_timeout(POWER_DN_TO);
			
			/* send an immediate power down */
			tasks.fw_logical.FWL_REMOVE_PWR = 1;
		}
		else {
			/* issue a soft power down */
			to_value = SOFT_PWR_DOWN_DELAY;
			timeout(POWER_DN_TO);
		}
		
		tasks.fw_logical.FWL_PWR_DN = 0;
	}



}

/***************************************************************************
 *																									*
 *	tasks_to - 	handles the timeout queue status when a timeeout period		*
 *				has expired.																	*
 *				The timeout tasks handled are:											*
 *					NMI button debounce timeout											*
 *					RESET button debounce timeout											*
 *					Front Panel Switch debounce timeout									*
 *					heart beat																	*
 *																									*
 ***************************************************************************/
void
tasks_to()
{
	
	bits	reg;


	ext_ptr_store = INPT2;
	reg = extMemRd();
	
	/* if key switch then read key switch position */
	if (TCB.to_status.KEY_TO) {

#ifdef	SPEEDO
		/* if in a power on state, then power down */
		if (!tasks.status.STAT_SYSPWR) 
			tasks.fw_logical.FWL_PWR_UP = 1;
		else {
			sendHubInt(INT_PD_OFF);
			tasks.fw_logical.FWL_PWR_DN = 1;
			speedoLED(AMBER, LED_BLINK);
		}
		
#elif		defined(_005)
		if (!PORTB.KEY_SW_OFF) { 
			tasks.switches.FPS_KEY_OFF = 1;
			reg_state.reg_rb.KEY_SW_OFF = 0;
			reg_state.reg_in2.DIAG_SW_ON = 1;
			cmdp.cmd_stat.SUP_MODE = 0;
		}
		else if (!reg.DIAG_SW_ON) {
			tasks.switches.FPS_KEY_DIAG = 1;
			reg_state.reg_rb.KEY_SW_OFF = 1;
			reg_state.reg_in2.DIAG_SW_ON = 0;
			cmdp.cmd_stat.SUP_MODE = 1;

		}
		else {
			tasks.switches.FPS_KEY_ON = 1;
			reg_state.reg_rb.KEY_SW_OFF = 1;
			reg_state.reg_in2.DIAG_SW_ON = 1;
			cmdp.cmd_stat.SUP_MODE = 0;
		}
#else
		if (!PORTA.KEY_SW_OFF) { 
			tasks.switches.FPS_KEY_OFF = 1;
			reg_state.reg_ra.KEY_SW_OFF = 0;
			reg_state.reg_in2.DIAG_SW_ON = 1;
			cmdp.cmd_stat.SUP_MODE = 0;
		}
		else if (!reg.DIAG_SW_ON) {
			tasks.switches.FPS_KEY_DIAG = 1;
			reg_state.reg_ra.KEY_SW_OFF = 1;
			reg_state.reg_in2.DIAG_SW_ON = 0;
			cmdp.cmd_stat.SUP_MODE = 1;

		}
		else {
			tasks.switches.FPS_KEY_ON = 1;
			reg_state.reg_ra.KEY_SW_OFF = 1;
			reg_state.reg_in2.DIAG_SW_ON = 1;
			cmdp.cmd_stat.SUP_MODE = 0;
		}
#endif

		/* reset the key switch timeout flag */
		TCB.to_status.KEY_TO = 0;

		/* reset the active debounce period flag */
		tasks.switches.FPS_KEY_BOUNCE = 0;
	}

	/* if NMI timeout flag then reset the flag and reset the 
	 * active debounce period.
	 */
	if (TCB.to_status.NMI_TO) {
		TCB.to_status.NMI_TO = 0;
		tasks.switches.FPS_NMI_BOUNCE = 0;
	}

	/* If Reset timeout flag then reset the flag and reset the 
	 * active debounce period.
	 */
	if (TCB.to_status.RESET_TO) {
		TCB.to_status.RESET_TO = 0;
		tasks.switches.FPS_RST_BOUNCE = 0;
	}
	if (TCB.to_status.FAN_TO) {

		TCB.to_status.FAN_TO = 0;
		
		/* enable temperature monitoring if not already enabled
			and check for proper fan speed  */
		if (!tasks.env1.ENV1_TMP_EN) {
			tasks.env1.ENV1_TMP_EN = 1;
			/* Set the Fan Speed */
#ifdef	FAN_FULL_SPEED
			reg_state.reg_out3.FAN_HI_SPEED = 1;
			ext_ptr_store = OUTP3;
			extMemWt(reg_state.reg_out3);
			if (mp_type == MP_KCAR) {
				reg_state.reg_out1.KCAR_HI_FAN_SPEED = 1;
				ext_ptr_store = OUTP1;
				extMemWt(reg_state.reg_out1);
			}

#endif
		}

		
		
#ifdef FAN_CHK
		if (fan_ptr.fan_stat_2.STAT2_FAN_CHK) {
			/* No tach pulse recevied, could be a locked rotor */
			fan_ptr.fan_stat_2.STAT2_FAN_LRTR = 1;
		}
		else
			/* Begin checking for fan pulses */
			next_fan();
#endif
	}

	if (TCB.to_status_1.PWR_UP_TD) {
		TCB.to_status_1.PWR_UP_TD = 0;
		tasks.fw_logical.FWL_PWR_UP = 1;
	}
	
	if (TCB.to_status.POWER_DN_TO) {
		TCB.to_status.POWER_DN_TO = 0;
		tasks.fw_logical.FWL_REMOVE_PWR = 1;
	}
	
	if (TCB.to_status.NMI_EX_TO) {
		TCB.to_status.NMI_EX_TO = 0;
		executeNMI();
	}

	if (TCB.to_status.RST_EX_TO) {
		TCB.to_status.RST_EX_TO = 0;
		executeReset();
	}
	
	if (TCB.to_status_1.HBT_INT) {
		TCB.to_status_1.HBT_INT = 0;
		issueHbtRestart();
	}	
}

