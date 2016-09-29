#! /usr/bin/perl
use POSIX;

my($top) = 0;
my(%good_codes);
foreach my $arg (@ARGV) {
    if ($arg =~ /^\d+$/) {
        $top = $arg;
    } elsif ($arg =~ /^\w+$/) {
        $good_codes{$arg} = 1;
    } else {
        print STDERR "Usage: ./plot.pl [CODE...] [TOPSIZE] < experiment.dat\n";
        exit 1;
    }
}

open(STDIN, "<", "experiment.dat") if -t STDIN;
my($out_is_terminal) = -t STDOUT;
open(STDOUT, "|gnuplot > results.png") if $out_is_terminal;

my(@codes, %codes, @sizes, %sizes, %stats, $low);
while (<STDIN>) {
    my($code, $size, $mean, $min, $max) = split;
    if ($code) {
        next if %good_codes && !exists($good_codes{$code});
        push @codes, $code if !exists($codes{$code});
        push @sizes, $size if !exists($sizes{$size});
        $codes{$code} = $sizes{$size} = 1;
        $stats{$code} = {} if !exists($stats{$code});
        $stats{$code}->{$size} = [$mean, $min, $max];
        $low = $min if !defined($low) || $min < $low;
    }
}

if (!@codes || !@sizes) {
    print STDERR "./plot.pl: Nothing to plot\n";
    exit 1;
}

$top = $sizes[@sizes - 1] if !$top;
$low = 10 ** POSIX::floor(log($low) / log(10));
$low = 0.01 if $low > 0.01;

print "set terminal png
set logscale x
set logscale y
set bars small
set key center left Left reverse
set yrange [$low:]
set xlabel 'N (initial set size)'
set ylabel 'Experiment time with initial size N (sec)'\n";
@plots = ();
$k = 0;
foreach my $j (@codes) {
    $k += 1;
    push @plots, "'-' with errorbars title '$j' ls $k pt 1, '-' with lines notitle ls $k";
}
print "plot ", join(", ", @plots), "\n";
foreach my $j (@codes) {
    foreach my $i (@sizes) {
        next if $i > $top;
        my $x = $stats{$j}->{$i};
        next if !defined($x);
        print $i, " ", $x->[0], " ", $x->[1], " ", $x->[2], "\n";
    }
    print "e\n";
    foreach my $i (@sizes) {
        next if $i > $top;
        my $x = $stats{$j}->{$i};
        next if !defined($x);
        print $i, " ", $x->[0], "\n";
    }
    print "e\n";
}

system("eog results.png 2>/dev/null") if $out_is_terminal;
