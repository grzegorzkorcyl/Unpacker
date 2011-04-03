#!/usr/bin/perl -w

use threads;
use threads::shared;

my $file   = $ARGV[0];
my $evtNum = $ARGV[1];
my $subId  = $ARGV[2];
my $refCh  = $ARGV[3];
my $endp   = $ARGV[4];


my @threads;

open(DAT, $file);
@data = <DAT>;
close(DAT);

chomp(@data);

my $size = scalar(@data);

for(my $i = 0; $i < $size; $i++) {
	print "Creating thread for $data[$i]\n\n";

	$threads[$i] = threads->create(sub { `root -l -b -q 'process.c("$data[$i]", 1000000, 32768, 95, "1234|ffff")'`});
}

for(my $i = 0; $i < $size; $i++) {
	$threads[$i]->join();
}

print("\n\n -------------- Done ------------ \n\n");