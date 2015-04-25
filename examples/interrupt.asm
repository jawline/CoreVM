load A 5
int 1
int 0
mov F E
jmp begin

data:
	db 4

begin:
	load A 10
	jeq E 10 right
left:
	set A data
	jmp exit
right:
	load A 4
	int 1
	load A 20
	jmp exit

exit:
	int 0
