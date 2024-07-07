#include "gl.h"
#include "stdio.h"
#include "signal.h"

extern int getopt(), optind;
extern char *optarg;
int x = -1;
int y = -1;
int runtime = -1;
int quit = 0;

static void
sigalarm(sig)
int sig;
{
	quit = 1;
}

main(argc, argv)
int argc;
char **argv;
{
	int i;
	int c;

	while ((c = getopt(argc, argv, "t:x:y:")) != EOF) {
		switch (c) {
		case 't':
			runtime = atoi(optarg);
			break;
		case 'x':
			x = atoi(optarg);
			break;
		case 'y':
			y = atoi(optarg);
			break;
		default:
			printf("invalid option %c\n", c);
			exit(1);
		}
	} 

	if (x > 0 && y > 0)
		prefposition(x, x+99, y, y+49);
	else
		prefsize(100,50);
	foreground();
#if _MIPS_SIM == _MIPS_SIM_NABI32
	winopen("N32 rgbmode");
#else
	winopen("rgbmode");
#endif
	RGBmode();

	if (runtime > 0) {
		sigset(SIGALRM, sigalarm);
		alarm(runtime);
	}

	while (!quit) {
	
		singlebuffer();
		gconfig();

		for (i = 0; i < 4; i++) {
			RGBcolor(255,0,0);
			clear();
			sginap(50);
			RGBcolor(0,255,0);
			clear();
			sginap(50);
		}

		doublebuffer();
		gconfig();

		for (i = 0; i < 4; i++) {
			RGBcolor(0,0,255);
			clear();
			swapbuffers();
			sginap(50);
			RGBcolor(255,255,0);
			clear();
			swapbuffers();
			sginap(50);
		}
	}

	exit(0);
}
