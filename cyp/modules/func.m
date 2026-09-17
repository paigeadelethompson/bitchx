alias ismask {return ${pass(!@ $0) ? 1 : 0}}
/* shade - ismask() && getuhost() */
/* thanks =] */

alias comchan {
	^assign -comchans
	fe ($mychannels()) ii { 
		if (onchannel($0 $ii)) {
			@ push(comchans $ii)
		}
	}
return $comchans
}	

alias spacestrip 
{
	return $sar(g/ //$*)
}

alias fullstrip 
{
	return $strip( $stripansicodes($stripmirc($*)))
}

alias striplen 
{
	return $strlen($strip( $stripansicodes($stripmirc($*))))
}

alias hfunky 
{ 
	fe ($*) ii { 
		@push(function_return ${striplen($ii)==1?[$left(1 $ii):striplen($ii)==2?[$left(1 $ii)$right(1 $ii)]:striplen($ii)>=3?[$left(1 $ii)$mid(1 ${striplen($ii) - 2} $ii)$right(1 $ii)]:})
	}
}			

alias getuhost
{
        wait for userhost $0 -cmd
        {
                return ${[$4] != [<UNKNOWN>] ? [$3@$4] :}
        }
}
alias isonline {
        wait for userhost $0 -cmd {
                return ${[$4] != [<UNKNOWN>] ? [1] : [0]}
        }
}

alias getlp {@function_return=page==[on]&&awayl==[on]?[$awayf4]:awayl==[on]&&page==[off]?[$awayf3]:awayl==[off]&&page==[on]?[$awayf2]:[$awayf1]}

## oweff's fix.cdcc
alias fix.cdcc {
        if ([$0]==[PRIVMSG]) {
        if ([$1]==C) {say $2-}{msg $1 $2-}
        }{
        notice $1 $2-}
}

alias usayfunct {
^assign -final
fe ($*) ii jj {
@ push(final $toupper($ii) $tolower($jj))
}
return $final
}
alias _time {
@ :_ctime = strftime(%r)
if (left(1 _ctime = 0))
{
@ function_return = [$mid(1 4 $_ctime)]##[ ]##[$tolower($right(2 $_ctime))]
} else {
@ function_return = [$mid(0 5 $_ctime)]##[ ]##[$tolower($right(2 $_ctime))]
}}

## shade/psy
alias numdots {@ function_return = (_absstrlen($1-) < [$0] ? [$1-] ## (hblk ## repeat(${[$0]-_absstrlen($1-)} .)) : left(${[$0]-3} $1-) ## [$(hblk).$(cl).$(hwht).$(cl)])}/* functions.. */

alias _uhost
{
	if (userhost($0)==[<UNKNOWN>@<UNKNOWN>]) {
		wait for userhost $0 -cmd {return $3@$4}} else { return $userhost($0)}}

alias _userhost {
@function_return=(:uhost=userhost($0))==[<UNKNOWN>@<UNKNOWN>]?[]:uhost}

alias _homedir {
	push function_return $twiddle(~)}	

alias fix.size {
        @ :_size=[$0]
	^stack pop set floating_point_math
        ^set floating_point_math on
        if (!_size) {@function_return=[0b]
	} elsif (_size<1024) {@function_return=[$(_size)b]
	} elsif (_size<1048576) {
                @ function_return = [$trunc(2 ${_size/1024})kb]
        } else {
                @ function_return = [$trunc(2 ${_size/1048576})mb]
        }
        ^stack push set floating_point_math
}

alias _printlen {return $printlen($stripansicodes($*))}

alias _pad {
	@ function_return = [$1-$repeat(${[$0]-_printlen($1-)}  )}]

alias _getflag {
	if (show_pubflag) {
	@ :nick = [$0], :chan = [$1]
	@ function_return = match(*@?$nick $channel($chan))?[$(hk)@$(cl)]:match(.+$nick $channel($chan))?[$(hk)+$(cl)]:[]
	} else {
	@ function_return = []}}

/* eof */