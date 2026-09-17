alias remlog {
	input " remove log? [y|n]: " if ([$0]==[y])
	{@unlink($twiddle($HOME)$(loadpath)$cyplog) 
	xecho -b $scriptname log removed.
}}
	
alias play readlog

alias readlog {
	more $twiddle($HOME)$(loadpath)$cyplog
	xecho -b type /remlog to remove log}


alias logm {
          if (![$0]) {xecho -b cypress msg logging set to $(hwht)$toupper($msgl)}
          if (match($0 on off)) {@msgl = [$0]
          xecho -b cypress msg logging set to $(hwht)$toupper($msgl)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logp {
          if (![$0]) {xecho -b cypress page logging set to $(hwht)$toupper($page)}
          if (match($0 on off)) {@page = [$0]
          xecho -b cypress page logging set to $(hwht)$toupper($page)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logc {
          if (![$0]) {xecho -b cypress ctcp logging set to $(hwht)$toupper($ctcpl)}
          if (match($0 on off)) {@ctcpl = [$0]
          xecho -b cypress ctcp logging set to $(hwht)$toupper($ctcpl)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logd {
          if (![$0]) {xecho -b cypress dcc logging set to $(hwht)$toupper($dccl)}
          if (match($0 on off)) {@dccl = [$0]
          xecho -b cypress dcc logging set to $(hwht)$toupper($dccl)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logn {
          if (![$0]) {xecho -b cypress notice logging set to $(hwht)$toupper($notl)}
          if (match($0 on off)) {@notl = [$0]
          xecho -b cypress notice logging set to $(hwht)$toupper($notl)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logw {
          if (![$0]) {xecho -b cypress wall logging set to $(hwht)$toupper($wlog)}
          if (match($0 on off)) {@wlog = [$0]
          xecho -b cypress notice logging set to $(hwht)$toupper($wlog)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logpub {
          if (![$0]) {xecho -b cypress public logging set to $(hwht)$toupper($plog)}
          if (match($0 on off)) {@plog = [$0]
          xecho -b cypress public logging set to $(hwht)$toupper($plog)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

alias logkick {
          if (![$0]) {xecho -b cypress kick logging set to $(hwht)$toupper($klog)}
          if (match($0 on off)) {@klog = [$0]
          xecho -b cypress kick logging set to $(hwht)$toupper($klog)}{
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}            

on -kick '$N' {
	if (awayl==[ON]&&awaystat&&klog==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
        @ write($savel $recvtime KICK $1 kicked you off $2 for reason $3-) 
	@ close($savel)}}

on -public_other * if (awayl==[ON]&&awaystat&&match(*$N* $2-)&&plog==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
        @ write($savel PUBLIC $recvtime $0:$1> $2-) 
	@ close($savel)}


on -public * if (awayl==[ON]&&awaystat&&match(*$N* $2-)&&plog==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
        @ write($savel PUBLIC $recvtime <$0:$1> $2-) 
	@ close($savel)}


on -ar_public * if (awayl==[ON]&&awaystat&&plog==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
        @ write($savel PUBLIC $recvtime <$0:$1> $2-) 
	@ close($savel)}

on -ar_public_other * if (awayl==[ON]&&awaystat&&plog==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
        @ write($savel PUBLIC $recvtime <$0:$1> $2-) 
	@ close($savel)}

on #-ctcp 2 " * " if (ctcpl==[ON]&&awaystat&&awayl==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)                              
	if ([$2]==[PAGE]&&page==[ON]) { 
		@ write($savel PAGE $recvtime $0 \($userhost()\) requested $2 $3- from $1)
        	^set BEEP ON
	        beep;beep;beep
	        xecho -b PAGE$(hblk):$(cyn) $recvtime $(cl)from $(cyn)$0$(hblk)[$(cyn)$msar(gã@ã$(hblk)@$(cyn)ã.ã$(hblk).$(cyn)ã$tr(/ã//$userhost()))$(hblk)]$(cl) $3-
	}{
        @ write($savel CTCP $recvtime $0 \($userhost()\) requested $2 $3- from $1) 
	@ close($savel)}}

on #-msg 4 " * " if (msgl==[ON]&&awaystat&&awayl==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)
	@ write($savel MSG $recvtime $0 \($userhost()\) $1-)
        @ close($savel)}

on #-dcc_request 6 " * " if (dccl==[ON]&&awaystat&&awayl==[ON]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
        @ savel = open($twiddle($HOME)$(loadpath)cyp.log W T) 
        @ write($savel DCC $recvtime dcc $1 request from $0 [$userhost()])
        @ close($savel)}

on #-notice 3 " * " if (notl==[ON]&&awaystat&&awayl==[ON]&&match(*[*#*]* $1-)==[0]) {
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)
	@ write($savel NOTICE $recvtime $0 \($userhost()\) $1-) 
	@ close($savel)}

on #-notice 4 "*[*#*]*" if (wlog==[ON]&&awaystat&&awayl==[ON]) { 
	@ recvtime = strftime(%x at %I:%M:%S %p)
	@ savel = open($twiddle($HOME)$(loadpath)cyp.log W T)
	@ write($savel WALL $recvtime $0 $1 $2-) 
	@ close($savel)}