#!/usr/sbin/perl

#This test script test the following scenerios
#	1. Simply retrieve the rpc entries for a given protocol name
#	   following command would repeat the test 100 times
#		./getrpcbyname.pl -repeat 100 -rpcname <comma_separated_rpc_names>
#
#	2. Change the timestamp of the /etc/rpc file so that it
#	   will cause the cache to be rebuild.
#		./getrpcbyname.pl -touch -repeat 100 -rpcname <comma_separated_rpc_names>
#
#	3. Add entries in the /etc/rpc file.This will cause the cache
#	   to be rebuild.Following test will add entries a,b,c in the /etc/rpc#	   file and repeat the test for 100 times
#	 	./getrpcbyname.pl -add <comma_separated_rpc_names> -repeat 100 -rpcname <comma_separated_rpc_names>
#
#	4. Stop the nsd, add new entries and retrive the information.
#		./getrpcbyname.pl -add <comma_separated_rpc_names> -stopnsd -repeat 100 -rpcname <comma_separated_rpc_names>
#
#	5. Wait for timeout and then retrieve the information, this will
#	   cause cache to be rebuild
#		./getrpcbyname.pl -wait <time_val_in_seconds> -repeat 100 -rpcname <comma_separated_rpc_names>
#
#	6.Add an arbitrary entry in the /etc/rpc file and look for it
#		./getrpcbyname.pl -entry <a_rpc_entry> -rpcname <rpc_name>

$repeatCount = 1;
$touchflg = 0;
$addflg = 0;
$stopnsdflg = 0;
$rpcnameFlg = 0;
$entryFlg = 0;
$waitForSecond = 0;
$prevUser = 0.0;
$prevSystem = 0.0;
$precCuser = 0.0;
$prevCsystem = 0.0;

@options = @ARGV;

while(@ARGV) {
  $_ = shift;
  if(/^-repeat(.*)/) {
	$repeatCount = shift(@ARGV);
  } elsif(/^-touch(.*)/) {
	$touchflg = 1;
  } elsif(/^-add(.*)/) {
	@names_to_add = split(/,/, shift(@ARGV));
	$addflg = 1;
  } elsif (/^-stopnsd(.*)/) {
	$stopnsdflg = 1;
  } elsif (/^-rpcname(.*)/) {
	@list_of_rpcnames = split(/,/, shift(@ARGV));
	$rpcnameFlg = 1;
  } elsif (/^-entry(.*)/) {
	$entry_to_add = shift(@ARGV);
	$entryFlg = 1;
  } elsif(/^-wait(.*)/) {
	$waitForSecond = shift(@ARGV);
  } else {
	print "Unknown options, exiting\n";
	&print_usage();
  }
  
}

if(!$rpcnameFlg) {
	&print_usage();
}


open(SAVEOUT, ">&STDOUT");
open(SAVEERR, ">&STDERR");

open(STDERR, ">&STDOUT") || die "Can't dup stdout";

select(STDOUT); $| = 1;       # make unbuffered
select(STDERR); $| = 1;       # make unbuffered

print "Start Script:getrpcbyname.pl\n";
print "####CMD: ./getrpcbyname.pl ", join(' ', @options), "\n";

($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
#print "Date:/$mon/$mday/$year  ", "Time:$hour:$min:$sec\n";

for($i=0; $i < $repeatCount ; $i++) {
	print STDOUT "==================getrpcbyname() - Begin :", $i,"=============\n";
	if($touchflg ) {
	   #change the timestap of the /etc/rpc file
	   #this will cause the cache to be rebuild
	   system "/sbin/touch /etc/rpc";
	}
	if($addflg ) {
	   system "/sbin/cp /etc/rpc /etc/rpc.old";
	   $rpc_num = 80000;

	   #Add the new entries in the /etc/rpc file
	   #this will cause the cache to be rebuild
	   open(ETC_RPC, ">> /etc/rpc");
	   @l_names_to_add = @names_to_add;
	   while(<@l_names_to_add>) {
		$rname = shift(@l_names_to_add);
		print ETC_RPC $rname, "\t\t$rpc_num", "\t$rname-alias", "\n";
	   }
	   close ETC_RPC;
	}
	elsif($entryFlg) {
	   system "/sbin/cp /etc/rpc /etc/rpc.old";
	   open(ETC_RPC, ">> /etc/rpc");
	   print ETC_RPC $entry_to_add;
	   close ETC_RPC;
	}
	
	#Wait for cache to timeout
	if($waitForSecond) {
	    sleep $waitForSecond;
	}

	if($stopnsdflg) {
	    system "/sbin/killall  -TERM nsd";
  	}
	
	##Call the unit test 
	print  "./getrpcbyname ", join(' ', @list_of_rpcnames), "\n";
        system "./getrpcbyname @list_of_rpcnames";

	print  "./getrpcbyname_r ", join(' ', @list_of_rpcnames), "\n";
        system "./getrpcbyname_r @list_of_rpcnames";

	#Get the cpu and system time to execute the test till now
        ($user,$system,$cuser,$csystem) = times;

	#Revert back to the original state, here assumption is that
	#stopnsd oprtion is being used when nsd was running
	if($addflg || $entryFlg) {
	   system "/sbin/cp /etc/rpc.old /etc/rpc";
	   unlink("/etc/rpc.old");
	}
	if($stopnsdflg) {
		system "/usr/etc/nsd `cat /etc/config/nsd.options`";
	}
	$luser = $user - $prevUser;
	$lsystem = $system - $prevSystem;
	$lcuser = $cuser - $prevCuser;
	$lcsystem = $csystem - $prevCsystem;	
#        print STDOUT "Time - user = $luser, system = $lsystem, cuser = $lcuser, csystem = $lcsystem\n";
	$prevUser = $user;
	$prevSystem = $system;
	$prevCuser = $cuser;
	$prevCsystem = $csystem;
	print STDOUT "==================getrpcbyname() - End :", $i,"===============\n";
}
close(STDOUT);
close(STDERR);
open(STDOUT, ">&SAVEOUT");
open(STDERR, ">&SAVEERR");
exit(0);


############ subs ##########
sub print_usage()
{
	print "Usage: ./getrpcbyname.pl \n\t[-add <comma_separated_rpc_names>] \n\t[-touch] \n\t[-stopnsd]\n\t[-entry <entry_to_add>]\n\t[-wait <wait_for_seconds>]\n\t[-repeat <n_times>]\n\t-rpcname <comma_separated_rpc_names>\n";
	exit(-1);
}
