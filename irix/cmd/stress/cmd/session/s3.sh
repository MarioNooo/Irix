#!/bin/ksh

npp=5		# -n number to do in parallel
ldir=/usr/tmp	# -d local directory to use
verbose=	# -v
cmdloc=.	# -c helper command locations
slp=0		# -s amount of type to 'idle'

while getopts c:vn:d:s: c
do
	case $c in
	n)	npp=$OPTARG;;
	d)	ldir=$OPTARG;;
	v)	verbose=1;;
	c)	cmdloc=$OPTARG;;
	s)	slp=$OPTARG;;
	esac
done
shift `expr $OPTIND - 1`
if [ "$ldir" != "" -a ! -d "$ldir" ]
then
	umask 0
	mkdir $ldir
	umask 022
fi

TMPDIR=$ldir
export TMPDIR
date
cd $ldir

while [ $npp -gt 0 ]
do
	(
	tf=tmu$$.$npp
	cat >$tf.c <<!
	main()
	{
	printf("hellow\n");
	}
!
	make $tf
	./$tf
	elfdump -h $tf
	rm -f $tf $tf.c
	)&
	npp=`expr $npp - 1`
done

wait
if [ $slp -gt 0 ]
then
	sleep $slp
fi

exit
