package winhelp
alias winhelp {
	if (!$[0]) {
			
xecho  $(hwht)ÚÄÄÄÄ$(cl)ÄÄÄÄÄ$(hwht)ÄÄ$(cl)ÄÄÄÄÄÄÄÄ$(blu)ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ$(hblk)ÄÄÄÄÄÄÄÄÄÄÄÄÄ
	
	
		xecho -b $(hwht)wc  $(hblk)<$(cl)window create$(hblk)> $(cl)creates new hidden window 
		xecho -b $(hwht)wj  $(hblk)<$(cl)window join$(hblk)> $(cl) creates new hidden window and joins specified channel
		xecho -b $(hwht)wk  $(hblk)<$(cl)window kill$(hblk)> $(cl) kills current window
		xecho -b $(hwht)wlk $(hblk)<$(cl)window leave kill$(hblk)> $(cl)kills current window and parts channel
		xecho -b $(hwht)wn  $(hblk)<$(cl)window next$(hblk)> $(cl)window next switches to next hidden window
		xecho -b $(hwht)wp  $(hblk)<$(cl)window previous$(hblk)> $(cl)switches to previous hidden window
		xecho -b $(hwht)mw  $(hblk)<$(cl)message window$(hblk)> $(cl)-hidden|split|kill <will create/kill a window bound to msgs>	
		xecho -b $(hwht)wlog $(hblk)<$(cl)window log$(hblk)> $(cl)toggles window logging
		xecho -b $(hwht)wlist $(hblk)<$(cl)window list$(hblk)> $(cl)lists windows in use  
		xecho -b $(hwht)wlevel $(hblk)<$(cl)window levels$(hblk)> $(cl)changes level of current window ie: /window level msgs
		xecho -b $(hwht)wlogfile $(hblk)<$(cl)window logfile$(hblk)> $(cl)sets logfile for current window
		xecho -b $(hwht)wg $(hblk)<$(cl)window grow$(hblk)> $(cl)grows current window ie: /wg 7
		xecho -b $(hwht)ws $(hblk)<$(cl)window shrink$(hblk) >$(cl)shrinks current window ie: /ws 7
		xecho -b $(hwht)1-9 $(hblk)<$(cl)swap windows$(hblk)> $(cl)swap windows ie: /1 for window 1 /2 for window 2 etc...

xecho  $(blu)À$(hblk)-----ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ-----ÄÄ ÄÄ  Ä
	
	}	
}