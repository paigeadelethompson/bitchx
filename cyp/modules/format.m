alias ce echo $cparse("$*")
alias format if ([$0]) {
	switch ($0) {
		(a) { if (![$1]) {aform.show} {aform $1} }
		(b) { if (![$1]) {echostr.show} {echostr $1} }
		(d) { if (![$1]) {iform.show} {iform $1} }
		(j) { if (![$1]) {jform.show} {jform $1} }
		(l) { if (![$1]) {kform.show} {kform $1} }
		(g) { if (![$1]) {mform.show} {mform $1} }
		(e) { if (![$1]) {nform.show} {nform $1} }
		(p) { if (![$1]) {ncomp.show} {ncomp $1} }
		(k) { if (![$1]) {pform.show} {pform $1} }
		(i) { if (![$1]) {qform.show} {qform $1} }
		(h) { if (![$1]) {smform.show} {smform $1} }
		(f) { if (![$1]) {snform.show} {snform $1} }
		(o) { if (![$1]) {sv.show} {svform $1} }
		(n) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/scan.ans} {sformat $1;@snf=[$1]} }
		(c) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/plist.ans} {pformat $1;@snf=[$1]} } 
		(q) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/whois.ans} {wformat $1;@fwhois=[$1]}}
		(m) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/public.ans} {pubformat $1}} 
		(r) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/dcc.ans} {dccformat $1}}
                (t) { if (![$1]) {scform.show} {scform $1} }
                (s) { if (![$1]) {cform.show} {cform $1} }
		(u) { if (![$1]) {qlogo.show} {qlogo $1} }
		(v) { if (![$1]) {abot.show} {abot $1}}
                (w) { if (![$1]) {mdform.show} {mdform $1}}
		(x) { if (![$1]) {ansiload $twiddle($HOME)$(loadpath)ans/dccbar.ans} {dbarformat $1}} 
		(*) { format }

	}
}{ load $twiddle($HOME)$(loadpath)ans/format.ans }


alias dbarformat {
	@dlimit=[2]
	if ([$0] > 2) {
		xecho -b dcc bar format number too high
	}{
		@dccbar=[$0]
		xecho -b dcc bar format set to $0
		}
}
alias mform if ([$0]) { 
	if (isnumber($0)&&[$0]<numitems(mform)]) {	
		^fset format_msg $getitem(mform $0) 
		echo $fparse(format_msg ! prophet knows@the.future.net hi!)
		xecho -b this is your new msg format, /fsave to save.
		@mform = [$0]
	}{ xecho -b please make a valid selection. }
}{
	mform.show
}

alias mform.load if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(mform)) {
                ^fset format_msg $getitem(mform $0) }
}

alias smform if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(smform)) {
                ^fset format_send_msg $getitem(smform $0)
                echo $fparse(format_send_msg ! prophet knows@the.future.net hi!)
                xecho -b this is your new msg format, /fsave to save.
		@smform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        smform.show
}

alias smform.load if ([$0]) {
        if (isnumber($0)]&&[$0]<numitems(smform)) {
                ^fset format_send_msg $getitem(smform $0)}
               }

alias mform.show {
	for (@mm=1, mm < numitems(mform), @mm++) { 
		^fset format_msg $getitem(mform $mm)			
		xecho -b $Cparse(%K[%n$mm%K]%n) $fparse(format_msg ! prophet knows@the.future.net hi.)}
	xecho -b /format g <number> to set msg format
	^eval xecho -b current format set to $(hwht)$mform
	^fset format_msg $getitem(mform $mform)}

alias smform.show {
        for (@mm=1, mm < numitems(smform), @mm++) {
                ^fset format_send_msg $getitem(smform $mm)
                xecho -b $Cparse(%K[%n$mm%K]%n) $fparse(format_send_msg ! prophet knows@the.future.net hi.)}
        xecho -b /format h <number> to set msg format
        ^eval xecho -b current format set to $(hwht)$smform
	^fset format_send_msg $getitem(smform $smform)}

alias ncomp if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(ncomp)) {
                ^fset format_nick_comp $getitem(ncomp $0)
                xecho -b $cparse("%K<%ncodelogic%K>%n") $fparse(format_nick_comp britch  hi!)
                xecho -b this is your new nick completion, /fsave to save.
		@ncomp = [$0]
        }{ xecho -b please make a valid selection. }
}{
        ncomp.show
}

alias ncomp.load if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(ncomp)) {
                ^fset format_nick_comp $getitem(ncomp $0)}
}

