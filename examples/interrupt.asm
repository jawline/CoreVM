entry:
	load A 2
	int 1
	
	load A 3
	int 1
	
	load A 4
	int 1

	int 0
	jeq B 10 exit

failure:
	int 3

exit:
	int 0