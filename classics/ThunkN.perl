use strict;
use warnings;

my $n= shift;
if ($n < 2 || $n > 1022) {
   die "usage: ThunkN <number> where <number> is the number of arguments in the function signature.";
   }

my $content= do {
   my $infname= "closure-=-MSonPC.h";
   open IN, "<", $infname
      or die "Cannot open $infname for reading.";
   local $/;
   my $x= <IN>;
   $x;
   };

my $outfname= "closure-$n.h";
open OUT, ">", $outfname
   or die "Cannot open $outfname for writing";

# look for the part I need to replicate
$content =~ m[^\s*//\s+##\s+ThunkN\s*\n(.*)^\s*//\s+##\s+end\s*\n]ms
   or die "Cannot find passage to replicate.";
$content= $1;  # just the part I'm interested in.

my $s= join (', ', map {"typename ParamType$_"} (1..$n));
$content =~ s/typename\s+ParamType(?=\s*>)/$s/
   or warn "Could not find template argument declaration.";

$content =~ s/member_callback_thunk/member_callback_thunk_$n/g;

$s= join (', ', map {"ParamType$_"} (1..$n));
$content =~ s/\(ParamType\)/($s)/g;

print OUT <<EOT;
// This file generated from the master code in closure-=-MSonPC.h.
// Don't edit this -- edit that instead and re-run ThunkN.perl.

#pragma once
#include "closure-=-MSonPC.h"

namespace classics {
$content
}
EOT

