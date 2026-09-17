@ pubmax = 9
alias pubformat if ([$0]<=pubmax) {
switch ($0) {
	(1) {pub1;@pub=1;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(2) {pub2;@pub=2;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(3) {pub3;@pub=3;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(4) {pub4;@pub=4;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(5) {pub5;@pub=5;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(6) {pub6;@pub=6;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(7) {pub7;@pub=7;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(8) {pub8;@pub=8;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
	(9) {pub9;@pub=9;xecho -b publics format currently set to $(hwht)$(pub)$(cl);xecho -b /fsave to save.}
}}{
ansiload $twiddle($HOME)$(loadpath)/ans/public.ans
xecho -b please choose a valid number. 
}

alias pubload { 
switch ($0) {
        (1) {pub1;@pub=1}
        (2) {pub2;@pub=2}
        (3) {pub3;@pub=3}
        (4) {pub4;@pub=4}
        (5) {pub5;@pub=5}
	(6) {pub6;@pub=6}
	(7) {pub7;@pub=7}
        (8) {pub8;@pub=8}
	(9) {pub9;@pub=9}

}
}

alias pub1 {
^fset FORMAT_PUBLIC %@%K<%n$$1%K>%n $$3-
^fset FORMAT_PUBLIC_AR %@%K<%W$$1%K>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K\(%n$$1%K/%n$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K\(%W$$1%K/%W$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%c$$1%K:%c$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%W$$1%K:%c$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%K<%n$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K<%c$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_SEND_PUBLIC %@%K<%n$$2%K>%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%K<%n$$2%K:%n$$1%K>%n $$3-
}

alias pub2 {
^fset FORMAT_PUBLIC %@%K\(%n$$1%K\)%n $$3-
^fset FORMAT_PUBLIC_AR %@%K\(%W$$1%K\)%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K\(%n$$1%K:%n$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K\(%W$$1%n/%W$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%n$$1%K:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%W$$1%K:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%K\(%n$$1%K:%n$$2%K\)%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K\(%W$$1%K:%W$$2%K\)%n $$3-
^fset FORMAT_SEND_PUBLIC %@%K\(%n$$2%K\)%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%K\(%n$$2%K:%n$$1%K\)%n $$3-
}
alias pub3 {
^fset FORMAT_PUBLIC %@%K[%n$$1%K]%n $$3-
^fset FORMAT_PUBLIC_AR %@%K[%W$$1%K]%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K\(%n$$1%K/%n$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K\(%W$$1%K/%W$3%K\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%n$$1%K:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%W$$1%K:%W$$3%K-%n $4-
^fset FORMAT_PUBLIC_OTHER %@%K[%n$$1%K:%n$$2%K]%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K[%W$$1%K:%W$$2%K]%n $$3-
^fset FORMAT_SEND_PUBLIC %@%K[%n$$2%K]%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%K[%n$$2%K:$$1%n]%n $$3-
}

alias pub4 {
^fset FORMAT_PUBLIC %@%K<%n$$1%K>%n $$3-
^fset FORMAT_PUBLIC_AR %@%K<%W$$1%K>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K\(%n$$1%K/%n$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K\(%W$$1%K/%W$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%n$$1%K:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%W$$1%K:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%K<%n$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K<%W$$1%K:%W$$2%K>%n $$3-
^fset FORMAT_SEND_PUBLIC %@%K\(%c$$2%K\)%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%K\(%c$$2%K:%c$$1%K\)%n $$3-
}

alias pub5 {
^fset FORMAT_PUBLIC %@%c<%K$$1%c>%n $$3-
^fset FORMAT_PUBLIC_AR %@%c<%K$$1%c>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%c\(%K$$1%c/%K$$3%c\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%c\(%w$$1%c/%w$$3%c\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%c-%K$$1%c:%K$$3%c-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%c-%n$$1%c:%n$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%c<%K$$1%c:%K$$2%c>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%c<%n$$1%c:%n$$2%c>%n $$3-
^fset FORMAT_SEND_PUBLIC %@%c<%K$$2%c>%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%c<%K$$2%c:%K$$1%c>%n $$3-
}
 
alias pub6 {
^fset FORMAT_PUBLIC %@%K<%n$$1%K>%n $$3-
^fset FORMAT_PUBLIC_AR %@%K<%W$$1%K>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K\(%n$$1%K/%n$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K\(%W$$1%K/%W$$3%K\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%c$$1%K:%c$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%W$$1%K:%c$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%K<%n$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K<%c$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_SEND_PUBLIC %@$(c1)<%n$$2$(c1)>%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@$(c1)<%n$$2%K:%n$$1$(c1)>%n $$3-
}

alias pub7 {
^fset FORMAT_PUBLIC %@%B<%n$$1%B>%n $$3-
^fset FORMAT_PUBLIC_AR %@%B<%Y$$1%B>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%b\(%n$$1%K/%n$$3%b\)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%b\(%Y$$1%K/%Y$$3%b\)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%P$$1%K:%p$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%G$$1%K:%g$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%b<%n$$1%K:%n$$2%b>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%b<%y$$1%K:%n$$2%b>%n $$3-
^fset FORMAT_SEND_PUBLIC %@%P<%n$$2%P>%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%p<%n$$2%K:%n$$1%p>%n $$3-
}

alias pub8 {
^fset FORMAT_PUBLIC %@%K<$(c1)$$1%K>%n $$3-
^fset FORMAT_PUBLIC_AR %@%K<$(c2)$$1%K>%n $$3-
^fset FORMAT_PUBLIC_MSG %@%K($(c1)$1%K/%c$3%K)%n $$4-
^fset FORMAT_PUBLIC_MSG_AR %@%K($(c2)$1%K/%C$3%K)%n $$4-
^fset FORMAT_PUBLIC_NOTICE %@%K-%P$$1%K:%p$$3%K-%n $$4-
^fset FORMAT_PUBLIC_NOTICE_AR %@%K-%G$$1%K:%g$$3%K-%n $$4-
^fset FORMAT_PUBLIC_OTHER %@%K<$(c1)$$1%K:%c$$2%K>%n $$3-
^fset FORMAT_PUBLIC_OTHER_AR %@%K<$(c2)$$1%K:%n$$2%K>%n $$3-
^fset FORMAT_SEND_PUBLIC %@%m(%n$2%m)%n $$3-
^fset FORMAT_SEND_PUBLIC_OTHER %@%m\(%n$2%K:%n$1%m\)%n $$3-
}

alias pub9 {
^fset format_public %@%b<%n$$1%b>%n $$3-
^fset format_public_ar %@%b<%Y$$1%b>%n $$3-
^fset format_public_msg %@%b(%n$1%K/%n$3%b)%n $$4-
^fset format_public_msg_ar %@%b(%W$1%K/%W$3%b)%n $$4-
^fset format_public_notice %@%K-%P$$1%K:%p$$3%K-%n $$5-
^fset format_public_notice_ar %@%K-%P$$1%K:%p$$3%K-%n $$5-
^fset format_public_other %@%b<%n$$1%K:%n$$2%b>%n $$3-
^fset format_public_other_ar %@%b<%W$$1%K:%W$$2%b>%n $$3-
^fset format_send_public %@%p<%n$$2%p>%n $$3-
^fset format_send_public_other %@%p<%n$$2%K:%n$$1%p>%n $$3-
}