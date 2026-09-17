alias cpsave {
        @ rename($savefile $savefile~)
        @ savemt = open($savefile W T)
        @ write($savemt ** cypress config file - saved $strftime($time() %D %T))
	@ write($savemt @fk1 = [$fk1])
	@ write($savemt @fk2 = [$fk2])
	@ write($savemt @fk3 = [$fk3])
	@ write($savemt @fk4 = [$fk4])
	@ write($savemt @fk5 = [$fk5])
	@ write($savemt @fk6 = [$fk6])
        @ write($savemt @top=[$top])
	@ write($savemt @plog = [$plog])
	@ write($savemt @ctcpl = [$ctcpl])
	@ write($savemt @msgl = [$msgl])
	@ write($savemt @notl = [$notl])
	@ write($savemt @page = [$page])
	@ write($savemt @dccl = [$dccl])
	@ write($savemt @wlog = [$wlog])
	@ write($savemt @kreas = [$kreas])
        @ write($savemt @kreas = [$kreas])	
	@ write($savemt @awayt = [$awayt])
	@ write($savemt @awayr = [$awayr])
	@ write($savemt @email = [$email])
	@ write($savemt @backr = [$backr])
	@ write($savemt @silentchans = [$silentchans])
	@ write($savemt @getumode = [$getumode])
        @ write($savemt @showaway = [$showaway])
	@ write($savemt @showtype = [$showtype])
	@ write($savemt @togaway = [$togaway])
	@ write($savemt @showop = [$showop])
	@ write($savemt @klog = [$klog])
	@ write($savemt @tstamp = [$tstamp])
	@ write($savemt @awayl = [$awayl])
	@ write($savemt @_ncompc = [$_ncompc])
	@ write($savemt @_klogotog = [$_klogotog])
	@ write($savemt @_quittog = [$_quittog])
	@ close($savemt)
       echo $G cypress: settings saved to $savefile
}

alias csave {
        @ rename($csavefile $csavefile~)
        @ savec = open($csavefile W T)
        @ write($savec ** cypress color config file - saved $strftime($time() %D %T))
        @ write($savec @c1=[$c1)
        @ write($savec @c2=[$c2)
	@ write($savec @c3=[$c3)
	@ write($savec @c4=[$c4)
	@ write($savec @sc1=[$sc1)
        @ write($savec @sc2=[$sc2)
	@ write($savec @sc3=[$sc3)
	@ write($savec @sc4=[$sc4)
	@ write($savec @sc5=[$sc5)
	@ close($savec)
       echo $G cypress: color settings saved to $csavefile
       
}

alias fsave {
        @ rename($fsavefile $fsavefile~)
        @ savefmt = open($fsavefile W T)
	@ write($savefmt @statbar=[$statbar])
	@ write($savefmt @mform=$mform)
	@ write($savefmt @smform=$smform)
	@ write($savefmt @ncomp=$ncomp)
	@ write($savefmt @echostr=$echostr)
	@ write($savefmt @svform=$svform)
	@ write($savefmt @aform=$aform)
	@ write($savefmt @kform=$kform)
	@ write($savefmt @top=[$top])
	@ write($savefmt @plistf=$plistf)
	@ write($savefmt @iform=$iform)
	@ write($savefmt @fnum=$fnum)
	@ write($savefmt @pub=$pub)
	@ write($savefmt @snform=$snform)
	@ write($savefmt @scform=$scform)
	@ write($savefmt @cform=$cform)
	@ write($savefmt @nform=$nform)
	@ write($savefmt @qform=$qform)
	@ write($savefmt @pform=$pform)
	@ write($savefmt @jform=$jform)
	@ write($savefmt @dccform=$dccform)
	@ write($savefmt @name=[$name])
	@ write($savefmt @snf=$snf)
        @ write($savefmt @scdesc=[$scdesc])
	@ write($savefmt @qlogo=$qlogo)
	@ write($savefmt @abot=$abot)
	@ write($savefmt @mdform=$mdform)
	@ write($savefmt @dccbar=$dccbar)
	@ close($savefmt)
	xecho -b cypress: format settings saved to $fsavefile
}

alias saveall {
	cpsave;csave;fsave;botsave
}
alias cyp.rehash {
@ c1 = cyn
@ c2 = hcyn
@ c3 = cyn
@ c4 = cyn
@ sc1 = cyn
@ sc2 = hcyn
@ sc3 = cyn
@ sc4 = hcyn
@ sc5 = cyn
@ snf = 3
@ mform = 2
@ smform = 2
@ ncomp = 1
@ echostr = 2
@ svform = 4
@ aform = 1
@ kform = 5
@ plistf = 2
@ nform = 1
@ snform = 6
@ qform = 1
@ jform = 3
@ iform = 1
@ pform = 1
@ bform = 1
@ page = [on]
@ fnum = 4
@ cform = 1
@ scform = 1
@ dccform = 1
@ pub = 1
@ top = [on]
@ statbar = [stat.1]
@ qlogo = 1
@ abot = 1
@ mdform = 1
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
^eval scform.load $scform
^eval cform.load $cform
^eval qlogo.load $qlogo
^eval abot.load $abot
^eval mdform.load $mdform
^eval ^load $twiddle($HOME)$(loadpath)stats/$statbar
^eval load $twiddle($HOME)$(loadpath)modules/filters.m
^eval load $twiddle($HOME)$(loadpath)wis/whois.$fnum
^eval load $twiddle($HOME)$(loadpath)sc/scan.$snf
}