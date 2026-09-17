alias mko {
	fe ($remw($N $chops())) n1 {
		quote kick $C $n1 :$*
        }
        
}

alias _klogo {
          if (![$0]) {xecho -b cypress show kick logo set to $(hwht)$toupper($_klogotog)}
          if ([$0]==[on]) {
		@_klogotog = [$0]
        	kform.load $kform
		xecho -b cypress show kick logo set to $(hwht)$toupper($0)  
	} elsif ([$0]==[off]) {		
		@kickr=[]
		@bkickr=[]  
		@_klogotog = [$0]
		xecho -b cypress show kick logo set to $(hwht)$toupper($0)
          } else {
	  if ([$0]&&!match($0 on off)) {xecho -b invalid choice}
    }
}               
@ kickr = [\(cyp-k) ]
@ bkickr = [\(cyp-bk) ]
alias randkick if ([$0]!=[on]&&[$0]!=[off]) {@kreas = [ON];xecho -b invalid choice, must be ON or OFF}{
               @ kreas = [$0]
                xecho -b cypress randkick msgs set to $(hwht)$toupper($kreas)}{
                if (![$0])
                xecho -b cypress randkick msgs set to $(hwht)$toupper($kreas)}


alias k {
         if ([$1]) {
	 //kick $C $0 $(kickr)$1-
	}
	if (![$1]) {
	if (kreas==[ON]) {
	//kick $C $0 $(kickr)$getreason(a)
	}{
	//kick $C $0 $(kickr)I pheer you.}
}}
alias kb bk
alias bk {
         if ([$1]) {
	 //bk $C $0 $(bkickr)$1-
	} else {
	if (kreas==[ON]) {
	//bk $C $0 $(bkickr)$getreason(a)
	}{
	//bk $C $0 $(bkickr)I pheer you.}
}}

alias qk {
		if (![$0]) {
			xecho -b usage: /qk <nick> <reason> - will bankick specified nick then unban them after 5 seconds. 
			}{
				bankick $*
				@_bnick=[$0]
					^timer 5 {ub $_bnick}
				}
}

alias massk if (![$0]) {
	xecho -b usage: /massk <version string> 
		}{
		@kvar=[$0]
			xecho -b kicking all users with $kvar in version reply.
				^ver $C
					^on ^ctcp_reply "% VERSION *" {
						if (!ischanop($0 $C)) {
							if (match(*$kvar* $2-)) {
								k $0 $kvar is ereet!@#$%^&*
							}
						}
   					}

	^timer 50 ^on ^ctcp_reply -"% % VERSION *"
}

alias mirck {
	xecho -b kicking all m1rc lamers, sit back and watch the phun.
	ver
	^on ^ctcp_reply "% VERSION *" {
		if  (!ischanop($0 $C)) {
		switch ($*) {
			(*mIRC*) {k $0 mIRC is ereet!@#$%^&*}
		}
	}

}
	^timer 50 ^on ^ctcp_reply -"% VERSION *"
}


# alias randw { @srand(${pid() * F * time()});return $word($rand($numwords($*)) $*) }

# randomkick by powuh


alias rkick {
   fe ($chanusers($C)) zz { @ setitem(array.randkick $numitems(array.randkick) $zz) }
   @ srand($time)

   for (@:tmp = 0, tmp < numitems(array.randkick), @:tmp++) {
        @ randkick.nick = getitem(array.randkick $rand($numitems(array.randkick)))

	if (randkick.nick == servernick()) {
	   continue
	}

   if (ischanop($randkick.nick $C)) {
            if (kick_ops == [ON]) {
               k $randkick.nick random kick!
               break
            }
         }{
            k $randkick.nick random kick!
            break
         }
   }
   @ randkick.nick = []
   @ delarray(array.randkick)
}
 
