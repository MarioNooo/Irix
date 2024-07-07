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

		/* Check on Polled Inputs */
		if ((PORTA ^ reg_state.reg_ra) & INPUT_MASK_PA)
			inputPortA();
			
		/* Check on Polled Inputs */
		if ((PORTB ^ reg_state.reg_rb) & INPUT_MASK_PB)
			inputPortB();

		t_reg = extMemRd();
		
		if (t_reg ^ reg_state.pwr_add)
			inputPwr();
			
		if (tasks.fw_logical != 0)
			tasks_fw();
			
		if ((fan_ptr.fan_stat_2.STAT2_CNT_CHK == 1) || fan_ptr.fan_stat_2.STAT2_FAN_LRTR)
			tasks_fan();

		/* check for expired time out conditions */
		if (TCB.to_status || TCB.to_status_1) 
			tasks_to();
	}
}


/***************************************************************************
 *																									*
 *	inputPortA - 	Handles monitor inputs from Port A for the following 		*
 *						signals:																	*
 *							PSOK																	*
 *																									*
 ***************************************************************************/
void
inputPortA()
{
	t_reg = PORTA;

	/* Power Supply Failure */
	if (((t_reg ^ reg_state.reg_ra) & PSOK_MASK) && !t_reg.PSOK && !reg_state.reg_ra.PWRON_L) {

		/* let's wait for 10 msec and sample again, to avoid any glitches */
		to_value = MSEC_10;
		delay();
		t_reg = PORTA;

		if(!t_reg.PSOK) {
			tasks.fw_logical.FWL_PWR_DN = 1;
			NoPower = 1;

			cntLED(FP_LED, LED_RED|LED_BLINK);
			
			to_value = TWO_SEC;
			delay();

		}
	}
	reg_state.reg_ra.PSOK = t_reg.PSOK;
	
}

/***************************************************************************
 *																									*
 *	inputPortB - 	Handles monitor inputs from Port B for the following 		*
 *						signals:																	*
 *							Over Temperture													*
 *							High Temperature													*
 *							MFG_MODE																*
 *							POWER UP/DOWN														*
 *																									*
 *																									*
 ***************************************************************************/
void
inputPortB()
{
	bits	t_reg;
	
	t_reg = PORTB;
	
	/* Manufacturing Mode */
	mfg_mode = t_reg.MFG_MODE_L ? 0 : 1;
	reg_state.reg_rb.MFG_MODE_L = t_reg.MFG_MODE_L;
	
	/* XBOX Over Temperature */
	if (!t_reg.TEMP_OVER_L && reg_state.reg_rb.TEMP_OVER_L && tasks.env.ENV_TMP_EN) {
		
		/* let's wait for 10 msec and sample again, to avoid any glitches */
		to_value = MSEC_10;
		delay();
		t_reg = PORTB;

		if(!t_reg.TEMP_OVER_L) {
			/* turn on RED LED */
			cntLED(FP_LED, LED_BLINK|LED_RED);
			
			/* update the status register */
			reg_state.reg_xbox_status.OVER_TEMP = 1;
			extMemWt(STATUS_REG);

			/* update the register copy of the port */
			reg_state.reg_rb.TEMP_OVER_L = 0;

			if (!mfg_mode)
				tasks.fw_logical.FWL_SFT_PWR_DN = 1;

		}
	}

	/* XBOX Temperature Normal (Not an over temperature condition) */
	else if(t_reg.TEMP_OVER_L && !reg_state.reg_rb.TEMP_OVER_L) {
		/* update the status register */
		reg_state.reg_xbox_status.OVER_TEMP = 0;
		extMemWt(STATUS_REG);

		/* update the register copy of the port */
		reg_state.reg_rb.TEMP_OVER_L = 1;
	}

	/* Check for power up */
	if (!tasks.status.STAT_SYSPWR && !NoPower && (t_reg.X9_RMTOK || t_reg.XA_RMTOK)) { 
		tasks.fw_logical.FWL_PWR_UP = 1;
		reg_state.reg_rb.X9_RMTOK = t_reg.X9_RMTOK;
		reg_state.reg_rb.XA_RMTOK = t_reg.XA_RMTOK;		
	}

	/* Check for power down */
	if (!t_reg.X9_RMTOK && !t_reg.XA_RMTOK) {
		if (tasks.status.STAT_SYSPWR) {
			/* power is applied then do a shutdown */
			tasks.fw_logical.FWL_PWR_DN = 1;
			reg_state.reg_rb.X9_RMTOK = 0;
			reg_state.reg_rb.XA_RMTOK = 0;
		}
		/* always reset the NoPower Flag */
		NoPower = 0;
	}

#if 0
	/* High temperature is not used, but the reg. copy has to be updated */
	reg_state.reg_rb.TEMP_UNDER_L = t_reg.TEMP_UNDER_L;
#endif
}
		

