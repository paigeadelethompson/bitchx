alias color {
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
	if ([$0]) {@ c1 = [$($0)]}
        if ([$1]) {@ c2 = [$($1)]}
        if ([$2]) {@ c3 = [$($2)]}
        if ([$3]) {@ c4 = [$($3)]}
	if ([$4]) {@ c5 = [$($4)]}
^xecho -b $scriptname usage $(cyn):$(cl) /color color1 color2 color3 color4 modeshow color: color5
^xecho -b color config set to $(c1)color1 $(c2)color2 $(c3)color3 $(c4)color4 $(c5)color5
^xecho -b available colors $(cyn): $(cl)clear $(blu)blue $(grn)green $(cyn)cyan $(red)red $(mag)magenta $(yel)yellow $(wht)white 
^xecho -b $(hblk)hblack $(hblu)hblue $(hgrn)hgreen $(hcyn)hcyan $(hred)hred $(hmag)hmagenta $(hyel)hyello $(hwht)hwhite $(bwht)bwhite
^xecho -b $(bmag)bmagenta$(cl) $(bblu)bblue$(cl) $(bred)bred$(cl) $(bblk)bblack$(cl) $(byel)byellow$(cl) $(bcyn)bcyan$(cl)
^eval ^load $twiddle($HOME)$(loadpath)stats/$statbar
^eval pubload $pub
^eval ^load $twiddle($HOME)$(loadpath)sc/scan.$snf
}