use strict;
use warnings;

# LOGIC
my $_true  = sub { 
    # shift is more convenient
    # my $x = $_[0];
    my $x = shift; 
    sub { $x } 
};
my $_false = sub { 
    sub { shift } 
};

my $not = sub { 
    my $b = shift; 
    $b->($_false)->($_true) 
};

my $and = sub {
    my $b1 = shift;
    sub {
        my $b2 = shift;
        $b1->($b2)->($_false)
    }
};

my $or = sub {
    my $b1 = shift;
    sub {
        my $b2 = shift;
        $b1->($_true)->($b2)
    }
};

# CHURCH NUMERALS
my $zero = sub { sub { shift } };
my $succ = sub {
    my $n = shift;
    sub {
        my $f = shift;
        sub {
            my $x = shift;
            $f->($n->($f)->($x))
        }
    }
};
my $pred = sub {
    my $n = shift;
    sub {
        my $f = shift;
        sub {
            my $x = shift;
            $n->(sub {
                my $g = shift;
                sub {
                    my $h = shift;
                    $h->($g->($f))
                }
            })->(sub { $x })->(sub { shift })
        }
    }
};
my $one = $succ->($zero);

# HELPERS - not pure lambda calculus
sub read_bool {
    my $b = shift;
    print $b->('true')->('false');
}

sub read_church {
    my $n = shift;
    print $n->(sub { $_[0] + 1 })->(0);
}

# EXAMPLES
print "LOGIC\n";
print "-------------\n";
print " TRUE: ";
read_bool($_true);
print "\n FALSE: ";
read_bool($_false);

print "\n NOT TRUE: ";
read_bool($not->($_true));
print "\n NOT FALSE: ";
read_bool($not->($_false));

print "\n TRUE AND TRUE: ";
read_bool($and->($_true)->($_true));
print "\n TRUE AND FALSE: ";
read_bool($and->($_true)->($_false));
print "\n FALSE AND TRUE: ";
read_bool($and->($_false)->($_true));
print "\n FALSE AND FALSE: ";
read_bool($and->($_false)->($_false));

print "\n TRUE OR TRUE: ";
read_bool($or->($_true)->($_true));
print "\n TRUE OR FALSE: ";
read_bool($or->($_true)->($_false));
print "\n FALSE OR TRUE: ";
read_bool($or->($_false)->($_true));
print "\n FALSE OR FALSE: ";
read_bool($or->($_false)->($_false));

print "\n\nCHURCH NUMERALS\n";
print "-------------\n";
print " ZERO: ";
read_church($zero);
print "\n ONE: ";
read_church($one);
print "\n SUCC ONE: ";
read_church($succ->($one));
print "\n SUCC SUCC ONE: ";
read_church($succ->($succ->($one)));

print "\n PRED ONE: ";
read_church($pred->($one));
print "\n PRED SUCC ONE: ";
read_church($pred->($succ->($one)));
print "\n PRED SUCC SUCC ONE: ";
read_church($pred->($succ->($succ->($one))));