alias ncomp.show { 
	for (@nc=1, nc < numitems(ncomp), @nc++) {  
		^fset format_nick_comp $getitem(ncomp $nc)
		xecho -b $Cparse("%K[%n$([2]nc)%K]%n %K<%ncodelogic%K>%n") $fparse(format_nick_comp britch  hi!)}
	xecho -b /format p <number> to set nick completion
	^eval xecho -b current format set to $(hwht)$ncomp
}
alias echostr if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(echostr)) {
                ^set show_numerics_str $getitem(echostr $0)
		@G = getitem(echostr $0)
 		xecho -b this is your new echostr: $show_numerics_str
		xecho -b /fsave to save.
		@echostr = [$0]
	}{ xecho -b please make a valid selection. }

}{
	echostr.show
}
alias echostr.load if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(echostr)) {
                ^set show_numerics_str $getitem(echostr $0)
		@G=getitem(echostr $0)}
}

alias echostr.show {
fe ($jot(1 ${numitems(echostr)-1})) aa bb cc dd { 
	ce %K[%w$[2]aa%K]%n $getitem(echostr $aa)    %K[%w$[2]bb%K]%n $getitem(echostr $bb)    %K[%w$[2]cc%K]%n $getitem(echostr $cc)    %K[%w$[2]dd%K]%n $getitem(echostr $dd)
	}
xecho -b /format b <number> to set echostr 
^eval xecho -b current format set to $(hwht)$echostr
}
alias svform if ([$0]) {
	        if (isnumber($0)&&[$0]<numitems(sv)) {
		^fset format_version $getitem(sv $0)
		echo $fparse(format_version $J $uname(%s) $uname(%s) $uname(%r)  Tcl1.5)
		xecho -b this is your new version format
		@svform = [$0]
		xecho -b /fsave to save.
	}{ xecho -b please make a valid selection. }
}{
	sv.show
}
alias svform.load if ([$0]) {
	        if (isnumber($0)&&[$0]<numitems(sv)) {
		^fset format_version $getitem(sv $0)}
}

alias sv.show {
	for (@sv=1, sv < numitems(sv), @sv++) {
		^fset format_version $getitem(sv $sv)
		xecho -b $cparse(%K[%w$sv%K]%n) $fparse(format_version $J $uname(%s) $uname(%s) $uname(%r)  Tcl1.5)}
	xecho -b /format o <number> to set version format
        ^eval xecho -b current format set to $(hwht)$(svform)
		^fset format_version $getitem(sv $svform)
}

alias aform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(aformlp)) {
                @awayf1 = getitem(aformnopagenolog $0)
                @awayf2 = getitem(aformnopagelog $0)
                @awayf3 = getitem(aformpagenolog $0)
                @awayf4 = getitem(aformlp $0)
     		@aform = [$0]
                echo britch is away, bye. $awayf4
                xecho -b this is your new away format
                xecho -b /fsave to save.
        }{ xecho -b please make a valid selection. }
}{
        aform.show
}

alias aform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(aformlp)) {
                @awayf1 = getitem(aformnopagenolog $0)
                @awayf2 = getitem(aformnopagelog $0)
                @awayf3 = getitem(aformpagenolog $0)
                @awayf4 = getitem(aformlp $0)
               }}


alias aform.show {
        for (@aw=1, aw < numitems(aformlp), @aw++) {
                xecho -b $cparse(%K[%w$aw%K]%n) * britch is away, putt-putt. $getitem(aformlp $aw)} 
        xecho -b /format a <number> to set away format
	^eval xecho -b current format set to $(hwht)$aform
}


alias kform.show {
        for (@kc=1, kc < numitems(kform), @kc++) {
		xecho -b $cparse(%K[%w$kc%K]%n) $getitem(kform $kc) mirc sucks.}
	xecho -b /format l <number> to set kick format
	^eval xecho -b current format set to $(hwht)$kform
}

alias kform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(kform)) {
                if (_klogotog==[on]) {
		@kickr = getitem(kform $0)
                @bkickr = getitem(kbform $0)
                }{ 	
			@kickr=[]
			@bkickr=[]
		}
		echo $getitem(kform $0) mirc sucks.
                xecho -b this is your new kick format
                xecho -b /fsave to save.
		@kform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        kform.show
}

alias kform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(kform)) {
                @kickr = getitem(kform $0)
                @bkickr = getitem(kbform $0)}
}

alias iform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(bwall)) {
                ^fset format_bwall $getitem(bwall $0)
                xecho -b $fparse(format_bwall $Z codelogic #BitchX ! phear me.)
                xecho -b this is your new wall format
                xecho -b /fsave to save.
		@iform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        iform.show
}

alias iform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(bwall)) {
		^fset format_bwall $getitem(bwall $0)}
               }


