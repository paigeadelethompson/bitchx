on -idle * if ([$0]!=0) { if ([$0] == awayt && !awaystat && togaway != [OFF]) {away autoaway after $0 min
	xecho -b auto set away after $0 minutes}}

on #-connect 1 * if (awaystat) {
        //away $awaymsg}

/* my first idea */

alias away {
	@ awaystat = 1
	@ awaytime = time()
        @ awaymsg = [$0]?[$*]:[$awayr]
        if (showaway!=[off]) {
	mme is gone.. $(awaymsg) $getlp()}
        //away is gone.. $(awaymsg) $getlp()
	@ awaytime = time()
	
			
}

alias getblogo if ([$0]) {
	switch ($0) {
		(1) {@ blogo = [..\[gone/$msar(gÿyÿyÿmÿmÿsÿsÿhÿhÿdÿdÿ$tr(/ÿ//$timediff))\]]}
		(2) {@ blogo = [gone\[$timediff\]]}
		(3) {@ blogo = [\[gone.$timediff\]]}
		(4) {@ blogo = [..gone\($timediff\)]}
		(5) {@ blogo = [gone/$(timediff)]}
		(6) {@ blogo = [\[gone!$(timediff)\]]}
		(7) {@ blogo = [Gone $timediff]}
		(8) {@ blogo = [..[gone/$msar(gÿyÿyÿmÿmÿsÿsÿhÿhÿdÿdÿ$tr(/ÿ//$timediff))]}
		(9) {@ blogo = [\($timediff\)]}
		(10) {@ blogo = [\($sar(g/ //$timediff)\)]}
		(11) {@ blogo = [<$sar(g/ //$timediff)>]}
}}

alias back if (A) {
	@ awaystat = [$0]
	@ backmsg = [$0]?[$*]:[$backr]
	@ backtime = time()
	if (awaytime > 0) {
	@ timediff = tdiff2(${backtime - awaytime})
	getblogo $aform
	//back
	if (showaway!=[off]) {
	mme has returned.. $(backmsg) $blogo}
        input "read away log? [y|n]: " if ([$0]==[Y]) {readlog}}
	@ blogo = []

}{xecho -b you are not away..}

alias awaytime if ([$0]) {
		@ awayt = [$0]  
                xecho -b cypress awaytime set to $(hwht)$awayt
                } else {
                xecho -b cypress awaytime set to $(hwht)$awayt}

alias awaymsg if ([$0]) {
                @ awayr = [$*]
                xecho -b cypress away reason set to $(cl)"$awayr"
 		} else {
                xecho -b cypress away reason set to $(cl)"$awayr"}


alias backmsg if ([$0]) {
                @backr = [$*]
                xecho -b cypress back reason set to $(cl)"$backr"
                } else {
                xecho -b cypress back reason set to $(cl)"$backr"}

alias showaway if ([$0]) {
	if ([$0]==[ON]) { @ showaway = [ON] 
	} else { @ showaway = [OFF] }
	xecho -b cypress public aways are set to $(cl)"$showaway"
	}		


alias awaytog {
         if ([$0]==[ON] || [$0]==[OFF]) {
                 xecho -b cypress away toggle is set to $(cl)"$0"
                 @togaway = [$*] 
	}{
                 xecho -b valid choices are ON or OFF
         }
 }
alias _awayl if ([$0]) {
        if ([$0]==[ON]) { @ awayl = [ON]
        } else { @ awayl = [OFF] }
        xecho -b cypress away logging is set to $(cl)"$awayl"
        }               

