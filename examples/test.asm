jmp start

#Program Entry Point
start:
	jmp auxProcess
ret:
	#Loop back
	jmp start

#Auxillery Process
auxProcess:
	loadi A 0
	loadi B 1
loop:
	add A A B
	jeq ret A 10
	jmp loop