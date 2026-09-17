
## the paste, relm, reln, relsm, relsn command now does number-number like /relw 1-10 thanks to krecca

alias paste relw
on #-msg 33 * if (relayw==[ON]) {
	if (numitems(rmesg)>=10) {@ delitem(rmesg 0)}	
	@ setitem(rmesg $numitems(rmesg) $fparse(format_msg $Z $0 $userhost() )$1-)}	

  
alias relm {
	if (![$0]) {@ relayw = [OFF]
		for (@yy=0, yy<numitems(rmesg), @yy++)
	{echo $(hblk)[$(hwht)$(yy)$(hblk)] $getitem(rmesg $yy)}
}
        input "$(hblk)[$(cl)enter which line(s) to paste$(hblk)]$(cl): " {                         
                                                                                                   
                fe ($*) xx {                                                                       
                        @ aa = substr("-", $xx)                                                    
                        if ( aa != -1 )                                                         
                        {                                                                          
                                @start = left( ${aa-2} $xx )                                       
                                @end = mid( ${aa+1} ${ strlen($xx)}   $xx )                        
                        }                                                                          
                        {                                                                          
                                @start = xx                                                        
                                @end = xx                                                          
                        }                                                                          
                        for (@cc=start,cc<=end, @cc++)                                             
                        {                                                                          
                                ^say $getitem(rmesg $cc);                                           
                                                                                           
                        }                                                                          
                }                                                                                  
          @relayw=[ON]                                                                             
        }                             
}
	

on #-notice 22 * if (relayw==[ON]) {
	if (numitems(rnot)>=10) {@ delitem(rnot 0)}	
	@ nottxt = [$1-]
	@ setitem(rnot $numitems(rnot) $fparse(format_notice $Z $0 $userhost() $1-))}
  
alias reln {
	if (![$0]) {@ relayw = [OFF]
		for (@cc=0, cc<numitems(rnot), @cc++)
	{echo $(hblk)[$(hwht)$(cc)$(hblk)] $getitem(rnot $cc)}
}
        input "$(hblk)[$(cl)enter which line(s) to paste$(hblk)]$(cl): " {                         
                                                                                                   
                fe ($*) xx {                                                                       
                        @ aa = substr("-", $xx)                                                    
                        if ( aa != -1 )                                                         
                        {                                                                          
                                @start = left( ${aa-2} $xx )                                       
                                @end = mid( ${aa+1} ${ strlen($xx)}   $xx )                        
                        }                                                                          
                        {                                                                          
                                @start = xx                                                        
                                @end = xx                                                          
                        }                                                                          
                        for (@cc=start,cc<=end, @cc++)                                             
                        {                                                                          
                                ^say $getitem(rnot $cc);                                           
                                                                                          
                        }                                                                          
                }                                                                                  
          @relayw=[ON]                                                                             
        }                             
}

	
  
^on #-send_msg 33 * if (relayw==[ON]) {
	if (numitems(smsg)>=10) {@ delitem(smsg 0)}
	@ setitem(smsg $numitems(smsg) $fparse(format_send_msg $Z $0 $userhost($N) $1-))}



alias relsm {
	if (![$0]) {@ relayw = [OFF]
		for (@zz=0, zz<numitems(smsg), @zz++)
	{echo $(hblk)[$(hwht)$(zz)$(hblk)] $getitem(smsg $zz)}
}
        input "$(hblk)[$(cl)enter which line(s) to paste$(hblk)]$(cl): " {                         
                                                                                                   
                fe ($*) xx {                                                                       
                        @ aa = substr("-", $xx)                                                    
                        if ( aa != -1 )                                                         
                        {                                                                          
                                @start = left( ${aa-2} $xx )                                       
                                @end = mid( ${aa+1} ${ strlen($xx)}   $xx )                        
                        }                                                                          
                        {                                                                          
                                @start = xx                                                        
                                @end = xx                                                          
                        }                                                                          
                        for (@cc=start,cc<=end, @cc++)                                             
                        {                                                                          
                                ^say $getitem(smsg $cc);                                           
                                                                                           
                        }                                                                          
                }                                                                                  
          @relayw=[ON]                                                                             
        }                             
}




on #-send_notice 33 * if (relayw==[ON]) {
	if (numitems(snot)>=10) {@ delitem(snot 0)}	
	@ setitem(snot $numitems(snot) $fparse(format_send_notice $Z $0 ! $1-))}	




alias relsn {
	if (![$0]) {@relayw=[OFF]
		for (@dd=0, dd<numitems(snot), @dd++)
	{echo $(hblk)[$(hwht)$(dd)$(hblk)] $getitem(snot $dd)}
}

        input "$(hblk)[$(cl)enter which line(s) to paste$(hblk)]$(cl): " {                         
                                                                                                   
                fe ($*) xx {                                                                       
                        @ aa = substr("-", $xx)                                                    
                        if ( aa != -1 )                                                         
                        {                                                                          
                                @start = left( ${aa-2} $xx )                                       
                                @end = mid( ${aa+1} ${ strlen($xx)}   $xx )                        
                        }                                                                          
                        {                                                                          
                                @start = xx                                                        
                                @end = xx                                                          
                        }                                                                          
                        for (@cc=start,cc<=end, @cc++)                                             
                        {                                                                          
                                ^say $getitem(snot $cc);                                           
                                                                                           
                        }                                                                          
                }                                                                                  
          @relayw=[ON]                                                                             
        }                             
}


## shade/psykotyks argon idea.

on #-window 33 * if (relayw==[ON]&&[$0]==winnum()) {
	if (numitems(_foo)>=winsize()) {@ delitem(_foo 0)}	
	@ setitem(_foo $numitems(_foo) $1-)}	


## shade did most of this. 
@ relayw = [ON]
alias relw {                                                                                       
        if (![$0]) {                                                                               
          @ relayw = [OFF]                                                                         
          for (@xx=0, xx<numitems(_foo), @xx++)                                                    
          {                                                                                        
            echo $(hblk)[$(hwht)$xx$(hblk)]$(cl) $getitem(_foo $xx)                                
          }                                                                                        
        }                                                                                          
        input "$(hblk)[$(cl)enter which line(s) to paste$(hblk)]$(cl): " {                         
                                                                                                   
                fe ($*) xx {                                                                       
                        @ aa = substr("-", $xx)                                                    
                        if ( aa != -1 )                                                         
                        {                                                                          
                                @start = left( ${aa-2} $xx )                                       
                                @end = mid( ${aa+1} ${ strlen($xx)}   $xx )                        
                        }                                                                          
                        {                                                                          
                                @start = xx                                                        
                                @end = xx                                                          
                        }                                                                          
                        for (@cc=start,cc<=end, @cc++)                                             
                        {                                                                          
                                ^say $getitem(_foo $cc);                                           
                                                                                           
                        }                                                                          
                }                                                                                  
          @relayw=[ON]                                                                             
        }                             
}
