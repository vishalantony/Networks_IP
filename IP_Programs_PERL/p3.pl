#! /usr/bin/perl

use CGI ':standard', '-debug';

print "content-type: text/html\n\n";

$name = param('name');
print html(body(h1("Greetings $name!")));

