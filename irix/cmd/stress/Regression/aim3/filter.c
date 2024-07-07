/*
 * AIM Suite III v3.1.1
 * (C) Copyright AIM Technology Inc. 1986,87,88,89,90,91,92.
 * All Rights Reserved.
 */


#ifndef	lint
	static char sccs_id[] = { " @(#) filter.c:3.2 5/30/92 20:18:37" };
#endif


#include <stdio.h>
#define BSIZ 132

/*
**  filter simply reads data generated by multiuser in "toutput", and
**  reformats it to be read by plot.  Filter is called by the shell
**  script REPT
*/

main(argc,argv)
int argc;
char **argv;
{

	FILE *fp1,*fp2;
	char *label = "123456789abcdefghijklmnopqrstuvwxyz";
	char tmpstr[BSIZ];
	int mnum;
	int doit,i;
	char mnums[3];
	float ctrl, real, cpu;

	fp1 = fopen("toutput","r");
	fp2 = fopen("tinput","w");

	    mnum = 0;
	    while (fgets(tmpstr,BSIZ,fp1) != NULL) {
	       if (tmpstr[0] == ':') {
	            /* skip machine label */
		    ++mnum;
		    continue;
	       }
		/* if selecting machines */
		if (argc > 1) {
		    doit = 0;
		    for (i=1;i<argc;i++) {
		    	if (label[mnum-1] == *argv[i])
			    doit = 1;
		    }
		    if ( doit == 0)
			continue;
		}
		sscanf(tmpstr,"%*d %f %*s %*f %*s %f %*s %f%*s",&ctrl,&real,&cpu);
		if ((ctrl<0) || (real<0) || (cpu<0)) {
			fputc('(',fp2);
			fputc(' ',fp2);
		}
	        sprintf(mnums,"%d ",mnum);
		fputs(mnums,fp2);
	        fputs(tmpstr,fp2);
	   }
	   fclose(fp1);
	   fclose(fp2);
}