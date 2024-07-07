#ident "$Revision: 1.2 $"

static char *indigo2[] = {
	"w| w| w| w|  w| w| w| w|  w| w| w| w|",
	"o| o| o| o|  o| o| o| o|  o| o| o| o|",
	"r| r| r| r|  r| r| r| r|  r| r| r| r|",
	"d| d| d| d|  d| d| d| d|  d| d| d| d|",
	" |  |  |  |   |  |  |  |   |  |  |  |",
	"3| 2| 1| 0|  3| 2| 1| 0|  3| 2| 1| 0|",
	" |  |  |  |   |  |  |  |   |  |  |  |",
	" |  |  |  |   |  |  |  |   |  |  |  |",
	"S1  2  3  4   5  6  7  8   9  10 11 12",
	" Bank 2       Bank 1       Bank 0",
	"",
	"",
	"====================================================",
	"              EISA/GIO backplane",
	"",
	"",
	"",
	"",
	"",
	"",
	0
};

static char *indy[] = {
	"",
	"  -------------------- S8  word 3",
	"  -------------------- S7  word 2  Bank",
	"  -------------------- S6  word 1   1",
	"  -------------------- S5  word 0",
	"",
	"  -------------------- S4  word 3",
	"  -------------------- S3  word 2  Bank",
	"  -------------------- S2  word 1   0",
	"  -------------------- S1  word 0",
	"",
	"====================================================",
	"|                   Power Supply                   |",
	"",
	0
};
static char *mh[] = {
	"====================================================",
	"|   Sim 8 -----------------------------------------|",
	"|   Sim 7 -----------------------------------------|",
	"|   Sim 6 -----------------------------------------|",
	"|   Sim 5 -----------------------------------------|",
	"|   Sim 4 -----------------------------------------|",
	"|   Sim 3 -----------------------------------------|",
	"|   Sim 2 -----------------------------------------|",
	"|   Sim 1 -----------------------------------------|",
	"|                                                  |",
	"|                   System Board                   |",
	"|                                                  |",
	"|                                                  |",
	"|                             |--------------------|",
	"|                             |     CPU Card       |",
	"",
	0
};

int
print_memory_diagram(void)
{
	char **p, *bd =
	   "+------------------------------------------------------------+\n";

#ifndef IP32
	p = is_fullhouse() ? indigo2 : indy;
#else /* !IP32 */
	p = mh;
#endif /* !IP32 */

	printf(bd);

	while(*p)
		printf("|    %-52s    |\n", *p++);

	printf(bd);
}