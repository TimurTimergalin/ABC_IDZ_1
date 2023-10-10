# Файл с реализацией всей содержательной части задачи


# Далее нотация (arg1, arg2, ...) -> res1, res2 означает, что перед запуском подпрограммы 
# в a0 должен лежать arg1, в a1 - arg2 и т.д.
# а после запуска в a0 будет лежать res1, в a1 - res2


# Копирует массив А в массив В и ищет адрес минимального элемента в В
# В случае, если массив A пуст, возвращает адрес, меньший arrA
.macro createB_body # (arrA, arrB, size) -> min_ind
.eqv max_word 0x7fffffff  # 2^31 -1 - максимальное число со знаком, умещающееся в 1 слово
.text
	mv t0 a2
	mv t1 a0
	mv t2 a1
	addi a0 a1 -4  # Адрес минимального элемента
	li t3 max_word  # Минимальное знчение (изначально 2^31-1)
	
	loop:
	beqz t0 end
		lw t4 (t1)
		
		bge t4 t3 min_chosen  # Если новый элемент меньше текущего минимального
			mv a0 t2
			mv t3 t4			
		min_chosen:  # Здесь минимальный всегда правильный (на данной итерации)
		
		# Копируем элемент из А в В
		sw t4 (t2)
		addi t0 t0 -1
		addi t1 t1 4
		addi t2 t2 4
		b loop
	end:
.end_macro


# Меняет местами минимальный элемент (если такой есть) и первый
.macro swap_body # (arr, ind)
.text
	ble a1 a0 end # В случае, если минимального элемента нет (пустой массив, a1 < a0, см. createB), или если первый элемент уже минимальный,
		      # менять что-либо местами не имеет смысла
		lw t1 (a0)
		lw t2 (a1)
		
		sw t1 (a1)
		sw t2 (a0)
	end:
.end_macro

# Определение подпрограмм и макросов для их удобного вызова	

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

# Основная программа
.macro mmain (%arrA, %arrB, %size)
	createB(%arrA, %arrB, %size)
	mv s1 a0
	
	swap(%arrB, s1)
.end_macro
