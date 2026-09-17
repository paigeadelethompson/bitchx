alias plist cdcc plist 

alias pformat {
	switch ($0) {
	(1) {/cdcc1}    
	(2) {/cdcc2}	
	(3) {/cdcc3}
	(4) {/cdcc4}
	(5) {/cdcc5}
	(6) {/cdcc6}
	(7) {/cdcc7}
	}
xecho -b cypress cdcc plist format is currently set to $(plistf)
xecho -b type /save to save formats
}

alias cdcc1 {
@ plistf = 1
	^on ^cdcc_prepack * {
	fix.cdcc $0 $1	::\;., \[cypress/cdcc]$[-2]3 pack\(s) offered total.] ,.\;::
	}
	^on ^cdcc_note * {
	fix.cdcc $0 $1		-^  $2- 
	}
^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 ::\;., [% leeched $fix.size($lsize) / top speed $fix.size($8) %] ,.\;::

}

}
alias cdcc2 {
@ plistf = 2
^on ^cdcc_prepack * {
fix.cdcc $0 $1	..:\; (cypress.cdcc) $[-2]3 pack(s) offered total. )\;:..
} 
^on ^cdcc_note * {
fix.cdcc $0 $1		^  $2- 
}

^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 ..:\; \(! leeched $fix.size($lsize) / top speed $fix.size($8) !) \;:..
}

}

alias cdcc3 {
@ plistf = 3
^on ^cdcc_prepack * {
fix.cdcc $0 $1	.,\;\;: <cypress!cdcc> $[-2]3 pack(s) offered total.> :\;\;,.
} 
^on ^cdcc_note * {
fix.cdcc $0 $1		-^  $2- 
}

^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 .,\;\;: <% leeched $fix.size($lsize) / top speed $fix.size($8) %> :\;\;,.
}

}

alias cdcc4 {
@ plistf = 4
^on ^cdcc_prepack * {
fix.cdcc $0 $1 ..[cyp/cdcc].. $[-2]3 total pack(s) offered
}
^on ^cdcc_note * {
fix.cdcc $0 $1		ÀÄÄ> $2-
}
^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 ..[cyp/cdcc].. stats\(top speed[$fix.size($8)] ! leeched[$fix.size($lsize)])
}
}

alias cdcc5 { 
@ plistf = 5
^on ^cdcc_prepack * {
fix.cdcc $0 $1 [cdcc] $[-2]3 file(s) offered- /ctcp $N cdcc send #x for pack #x
}
^on ^cdcc_note { 
fix.cdcc $0 $1     $2-
}
^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 [cdcc] stats: top speed/$fix.size($8) % leeched/$fix.size($lsize)
}
}

alias cdcc6 {
@ plistf = 6
^on ^cdcc_prepack * {
fix.cdcc $0 $1 \(cyp.cdcc\) files offered! /ctcp $N cdcc help for help!
}
^on ^cdcc_pack * {
@ lsize = [$4]
fix.cdcc $0 $1 \($sar(g/././$strip( $fix.size($lsize)))[$[2]strip( $5) gets]\) $6-
}
^on ^cdcc_note * {
fix.cdcc $0 $1  ^-.  $2-
}
^on ^cdcc_postpack * {
@ lsize = [$9]
@ tspeed = [$8]
fix.cdcc $0 $1 \(cdcc.stats\) [leeched/$sar(g/././$strip( $fix.size($lsize))) . top speed/$sar(g/././$strip( $fix.size($8)))]
}}

alias cdcc7 {
@ plistf = 7
^on ^cdcc_prepack * {
fix.cdcc $0 $1 ..[cyp/cdcc\($[-1]3 packs/$strip( $fix.size($12)) total\)]..
}
^on ^cdcc_pack * {
@ :filesize = strip( $fix.size($4))
@ :gets = [$[2]5]
@ :packnum = [$2]
fix.cdcc $0 $1 [#$(packnum)\($(gets) gets\) $filesize]: $6-
}
^on ^cdcc_note * { 
fix.cdcc $0 $1		- $2-
}
^on ^cdcc_postpack * { 
@ :sent = strip( $fix.size($8))
@ :fastest = strip( $fix.size($7)) 
fix.cdcc $0 $1 ..[cyp/cdcc\($sent sent/$fastest top speed\)]..
}}
 
alias s {if ([$0]) {
        if ([$1]) {ctcp $0 cdcc send #$1
        }{
         ctcp $0 cdcc list
}

}}

alias x {if ([$0]) {
        if ([$1]) {ctcp $0 xdcc send #$1
        }{
         ctcp $0 xdcc list
}

}}