#!/usr/bin/perl -w

use threads;
use threads::shared;

my $file   = $ARGV[0];
my $evtNum = $ARGV[1];
my $subId  = $ARGV[2];
my $refCh  = $ARGV[3];
my $endp   = $ARGV[4];
my $minWin = $ARGV[5];
my $maxWin = $ARGV[6];


my @threads;

open(DAT, $file);
@data = <DAT>;
close(DAT);

chomp(@data);

my $size = scalar(@data);

for(my $i = 0; $i < $size; $i++) {
	print "Creating thread for $data[$i]\n\n";

	if (!defined $minWin || !defined $maxWin) {
		$threads[$i] = threads->create(sub { `root -l -b -q 'process.c("$data[$i]", $evtNum, "$subId", $refCh, "$endp", -100000, -100000)'`});
	}
	else {
		$threads[$i] = threads->create(sub { `root -l -b -q 'process.c("$data[$i]", $evtNum, "$subId", $refCh, "$endp", $minWin, $maxWin)'`});
	}
}

for(my $i = 0; $i < $size; $i++) {
	$threads[$i]->join();
}

print("\n\n -------------- Done ------------ \n\n");
