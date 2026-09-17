
#^on ^action * {
#	if ([$0]==N) {
#		xecho -b $(c2)$0$(hblk)/$(cl)$1$(cl) $2-
#	}
#	if ([$1]==C && [$0]!=N) {xecho -b $(hwht)$0 $(cl)$2-
#	}
#	if ([$1]!=C && [$0]!=N) { 
#		echo $winchan($1)
#		xecho -b $(hwht)$0$(hblk)!$(cl)$1 $2-
#	}
#}

^on ^action * {
	if ([$0]==N) {
		xecho -b $(c2)$0$(hblk)/$(cl)$1$(cl) $2-
	}
	 
	if (winchan($winchan($1))==[$1]) {xecho -b $(hwht)$0 $(cl)$2-
	}{
	xecho -b $(hwht)$0$(hblk)!$(cl)$1 $2-
	}
}
		
^on ^send_action "*" {
@ :sdesc1 = [$(cl)-> $(hwht)$0 $(c3)$N $(cl)$1-]  
@ :sdesc2 = [$(hwht)$N $(cl)$1-]
@ :sdesc3 = [$(hwht)$N$(hblk)!$(cl)$0 $(cl)$1-]
	switch ( $0 ) {
		($C) {^xecho -b $sdesc2}
		(#*) {#}
		(*) {^xecho -b $sdesc1} 
	}
}

## oweff's mme with youngdrow's silentchans
alias mme {
  if (mychannels()) {
    fe ($mychannels()) mychan {
      if (findw($tolower($mychan) $tolower($silentchans)) == -1) {
        if (mychan==C)
          {^me $*}
          {^describe $mychan $*}
      }
    }
  }
}

alias saway if ([$0]) {
	@ silentchans = [$*]
	xecho -b cypress silent away channels set to "$silentchans"
	}{
	xecho -b cypress away channels set to "$silentchans"
}