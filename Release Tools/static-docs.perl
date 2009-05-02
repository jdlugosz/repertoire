use strict;
use warnings;

my $baseDir= 'E:\Web Mirror\Repertoire\refman';
my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
$year += 1900;
my @monthnames= qw/January February March April May June July August September October November December/;
my $month= $monthnames[$mon];

sub slurp
 {
 my $fname= shift;
 my $fh;
 if (!open $fh, "<", $fname) {
    warn "Cannot read [$fname]\n";
    return undef;
    }
 local $/; # enable localized slurp mode
 my $content = <$fh>;
 close $fh;
 return $content;
 }

sub writeout
 {
 my ($fname, $s)= @_;
 my $fh;
 if (!open $fh, ">", $fname) {
    warn "Cannot write [$fname]\n";
    return;
    }
 print {$fh} $s;
 close $fh;
 }

sub docdate
 {
 my $format= shift;
 return $year  if ($format eq "year");
 return "$month $year"  if $format eq "my";
 return "$mday-$month-$year"  if $format eq "full";
 return "***UNKNOWN FORMAT***";
 }

sub htmlCheck
 {
 my $fname= shift;
 my $s= slurp ($fname);
 my $count= $s =~ s{<span\s*class="docdate_(\w+)"\s*>(.*?)</span>}{qq/<span class="docdate_$1">/ . docdate($1) . "</span>"}sgie;
 print "$count matches in [$fname]\n";
 writeout ($fname, $s);
 }


htmlCheck ("$baseDir\\footer.html");
htmlCheck ("$baseDir\\static.html");
system qq(zip -urD9X "Repertoire Documentation.zip" * -x "Repertoire Documentation.zip vssver.scc");

