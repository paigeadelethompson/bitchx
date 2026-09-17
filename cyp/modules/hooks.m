## various hooks
## mail stuff :>
on ^mail "*" {
xecho -b you$(hblk)\($(c1)$USER$(c2)@$(c1)$word(0 $split(. $HOSTNAME))$(hblk)\($(c1)$_time()$(hblk)\)\)$(cl) have new mail! $(hblk)\($(c1)$1$(cl) total$(hblk)\)$(cl)}
 
/* no on
^bind ^D parse_command do.ig
^on ^flood "*" {
@ floodnick = [$0]
@ :flooduh = userhost($0)
@ floodtype = [$1]
xecho -b $(c2)$1 $(cl)flood detected from $(c1)$0$(hblk)\($(c1)$userhost($0)$(hblk)\)$(cl)
if (tolower($flood_protection)==[off]) {
xecho -b ^D to ignore $(c1)$0$(cl)
}{do.ig}}

alias do.ig {
if (floodnick&&floodtype) {
^ignore $mask($userhost($floodnick) 13) $floodtype
xecho -b now ignoring $(c1)$floodnick$(hblk)\($(c1)$userhost($floodnick)$(hblk)\)$(cl) for 10 minutes $(hblk)[$(c1)$floodtype flood$(hblk)]$(cl)
^timer 600 ^tig $mask($userhost($floodnick) 13)
}}
*/

# ..timer thingy from parallax..
on #-timer 23 * {
  if (Z =~ [\\[??:00??\\]]) {
    xecho -b the time is now $(c1)$(Z).}}

/* <panasync_> /on llook_split
<panasync_> 2 servernames are passed
something to do later. :>
*/



alias _ncompchar if ([$0]) {
	@ _ncompc = [$*]
 	xecho -b cypress nick completion character set to $(cl)"$_ncompc"
	} else {
	xecho -b cypress nick completion character set to $(cl)"$_ncompc"
	}
	


/* 
 * problems? along comes psykotyk to help me out =\ 
 * KrOn's friend parker helped us out by adding a few more lines to this. - void
 */
 

^on ^input "*" {
	if (strlen($before($_ncompc $0)) > 1&&right(1 $0)==_ncompc) {
	@_txt = before($_ncompc $0)
		if (pattern($_txt $chanusers($C))) {
		@per = word(0 $pattern($_txt $chanusers($C)))
        } elsif (pattern($_txt* $chanusers($C))) {
            @per = word(0 $pattern($_txt* $chanusers($C)))
        
		} elsif (pattern(*$_txt* $chanusers($C))) {
            @per = word(0 $pattern(*$_txt* $chanusers($C)))
        }
        if (per) {
            sendline $stripansicodes($fparse(format_nick_comp $per  $1-))
        }{
 	 			sendline $*
		}
	}{
	sendline $*
	}
^assign -per
}
# clogic/void '98