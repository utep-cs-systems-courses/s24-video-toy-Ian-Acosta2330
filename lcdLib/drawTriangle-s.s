	.arch msp430g2553
	.p2align 1,0
	
	.text
	
	.global drawTriangle
	.extern drawPixel
drawTriangle:
	sub #4, r1
	mov r13, 2(r1)
	sub r14, 2(r1)		;t1
	mov r13, 3(r1)
	add r14, 3(r1)
	jmp loop1
loop1:
	cmp 3(r1), 0(r1)
	jz int1
	mov 0(r1),r12
	mov 0(r1), r13
	call #drawPixel		;(0(r1), 0(r1), r15)
	add #1, 0(r1)
	jmp loop1
int1:
	mov 3(r1), 0(r1)
	jmp loop2
loop2:
	cmp 2(r1), 0(r1)
	jz int2
	mov 0(r1), r12
	mov 3(r1), r13
	call #drawPixel ;(0(r1), 3(r1), r15)
	sub #1, 0(r1)
	jmp loop2
int2:
	mov 2(r1), 0(r1)
	jmp loop3
loop3:
	cmp 3(r1), 0(r1)
	jz end
	mov 0(r1), r13
	call #drawPixel ;(r12, 0(r1), r15)
	add #1, 0(r1)
	jmp loop3
end:
	add #4, r1
	pop r0