alias iform.show {
        for (@bw=1, bw < numitems(bwall), @bw++) {
                ^fset format_bwall $getitem(bwall $bw)
		echo $cparse(%K[%n$(bw)%K]%n) $fparse(format_bwall $Z codelogic #BitchX ! phear.)}
	^fset format_bwall $getitem(bwall $iform)
        xecho -b /format d <number> to set wall format
        ^eval xecho -b current format set to $(hwht)$iform
}

alias nform if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(nform)) {
                ^fset format_notice $getitem(nform $0)
                echo $fparse(format_notice ! prophet knows@the.future.net hi!)
                xecho -b this is your new notice format, /fsave to save.
        	@nform = [$0]
	}{ xecho -b please make a valid selection. }
}{
        nform.show
}

alias nform.load if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(nform)) {
                ^fset format_notice $getitem(nform $0) }

}

alias nform.show {
        for (@nn=1, nn < numitems(nform), @nn++) {
                ^fset format_notice $getitem(nform $nn)
                xecho -b $Cparse(%K[%n$nn%K]%n) $fparse(format_notice ! prophet knows@the.future.net hi)}
        xecho -b /format e <number> to set notice format
        ^eval xecho -b current format set to $(hwht)$nform
        ^fset format_notice $getitem(nform $nform)}

alias snform if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(snform)) {
                ^fset format_send_notice $getitem(snform $0)
                echo $fparse(format_send_notice ! prophet knows@the.future.net hi!)
                xecho -b this is your new sent notice format, /fsave to save.
		@snform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        snform.show
}

alias snform.load if ([$0]) {
        if (isnumber($0)&&[$0]<numitems(snform)) {
                ^fset format_send_notice $getitem(snform $0)}
               }

alias snform.show {
        for (@sn=1, sn < numitems(snform), @sn++) {
                ^fset format_send_notice $getitem(snform $sn)
                xecho -b $Cparse(%K[%n$sn%K]%n) $fparse(format_send_notice ! prophet knows@the.future.net hi!)}
        xecho -b /format f <number> to set sent notice format
        ^eval xecho -b current format set to $(hwht)$snform
        ^fset format_send_notice $getitem(snform $snform)}

alias qform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(qform)) {
		^fset format_channel_signoff $getitem(qform2 $0)
                ^fset format_signoff $getitem(qform $0)
                xecho $fparse(format_signoff $Z codelogic #BitchX cypress, uNF)
                xecho -b this is your new signoff format
                xecho -b /fsave to save.
		@qform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        qform.show
}

alias qform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(qform)) {
		^fset format_channel_signoff $getitem(qform2 $0)
                ^fset format_signoff $getitem(qform $0)}
               }


alias qform.show {
        for (@qf=1, qf < numitems(qform), @qf++) {
                ^fset format_signoff $getitem(qform $qf)
                echo $cparse(%K[%n$(qf)%K]%n) $fparse(format_signoff $Z codelogic ! cypress, uNF)}
        ^fset format_signoff $getitem(qform $qform)
        xecho -b /format i <number> to set signoff format
        ^eval xecho -b current format set to $(hwht)$qform
}

alias jform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(jform)) {
                ^fset format_join $getitem(jform $0)
                xecho $fparse(format_join $Z codelogic clogic@cypress.telekinesis.org #BitchX)
                xecho -b this is your new join format
                xecho -b /fsave to save.
		@jform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        jform.show
}

alias jform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(jform)) {
                ^fset format_join $getitem(jform $0)}
               }


alias jform.show {
        for (@jf=1, jf < numitems(jform), @jf++) {
                ^fset format_join $getitem(jform $jf)
                echo $cparse(%K[%n$(jf)%K]%n) $fparse(format_join $Z codelogic clogic@cypress.telekinesis.org #BitchX goodbye!)}
        ^fset format_join $getitem(jform $jform)
        xecho -b /format j <number> to set join format
        ^eval xecho -b current format set to $(hwht)$jform
}

alias pform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(pform)) {
                ^fset format_leave $getitem(pform $0)
                xecho $fparse(format_leave $Z codelogic clogic@cypress.telekinesis.org #BitchX goodbye!)
                xecho -b this is your new part format
		@pform = [$0]
                xecho -b /fsave to save.
        }{ xecho -b please make a valid selection. }
}{
        pform.show
}

alias pform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(pform)) {
                ^fset format_leave $getitem(pform $0)}
               }


