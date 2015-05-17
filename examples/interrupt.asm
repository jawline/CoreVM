entry:
	load A 2
	int 1
	
	load A 3
	int 1

	jeq B C exit
	jeq B 5 exit
	jeq C 10 exit
	jeq B C exit
	mov D C
	gt D 3
	jeq D 1 exit
	mov D C
	gt D 3
	jeq D 0 exit
fail:
	int 2
exit: