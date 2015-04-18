load A 0
jmp repeat

repeat:
	add A 1
	jeq A 5 exit
	jmp repeat

exit: