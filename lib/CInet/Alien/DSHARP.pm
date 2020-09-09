=encoding utf8

=head1 NAME

CInet::Alien::DSHARP - The model counter DSHARP

=cut

# ABSTRACT: The model counter DSHARP
package CInet::Alien::DSHARP;
use base qw(Alien::Base);

=head1 SYNOPSIS

    use IPC::Run3;
    use CInet::Alien::DSHARP qw(dsharp);

    # Run #SAT solver on a DIMACS CNF file
    run3 [dsharp, $cnf_file], \undef, \my $out, \undef;

    # Clauses produced programmatically can be sent to stdin
    run3 [dsharp], \&produce_clauses, \my $out, \undef;

    # In any case, parse the answer from $out.
    # CAUTION: it may overflow Perl's native integer,
    # consider C<use bignum>.
    my ($count,) = $out =~ /^#SAT.* (\d+)$/;

=head2 VERSION

This document describes CInet::Alien::DSHARP v1.0.0.

=cut

our $VERSION = "v1.0.0";

=head1 DESCRIPTION

This module builds a custom version of the model counter DSHARP developed
by Muise, McIlraith, Beck and Hsu. It takes a Boolean formula in conjunctive
normal form (in the DIMACS CNF format) and produces the I<number> of
satisfying assignments to it.

The package C<CInet::Alien::DSHARP> is an L<Alien::Base> with one
additional method:

=head2 exe

    my $program = CInet::Alien::DSHARP->exe;

Returns the absolute path of the C<dsharp> executable bundled with
this module.

=head1 EXPORTS

There is one optional export:

=head2 dsharp

    use CInet::Alien::DSHARP qw(dsharp);
    my $program = dsharp;

Returns the same path as C<exe> but is shorter to type.

=cut

use Path::Tiny;

our @EXPORT_OK = qw(dsharp);
use Exporter qw(import);

sub exe {
    my $self = shift;
    path($self->dist_dir, $self->runtime_prop->{exename});
}

sub dsharp {
    __PACKAGE__->exe
}

=head1 SEE ALSO

=over

=item *

The original paper about DSHARP is
L<https://doi.org/10.1007/978-3-642-30353-1_36>.

=item *

The original source code for C<dsharp> is on github:
L<https://github.com/QuMuLab/dsharp>.

=item *

The source code repository of the fork bundled with this module is
L<https://github.com/taboege/dsharp>.

=back

=head1 AUTHOR

Tobias Boege <tobs@taboege.de>

=head1 COPYRIGHT AND LICENSE

This software is copyright (C) 2020 by Tobias Boege.

This is free software; you can redistribute it and/or
modify it under the terms of the Artistic License 2.0.

=head2 Bundled software

The C<DSHARP> solver is Copyright (C) 2012 by Christian Muise
and collaborators who released it under the GPLv2 license.

Parts of C<DSHARP> are based on C<sharpSAT> which is
Copyright (C) 2012 by Marc Thurley and released under
the MIT license.

Our modifications in particular replace usage of the GMP library
by C<BigInt> which is Copyright (C) 2019 Syed Faheel Ahmad who
released it under the MIT license.

=cut

":wq"
