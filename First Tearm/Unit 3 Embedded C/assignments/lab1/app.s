	.cpu arm926ej-s
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"app.c"
	.global	string_buffer
	.data
	.align	2
	.type	string_buffer, %object
	.size	string_buffer, 100
string_buffer:
	.ascii	"Learn-in-depth:Abdallah Ghazy\000"
	.space	70
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L2
	bl	uart_send_string
	ldmfd	sp!, {fp, pc}
.L3:
	.align	2
.L2:
	.word	string_buffer
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.2"
