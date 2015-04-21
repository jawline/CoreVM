jmp start

start:
  load A 50
  load B 50
loop:
  add A B
  jne A 500 loop
exit:
