#!/bin/perl -w

while (<>) {
   if (
      ($num,$counter,$op,$address) = 
         (/^## (\d+) ##> counter (\d+), (constructing|destructing) ([\da-fA-F]+),/)
      ) {
      if ($op eq "constructing") {
         if (exists $store{$address}) {
            print "problem: line $num re-constructs line $store{$address}\n";
            }
         $store{$address} = $num;
         }
      else { #must be destructing
         if (!exists $store{$address}) {
            print "problem: line $num deletes something that was not allocated.\n";
            }
         else {
            delete $store{$address};
            }
         }
      }
   }
#anything left in list must be leaks.

@list= sort keys %store;
if (@list) {
   print "unfreed items:\n";
   foreach (@list) {
      print "line $store{$_}, address $_\n";
      }
   }
   
