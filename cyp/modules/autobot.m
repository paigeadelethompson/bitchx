/* botlist..rewritten.. */
/* 1999 codelogic/void */
@ bsavefile = [~/.bot.save]
#^eval load $bsavefile  

alias bot switch ($0) {
		(add) {addbot $1-}
		(list) {botlist}
		(save) {botsave}
		(delete) {botdel $1-}
		(*) {banner.lchead
			banner.lcmid usage: \/bot $(hblk)[$(c2)c$(c1)ommand$(hblk)] [$(c2)a$(c1)rgs$(hblk)]$(cl)
			banner.lcsep
			banner.lcmid $(hblk)[$(c2)c$(c1)ommands$(hblk)]$(cl)
			banner.lcmid $(hblk)[$(c2)a$(c1)dd$(hblk)]:$(cl) /bot add $(hblk)<$(c2)b$(c1)otnick$(hblk)|$(c2)b$(c1)otnick$(hblk)!$(c2)b$(c1)otident$(c2)@$(c1)bothost$(hblk)> <$(c2)p$(c1)assword$(hblk)>
			banner.lcmid        $(hblk)<$(c2)c$(c1)hannel$(hblk)> <$(c2)o$(c1)pcmd$(hblk)>:$(cl) add a bot to the botlist..
			banner.lcsep 
			banner.lcmid $(hblk)[$(c2)l$(c1)ist$(hblk)]$(cl) /bot list: list all bots..
			banner.lcsep 
			banner.lcmid $(hblk)[$(c2)s$(c1)ave$(hblk)]$(cl) /bot save: save bots to file for future use..
			banner.lcsep 
			banner.lcmid $(hblk)[$(c2)d$(c1)elete$(hblk)]$(cl) /bot delete $(hblk)[$(c2)n$(c1)umber$(hblk)]:$(cl) delete a bot from the botlist..
			banner.lcfoot}}
		
alias addbot {
	if (![$3]) {chelp addbot} else {
	@ _bot.addr = [$0]
	if (!_userhost($_bot.addr)) {
		@ _bot.host = sar(g/~/\*/$after(! $_bot.addr)), _bot.nick = before(! $_bot.addr) 
	} else { 
		if (!_userhost($_bot.addr)) { 
			xecho -b $_bot.addr is not on irc! } else {
			@ _bot.host = sar(g/~/\*/$_userhost($_bot.addr)), _bot.nick = _bot.addr}
	}
	if (_bot.host&&_bot.nick) {
		@ _bot.pass = encode($1), _bot.chan = [$2], _bot.cmd  = [$3-]
		@ setitem(botlist 0 !)
		@ setitem(botlist $numitems(botlist) $_bot.nick!$_bot.host $_bot.pass $_bot.chan $_bot.cmd)
		xecho -b bot added: $_bot.nick!$_bot.host pass: $decode($_bot.pass) channel: $_bot.chan command: $_bot.cmd
		}
	}
}

alias botlist {
	^local _bot.
	if (numitems(botlist)<2) 
	{ 
		xecho -b the botlist is empty..
	} else {
		banner.lchead
		banner.lcmid  $(hblk)[$(c2)n$(c1)um$(hblk)] [$(cl)$_pad(10 $(c2)c$(c1)hannel)$(hblk)] [$_pad(34 $(c2)u$(c1)serhost)$(hblk)] [$_pad(9 $(c2)n$(c1)ickname)$(hblk)]$(cl)
	  	for (@xx=1, xx<numitems(botlist), @xx++)
        	{
		@ _bot.pass = decode($word(1 $getitem(botlist $xx))), _bot.addr = word(0 $getitem(botlist $xx)), _bot.cmd = word(3 $getitem(botlist $xx)), _bot.chan = word(2 $getitem(botlist $xx))
		banner.lcmid  $(hblk)[$(c1)$[3]xx$(hblk)] [$(c1)$[10]_bot.chan$(hblk)] [$(c1)$[34]after(! $_bot.addr)$(hblk)] [$(c1)$[9]before(! $_bot.addr)$(hblk)]$(cl)}
		banner.lcfoot}}

alias botsave {
        @ rename($_homedir()/.bot.save $_homedir()/.bot.save~)
        @ fd = open($bsavefile W T)
        for (@xx=0, xx<numitems(botlist), @xx++)
        {@ write($fd @bot[$xx]=[$getitem(botlist $xx)])}
		@ close($fd)
       xecho -b bot settings saved to $_homedir()/.bot.save
       
}

alias botdel 
{if ([$0]==[]) { chelp botdel 
} elsif ([$0]==0) {xecho -b no such bot.. } else { dobotdel $0 }}

alias dobotdel {
	if (numitems(botlist)<=[$0]) { xecho -b no such bot! 
	} elsif (numitems(botlist)>1) { 
		@ _botaddr = word(0 $getitem(botlist $0))
		@ delitem(botlist $0)
		xecho -b $before(! $uhost)[$after(! $_botaddr)] has been deleted..
	} else { xecho -b botlist is empty.. }
}

alias shit {
	for (@x=numitems(botlist),x>0,@x--) {
        @ bot[$x] = []
        }
               
}
alias botload 
{
	for (@x=numitems(botlist),x>0,@x--) {
        	@ bot[$x] = []
    			}
       			@ delarray(botlist)
			@ setitem(botlist 0 !)
       			^load $bsavefile
			@ i = 1
			while (bot[$i]) {
				@ setitem(botlist $i $bot[$i])
				@ i++}
				xecho -b botlist loaded from $bsavefile
	}

alias startbotload 
{
	for (@x=numitems(botlist),x>0,@x--) {
        	@ bot[$x] = []
    			}
       			@ delarray(botlist)
			@ setitem(botlist 0 !)
       			^load $bsavefile
			@ i_ = 1
			while (bot[$i_]) {
				@ setitem(botlist $i_ $bot[$i_])
				@ i_++}
				
	}



^on #-channel_synch 11 * {
	@ _chan=[$0]
	^local _bot.
	fe ($getmatches(botlist *$_chan*)) ii { 
		@ _bot.1 = getitem(botlist $ii), _bot.2 = before(! $word(0 $_bot.1)), _bot.3 = after(! $word(0 $_bot.1))
		fe ($chops($_chan)) jj {
			if (userhost($jj) =~ _bot.3) {
				@ _item = getitem(botlist $ii)
			}
		}
	}
	if (_item) { 
		@ _bot.host = after(! $word(0 $_item)), _bot.nick = before(! $word(0 $_item)), _bot.cmd = word(3 $_item), _bot.pass = decode($word(1 $_item))
		if (match($_bot.host $userhost($_bot.nick))) { 
		        xecho -b $botprompt $fparse(format_autobot $_bot.nick $_chan)
			^quote PRIVMSG $_bot.nick :$_bot.cmd $_bot.pass
		}
	}
	^assign -_item 
}
^startbotload
/* eof */