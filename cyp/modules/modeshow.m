alias vocop {
	if ([$0]==[ON] || [$0]==[OFF]) {
		@showop = [$0]
		xecho -b showing <$(c5)@$(cl)nick> and <$(c5)+$(cl)nick> in public set to $0 
		}{
			xecho -b modeshow value set to $showop
		}
}
	


on ^public * {
	if (ischanop($0 $1) && showop == [on]) {
		echo $fparse(format_public 1 $(c5)@$(cl)$0 3 $2-)
		}
		if (!ischanop($0 $1) && !isvoice($1 $0) && showop != [off]) {
			echo $fparse(format_public 1 $0 3 $2-)
			}
			if (showop == [off]) {
                                echo $fparse(format_public 1 $0 3 $2-)
                        }      
			if (isvoice($1 $0) && showop == [on] && !ischanop($0 $1)) {
				echo $fparse(format_public 1 $(c5)+$(cl)$0 3 $2-)		
				}
}

on ^public_other * {
	if (ischanop($0 $1) && showop == [on]) {
		echo $fparse(format_public_other 1 $(c5)@$(cl)$0 $1 $2-)
		}
		if (!ischanop($0 $1) && !isvoice($1 $0) && showop != [off]) {
			echo $fparse(format_public_other 1 $0 $1 $2-)
			}
	
		if (showop == [off]) {
                                echo $fparse(format_public_other 1 $0 $1 $2-)
                        }      	
		if (isvoice($1 $0) && showop == [on] && !ischanop($0 $1)) {
				echo $fparse(format_public_other 1 $(c5)+$(cl)$0 $1 $2-)		
				}
}

on ^send_public * {
	if (ischanop($N $0) && showop == [on]) {
		echo $fparse(format_send_public 1 2 $(c5)@$(cl)$N $1-)
		}
		if (!ischanop($N $0) && !isvoice($0 $N) && showop != [off]) {
			echo $fparse(format_send_public 1 2 $N $1-)
			
			}
			if (showop == [off]) {
				echo $fparse(format_send_public 1 2 $N $1-)
			}
			if (isvoice($0 $N) && showop == [on]  && !ischanop($N $0)) {
				echo $fparse(format_send_public 1 2 $(c5)+$(cl)$N $1-)		
				}
}

on ^public_ar * {
	if (ischanop($0 $1) && showop == [on]) {
		echo $fparse(format_public_ar 1 $(c5)@$(cl)$0 3 $2 $3-)
		}
		if (!ischanop($0 $1) && !isvoice($1 $0) && showop != [off]) {
			echo $fparse(format_public_ar 1 $0 3 $2 $3-)
			}
			if (showop == [off]) {
                                echo $fparse(format_public_ar 1 $0 3 $2 $3-)
                        }      
			if (isvoice($1 $0) && showop == [on] && !ischanop($0 $1)) {
				echo $fparse(format_public_ar 1 $(c5)+$(cl)$0 3 $2 $3-)		
				}
}

on ^public_other_ar * {
	if (ischanop($0 $1) && showop == [on]) {
		echo $fparse(format_public_other_ar 1 $(c5)@$(cl)$0 $1 $2 $3-)
		}
		if (!ischanop($0 $1) && !isvoice($1 $0) && showop != [off]) {
			echo $fparse(format_public_other_ar 1 $0 $1 $2 $3-)
			}
	
		if (showop == [off]) {
                                echo $fparse(format_public_other_ar 1 $0 $1 $2 $3-)
                        }      	
		if (isvoice($1 $0) && showop == [on] && !ischanop($0 $1)) {
				echo $fparse(format_public_other_ar 1 $(c5)+$(cl)$0 $1 $2 $3-)		
				}
}
