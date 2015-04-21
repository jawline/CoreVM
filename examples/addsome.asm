jmp start

start:
  load A 50
  load B 50
  add A B
  jne A 500 start

exit:
