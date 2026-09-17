## robohaks wall.bx pr0pz 

^on #^notice '% %[%\\[# & +\\]%]*' 11 {
	^local loc,char
	@ :chans = mychannels()
	fec (#&+) cc {@loc = index($cc $1);if (loc>=0) {@ char = cc;break}}
	if (!numwords($pattern($char* $chans))) {^return}
	@ loc++
	@ :append = mid($loc 1 $1)
	while (numwords($pattern($char$append* $chans))>1) {
		@ loc++
		@ append#=mid($loc 1 $1)
    }
	@ :chan = pattern($char$append* $chans)
	echo $fparse(format_bwall $Z $chan $0 ! $2-)
}
