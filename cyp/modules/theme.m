## theme module, thanx to robohak for help w/ padding
alias tsave if ([$1]) {
	@ blahfile = fullstrip($0)
	if (fexist(~/cyp/themes/$(blahfile).th)) {
		@ rename(~/cyp/themes/$(blahfile).th ~/cyp/themes/$(blahfile).th.old)
		^exec rm ~/cyp/themes/$(blahfile).th.old 1> /dev/null 2> /dev/null
	}
        @ :saveth = open($twiddle($HOME)$(loadpath)themes/$(blahfile).th W T)
        @ :author = N
	@ :desc = [$1]
	@ :name = blahfile
        @ write($saveth :$author)
        @ write($saveth :$desc)
        @ write($saveth :$name)
	@ write($saveth @auth=[$N])
	@ write($saveth @desc=[$desc])
	@ write($saveth @name=[$name])
	@ write($saveth @scdesc=[ ..$desc])
	@ write($saveth @mform=$mform)
        @ write($saveth @smform=$smform)
        @ write($saveth @ncomp=$ncomp)
        @ write($saveth @echostr=$echostr)
        @ write($saveth @svform=$svform)
        @ write($saveth @aform=$aform)
        @ write($saveth @kform=$kform)
        @ write($saveth @top=[$top])
        @ write($saveth @plistf=$plistf)
        @ write($saveth @iform=$iform)
        @ write($saveth @fnum=$fnum)
        @ write($saveth @pub=$pub)
        @ write($saveth @snform=$snform)
        @ write($saveth @nform=$nform)
        @ write($saveth @qform=$qform)
        @ write($saveth @pform=$pform)
        @ write($saveth @jform=$jform)
	@ write($saveth @scform=$scform)
	@ write($saveth @cform=$cform)
        @ write($saveth @dccform=$dccform)
        @ write($saveth @snf=$snf)
	@ write($saveth @statbar = [$statbar])
	@ write($saveth @fnum=$fnum)
	@ write($saveth @qlogo=$qlogo)
	@ write($saveth @abot=$abot)
	@ write($saveth @mdform=$mdform)
        @ write($saveth @c1=[$c1)
        @ write($saveth @c2=[$c2)
        @ write($saveth @c3=[$c3)
        @ write($saveth @c4=[$c4)
        @ write($saveth @sc1=[$sc1)
        @ write($saveth @sc2=[$sc2)
        @ write($saveth @sc3=[$sc3)
        @ write($saveth @sc4=[$sc4)
        @ close($saveth)
	xecho -b $scriptname: saved theme file $(hblk)[$(cl)~/cyp/themes/$(name).th$(hblk)]$(cl) $(hblk)\($(cl)$desc$(hblk)\)$(cl)
        ^load ~/cyp/themes/$(name).th
        ^do.formatupdate
}{ xecho -b $scriptname usage: /tsave <theme> <description> }

# thanks to ttb for some original help w/ read(), but it still didn't work :P
alias theme if (![$0]) {
	echo      $(hwht)f$(cl)ile $(hwht)n$(cl)ame$(hblk)      ú     $(hwht)a$(cl)uthor     $(hblk)     ú     $(hwht)d$(cl)escription
	echo 
	fe ($glob(~/cyp/themes\/*.th)) th {
	  @ :thfile = open($th R T)
	  @ :auth = after(: $read($thfile))
	  @ :desc = after(: $read($thfile))
	  @ :name = after(: $read($thfile))
	  @ close($thfile)
	  echo      $(cl)$[10]name$(hblk)     ú     $(cl)$[12]auth    $(hblk)ú     $(cl)$desc$repeat(${20-strlen($strip( $stripansicodes($desc)))}  )$(cl)
	}
}{
if (fexist(~/cyp/themes/$0.th)==-1) { xecho -b $scriptname: theme $0 does not exist }{
	@ name = [$0]
	^load ~/cyp/themes/$(0).th
	^do.formatupdate  
	xecho -b loaded theme file $(hblk)[$(cl)$(0).th$(hblk)]$(cl) by $auth $(hblk)\($(cl)$desc$(hblk)\)$(cl)
}}

alias do.formatupdate {
^eval mform.load $mform
^eval smform.load $smform
^eval ncomp.load $ncomp
^eval echostr.load $echostr
^eval svform.load $svform
^eval aform.load $aform
^config x $_klogotog
^eval topwin $top
^eval iform.load $iform
^eval qform.load $qform
^eval pform.load $pform
^eval jform.load $jform
^eval nform.load $nform
^eval snform.load $snform
^eval cform.load $cform
^eval scform.load $scform
^eval pubload $pub
^eval qlogo.load $qlogo
^eval abot.load $abot
^eval mdform.load $mdform
if (plistf ==1) cdcc1
if (plistf ==2) cdcc2
if (plistf ==3) cdcc3
if (plistf ==4) cdcc4
if (plistf ==5) cdcc5
if (plistf ==6) cdcc6
if (plistf ==7) cdcc7

^eval do.dccload $dccform
^eval ^load $twiddle($HOME)$(loadpath)wis/whois.$fnum
^eval ^load $twiddle($HOME)$(loadpath)stats/$statbar
^eval load $twiddle($HOME)$(loadpath)sc/scan.$snf
}

alias dotopwin { if (top==[on]) {^window split on} }
dotopwin
alias untheme { @name=[];@scdesc=[stock];cyp.rehash;xecho -b $scriptname: no longer using a theme, /fsave to save}
alias rtheme if ([$0]) { 
if (fexist(~/cyp/themes/$0.th)==-1) { xecho -b theme $(0) does not exist!
}{
^exec rm -rf ~/cyp/themes/$(0).th 1> /dev/null 2> /dev/null
xecho -b theme $(0) has been removed!
}}{xecho -b $scriptname usage: /rtheme <theme>}

# .:. clogic '98