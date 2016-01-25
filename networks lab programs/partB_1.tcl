# create new simulator
set ns [new Simulator]
$ns color 1 Blue
$ns color 2 Red
#nam trace file for running animation
set nf [open out.nam w]
$ns namtrace-all $nf

#trace file for counting the number of dropped packets
set tr [open out.tr w]
$ns trace-all $tr

proc finish {} {
	#these are global variables
	global ns nf tr
	#flush all the output
	$ns flush-trace
	close $nf
	close $tr
	exec nam out.nam &
	exit 0
}

#create the nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]


$n0 label "Source/UDP"
$n1 label "Source/UDP"
$n2 label "Router"
$n3 label "Destination/Null"

#create links
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n3 $n2 1Mb 10ms DropTail

$ns set queue-limit $n0 $n2 10
$ns set queue-limit $n1 $n2 10
$ns set queue-limit $n2 $n3 10

#attach UDP agent and CBR
#create UDP agent and CBR traffic source

set udp0 [new Agent/UDP]
#attach udp0 agent to node 0
$ns attach-agent $n0 $udp0

set udp1 [new Agent/UDP]
#attach udp1 agent to node 1
$ns attach-agent $n1 $udp1


$udp0 set class_ 1
$udp1 set class_ 2

#create traffic sink
set null0 [new Agent/Null]
#attach null0 agent to node 3
$ns attach-agent $n3 $null0

#cbr stands for constant bit rate.
#this is responsible for generating the packets.
set cbr0 [new Application/Traffic/CBR]
#packet is 500 bytes and interval between the packets is 5 ms (0.005s)
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
#attach cbr0 to udp0
$cbr0 attach-agent $udp0

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
#attach cbr1 to udp1
$cbr1 attach-agent $udp1

#connect the agents
$ns connect $udp0 $null0
$ns connect $udp1 $null0

#timed commands to run the simulator
#cbr0 starts generating packets at 0.5 s
#cbr1 starts generating packets at 1.0 s
$ns at 0.5 "$cbr0 start"
$ns at 0.5 "$cbr1 start"
$ns at 4.0 "$cbr0 stop"
$ns at 4.0 "$cbr1 stop"

#call finish procedure at 5.0
$ns at 5.0 "finish"

#run the simulator
$ns run
