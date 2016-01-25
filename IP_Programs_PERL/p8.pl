#! /usr/bin/perl

use CGI ':standard', '-debug';
use DBI;

print "content-type:text/html\n\n";
$dbh = DBI->connect("DBI:mysql:iplab", "root", "root");
$name = param('name');
$regno = param('regno');
$r = $dbh->prepare("insert into student values(\"$name\", $regno);");
$r->execute();
$r = $dbh->prepare("select * from student;");
$r->execute();
print '<table>';
print "<tr><td>NAME</td><td>REGNO</td></tr>";
while(($name, $regno) = $r->fetchrow_array()) {
	print "<tr><td>$name</td><td>$regno</td></tr>";
}
print "</table>";
$r->finish();
