use strict;
use warnings;
use Getopt::Long qw (:config bundling);
use File::Spec;

################################

my $readonly;

sub read_file
 {
 my $filename= shift;
 open (my $fh, "<", $filename)  or die "Cannot open $filename for reading ";
 read ($fh, my $buffer, 9999999);
 return $buffer;
 }

sub write_file
 {
 my ($filename, $contents)= @_;
 if ($readonly) {
    print "skipping write-out of [$filename] because read-only mode is enabled.\n";
    return;
    }
 open (my $fh, ">", $filename)  or die "Cannot open $filename for writing ";
 print $fh $contents;
 }


my $lib;
my $projroot= do {
   my $s=$0;  # script name
   $s =~ s{[^\\/]+$}{..};
   File::Spec->canonpath ($s);
   };
my $newversion;

################################

sub DO_checkout
 {
 my $fname= shift;
 unless (-w $fname) {
    print "file [$fname] is read-only.  Check-out and press ENTER.";
    <>;
    }
 }

################################
###### Process Files #############


sub process_dsp
 {
 my @project_file_names= (
    "$projroot\\compile.vc6\\$lib\\$lib.dsp",
    "$projroot\\compile.vc7\\$lib\\$lib.vcproj",
    "$projroot\\compile.vc71\\$lib\\$lib.vcproj" );
 foreach my $filename (@project_file_names) {
    next unless -e $filename;
    DO_checkout ($filename);
	my $data= read_file ($filename);
	unless ($newversion) {
	   die "must specify --new on command line\n"
	   # look for existing version string
	   #($oldversion)= $data =~ /Kodak KFC Standard Log Server({[^}]+}).exe/;
	   #print "Old version: $oldversion\n";
#	   figure_new_version;
	   }
	# OK, apply the change
	$data =~ s/(Dlugosz Repertoire $lib[^{]*){[^}]+}/$1\{$newversion\}/gi;
	write_file ($filename, $data);
	}
 }


sub process_autolink
 {
 my $filename= "$projroot\\$lib\\autolink.h";
 print "processing [$filename]\n";
 return unless -e $filename;
 DO_checkout ($filename);
 my $data= read_file ($filename);
 $data =~ s/(Dlugosz Repertoire $lib[^{]*){[^}]+}/$1\{$newversion\}/gi;
 write_file ($filename, $data);
 }

sub process_version_rc
 {
 my $filename= "$projroot\\$lib\\version.rc";
 print "processing [$filename]\n";
 return unless -e $filename;
 DO_checkout ($filename);
 my $data= read_file ($filename);
 my ($pbnum, $plusnum)= ($newversion =~ /^pb(\d+)(?:\+(\d+))?/i);
 $plusnum= 0 unless defined $plusnum;
 my $s= "#define VERSION_ID 3,$pbnum,0,$plusnum";
 $data =~ s/^\s*#define\s+VERSION_ID\s+.*$/$s/m
    or warn "can't match VERSION_ID\n";
 $s= "#define VERSION_NAME \"Public Build $pbnum";
 $s .= ", plus modifications"  if $plusnum;
 $s .= "\"";
 $data =~ s/^\s*#define\s+VERSION_NAME\s+.*$/$s/m
	or warn "can't match VERSION_NAME\n";

 write_file ($filename, $data);
 }


################################
###### Main Code  #############

print "Project root: [$projroot]\n";

sub show_options
 {
 print <<"EOF";
 --new=string	specify the version string
 --ro	read-only mode (for testing)
EOF
 exit 1;
 }

GetOptions (
   'help|?|h' => \&show_options,
   'new=s' => \$newversion,
   'ro' => \$readonly
   )  or exit 1;

$lib= shift(@ARGV);
die "library name expected.\n"
   unless defined $lib && $lib =~ /^(?:classics|ratwin|tomahawk)$/i;


process_dsp;
process_version_rc;
process_autolink;
print "Done.\n";

