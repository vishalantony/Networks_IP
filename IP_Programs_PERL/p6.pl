#! /usr/bin/perl

use CGI ":standard", '-debug';
print "content-type: text/html \n\n";

($sec, $min, $hr) = localtime(time);
print '<html><head><meta http-equiv="refresh" content="1"></head>';
$time = sprintf("%02d:%02d:%02d", $hr, $min, $sec);
print body(p("$time")), '</html>';
