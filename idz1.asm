# ���� � �������� ����������

.include "idz1.inc"
.data
	# ��� ������� ������� �� ����
	.align 2
	arrA: .space 40
	arrB: .space 40


.text
.globl main
main:
 	input (arrA, 10)  
 	mv s0 a0  # ��������� ������
      	mmain (arrA, arrB, s0)
      	
      	print (arrB, s0)
      	exit ()
