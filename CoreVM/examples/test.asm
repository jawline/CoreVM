jmp start

#Program Entry Pointer
start:
	jmp auxProcess
ret:
	#Loop back
	jmp start

#Auxillery Process
auxProcess:
	loadi $1 0
	loadi $2 1
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	add $1 $1 $2
	jmp ret