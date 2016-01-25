#! /usr/bin/perl

use CGI ':standard', '-debug';
use DBI;

print "content-type: text/html \n\n";
$dbh = DBI->connect("dbi:mysql:iplab", "root", "root");
$r = $dbh->prepare("select * from student;");
$r->execute();
print "<table>";
print "<tr><td>NAME</td><td>REGNO</td></tr>", br;
while(($name, $regno) = $r->fetchrow_array()) {
	print "<tr><td>$name</td><td>$regno</td></tr>", br;
}
print "</table>";
$r->finish();
