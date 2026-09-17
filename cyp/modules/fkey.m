alias fkey1 {
	if (![$0]) {
	xecho -b cypress function key 1 set to $fk1
	}{
	@fk1 = [$*]
	^bind META3-A parse_command $*
        ^bind ^[[11~ parse_command $*
        ^bind ^[[[A parse_command $*
        ^bind ^[OP parse_command $*

	xecho -b cypress function key 1 set to $fk1}
}

alias fkey2 {
        if (![$0]) {
        xecho -b cypress function key 2 set to $fk2
	}{
	@fk2 = [$*]
	^bind META3-B parse_command $*
        ^bind ^[[12~ parse_command $*
        ^bind ^[[[B parse_command $* 
        ^bind ^[OQ parse_command $* 

        xecho -b cypress function key 2 set to $fk2}
}
alias fkey3 {
        if (![$0]) {
	xecho -b cypress function key 3 set to $fk3
        }{
	@fk3 = [$*]
	^bind META3-C parse_command $*
        ^bind ^[[13~ parse_command $*
        ^bind ^[[[C parse_command $* 
        ^bind ^[OR parse_command $*

        xecho -b cypress function key 3 set to $fk3}
}
alias fkey4 {
         if (![$0]) {
        xecho -b cypress function key 4 set to $fk4 
        }{
	@fk4 = [$*]
	^bind META3-D parse_command $*
        ^bind ^[[14~ parse_command $*
        ^bind ^[[[D parse_command $*
        ^bind ^[OS parse_command $*

        xecho -b cypress function key 4 set to $fk4}
}
alias fkey5 {
         if (![$0]) {
        xecho -b cypress function key 5 set to $fk5
        }{
	@fk5 = [$*]
	^bind META3-E parse_command $*
        ^bind ^[[15~ parse_command $*
        ^bind ^[[[E parse_command $*

        xecho -b cypress function key 5 set to $fk5}
}
alias fkey6 {
         if (![$0]) {
        xecho -b cypress function key 6 set to $fk6
        }{
	@fk6 = [$*]
	^bind META3-7 parse_command $*
        ^bind ^[[18~ parse_command $*

        xecho -b cypress function key 6 set to $fk6}
}

alias do.fkey {
^bind META3-A parse_command $fk1
^bind ^[[11~ parse_command $fk1
^bind ^[[[A parse_command $fk1
^bind ^[OP parse_command $fk1

^bind META3-B parse_command $fk2
^bind ^[[12~ parse_command $fk2
^bind ^[[[B parse_command $fk2 
^bind ^[OQ parse_command $fk2 

^bind META3-C parse_command $fk3
^bind ^[[13~ parse_command $fk3
^bind ^[[[C parse_command $fk3 
^bind ^[OR parse_command $fk3

^bind META3-D parse_command $fk4
^bind ^[[14~ parse_command $fk4
^bind ^[[[D parse_command $fk4
^bind ^[OS parse_command $fk4

^bind META3-E parse_command $fk5
^bind ^[[15~ parse_command $fk5
^bind ^[[[E parse_command $fk5

^bind META3-7 parse_command $fk6
^bind ^[[17~ parse_command $fk6


}
do.fkey