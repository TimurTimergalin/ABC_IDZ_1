# ���� � �������

.include "idz1.inc"

# ������ ������� ����� � ������ �� ������
.eqv size1 0
.eqv size2 1
.eqv size3 4
.eqv size4 10

.data
	.align 2
	out: .space 40  # ���� ������������ ����� �������� ������
	
	# ������� ������ � ��������������� ���������� ������
	in1:
	an1:
	in2: .word -7
	an2: .word -7
	in3: .word 1
	     .word 2
	     .word -3
	     .word 4
	an3: .word -3
	     .word 2
	     .word 1
	     .word 4
	in4: .word -252
	     .word 140
	     .word 268
	     .word -381
	     .word -258
	     .word 490
	     .word -27
	     .word 304
	     .word -205
	     .word -25
	an4: .word -381
	     .word 140
	     .word 268 
	     .word -252
	     .word -258
	     .word 490
	     .word -27
	     .word 304
	     .word -205
	     .word -25
	s_test: .asciz "Testcase "
	s_colon: .asciz ": "
	s_ok: .asciz "OK\n"
	s_wa: .asciz "Wrong answer\n"
	s_correct: .asciz "    Correct: "
	s_actual: .asciz "    Actual: " 


# ����������� ��������� 2 ������� �� ��������� 
.macro compare_body  # (arrA, arrB, size) -> are_equal,
.text
	mv t0 a0
	li a0 1
	
	loop:
	beqz a2 end
		lw t1 (t0)
		lw t2 (a1)
		bne t1 t2 nope
		addi t0 t0 4
		addi a1 a1 4
		addi a2 a2 -1
		b loop
	
	nope:
	mv a0 zero
	end:
.end_macro

# ������� compare
func(_compare, compare_body)
.macro compare (%arrA, %arrB, %size)
.text
	la a0 %arrA
	la a1 %arrB
	mv a2 %size
	jal _compare
.end_macro

# ������ ��� ������� �����
.macro testcase (%number, %in, %out, %an, %size)
.text
	li s0 %size  # ��������� ������ � �������, ������ ��� ����� ������� ������ �������
	mmain (%in, %out, s0)  # ��������� ���������
	compare (%an, %out, s0) # ��������� ��������� � ���������
	mv t0 a0
	
	# ������� ���������...
	la a0 s_test
	li a7 4
	ecall
	li a0 %number
	li a7 1
	ecall
	la a0 s_colon
	li a7 4
	ecall
	
	beqz t0 wrong  # ... � ����������� �� ������������ ����������
		la a0 s_ok
		ecall
		b end
	wrong:
		la a0 s_wa
		ecall
		
		la a0 s_correct
		ecall
		print (%an, s0)
		la a0 s_actual
		ecall
		print (%out, s0)
	end:
.end_macro
.globl main
.text
main:
	# ��������� �����
	testcase (1, in1, out, an1, size1)
	testcase (2, in2, out, an2, size2)
	testcase (3, in3, out, an3, size3)
	testcase (4, in4, out, an4, size4)
	exit()
	
	
	
	
	
