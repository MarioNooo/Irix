/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

/*
 * Frame Scheduler Test
 */

#include "main.h"

extern int errno;

/*
 * This example creates 2 synchronous frame schedulers,
 * each running 1 process at 1Hz.
 */

/*
 * Globally visible reference to master FRS
 * We need it to create the slave frs's.
 */

frs_t* master_frs = 0;
volatile frs_t* slave_frs = 0;
/*
 * Globally visible semaphore to let
 * everybody know when the master FRS has
 * been created.
 */

usema_t* master_frs_created = 0;

/*
 * Barrier to synchronize enqueues, joins, and starts.
 */
barrier_t* all_procs_enqueued = 0;
 

/*
 * Recovery option
 */

volatile  mfbe_rmode_t recovery = MFBERM_NORECOVERY;

/*
 * Management of pdesc_t objects
 */

pdesc_t*
pdesc_create(frs_t* frs, uint messages, int (*action_function)())
{
	pdesc_t* pdesc;
	
	assert(frs != NULL);
	assert(action_function != NULL);

	pdesc = (pdesc_t*)malloc(sizeof(pdesc_t));
	if (pdesc == NULL) {
		perror("[pdesc_create]: malloc");
		exit(1);
	}

	pdesc->frs = frs;
	pdesc->messages = messages;
	pdesc->action_function = action_function;

	return (pdesc);
}

/*
 * Error Signal handlers
 */

void
underrun_error()
{
	if ((int)signal(SIGUSR1, underrun_error) == -1) {
		perror("[underrun_error]: Error while resetting signal");
		exit(1);
	}
	fprintf(stderr, "[underrun_error], PID=%d\n", getpid());	
	exit(2);
}

void
overrun_error()
{
	if ((int)signal(SIGUSR2, overrun_error) == -1) {
		perror("[overrun_error]: Error while resetting signal");
		exit(1);
	}
	fprintf(stderr, "[overrun_error], PID=%d\n", getpid());	
	exit(2);
}

void
termination_signal()
{
	if ((int)signal(SIGHUP, termination_signal) == -1) {
		perror("[termination_signal]: Error while resetting signal");
		exit(1);
	}
	fprintf(stderr, "[termination_signal], PID=%d\n", getpid());	
	exit(8);
}

void
process_skeleton(void* arg)
{
	int previous_minor;
	int rv;
	int pid;
	int cpu;
	pdesc_t* pdesc;
	
	pdesc = (pdesc_t*)arg;
	assert(pdesc != NULL);

	pid = getpid();
	cpu = pdesc->frs->frs_info.cpu;
	
	/*
	 * First, we join the frame scheduler
         * after all procs have been enqueued
	 */

        barrier(all_procs_enqueued, 4);
        
	if (frs_join(pdesc->frs) < 0) {
		fprintf(stderr,
			"[process_skeleton]: Cpu [%d] Process [%d] frs_join failed\n",
			cpu, pid);
		perror("[process_skeleton]");
		exit(1);
	}
    
	if (pdesc->messages & PDESC_MSG_JOIN) {
		fprintf(stderr,
			"[process_skeleton] Cpu [%d] Process [%d]: Joined Frame Scheduler\n",
			cpu, pid);
	}


	/*
	 * This is the real-time loop. The first iteration
	 * is done right after returning from the join
	 */

	rv = 0;
    
	do {
		/*
		 * We call the routine that executes the rt code
		 */

		rv = (*pdesc->action_function)();
		
		/*
		 * After we are done with our computations, we
		 * yield the cpu. THe yield call will not return until
		 * it's our turn to execute again.
		 */

		if ((previous_minor = frs_yield()) < 0) {
			fprintf(stderr,
				"[process_skeleton]: Cpu [%d] Process [%d] frs_yield failed\n",
				cpu, pid);
			perror("[process_skeleton]");
			exit(1);
		}

		if (pdesc->messages & PDESC_MSG_YIELD) {
			fprintf(stderr,
				"[process_skeleton] Cpu [%d] Proc [%d]: Ret from Yield; pm: %d\n",
				cpu, pid, previous_minor);
		}
		
	} while (!rv);

	fprintf(stderr,
		"[process_skeleton]: Cpu [%d] Process [%d]: Exiting\n",
		cpu, pid);

	exit(0);
}
 


