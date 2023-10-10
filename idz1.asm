# Файл с основной программой

.include "convenience.inc"
.include "mfunc.inc"
.include "io.inc"
.include "idz1.inc"
.data
	# Эти массивы подаются на вход
	.align 2
	arrA: .space 40
	arrB: .space 40


.text
.globl main
main:
 	input (arrA, 10)  
 	mv s0 a0  # Сохраняем размер
      	mmain (arrA, arrB, s0)
      	
      	print (arrB, s0)
      	exit ()
