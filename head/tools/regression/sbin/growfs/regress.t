#! /usr/bin/perl
#
# $FreeBSD: soc2013/dpl/head/tools/regression/sbin/growfs/regress.t 212882 2010-09-19 08:18:56Z brian $

use strict;
use warnings;
use Test::More tests => 19;
use Fcntl qw(:DEFAULT :seek);

use constant BLK => 512;
use constant BLKS_PER_MB => 2048;

my $unit;
END { system "mdconfig -du$unit" if defined $unit };

sub setsize {
    my ($partszMB, $unitszMB) = @_;

    open my $fd, "|-", "disklabel -R md$unit /dev/stdin" or die;
    print $fd "a: ", ($partszMB * BLKS_PER_MB), " 0 4.2BSD 1024 8192\n";
    print $fd "c: ", ($unitszMB * BLKS_PER_MB), " 0 unused 0 0\n";
    close $fd;
}

sub fill {
    my ($start, $size, $content) = @_;

    my $content512 = $content x (int(512 / length $content) + 1);
    substr($content512, 512) = "";
    sysopen my $fd, "/dev/md$unit", O_RDWR or die "/dev/md$unit: $!";
    seek($fd, $start * BLK, SEEK_SET);
    while ($size) {
	syswrite($fd, $content512) == 512 or die "write: $!";
	$size--;
    }
}

SKIP: {
    skip "Cannot test without UID 0", 19 if $<;

    chomp(my $md = `mdconfig -s40m`);
    like($md, qr/^md\d+$/, "Created $md with size 40m") or die;
    $unit = substr $md, 2;

    for my $type (1..2) {

	initialise: {
	    ok(setsize(10, 40), "Sized ${md}a to 10m");
	    system "newfs -O $type -U ${md}a >/dev/null";
	    is($?, 0, "Initialised the filesystem on ${md}a as UFS$type");
	    chomp(my @out = `fsck -tufs -y ${md}a`);
	    ok(!grep(/MODIFIED/, @out), "fsck says ${md}a is clean, " .
		scalar(@out) . " lines of output");
	}

	extend20_zeroed: {
	    ok(setsize(20, 40), "Sized ${md}a to 20m");
	    diag "Filling the extent with zeros";
	    fill(10 * BLKS_PER_MB, 10 * BLKS_PER_MB, chr(0));
	    my $out = `growfs -y ${md}a`;
	    is($?, 0, "Extended the filesystem on ${md}a") or print $out;

	    my ($unallocated) = $out =~ m{\d+ sectors cannot be allocated};
	    fill(30 * BLKS_PER_MB - $unallocated, $unallocated, chr(0))
		if $unallocated;

	    chomp(my @out = `fsck -tufs -y ${md}a`);
	    ok(!grep(/MODIFIED/, @out), "fsck says ${md}a is clean, " .
		scalar(@out) . " lines of output");
	}

	extend30_garbaged: {
	    ok(setsize(30, 40), "Sized ${md}a to 30m");
	    diag "Filling the extent with garbage";
	    fill(20 * BLKS_PER_MB, 10 * BLKS_PER_MB, chr(0xaa) . chr(0x55));
	    my $out = `growfs -y ${md}a`;
	    is($?, 0, "Extended the filesystem on ${md}a") or print $out;

	    my ($unallocated) = $out =~ m{\d+ sectors cannot be allocated};
	    fill(30 * BLKS_PER_MB - $unallocated, $unallocated, chr(0))
		if $unallocated;

	    chomp(my @out = `fsck -tufs -y ${md}a`);
	    ok(!grep(/MODIFIED/, @out), "fsck says ${md}a is clean, " .
		scalar(@out) . " lines of output");
	}
    }

    system "mdconfig -du$unit";
    undef $unit;
}
