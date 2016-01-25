#second program of NS lab

#create new simulator
set ns [new Simulator]
set nf [open out.nam w]
set tr [open out.tr w]

#set the trace files
$ns namtrace-all $nf
$ns trace-all $tr

proc finish {} {
	global ns nf tr
	$ns flush-trace
	close $nf
	close $tr
	exec nam out.nam &
	exit 0
}

#set colors
$ns color 1 Blue
$ns color 2 Red

#create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#create labels
$n0 label "Source/TCP"
$n1 label "Source/UDP"
$n2 label "Router"
$n3 label "Destination"

#create links
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ns DropTail

#set the agents

#set TCP agent
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
$tcp0 set class_ 1
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

#UDP agent
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
$udp1 set class_ 2
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1

#attach TCP sink to n3 for TCP packets
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3

#attach Null agent to n3 for UDP traffic
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

#set the traffic param
$ftp0 set packetSize_ 500
$ftp0 set interval_ 0.005

$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005

#connect the agents
$ns connect $udp1 $null3
$ns connect $tcp0 $sink3

#timer commands
$ns at 0.5 "$cbr1 start"
$ns at 0.6 "$ftp0 start"
$ns at 4.5 "$cbr1 stop"
$ns at 4.5 "$ftp0 stop"

$ns at 5.0 "finish"
$ns run
