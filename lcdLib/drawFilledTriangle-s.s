	.arch msp430g2553
	.p2align 1,0
	.text
	
	.global drawFilledTriangle
	.extern drawPixel

drawFilledTriangle:
	sub #5, r1
	mov #0, 0(r1)
	jmp loop1
loop1:
	cmp #60, 0(r1)
	jnc end
	jmp loop2
loop2:
	mov r12, 2(r1)
	sub 0(r1), 2(r1)
	mov r12, 5(r1)
	add 0(r1), 5(r1)
	cmp 5(r1), 2(r1)
	jge loop1
	call #drawPixel
end:
	add #5, r1
	pop r0
