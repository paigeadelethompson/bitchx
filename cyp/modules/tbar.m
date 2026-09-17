alias topwin {
	if (![$0]) {
	xecho -b sets topic window on or off}
	if ([$0]==[on]) { 
	@ top = [on]
	^window split on}
	if ([$0]==[off]) {
	@ top = [off]
	^window split off}
}