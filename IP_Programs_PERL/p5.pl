#! /usr/bin/perl

use CGI ':standard', '-debug';

print "content-type: text/html \n\n";
$webmaster = 'root';
($sec, $min, $hr) = localtime(time);
$ampm = 'am';
if($hr >= 12) {
	$ampm = 'pm';
	$hr = $hr - 12*($hr > 12);
}
$greet = "Good morning";

if(($hr >= 12) && ($hr <= 16)) {
	$greet = "Good afternoon";
}
elsif(($hr > 16) && ($hr <= 19)) {
	$greet = "Good evening";
}
elsif(($hr > 19) || ($hr <= 3)) {
	$greet = "Good night";
}

$name = param('name');
print p("$greet $name!");
print p("<pre>Current server time is $hr:$min:$sec $ampm</pre>");
@output = qx(who | grep $webmaster);
if(scalar @output) {
	print p("webmaster $webmaster is currently logged in");
}
else {
	print p("webmaster $webmaster not logged in");
}
