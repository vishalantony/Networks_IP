#! /usr/bin/perl

use CGI ":standard", "-debug";
print "content-type: text/html\n\n";

@output = qx(ls /usr/lib/cgi-bin/access);
$size = @output;
if($size == 0) {
	system("touch /usr/lib/cgi-bin/access") != -1 or die("can't create file.");
	system("chmod 0777 /usr/lib/cgi-bin/access") != -1 or die("chmod");
	system("echo 0 > /usr/lib/cgi-bin/access") != -1 or die("echo");
}
open(FILE, "</usr/lib/cgi-bin/access") or die("can't access");
$accesses = <FILE>;
close(FILE);
$accesses = $accesses+1;
print html(body(p("this page has been accessed $accesses times.")));
open(FILE, ">/usr/lib/cgi-bin/access") or die("can't write");
print FILE $accesses;
close(FILE);
