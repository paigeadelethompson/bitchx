
alias sbcolor {
@ :clear = cl
@ :blue = blu
@ :green = grn
@ :cyan = cyn
@ :red = red
@ :magenta = mag
@ :yellow = yel
@ :white = wht
@ :hblack = hblk
@ :hblue = hblu
@ :hgreen = hgrn
@ :hcyan = hcyn
@ :hred = hred
@ :hmagenta = hmag
@ :hyello = hyel
@ :hwhite = hwht
@ :bwhite = bwht
@ :bmagenta = bmag
@ :bblue = bblu
@ :bred = bred
@ :bblack = bblk
@ :bgreen = bgrn
@ :byellow = byel
@ :bcyan = bcyn
	if ([$0]) {@ sc1 = [$($0)]}
        if ([$1]) {@ sc2 = [$($1)]}
        if ([$2]) {@ sc3 = [$($2)]}
        if ([$3]) {@ sc4 = [$($3)]}
^xecho -b $scriptname usage $(cyn):$(cl) /sbcolor color1 color2 color3 color4
^xecho -b color statbar config set to $(sc1)color1 $(sc2)color2 $(sc3)color3 $(sc4)color4
^xecho -b available colors $(cyn): $(cl)clear $(blu)blue $(grn)green $(cyn)cyan $(red)red $(mag)magenta $(yel)yellow $(wht)white 
^xecho -b $(hblk)hblack $(hblu)hblue $(hgrn)hgreen $(hcyn)hcyan $(hred)hred $(hmag)hmagenta $(hyel)hyello $(hwht)hwhite $(bwht)bwhite
^xecho -b $(bmag)bmagenta$(cl) $(bblu)bblue$(cl) $(bred)bred$(cl) $(bblk)bblack$(cl) $(byel)byellow$(cl) $(bcyn)bcyan$(cl)
^eval ^load $twiddle($HOME)$(loadpath)stats/$statbar
}