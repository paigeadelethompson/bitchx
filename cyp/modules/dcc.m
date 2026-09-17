### shiftee's is better so I took it :)

### based on embryonic's dcc module =)

### suicide's percent bar
alias fixmeter if (isdigit($0)) {
        @ fixp = [$0]
	@ hc1 = hcyn
if (fixp < 10) {return $(hblk)±°°°°°°°°°°$(cl)}
if ((fixp < 20)&& (fixp >= 10)) {return $(hblk)±²°°°°°°°°°$(cl)}
if ((fixp < 30)&& (fixp >= 20)) {return $(hblk)±²Û°°°°°°°°$(cl)}
if ((fixp < 40)&& (fixp >= 30)) {return $(hblk)±²Û$cparse($(c1)²)$(hblk)°°°°°°°$(cl)}
if ((fixp < 50)&& (fixp >= 40)) {return $(hblk)±²Û$cparse($(c1)²±)$(hblk)°°°°°°$(cl)}
if ((fixp < 60)&& (fixp >= 50)) {return $(hblk)±²Û$cparse($(c1)²±°)$(hblk)°°°°°$(cl)}
if ((fixp < 70)&& (fixp >= 60)) {return $(hblk)±²Û$cparse($(c1)²±°°)$(hblk)°°°°$(cl)}
if ((fixp < 80)&& (fixp >= 70)) {return $(hblk)±²Û$cparse($(c1)²±°°°)$(hblk)°°°$(cl)}
if ((fixp < 90)&& (fixp >= 80)) {return $(hblk)±²Û$cparse($(c1)²±°°°°)$(hblk)°°$(cl)}
if ((fixp < 100)&& (fixp >= 90)) {return $(hblk)±²Û$cparse($(c1)²±°°°°°)$(hblk)°$(cl)} 
if ((fixp < 110)&& (fixp >= 100)) {return$(hblk)±²Û$cparse($(c1)²±°°°°°) $(cl)}
}


on ^dcc_header * {
	@dnum = [$0]
	@ty = [$1]
	@num = [$2]
	@status = [$3]
	@kbs = [$4]
	@file = [$5]
if (dccbar == 1) {
xecho   $cparse($(c1)ÚÄÄÄÄÄÄÄÄÄÄÄ)$(hblk)----$cparse($(c1)ÄÄÄÄÄÄÄÄ)$(hblk)-$cparse($(c1)ÄÄ)$(hblk)-$cparse($(c1)ÄÄÄÄÄÄ-)$(hblk)ÄÄ-ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ        Ä
xecho  $(hblk)[$cparse($(c1)³)$(hblk)]$(cl) #   type   nick        status   complete     perc  kb$(hblk)/$(cl)s      file 
}

if (dccbar == 2) {

	xecho  $(hwht)ÚÄÄ$(cl)Ä$(hwht)-$(cl)- $(hblk)-$(cl)    ú$(cl)ú$(hblk)--$(cl)ÄÄ$(hblk)ÄÄÄÄ$(cl)ÄÄ$(hblk)Ä$(cl)ÄÄÄ$(hblk)ÄÄÄ$(cl)ÄÄÄÄÄÄ$(hblk)Ä$(cl)ÄÄÄÄÄÄÄ$(hwht)ÄÄ$(cl)ÄÄ$(hwht)ÄÄÄÄ$(cl)ÄÄ$(hwht)ÄÄ$(cl)ÄÄÄÄ$(hwht)ÄÄÄÄÄ$(cl)ÄÄ$(hwht)ÄÄ¿
	xecho $(cl) ³ $(hblk)[$(hcyn)t$(cyn)ype$(hblk) ] [$(hcyn)n$(cyn)ick$(hblk)      ] [$(hcyn)c$(cyn)omplete$(hblk)          ] [$(hcyn)f$(cyn)ile $(hblk)          ] [$(hcyn)k$(cyn)b/s $(hblk)]$(cl) ³
}

}

on ^dcc_post * {
if (dccbar == 1) {
	xecho  $(hblk) À---Ä-Ä-ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
}
if (dccbar == 2) {
	xecho $(hblk) ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
}
}
on ^dcc_stat * {
	@cnum = [$0]
	@ctype = [$1]
	@cuser = [$2]
	@cstatus = [$3]
	@cna = [$4]
	@cdes = [$5]
	@cen = [$6]	
if (dccbar == 1) {
        _decho $cnum $ctype $cuser $cstatus $cna $cdes 
}

if (dccbar == 2) {
	_decho $cnum $ctype $cuser $cstatus $cna $cdes 
}
}

alias _decho {
if (dccbar == 1) {
	if ([$5]==[chat]) {
	echo  $(hblk)[$cparse($(c1)³)$(hblk)]$(cl) $[2]0  $[5]1  $[9]2   $[20]3 $[7]4      
	}{
	echo  $(hblk)[$cparse($(c1)³)$(hblk)]$(cl) $[2]0  $[5]1  $[9]2   $[20]3 $[7]4       $5
	}
}
if (dccbar == 2) {
	if ([$5]==[chat]) {
	echo  $(hblk)³ [$(cl)$[5]1$(hblk)] [$(cl)$[9]2$(hblk) ] [$(cl)$[18]3$(hblk)] [$(cl)$[15]4$(hblk)]         ³
	}{
	echo  $(hblk)³ [$(cl)$[5]1$(hblk)] [$(cl)$[9]2$(hblk) ] [$(cl)$[18]3$(hblk)] [$(cl)$[15]5$(hblk)] [$(cl)$4 $(hblk) ] ³
	}
}
}

alias _decho2 {
if (dccbar == 1) {
        echo  $(hblk)[$cparse($(c1)³)$(hblk)]$(cl) $[2]0  $[5]1  $[9]2   $[6]3   $fixmeter($[7]4)  $[3]7   $[5]5   $6 
}
if (dccbar == 2) {
        echo  $(hblk)³ [$(cl)$[5]0$(hblk)] [$(cl)$[9]1$(hblk) ] [$(cl)$[7]fix.size($2)$(hblk)/$(cl)$[7]fix.size($3) $(hblk)  ] [$(cl)$[15]4$(hblk)] [$(cl)$[5]5$(hblk)] $(cl)³   
}

}

on ^dcc_statf * {
	@dfnum = [$0]
	@dtype = [$1]
	@duser = [$2]
	@dstatus = [$3]
	@dkb = [$4]
	@ddes = [$5]
	@den = [$6]
}


on ^dcc_statf1 * {
	@perc = [$before(. $0)%]
	@bt = [$1]
	@totf = [$2]
	@min = [$3]
	@sec = [$4]
if (dccbar == 1) {
        _decho2 $dfnum $dtype $duser $dstatus $perc $dkb $ddes $perc
}
if (dccbar == 2) {
	_decho2 $dtype $duser $bt $totf $ddes $dkb 
	
}
}

on #-dcc_request " *  {
	@dccnick = [$0]
	@dccfile = [$5]
	@dcctype = [$1]
	if (dcctype==[GET]) {
	xecho -b cypress press ctrl-T to accept file or ctrl-R to reject}
}
alias dcc.get {
/dcc get $dccnick
 }
alias dcc.rej {
/dcc close get $dccnick
}