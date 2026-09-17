alias randcl {
	
	
	^local rcl.
	@ rcl.0 = [ should of put the glock down.]
	@ rcl.1 = [ hot damn, I didn't want to kill a man.]
	@ rcl.2 = [ check me and I'll check ya back.]
	@ rcl.3 = [ put the blunt down just for a minute]
	@ rcl.4 = [ tried to jack me, my homie got shot.]
	@ rcl.5 = [ insane in the membrane]
	@ rcl.6 = [ slow hits from the bong]		 	
	@ rcl.7 = [ k-leet]
	@ rcl.8 = [ hello my name is dr. greenthumb]
^eval set client_information $rcl[$rand(9)] 
	
}
on #-ctcp 20 * if ([$2]==[VERSION]) {^randcl}