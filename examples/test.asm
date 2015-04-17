jmp start

padding:
	db 1024

start:
	load A 5
	load B 10
	set A min
	set B max
	load C loop_forever
	jmp C
	jmp exit

loop_forever:
	jmp loop_forever

min:
	db 4
padding:
	db 2
max:
	db 4

exit: