set ns [new Simulator]
set nf [open cwnd.nam w]
set tr [open cwnd.tr w]

$ns trace-all $tr
$ns namtrace-all $nf

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns make-lan "$n1 $n2 $n3 $n4" 10Mb 10ms LL Queue/DropTail Mac/802_3

set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set sink4 [new Agent/TCPSink]
$ns attach-agent $n4 $sink4
$ns connect $tcp1 $sink4

set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp2 $sink3

set file1 [open file1.tr w]
$tcp1 attach $file1
$tcp1 trace cwnd_
$tcp1 set maxcwnd_ 10

set file2 [open file2.tr w]
$tcp2 attach $file2
$tcp2 trace cwnd_

proc finish {} {
	global nf tr ns
	$ns flush-trace 
	exec nam cwnd.nam &
	close nf
	close tr
	exit 0
}

$ns at 0.1 "$ftp1 start"
$ns at 1.5 "$ftp1 stop"

$ns at 2 "$ftp1 start"
$ns at 3 "$ftp1 stop"

$ns at 0.2 "$ftp2 start"
$ns at 1.5 "$ftp2 stop"

$ns at 2 "$ftp2 start"
$ns at 4 "$ftp2 stop"

$ns at 5 "finish"

$ns run
