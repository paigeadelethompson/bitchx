
alias mnot {
	if (![$0]) {xecho -b syntax /mnot text to send to channel.}{
	fe ($onchannel()) luser { if (luser != N) { @push(lusers $luser) } }
	fe ($lusers) o1 o2 o3 o4 o5 o6 o7 o8 {^quote NOTICE $o1,$o2,$o3,$o4,$o5,$o6,$o7,$o8 :$*}
	echo mass noticing users with $*
^assign -lusers;^assign -o1;^assign -o2;^assign -o3;^assign -o4;^assign -o5;^assign -o6;^assign -o7;^assign -o8 
}}

alias minv {
	if (![$0]) {xecho -b syntax /minv #chan }{
	fe ($sar(g/$N//$chanusers())) o1 {^quote invite $o1 $0}
	echo mass inviting users from current channel to $0
	}}


alias mmsg {
	if (![$0]) {xecho -b syntax /mmsg text to send to channel.}{
	fe ($onchannel()) luser { if (luser != N) { @push(lusers $luser) } }
	fe ($lusers) o1 {^quote privmsg $o1 :$*}
	echo mass msging users with $*
^assign -lusers 
}}