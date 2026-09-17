package dict
## most of this taken from crackrock. server var taken from pv


@ dict.serv = [dict.org]
@ dict.port = 2628
alias dict {
	if (![$0]) {/chelp dict}{
		@ dword = [$*]
		^exec -name dict telnet $dict.serv $dict.port
		 ^on ^exec "dict *" {xecho -c $(c1)> $(cl)$1-}
		^on ^exec "dict Trying *" #
		^on ^exec "dict *Trying *" #
		^on ^exec "dict Connected to *" #
		^on ^exec "dict *Connected to *" #
		^on ^exec "dict Escape character is '^]'." {^exec -in %dict DEFINE * $dword}
		^on ^exec "dict 220*" #
		^on ^exec "dict 150*" #
		^on ^exec "dict 151*" #
		^on ^exec "dict 250*" {^exec -9 %dict}
		^on ^exec "dict 501*" {xecho -c -b syntax error, illegal parameters;^exec -9 %dict}
		^on ^exec "dict ?" {^exec -9 %dict}
		^on ^exec_prompt * {^exec -9 %dict}
		^on ^exec "dict ?DEFINITION 0" {^exec -9 %dict}
		^on ^exec "dict 552* no match*" {xecho -c -b no match for $dword;^exec -9 %dict}
		^on ^exec "dict SPELLING 0"{xecho -c -b $(hwht)$dword$(hblk):$(cl) No suggestions given.;^exec -9 %dict}
		^on ^exec "*connection closed by foreign host*" #
		^on ^exec_exit "DICT % %" #
	}
^assign -dict
}	