# Макросы выхода
.macro exit
	li a7 10
	ecall
.end_macro

.macro exit (%code)
	li a7 93
	li a0 %code
	ecall
.end_macro