void
setup_signals()
{
	if ((int)signal(SIGUSR1, underrun_error) == -1) {
		perror("[setup_signals]: Error while setting underrun_error signal");
		exit(1);
	}

	if ((int)signal(SIGUSR2, overrun_error) == -1) {
		perror("[setup_signals]: Error while setting overrun_error signal");
		exit(1);
	}
	if ((int)signal(SIGHUP, termination_signal) == -1) {
		perror("[setup_signals]: Error while setting termination signal");
		exit(1);
	}
}

void
process_for_master_frs(void* arg)
{
	frs_t* frs;
	pdesc_t* pdesc;
	int pid;
	int minor;
	int wstatus;
	frs_attr_info_t attr_info;
	frs_recv_info_t recv_info;
	
	/*
	 * Create the master frame scheduler
	 * cpu = 1
	 * interrupt source = CCTIMER
	 * number of minors = 1
	 * slaves = cpu2
	 * number_of_slaves = 1
	 * period (intr_qualifier) = 1000 [ms] == 1000000 [microseconds]
	 */


	if ((frs = frs_create_master(1, FRS_INTRSOURCE_CCTIMER, 1000000, 1, 1)) == NULL) {
		perror("[main]: frs_create_master failed");
		exit(1);
	}

	/*
	 * Set the recovery attribute
	 */

        switch (recovery) {
            case MFBERM_NORECOVERY:
                    break;
            case MFBERM_INJECTFRAME:
            {
                    recv_info.rmode = MFBERM_INJECTFRAME; 
                    recv_info.tmode = EFT_FIXED;
                    recv_info.maxcerr = 0;
                    recv_info.xtime = 0;

                    if (frs_setattr(frs, 0, 0, FRS_ATTR_RECOVERY,  &recv_info) < 0) {
                            perror("[main]: frs_setattr failed");
                            fprintf(stderr, "errno=%d\n", errno);
                            exit(1);
                    }
            }
            break;
            case MFBERM_EXTENDFRAME_STRETCH:
            {
                    recv_info.rmode = MFBERM_EXTENDFRAME_STRETCH;
                    recv_info.tmode = EFT_FIXED;
                    recv_info.maxcerr = 0;
                    recv_info.xtime = 10000;

                    if (frs_setattr(frs, 0, 0, FRS_ATTR_RECOVERY,  &recv_info) < 0) {
                            perror("[main]: frs_setattr failed");
                            fprintf(stderr, "errno=%d\n", errno);
                            exit(1);
                    }
            }
            break;
            case MFBERM_EXTENDFRAME_STEAL:
            {
                    recv_info.rmode = MFBERM_EXTENDFRAME_STEAL;
                    recv_info.tmode = EFT_FIXED;
                    recv_info.maxcerr = 0;
                    recv_info.xtime = 10000;

                    if (frs_setattr(frs, 0, 0, FRS_ATTR_RECOVERY,  &recv_info) < 0) {
                            perror("[main]: frs_setattr failed");
                            fprintf(stderr, "errno=%d\n", errno);
                            exit(1);
                    }
            }
            break;
            default:
                    fprintf(stderr, "Invalid recovery mode\n");
                    exit(1);
	}
        
	/*
	 * Signal the main process that the
	 * master frs has been created
	 */
	assert(master_frs_created != 0);
	master_frs = frs;
	sema_v(master_frs_created);

	/*
	 * Process A
	 * frs: 0 (on cpu 1)
	 * freq: 1 Hz
	 */

	pdesc = pdesc_create(frs, PDESC_MSG_JOIN | PDESC_MSG_YIELD, processA_loop);
	pid = sproc(process_skeleton, PR_SALL, (void*)pdesc);
	if (pid == -1) {
		perror("[sproc] processA");
		exit(1);
	}

	minor = 0;
	if (frs_enqueue(frs, pid, minor, FRS_DISC_RT) < 0) {
		perror("[frs_enqueue]: processA");
		exit(1);
	}

        barrier(all_procs_enqueued, 4);
        
	/*
	 * We now start this Frame Scheduler
	 */
	
	if (frs_start(frs) < 0) {
		fprintf(stderr, "[frs_start]: Cpu: [%d] MasterProcess: [%d]\n",
			frs->frs_info.cpu, getpid());
		perror("[frs_start]");
		exit(1);
	}


	
       /*
	* Wait for the  process to finish
	* The actual exit will happen from the
	* termination signal handler.
	*/
	wait(&wstatus);

	exit(0);
}


