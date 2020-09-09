use strict;
use warnings;
use Test::More;
use Test::Alien;

use List::Util qw(first);
use Path::Tiny;
use CInet::Alien::DSHARP qw(dsharp);

my %COUNT = (
    'gaussoid4.cnf'   => 679,
    'orientable4.cnf' => 629,
    'oriented4.cnf'   => 34873,
    'markov5.cnf'     => 1024,
    'LUBF5.cnf'       => 1166,
);

for (sort keys %COUNT) {
    my $out = run_ok([dsharp, path('t', $_)])->success->out;
    my $mc = first { $_ } map { /^#SAT.*?(\d+)$/g } split /\n/, $out;
    is $mc, $COUNT{$_}, 'count ok';
}

done_testing;
