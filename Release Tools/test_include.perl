# This will verify that all Ratwin header files
#  1. may be included first
#  either...
#   2. define the RATWIN_NoGlobals macro, or
#   both...
#      3. can be included before WINDOWS.H
#      4. can be included after WINDOWS.H

use strict;
use warnings;
use File::Find;
use File::Spec;
use File::Path;
use Carp;

my $topdir= find_topdir();
my $workdir= find_workdir();
my $CPPfile= File::Spec->catfile ($workdir, "test.cpp");
my $failnotes= File::Spec->catfile ($workdir, "failnotes.txt");
my @faillist;

sub find_workdir
 {
 my $dir= File::Spec->catfile (File::Spec->tmpdir(), "test_include");
 mkpath ($dir);  # make sure it exists.
 return $dir;
 }

sub find_topdir
 {
 my ($volume,$directories,$file) = File::Spec->splitpath($0);
 my @path= File::Spec->splitdir ($directories);
 pop @path;  # last one is empty.
 my $finalnode= lc (pop @path);
 croak "Can't automatically find files if not run from my release structure's location! stopped"
    unless $finalnode eq "release tools";
 $directories= File::Spec->catdir (@path);
 return File::Spec->catpath ($volume,$directories);
 }


sub try_compile ($;$)
 {
 my ($CPPfile, $noshow)= @_;
 (my $OBJfile=$CPPfile) =~ s/\.cpp$/\.obj/i;
 my $cmdline= qq(CL /c /nologo /GR /I"$topdir" /Fo"$OBJfile" "$CPPfile");
 my $result= `$cmdline`;
 if ($result =~ / error /) {
    print $result unless $noshow;
    return undef;  # report an error
    }
 return 1;  # report OK.
 }

my %errortext= (
   '1' => "file could not be included first (alone)"
  );
   
sub notefailure ($$)
 {
 my ($filename, $testID)= @_;
 if (@faillist==0 || ( $faillist[-1] ne $filename))  { push @faillist, $filename }
 print "$filename Failed test '$testID'\n";
 print "=============\n";
 }

sub process_file ($)
 {
 my $filename= shift;
 return if -d $filename;  # don't do anything with directory names
 return unless $filename =~ /\.[hH]$/;  # only interested in .h files
 $filename =~ tr [/][\\];  # put path in canonocal form.
 print "Processing $filename\n";
 (my $relname= $filename) =~ s/^\Q$topdir\E\\//i;
 my $handle;
 open ($handle, ">$CPPfile") or die;
 print $handle qq(#include "$relname"\n);
 close $handle;
 unless (try_compile ($CPPfile)) {
    notefailure ($filename, "include first (only)");
    return;  # don't go on to the other tests.
    }
 # try test 2
 open ($handle, ">$CPPfile") or die;
 print $handle qq(#define RATWIN_NoGlobals\n#include "$relname"\n);
 close $handle; 
 my $noglobals= try_compile ($CPPfile, 1);
 print ($noglobals? "Doesn't contain globals.\n" : "Flagged as containing globals.\n");
 return  unless $noglobals;
 # try test 3 - include before WINDOWS.H
 open ($handle, ">$CPPfile") or die;
 print $handle qq(#include "$relname"\n#include <WINDOWS.H>\n);
 close $handle; 
 unless (try_compile ($CPPfile)) {
    notefailure ($filename, "include before WINDOWS.H");
    return;  # don't try the other way either.
    }
 # try test 4 - include after WINDOWS.H
 open ($handle, ">$CPPfile") or die;
 print $handle qq(#include <WINDOWS.H>\n#include "$relname"\n);
 close $handle; 
 unless (try_compile ($CPPfile)) {
    notefailure ($filename, "include after WINDOWS.H");
    return;
    }
 # future tests go here.
 }

############### main program

print "Found topdir is [$topdir]\n";
print "Work directory is [$workdir]\n";

if (@ARGV) {
   # If files were specified on the command line, do those (only).
   foreach my $fname (@ARGV) {
      $fname= Win32::GetFullPathName ($fname);
      process_file ($fname);
      }
   exit 1;  # don't write fail report file.
   }

if (-e $failnotes) {
   # retry those that failed last time.
   my $file;
   open $file, '<', $failnotes  or die;
   my @list= <$file>;
   close $file;
   foreach (@list) {
      chomp;
      process_file ($_);
      }
   }
else {
   # scan the directory
   find (sub{ process_file($File::Find::name)}, File::Spec->catfile ($topdir, "ratwin"));
   }

print "\n\n";
if (@faillist) {
   print (scalar @faillist, " files failed.\n");
   my $output;
   open $output, '>', $failnotes;
   print $output join ("\n", @faillist);
   close $output;
   }
else {
   unlink $failnotes;
   print "All files passed.\n";
   }


