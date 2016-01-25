#simulator for PING

set ns [new Simulator]
set tr [open out.tr w]
set nf [open out.nam w]

$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green

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

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$n0 label "ping0"
$n1 label "ping1"
$n4 label "ping4"
$n5 label "ping5"

$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link $n3 $n5 1Mb 10ms DropTail

set ping0 [new Agent/Ping]
set ping1 [new Agent/Ping]
set ping4 [new Agent/Ping]
set ping5 [new Agent/Ping]

$ping0 set packetSize_ 128
$ping0 set interval_ 0.001
$ping0 set class_ 1

$ping1 set packetSize_ 128
$ping1 set interval_ 0.001
$ping1 set class_ 2

$ping4 set packetSize_ 128
$ping4 set interval_ 0.001

$ping5 set packetSize_ 128
$ping5 set interval_ 0.001

$ns attach-agent $n0 $ping0
$ns attach-agent $n1 $ping1
$ns attach-agent $n4 $ping4
$ns attach-agent $n5 $ping5

#create extra traffic too by making CBRs
set udp0 [new Agent/UDP]
set null4 [new Agent/Null]
set cbr0 [new Application/Traffic/CBR]

$cbr0 set packetSize_ 512
$cbr0 set interval_ 0.005
$udp0 set class_ 3

$ns attach-agent $n0 $udp0
$ns attach-agent $n4 $null4
$cbr0 attach-agent $udp0

#connect the applications
$ns connect $udp0 $null4
$ns connect $ping0 $ping4
$ns connect $ping1 $ping5

#this function is executed when a ping agent recieves a reply
Agent/Ping instproc recv {from rtt} {
	$self instvar node_
	puts  "[$node_ id] received a reply from $from. Round trip time : $rtt ms"
}

#schedule events
$ns at 0.1 "$ping0 send"
$ns at 0.2 "$ping0 send"
$ns at 0.3 "$ping0 send"
$ns at 0.4 "$ping0 send"
$ns at 0.5 "$ping0 send"
$ns at 0.6 "$ping0 send"
$ns at 0.7 "$ping0 send"
$ns at 0.8 "$ping0 send"

$ns at 0.1 "$ping1 send"
$ns at 0.2 "$ping1 send"
$ns at 0.3 "$ping1 send"
$ns at 0.4 "$ping1 send"
$ns at 0.5 "$ping1 send"
$ns at 0.6 "$ping1 send"
$ns at 0.7 "$ping1 send"
$ns at 0.8 "$ping1 send"

$ns at 0.5 "$cbr0 start"
$ns at 4.0 "$cbr0 stop"
$ns at 5.0 "finish"
$ns run
