#alias chelp if (![$0]) {load $twiddle($HOME)$(loadpath)ans/help.ans}{
@hwords=[mw qk bkt massk rkick not mreop mko mirck clones cig mnot mmsg minv cypress flags lsay emsg esay untheme rtheme theme frelm tsave freln away back format config color sbcolor v rn csc dict paste saveall fsave cpsave sbar scan topwin wk wlk wn wp wj wc csave usay country addbot listbot botdel botsave]
alias chelp if (![$0]) {
#@:hwords=[mw qk bkt massk rkick not mreop mko mirck clones cig mnot mmsg minv cypress flags lsay emsg esay untheme rtheme theme frelm tsave freln away back format config color sbcolor v rn csc dict paste saveall fsave cpsave sbar scan topwin wk wlk wn wp wj wc csave usay country addbot listbot botdel botsave]
banner.head   
	@_ohcenter=[${word(0 $geom()) / 2 + 40}]
	oecho  %K[$(c1)³%K] $center($_ohcenter %W c y %wp r %Ke s s    %Wh %we l %Kp) 
	@_ohwidth=[${word(0 $geom()) / 14}]
		fe ($jot(1 $_ohwidth)) n1 {
							^push _htopics ohelp.$n1 
							^push _htopics2 %K[%n\$[10]ohelp\.$(n1)%K]  
						}
							   fe ($hwords) n1 {
									if (match($n1 $aliasctl(alias match *))) {
										^push hwords2 $n1
									}
								}	
							fe ($hwords2) $_htopics {
								eval banner.mid  $_htopics2  
							}
					^assign -_htopics;^assign -_htopics2;^assign -hwords2;^assign -hwords		
					banner.foot   
obecho $scriptname usage -> /chelp %K<%nhelpword%K> 
}{

@ :mw=[%Wu%nsage%K:%n /mw -hidden|split|kill <will create/kill a window bound to msgs>]
@ :bkt=[%Wu%nsage%K:%n /bkt <nick> see /chelp qk]
@ :qk=[%Wu%nsage%K:%n /qk <nick> will bankick nick from current channel and unban after 5 seconds]
@ :massk=[%Wu%nsage%K:%n /massk <string> will kick all nonops with a version reply found with specified string] 
@ :rkick=[%Wu%nsage%K:%n /rkick will kick a random non op out of the channel]
@ :not=[%Wu%nsage%K:%n /not unsets the topic on the current channel] 
@ :mreop=[%Wu%nsage%K:%n /mreop will reop all ops on current channel]
@ :mko=[%Wu%nsage%K:%n /mko will kick all ops from current channel]
@ :mirck=[%Wu%nsage%K:%n /mirck will kick all users with a version reply of mirc out of current channel]
@ :clones=[%Wu%nsage%K:%n /clones will show clones from current channel]
@ :cig=[%Wu%nsage%K:%n /cig will ignore public from current channel]
@ :away=[%Wu%nsage%K:%n /away <awaymsg> publicly declares yourself away]
@ :back=[%Wu%nsage%K:%n /back <backmsg> publicaly declares yourself back]
@ :format=[%Wu%nsage%K:%n /format <letter> <number> changes format letter to #]
@ :config=[%Wu%nsage%K:%n /config <letter> <setting> changes config letter to #]
@ :color=[%Wu%nsage%K:%n /color <color1> <color2> <color3> <color4> changes color to desired colors]
@ :sbcolor=[%Wu%nsage%K:%n /sbcolor <color1> <color2> <color3> <color4>  changes sbar color to desired colors]
@ :v=[%Wu%nsage%K:%n /v <nick> voices nick]
@ :rn=[%Wu%nsage%K:%n /rn changes nick to a random nick]
@ :csc=[%Wu%nsage%K:%n /csc clears screen then does /scan]
@ :dict = [%Wu%nsage%K:%n /dict <word> looks up word in online dictionary]
@ :paste = [%Wu%nsage%K:%n /paste then <number> to paste line in buffer]
@ :saveall = [%Wu%nsage%K:%n /saveall saves all settings]
@ :fsave = [%Wu%nsage%K:%n /fsave saves all format settings]
@ :cpsave = [%Wu%nsage%K:%n /cpsave saves cypress settings]
@ :sbar = [%Wu%nsage%K:%n /sbar <number> changes sbar to desired number]
@ :scan = [%Wu%nsage%K:%n /scan scans current channel for nicks]
@ :topwin = [%Wu%nsage%K:%n /topwin <on|off> toggles topic bar on or off]
@ :wk = [%Wu%nsage%K:%n /wk kills current window]
@ :wlk = [%Wu%nsage%K:%n /wlk leaves channel and kills window]
@ :wn = [%Wu%nsage%K:%n /wn changes to next window]
@ :wp = [%Wu%nsage%K:%n /wp changes to previous window]
@ :wj = [%Wu%nsage%K:%n /wj <channel> opens up new window and joins channel specified]
@ :wc = [%Wu%nsage%K:%n /wc creates new window]
@ :theme = [%Wu%nsage%K:%n /theme <themename> loads preset theme] 
@ :tsave = [%Wu%nsage%K:%n /tsave saves loaded theme]
@ :frelm = [%Wu%nsage%K:%n /frelm <fakenick> <channel> <text to fake> fakes recvied msg and pastes it to channel]
@ :freln = [%Wu%nsage%K:%n /freln <fakenick> <channel> <text to fake> fakes recvied notice and pastes it to channel]
@ :esay = [%Wu%nsage%K:%n /esay <text> sends encrypted text through special filters.]
@ :emsg = [%Wu%nsage%K:%n /emsg <nick> <text> sends encrypted text through msg.]
@ :csave = [%Wu%nsage%K:%n /csave saves color settings]
@ :lsay = [%Wu%nsage%K:%n /lsay <text> says ereet text!#]
@ :flags = [%Wu%nsage%K:%n flags that can be used with /echo, /say, /msg, /emsg, /esay, and /usay: -b(blue) -c(cyan) -g(green) -m(magenta) -r(red) -w(white) -y(yellow)]
@ :untheme = [%Wu%nsage%K:%n /untheme <theme> removes current theme]
@ :rtheme = [%Wu%nsage%K:%n /rtheme <theme> removes current theme]
@ :usay = [%Wu%nsage%K:%n /usay <text> UP and DOWN word TALKER] 
@ :cypress = [%Wu%nsage%K:%n /cypress show cypress ansi]
@ :country = [%Wu%nsage%K:%n /country <abbr> get country name from abbreviation]
@ :addbot = [%Wu%nsage%K:%n /addbot <botnick|botnick!botident@bothost> <password> <channel> <cmd> - adds a bot to the botlist] 
@ :botdel = [%Wu%nsage%K:%n /botdel <num> delete bot from botlist
@ :botsave = [%Wu%nsage%K:%n /botsave saves bots to file
@ :listbot = [%Wu%nsage%K:%n /listbot lists all bots
@ :minv = [%Wu%nsage%K:%n /minv <#chan> will mass invite current channel to specified
@ :mnot = [%Wu%nsage%K:%n /mnot <text> will mass notice current channel with specified text
@ :mmsg = [%Wu%nsage%K:%n /mmsg <text> will mass msg current channel with specified text
	if ([$0]) {
	if (!match($0 $hwords)) {
	eval echo $_boxhead
	echo $(hblk)[$(c1)³$(hblk)]$(cl) $scriptname command: $(hwht)$0 $(cl)not found
	eval echo $_boxfoot
	} else {
	eval echo $_boxhead
	echo $(hblk)[$(c1)³$(hblk)]$(cl) cypress $Cparse("$($0)") 
	eval echo $_boxfoot
}}}