alias pform.show {
        for (@pf=1, pf < numitems(pform), @pf++) {
                ^fset format_leave $getitem(pform $pf)
                echo $cparse(%K[%n$(pf)%K]%n) $fparse(format_leave $Z codelogic clogic@cypress.telekinesis.org #BitchX goodbye!)}
        ^fset format_leave $getitem(pform $pform)
        xecho -b /format k <number> to set part format
        ^eval xecho -b current format set to $(hwht)$pform
}

alias scform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(scform)) {
                ^fset format_send_ctcp $getitem(scform $0)
                xecho $fparse(format_send_ctcp $Z void PING 897655002)
                xecho -b this is your new ctcp send format
                xecho -b /fsave to save.
		@scform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        scform.show
}

alias scform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(scform)) {
                ^fset format_send_ctcp $getitem(scform $0)}
               }


alias scform.show {
        for (@sc=1, sc < numitems(scform), @sc++) {
                ^fset format_send_ctcp $getitem(scform $sc)
                echo $cparse(%K[%n$(sc)%K]%n) $fparse(format_send_ctcp $Z void PING 897655002)}
        ^fset format_send_ctcp $getitem(scform $scform)
        xecho -b /format t <number> to set ctcp send format
        ^eval xecho -b current format set to $(hwht)$scform
}

alias cform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(cform)) {
                ^fset format_ctcp $getitem(cform $0)
                xecho $fparse(format_ctcp $Z void void@hellfire.liii.com codelogic VERSION)
                xecho -b this is your new ctcp format
                xecho -b /fsave to save.
		@cform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        cform.show
}

alias cform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(cform)) {
                ^fset format_ctcp $getitem(cform $0)}
               }


alias cform.show {
        for (@cf=1, cf < numitems(cform), @cf++) {
                ^fset format_ctcp $getitem(cform $cf)
                echo $cparse(%K[%n$(cf)%K]%n) $fparse(format_ctcp $Z void hellfire@liii.com codelogic VERSION)}
        ^fset format_ctcp $getitem(cform $cform)
        xecho -b /format s <number> to set ctcp format
        ^eval xecho -b current format set to $(hwht)$cform
}

alias qlogo.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(qlogo)) {
                @quitlogo = getitem(qlogo $0)}
               }

alias qlogo if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(qlogo)) {
                @quitlogo = getitem(qlogo $0)
                xecho $fparse(format_signoff $Z codelogic ! $quitlogo goodbye.)
		xecho -b this is your new quit logo.
                xecho -b /fsave to save.
                @qlogo = [$0]
        }{ xecho -b please make a valid selection. }
}{
        qlogo.show
}

alias qlogo.show {
        for (@ql=1, ql < numitems(qlogo), @ql++) {
                @quitlogo = getitem(qlogo $ql)
                xecho $cparse(%K[%n$(ql)%K]%n) $fparse(format_signoff $Z codelogic ! $quitlogo goodbye!)}
        @quitlogo = getitem(qlogo $qlogo)
        xecho -b /format u <number> to set quit logo
        xecho -b current format set to $(hwht)$qlogo
}

alias abot.show { 
	^local abotblah
	for (@ abotblah = 1, abotblah < numitems(abotform), @ abotblah++) {
		^fset +format_abot_show $getitem(abotform $abotblah)
		xecho -b $(hblk)[$(cl)$abotblah$(hblk)]$(cl) $botprompt $fparse(format_abot_show LlamaBot #botcentral)
	}
	xecho -b /format v <number> to set autobot format
	xecho -b current format is set to $(hwht)$abot
}

alias abot.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(qlogo)) {
                fset +format_autobot $getitem(abotform $0)
               }

alias abot if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(abotform)) {
		fset +format_autobot $getitem(abotform $0)
                xecho -b $botprompt $fparse(format_autobot LlamaBot #botcentral)}
                xecho -b this is your new autobot format.
                xecho -b /fsave to save.
                @ abot = [$0]
        }{ xecho -b please make a valid selection. }
}{
        abot.show
}

alias mdform if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(mdform)) {
                ^fset format_mode $getitem(mdform $0)
                xecho $fparse(format_mode $Z void blah #bitchx +o)
                xecho -b this is your new join format
                xecho -b /fsave to save.
		@mdform = [$0]
        }{ xecho -b please make a valid selection. }
}{
        mdform.show
}

alias mdform.load if ([$0]) {
                if (isnumber($0)&&[$0]<numitems(mdform)) {
                ^fset format_mode $getitem(mdform $0)}
               }


alias mdform.show {
        for (@md=1, md < numitems(mdform), @md++) {
                ^fset format_mode $getitem(mdform $md)
                echo $cparse(%K[%n$(md)%K]%n) $fparse(format_mode $Z void blah #bitchx +o)}
        ^fset format_mode $getitem(mdform $mdform)
        xecho -b /format w <number> to set mode format
        ^eval xecho -b current format set to $(hwht)$mdform
}

# .:. clogic '98