alias email if (![$0]) {xecho -b email address currently set to: $email}{@ email= sar(g/@/@/$0);xecho -b e-mail address set to: $email}
alias setumode if (![$0]) {xecho -b current usermode set to: $getumode}{@ getumode = [$0];xecho -b usermodes set to: $getumode}

alias config  {
@ :choice = [$1-]
switch ($0) {
	(a) {set cdcc_flood_after $choice}
	(b) {awaytime $choice}
	(c) {logm $choice}
	(d) {logp $choice}
	(e) {logc $choice}
	(f) {logd $choice}
	(g) {logn $choice}
	(h) {logw $choice}
	(l) {logpub $choice}
	(i) {awaymsg $choice}
	(j) {backmsg $choice}
	(k) {saway $choice}
	(m) {randkick $choice}
	(n) {email $choice}
	(o) {setumode $choice}
	(p) {showaway $choice}
	(q) {bot_tog}
	(r) {awaytog $choice}
	(s) {saveall}
	(t) {vocop $choice}
	(u) {logkick $choice}
	(v) {_awayl $choice}
	(w) {_ncompchar $choice}
	(x) {_klogo $choice}
	(y) {quittoggle $choice}
	(f1) {/fkey1 $choice}
	(f2) {/fkey2 $choice}
	(f3) {/fkey3 $choice}
	(f4) {/fkey4 $choice}
	(f5) {/fkey5 $choice}
	(f6) {/fkey6 $choice}

	(*) {ansiload $twiddle($HOME)$(loadpath)ans/config.ans;^xecho -b usage -$(hwht)> $(hwht)c$(cl)onfig $(hblk)<$(cl)letter$(hblk)> <$(cl)setting$(hblk)>}
}}

alias bot_tog { if (showtype==1) { @ showtype = 2;xecho -b now showing passwords. } else { @ showtype = 1;xecho -b not showing passwords }}
alias quittoggle {
          if (![$0]) {xecho -b cypress quit logo toggle set to $(hwht)$toupper($_quittog)}
          if (match($0 on off)) {@_quittog = [$0]
          xecho -b cypress quit logo toggle set to $(hwht)$toupper($_quittog)}{
          if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }}          