@ sbar.max = 21
alias sbar if ([$0] && ([$0] <= sbar.max)) {
	@ statbar = [stat.$0]
	@ statnum = [$0]
	load $twiddle($HOME)$(loadpath)stats/$statbar
	xecho -b $scriptname sbar set to $(hwht)$0
	xecho -b type /cpsave to save status bar
} { xecho -b $scriptname usage: /sbar <1-$(sbar.max)> current sbar is $(hwht)$after(. $statbar)}