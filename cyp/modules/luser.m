## stolen from argon cause of sheer leetness.
 
on ^001 * #
on ^002 * #
on ^003 * #
on ^004 * {
  @ _lu.v = [$2]}
on ^251 * {
  echo   $(hwht)s$(cl)tatistics for $(c1)$S
  echo  $(hwht)ÚÄ$(cl)ÄÄ$(c1)Ä$(cl)ÄÄ$(hwht)Ä$(cl)Ä$(c1)Ä$(hblk)-                   --            -
  ^on ^raw_irc "$S % $N :Highest connection count*" {
    @ _lu.lum = _lu.um = []
    ^shook 266 0 0 0 0 0 0 0}
  @ _lu.u = [$3] + [$6]
  @ _lu.i = [$6]
  @ _lu.s = [$9]}
on ^252 * {
  @ _lu.o = [$1]}
on ^254 * {
  @ _lu.c = [$1]}
on ^255 * {
  @ _lu.lu = [$3]
  @ _lu.ls = [$6]}
on ^265 * {
  @ _lu.lum = [$6]}
on ^266 * {
  ^on ^raw_irc -"$S % $N :Highest connection count*" #
  @ _lu.um = [$6]
  ^set floating_point_math_var on
  echo $(hblk)[$(c2)³$(hblk)] $(c2)g$(c1)lobal users$(hblk).. $(cl)$[6]_lu.u ${_lu.um?[$(cl)max$(c.hk).. $(cl)$[6]_lu.um ]:}$(c1)\($(cl)$_lu.i invisible, $_lu.o operators$(c1)\)
  echo $(hblk)[$(c1)³$(hblk)] $(c2)l$(c1)ocal users$(hblk)... $(cl)$[6]_lu.lu ${_lu.lum?[$(cl)max$(c.hk).. $(cl)$[6]_lu.lum ]:}$(c1)\($(cl)$trunc(1 ${100 * _lu.lu / _lu.u})\%$(c1)\)
  echo $(hblk)[$(c1)³$(hblk)] $(c2)s$(c1)ervers$(hblk)....... $(cl)$[6]_lu.s $(c1)\($(cl)$trunc(1 ${_lu.u / _lu.s}) avg users per server$(c1)\)
  echo $(hblk)[$(c1)³$(hblk)] $(c2)c$(c1)hannels$(hblk)...... $(cl)$[6]_lu.c $(c1)\($(cl)$trunc(1 ${_lu.u / _lu.c}) avg users per channel$(c1)\)
  echo  $(c1)ÀÄ$(cl)Ä$(hblk)-                           Ä   -     -Ä$(cl)
 }