/***************************************************************************
 *																									*
 *	inputPwr - 	Handles monitor inputs from the PAL for POK					 	*
 *																									*
 ***************************************************************************/
void
inputPwr()
{
	/* Check for a Power Ok error flag */
	if (!t_reg.SC_LPOK && reg_state.reg_pwr_add.SC_LPOK) {

		/* Read it again to avoid any glitches */
		t_reg = extMemRd();

		if(!t_reg.SC_LPOK) {
			cntLED(FP_LED, LED_RED);
			tasks.fw_logical.FWL_PWR_DN = 1;
			NoPower = 1;
			reg_state.reg_pwr_add = t_reg;
		}
	}
}

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

	if (fan_ptr.fan_add == 2)
		pulse_cnt = PCI_FAN_HI_CNT;
	else
		pulse_cnt = X_FAN_HI_CNT;


	/* Reset Monitor Flag */
	fan_ptr.fan_stat_2.STAT2_CNT_CHK = 0;


	/* check for out of tolerance conditions */
	// A fan failure is any fan operating below the lower tolerance.
	
	if (fan_ptr.fan_stat_2.STAT2_FAN_LRTR) {
		/* adjust the multiplexer now to avoid unstable address lines, the lines
		 * are also adjusted in the interrupt capture routine.
		 */

		if (!tasks.env.ENV_FAN_RUNNING)
			fan_ptr.fan_retry = FAN_MAX_RETRY;
		fan_fail();
	}
		
	else if ((char)fan_ptr.fan_period > (char) pulse_cnt)
		fan_fail();

	else {
		fan_ptr.fan_retry = 0;

		/*
		 * before addressing the next fan, make sure the current
		 * fan is marked as good
		 */
		 if (fan_ptr.fan_add == 0)
		 	fan_ptr.fan_stat_1.STAT1_FAN_0 = 0;
		 else if (fan_ptr.fan_add == 1)
		 	fan_ptr.fan_stat_1.STAT1_FAN_1 = 0;
		 else if (fan_ptr.fan_add == 2)
		 	fan_ptr.fan_stat_1.STAT1_FAN_2 = 0;
		 
		next_fan();
	}
}

/***************************************************************************
 *																									*
 *	tasks_fw - 	Executes outstanding tasks logical firmware actions			*
 *				The tasks executed are:														*
 *					power up																		*
 *					power down																	*
 *																									*
 ***************************************************************************/
void
tasks_fw()
{


	if (tasks.fw_logical.FWL_PWR_UP) {
		power_up();
		tasks.fw_logical.FWL_PWR_UP = 0;
	}
	
	else if (tasks.fw_logical.FWL_PWR_DN) {
		shutdown_pending = 1;
		power_dn();
		tasks.fw_logical.FWL_PWR_DN = 0;
	}

	else if (tasks.fw_logical.FWL_SFT_PWR_DN) {
		shutdown_pending = 1;
		to_value = SOFT_PWR_DN_DELAY;
		timeout(PWR_DOWN_TO);
		tasks.fw_logical.FWL_SFT_PWR_DN = 0;
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

	if (TCB.to_status.FAN_TO) {

		TCB.to_status.FAN_TO = 0;
		
		/* enable temperature monitoring  */
			tasks.env.ENV_TMP_EN = 1;
		
		/* only check the fans if the manufacturing mode jumper is not installed */
		if (!mfg_mode) {
			if (fan_ptr.fan_stat_2.STAT2_FAN_CHK) {
				/* No tach pulse recevied, could be a locked rotor */
				fan_ptr.fan_stat_2.STAT2_FAN_LRTR = 1;
			}
			else 
				/* Begin checking for fan pulses */
				next_fan();
		}
	}
	if (TCB.to_status.PWR_DOWN_TO) {
		/*
		 * The soft power down timeout has expired, therefore we must shut the XBOX down
		 * without waiting any longer for the CPU to signal a timeout
		 */
		TCB.to_status.PWR_DOWN_TO = 0;
		tasks.fw_logical.FWL_PWR_DN = 1;
		NoPower = 1;
	}
}


