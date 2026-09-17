/* clones alias, rewritten by codelogic..
 * codelogic got bored =[
 */

alias clones {
	@ delarray(clones)
	@ setitem(clones 0)
	^local chan, people, check, ii, jj, i
	@ chan = ![$0]?C:match($0 $mychannels())?[$0]:C, people = chanusers($chan)
	fe ($people) ii { 
		fe ($people) jj {
		if ((ii!=jj) && (after(@ $userhost($ii))==after(@ $userhost($jj)))) {
				if (matchitem(clones $jj)==-2) {
					@ setitem(clones $numitems(clones) $jj)
				}
			}
		}
	}
	xecho -b clones on $chan: [${numitems(clones)-1} total..]
	for (@ i=1,i<numitems(clones),@ i++) {
		xecho -b $_flag($getitem(clones $i) $chan)$getitem(clones $i)!$userhost($getitem(clones $i))
	}
}

alias _flag {
	@ function_return = [${ischanop($0 $1) ? [@] : isvoice($1 $0) ? [+] : []}]
}

			
	
		

