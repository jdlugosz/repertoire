use strict;
use warnings;
use IO::Handle;
use Win32::Console;

my $CONSOLE = new Win32::Console(STD_OUTPUT_HANDLE);
my $save_attr= $CONSOLE->Attr;

my $caption_attr= 10;  # bright green on black

sub print_color ($@)
 {
 my $color= shift;
 $CONSOLE->Attr ($color);
 print @_;
 STDOUT->flush();
 $CONSOLE->Attr ($save_attr);
 }

my @test_programs= glob ("*_UT*.exe");
{   my $pattern= shift;
   @test_programs= grep (/\Q$pattern\E/, @test_programs)  if $pattern;
   }
my @errored;
my $OK_count= 0;
my $skip_count= 0;

foreach my $program (@test_programs) {
   my $commandline= $program;
   if ($program =~ /^virtual_key/i) {
      print_color ($caption_attr, "skipping $program because it's interactive.\n");
      ++$skip_count;
      next;
      }
   if ($program =~ /^baro_UT_helper/i) {
      $commandline= qq("$^X" "..\\..\\classics\\baro_UT.perl" "$program");
      }
   print_color ($caption_attr, "running $program\n");
#   my $result= (system $program ($commandline)) >> 8;
   my $result= (system ($commandline)) >> 8;
   print_color $caption_attr, "$commandline ==>> result is: $result\n\n";
   if ($result) {
      push @errored, $program }
   else { ++$OK_count }
   }

print_color $caption_attr, "\n$OK_count unit test programs OK.\n";
print_color $caption_attr, "$skip_count unit test programs were skipped.\n"  if $skip_count;
print_color $caption_attr, "Programs failed:\n\t", join ("\n\t", @errored), "\n"
   if @errored;

