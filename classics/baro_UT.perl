#!perl -w

print "Tests baro semantics by invoking baro_UT_helper.cxx and analysing the results.\n";
open INFILE, "baro_UT_helper + |"
   or die "Cannot spawn baro_UT_helper.  use current directory, put it on the PATH, or change this line. ";
$errorcount= 0;
while (<INFILE>) {  #for each line of input
   my $thd;  #I don't use this value for anything.
   ($linenum,$thd,$addr,$command) = split;
   chop $linenum;  #get rid of trailing dot.
   if ($command eq 'accept') {
      #make sure it's not on the deleted list
      if (exists $gone{$addr}) {
         print "* error: $addr accepted on $linenum after deleted on line $gone{$addr}\n";
         ++$errorcount;
         }
      }
   elsif ($command eq 'reject') {
      #make sure it is on the deleted list
      unless (exists $gone{$addr}) {
         print "* error: $addr rejected on line $linenum before deleted\n";
         ++$errorcount;
         }
      }
   elsif ($command eq 'destruct') {
      #add it to the destructed list
      $gone{$addr} = $linenum;
      }
   else {
      print "** parse error: '$command' on line $linenum\n";
      ++$errorcount;
      }
   }
print "$linenum records processed.\n";
if ($errorcount==0) {   print "Looks OK.\n";   }
else { print "no errors detected.\n"; }

