int 0
jmp begin

data:
	db 4

begin:
	load A 10
	jeq A 10 right
left:
	set A data
	jmp exit
right:
	load A 20
exit:
	int 0