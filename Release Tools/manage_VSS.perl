use strict;
use warnings;
use Win32::OLE;

my $SS= new Win32::OLE:: "SourceSafe";
$SS->Open ('F:\VSS Version Control\srcsafe.ini');


sub get_VSS_item ($)
 {
 my $name= shift;  # relative name to project.
 $name =~ s[\\][/]g;
# print "setting item to $name\n";
 my $item= $SS->VSSItem ("\$/repertoire/$name");
 return $item;
 }
 

sub project_base
 {
 if ($_[0] =~ /^(C:\\work\\dev\\Repertoire\\development\\)(.*)$/i) {
    $_[0]= $2;  # set param to relative name
    return $1;  # return base part
    }
 die "$_[0] not a known project base ";
 }


sub DO_checkout
 {
 my $fname= shift;
 print "checkout $fname\n";
 my $base= project_base ($fname);
 my $item= get_VSS_item ($fname);
 $item->CheckOut();
 }

sub DO_checkin
 {
 die "not yet implemented";
 }

sub DO_get_tip
 {
 die "not yet implemented";
 }

#main logic
my $opcode= lc shift;
{no strict 'refs';  #allow symbolic reference
   &{"DO_$opcode"} (@ARGV);
   }

