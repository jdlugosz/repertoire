use strict;
use warnings;

process_file ($_)  foreach (@ARGV);


sub top_lines
 {
 my @macrolist= @{$_[0]};
 my @result= (
    "// ## BEGIN MacroCloak Generated Code\n",
    "#if defined ($macrolist[0])\n",
    "// if one of these is defined, user included WINDOWS.H first.\n",
    qq(#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")\n),
    "#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.\n"
    );
 foreach (@macrolist) {
    push @result, "#undef $_\n";
    }
 push @result, "#endif\n";
 push @result, "// ## END Generated Code\n";
 return @result;
 }
 
sub bottom_lines
 {
 my @macrolist= @{$_[0]};
 my $namespace= $_[1];
 my @result= (
    "// ## BEGIN MacroCloak Generated Code\n",
    "#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef\n",
    "#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef\n",
    (map { "using ${namespace}::$_;\n" } (@macrolist)),
    "#endif\n",
    "// ## END Generated Code\n"
    );
 return @result;
 }

sub process_file
 {
 my $fname= shift;
 print "Processing ($fname)\n";
 open INFILE, "<$fname"  or die "cannot open ($fname) for input.";
 my @lines= <INFILE>;
 close INFILE;
 unless (grep /##\s*Macro_Cloak_Def/, @lines) {
    print "File does not contain \"## Macro_Cloak_Def\" so there is nothing to do.\n";
    return;
    }
 # remove old generated code.
 my $startline= 0;
 while ($startline < @lines) {
    ++$startline  until $startline >= @lines  ||  $lines[$startline] =~ /## BEGIN MacroCloak Generated Code/;
    my $endline= $startline+1;
    ++$endline  until $endline >= @lines  ||  $lines[$endline] =~ /## END/;
    splice (@lines, $startline, $endline-$startline+1)   if ($startline < @lines && $endline < @lines);
    }
 # find Macro_Cloak_Def line
 $startline= 0;
 ++$startline  until $startline >= @lines || $lines[$startline] =~ /##\s*Macro_Cloak_Def\s*\((.*)\)/;
 die "Cannot find proper Macro_Cloak_Def line"  unless $1;
 my $namespace= $1;
 ++$startline;  # real content starts on next line
 my $endline= $startline;
 ++$endline  until $lines[$endline] =~ m(\*/);
 # parse out list of macros.
 my @macrolist= split (' ', join('',@lines[$startline .. $endline]));
 pop @macrolist;  # remove trailing '*/'
 # add lines at this point.
 my @newlines= top_lines (\@macrolist);
 splice @lines, $endline+1, 0, @newlines;
 $startline= $endline+1+scalar(@newlines);  #resume looking after this chunk.
 ++$startline  until $startline >= @lines  ||  $lines[$startline] =~ /##\s*Macro_Cloak_After/;
 die "Cannot find Macro_Cloak_After line."  if $startline >= @lines;
 @newlines= bottom_lines (\@macrolist, $namespace);
 splice @lines, $startline+1, 0, @newlines;
 # write out results.
 open OUTFILE, ">$fname"  or die "cannot open ($fname) for output.\n";
 print OUTFILE @lines;
 close OUTFILE;
 }
 
