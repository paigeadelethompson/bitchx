## fully functional encryption, not very secure, excuse my laziness.

@eprompt = [$(hblk)[$(hwht)e$(cl)ncrypted$(hblk)]$(cl)]

alias esay2 if ([$0]) {
@ :chan = C
@ :text = [$*]
^quote PRIVMSG $chan :SED [C] $encode($text)
echo $fparse(format_send_public ! ! $N $eprompt $text)
}

alias emsg2 if ([$1]) {
@ :nick = [$0]
@ :text = [$1-]
^quote PRIVMSG $nick :SED [C] $rot13($encode($text-))
echo $fparse(format_send_msg ! $0 ! $eprompt $text)
}

on ^raw_irc "% PRIVMSG % :SED [C] *" {
@ :text = [$5-]
@ :sender = before(! $0)
@ :dest = [$2]
^xecho -b $eprompt $(hblk)<$(cl)$sender$(hblk)->$(cl)$dest$(hblk)>$(cl) $decode($text)
}

# .:. clogic '98