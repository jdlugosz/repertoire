#!/usr/bin/perl -w
require 5.005;
use strict;
use vars qw($root $revision $exact $fileID $shell);

### update these values for this particular run.
$root= 'F:\\work\\incoming\\dev\\Repertoire\\development\\';    #where the files are found
$revision= 'public build 9';   #the name to stamp everything
$exact= 1;  #TRUE is "built on", FALSE is "...or later".
$fileID= "{pb9}";  #what the DLL's are called

$shell= "C:\\Progra~1\\4nt\\4nt.exe -C";    #uses the DIR command in 4NT by jp software.


my @monthnames= qw(Jan Feb March April May June July Aug Sept Oct Nov Dec);
use vars '$date';

#####################

sub hunt_and_replace_fileID ($)
 {
 my $line= shift;
 $line =~ s/(Dlugosz Repertoire .*?){.*?}(\.)/$1$fileID$2/g;
 return $line;
 }

#####################

sub version_stamp
 {
 my $filename= shift;
 print LOGFILE "processing $filename\n";
 unless (open FILE, "<$filename") {
    print LOGFILE "Error opening file for reading.  Skipped.  O.S. says $!\n";
    return;
    }
 my @save;
 for (;;) {
    my $line= <FILE>;
    push @save, $line
       unless $line =~ m[^//\s*(The Repertoire Project)|(File:)|(Revision:)];
    last unless $line =~ m[^//];  #stop scanning when I get my first non-comment line.
    }
 push @save, <FILE>;  #get the rest of the file
 unless (open (FILE, ">$filename")) {
    print LOGFILE "Error opening file for writing.  Aborted processing.  O.S. says $!\n";
    return;
    }
 # modify the file content for some special files
 if ($filename =~ /\\autolink.h$/) {
    @save= map { hunt_and_replace_fileID $_ } (@save);
    }
 # write the new header information
 print FILE "// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>\n";
 my $root= $main::root;
 $root =~ s/\\/\\\\/g;
 my ($normname)= $filename =~ /^$root(.*)$/i;
 print FILE "// File: $normname\n";
 my $datestamp= $main::exact ? "$main::revision, shipped on $main::date" : "$main::revision, modified $main::date or later";
 print FILE "// Revision: $datestamp\n";
 print FILE @save;
 close FILE;
 }

#####################

sub update_dsp($)
 {
 my $filename= shift;
 print LOGFILE "processing $filename\n";
 unless (open FILE, "<$filename") {
    print LOGFILE "Error opening file for reading.  Skipped.  O.S. says $!\n";
    return;
    }
 my @save= map { hunt_and_replace_fileID $_ } (<FILE>);
 unless (open (FILE, ">$filename")) {
    print LOGFILE "Error opening file for writing.  Aborted processing.  O.S. says $!\n";
    return;
    }
 print FILE @save;
 close FILE;
 }

#####################

sub main
 {
 print "Version stamp utility.  Processing tree from $main::root\n";
 my @filelist= `$shell dir $main::root /sf /A:-D`;     #requires the 4NT shell to generate the main file list.
 my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;
 $year += 1900;  #struct tm field is years-1900, not simply last two digits of year.
 $date= "$mday-$monthnames[$mon]-$year";
 open LOGFILE, ">>version_stamp_log.txt";
 print LOGFILE "================= run at $main::date $hour:$min:$sec ==== processing $main::root\n";
 my $file;
 foreach $file (@filelist) {
    chomp ($file);
    if ($file =~ /\.(?:(?:cpp)|(?:cxx)|(?:h)|(?:hpp))$/i) {
       #is a source file
       version_stamp($file)  if -W $file;
       }
    if ($file =~ /\.dsp/i) {
       #is a Microsoft Visual Studio Project file
       update_dsp($file)  if -W $file;
       }
    # other special files ...
    }
 }

####################
#execution starts here
main;
1;

