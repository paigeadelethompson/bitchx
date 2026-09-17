## pr0pz to shiftee for this, from oscz and codelogic for suggesting fparse :)

alias frelm {
   if ([$2]) {
    @ffrom = [$0]
    @fto   = [$1]
    @fmsg  = [$2-]
   ^userhost $0 -direct -cmd if ([$4]!=[<UNKNOWN>]) {
   say $fparse(format_msg $Z $0 $3@$4 )$fmsg
   }{
      echo $(hblk)$0$(cl) isn't on IRC right now.
   }
}{eval echo $(hblk)\($(hwht)usage$(hblk))$(hwht):$(cl) /frelm $(hblk)[$(cl)fake nick$(hblk)] [$(cl)nick$(hblk)/$(cl)channel to send to$(hblk)] [$(cl)fake msg$(hblk)]$(cl)}
}

alias freln {
   if ([$2]) {
    @ffrom = [$0]
    @fto   = [$1]
    @fnot  = [$2-]
   userhost $0 -direct -cmd if ([$4]!=[<UNKNOWN>]) {
	say $fparse(format_notice $Z $0 $3@$4 )$fnot
   }{
      echo $(hblk)$0$(cl) isn't on IRC right now.
   }
}{eval echo $(hblk)\($(hwht)usage$(hblk))$(hwht):$(cl) /freln $(hblk)[$(cl)fake nick$(hblk)] [$(cl)nick$(hblk)/$(cl)channel to send to$(hblk)] [$(cl)fake notice$(hblk)]$(cl)}
}