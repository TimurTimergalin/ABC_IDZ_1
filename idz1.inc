# ���� � ����������� ���� ������������� ����� ������

.include "mfunc.inc"
.include "convenience.inc"


# ����� ������� (arg1, arg2, ...) -> res1, res2 ��������, ��� ����� �������� ������������ 
# � a0 ������ ������ arg1, � a1 - arg2 � �.�.
# � ����� ������� � a0 ����� ������ res1, � a1 - res2


# ���������� ���� �������. � ������, ���� ��������� ������ �������� ������������ �����, �������� �������� ���������
.macro input_body  # (arr, max_length) -> length
.data
	s_input_size: .asciz "������� ������ �������: "
	s_input_elements: .asciz "������� �������� ������� A:\n"
	s_invalid_size: .asciz "������: ������ ������ ���� ������ �� 0 �� 10"
.text
	mv t1 a0  # � t1 ����� �������

	la a0 s_input_size
	li a7 4  # ����� ������
	ecall
	
	li a7 5  # ���� �����
	ecall
	
	mv t6 a0  # � t6 ������ �������
	
	bgt a0 a1 invalid
	bltz a0 invalid
	b valid
	invalid:  # � ������, ���� ������ ������������ ������
		la a0 s_invalid_size
		li a7 4
		ecall
		exit (1)
	valid:
		li a7 4
		la a0 s_input_elements
		ecall
		
		li a7 5
		mv t0 t6  # � t0 ������� �����
		
		loop:  # ���� ��������� �������
		beqz t0 end
			# ��������� ��������� �������� � ������
			ecall  # a7 = 5
			sw a0 (t1)
			addi t1 t1 4
			addi t0 t0 -1
			b loop
		end:
		mv a0 t6
.end_macro

# �������� ������ � � ������ � � ���� ����� ������������ �������� � �
# � ������, ���� ������ A ����, ���������� �����, ������� arrA
.macro createB_body # (arrA, arrB, size) -> min_ind
.eqv max_word 0x7fffffff  # 2^31 -1 - ������������ ����� �� ������, ����������� � 1 �����
.text
	mv t0 a2
	mv t1 a0
	mv t2 a1
	addi a0 a1 -4  # ����� ������������ ��������
	li t3 max_word  # ����������� ������� (���������� 2^31-1)
	
	loop:
	beqz t0 end
		lw t4 (t1)
		
		bge t4 t3 min_chosen  # ���� ����� ������� ������ �������� ������������
			mv a0 t2
			mv t3 t4			
		min_chosen:  # ����� ����������� ������ ���������� (�� ������ ��������)
		
		# �������� ������� �� � � �
		sw t4 (t2)
		addi t0 t0 -1
		addi t1 t1 4
		addi t2 t2 4
		b loop
	end:
.end_macro


# ������ ������� ����������� ������� (���� ����� ����) � ������
.macro swap_body # (arr, ind)
.text
	ble a1 a0 end # � ������, ���� ������������ �������� ��� (������ ������, a1 < a0, ��. createB), ��� ���� ������ ������� ��� �����������,
		      # ������ ���-���� ������� �� ����� ������
		lw t1 (a0)
		lw t2 (a1)
		
		sw t1 (a1)
		sw t2 (a0)
	end:
.end_macro

# ����� ������� � ������� 
.macro print_body # (arr, size) 
.data
	s_sp: .asciz " "
.text
	mv t1 a0
	
	loop:
	beqz a1 end
		# ������� ������� � �������� �����
		lw a0 (t1)
		li a7 1
		ecall
		li a7 4
		la a0 s_sp
		ecall
		addi a1 a1 -1
		addi t1 t1 4
		b loop
	end:
.end_macro

# ����������� ����������� � �������� ��� �� �������� ������
func(_input, input_body)
.macro input (%arr, %max_length)
	la a0 %arr
	li a1 %max_length
	jal _input
.end_macro
	
func(_createB, createB_body)
.macro createB (%arrA, %arrB, %size)
	la a0 %arrA
	la a1 %arrB
	mv a2 %size
	jal _createB
.end_macro

func(_swap, swap_body)
.macro swap (%arr, %ind)
	la a0 %arr
	mv a1 %ind
	jal _swap
.end_macro

func(_print, print_body)
.macro print (%arr, %size)
	la a0 %arr
	mv a1 %size
	jal _print
.end_macro


# �������� ���������
.macro mmain (%arrA, %arrB, %size)
	createB(%arrA, %arrB, %size)
	mv s1 a0
	
	swap(%arrB, s1)
.end_macro