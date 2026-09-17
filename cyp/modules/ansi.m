alias cypress {
@ :ansifile = open(~/cyp/logos/logo.$(rand(3)) R)
	while (!eof($ansifile)) {
		echo $read($ansifile)
	}
@ close($ansifile)
}

alias ansiload if ([$0]) {
@ :ansifile = open($0 R)
	while (!eof($ansifile)) {
		eval echo $read($ansifile)
	}
@ close($ansifile)
}

# clogic '98