void
process_for_first_slave_frs(void* mfrs_arg)
{
	frs_t* frs;
	pdesc_t* pdesc;
	int pid;
	int minor;
	int subminor;
	int wstatus;

	/*
	 * Create first slave
	 * cpu = 2
	 * interrupt source = CCTIMER
	 * number of minors = 1
	 * slaves = --
	 * number_of_slaves = --
	 * period (intr_qualifier) = 1000 [ms] == 1000000 [microseconds]
	 */

	if ((frs = frs_create_slave(2, (frs_t*)mfrs_arg)) == NULL) {
		perror("[main]: frs_create_slave on cpu 2 failed");
		exit(1);
	}

        slave_frs = frs;
        
	/*
	 * Process B
	 * frs: 1 (on cpu 2)
	 * freq: 1 Hz
	 */

	pdesc = pdesc_create(frs, PDESC_MSG_JOIN | PDESC_MSG_YIELD, processB_loop);
	pid = sproc(process_skeleton, PR_SALL, (void*)pdesc);
	if (pid == -1) {
		perror("[sproc] processB");
		exit(1);
	}

	minor = 0;
	if (frs_enqueue(frs, pid, minor, FRS_DISC_RT) < 0) {
		perror("[frs_enqueue]: processB");
		exit(1);
	}

        barrier(all_procs_enqueued, 4);
        
	/*
	 * We now start this Frame Scheduler
	 */
	
	if (frs_start(frs) < 0) {
		fprintf(stderr, "[frs_start]: Cpu: [%d] MasterProcess: [%d]\n",
			frs->frs_info.cpu, getpid());
		perror("[frs_start]");
		exit(1);
	}


	/*
	 * Wait for the three processes to finish
	 * The actual exit will happen from the
	 * termination signal handler.
	 */
	wait(&wstatus);
	exit(0);
}

main(int argc, char** argv)
{
	int rv;
	int wstatus;
	frs_t master_frs1;
        int errflag = 0;
        int c;
        char* command = argv[0];
	
	printf("Running Frame Scheduler on Processors 1, 2...\n");

        while ((c = getopt(argc, argv, "pxs")) != EOF) {
                switch (c) {
                    case 'p':
                            recovery = MFBERM_INJECTFRAME;
                            break;
                    case 'x':
                            recovery = MFBERM_EXTENDFRAME_STRETCH;
                            break;
                    case 's':
                            recovery = MFBERM_EXTENDFRAME_STEAL;
                            break;
                    case '?':
                            errflag++;
                }
        }

        if (errflag) {
                (void)fprintf(stderr, "usage: %s [-pxs]\n", command);
                exit(1);
        }

       
	/*
	 * Initialization of semaphores
	 */

	sema_init();
	master_frs_created = sema_create();
        all_procs_enqueued = barrier_create();
	
	/*
	 * Initialize signals to catch
	 * termination signals and underrun, overrun errors.
	 */
	
	setup_signals();
	

	/*
	 * Create the master processes that will
	 * create the frame schedulers
	 */

	rv = sproc(process_for_master_frs, PR_SALL, NULL);
	if (rv == -1) {
		perror("[sproc]-master_frs");
		exit(1);
	}

	/*
	 * Wait for the master FRs to be created
	 */

	sema_p(master_frs_created);
	assert(master_frs != 0);

	printf("The master has been created\n");

	master_frs1 = *master_frs;
	
	/*
	 * The master has been created,
	 * we can proceed to create the slaves
	 */
	
	rv = sproc(process_for_first_slave_frs, PR_SALL, (void*)&master_frs1);
	if (rv == -1) {
		perror("[sproc]-first_slave_frs");
		exit(1);
	}

	
	/*
	 * Wait for each of the master processes
	 */

	wait(&wstatus);
	wait(&wstatus);
        
	sema_destroy();
        
	exit(0);
}

	













