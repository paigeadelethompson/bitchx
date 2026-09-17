## windowing commands done by youngdrow
alias mw {
	if (![$0]) {
		xecho -b /mw -hidden|split|kill <will create/kill a window bound to msgs>
		}	
			switch ($0) {
			(-hidden) {^window new hide swap last double on level msgs name msgs}
			(-split) {^window new fixed on size 7 level msgs name msgs;^set status_format %>$(hblk)[$(cl)msgs$(hblk)]$(cl);^wset * status_format $status_format;^window back}
			(-kill) {^window msgs kill}
			}
	}


#alias channame if (left(1 $0)==[#]) {return $0} {return #$0}
alias channame if (left(1 $0)==[#] || left(1 $0)==[&]) { return $0 }{ return #$0 }
alias wc {^window new hide swap last double on}

# alias wj if ([$0])
#	{wc;^window bind $channame($0);join $*}
#	{echo Usage:  /wj <channel>}
alias wj {
        if (![$0]) {
                xecho -b usage: /wj <channel> [key]
        }       
                ^window new channel "$channame($0) $1-" bind $channame($0) hide swap last double on
}

alias win1 ^window swap 1
alias win2 ^window swap 2
alias win3 ^window swap 3
alias win4 ^window swap 4
alias win5 ^window swap 5
alias win6 ^window swap 6
alias win7 ^window swap 7
alias win8 ^window swap 8
alias win9 ^window swap 9

alias wk  {window kill}
alias wlk {part $C;wk}
alias wsc {^window refnum $0}
alias wn {window next}
alias wp {window previous}
## hayzus's aliases   
alias wlog window log toggle
alias wlist window list
alias wlogfile window logfile
alias wlevel window level
alias wg {window grow}   
alias ws {window shrink} 
alias wl wlist
## end

bind ^W meta5_character

bind META1-1 PARSE_COMMAND win1
bind META1-2 PARSE_COMMAND win2
bind META1-3 PARSE_COMMAND win3
bind META1-4 PARSE_COMMAND win4
bind META1-5 PARSE_COMMAND win5
bind META1-6 PARSE_COMMAND win6
bind META1-7 PARSE_COMMAND win7
bind META1-8 PARSE_COMMAND win8
bind META1-9 PARSE_COMMAND win9


bind META5-1 PARSE_COMMAND win1
bind META5-2 PARSE_COMMAND win2
bind META5-3 PARSE_COMMAND win3
bind META5-4 PARSE_COMMAND win4
bind META5-5 PARSE_COMMAND win5
bind META5-6 PARSE_COMMAND win6
bind META5-7 PARSE_COMMAND win7
bind META5-8 PARSE_COMMAND win8
bind META5-9 PARSE_COMMAND win9

bind META5-c PARSE_COMMAND wc
bind META5-k PARSE_COMMAND wk
bind META5-h PARSE_COMMAND wh
bind META5-p PARSE_COMMAND wp
bind META5-n PARSE_COMMAND wn
bind ^T parse_command dcc.get
bind ^R parse_command dcc.rej
bind ^O self_insert
bind ^G self_insert