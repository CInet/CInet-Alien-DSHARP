use strict;
use warnings;
use Test::More;
use Test::Alien;

use CInet::Alien::DSHARP;

alien_ok 'CInet::Alien::DSHARP';
run_ok([CInet::Alien::DSHARP->exe, '-V'])
    ->success
    ->out_like(qr/^([0-9.a-z]+)/);

done_testing;
