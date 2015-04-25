entry:
	load A 2
	int 1
	
	load A 3
	int 1

	jeq B C exit
	jeq B 5 exit
	jeq C 10 exit
	jne B C exit
fail:
	int 2
exit: