	.arch	msp430g2553
	.p2align 1,0

	.text

	.extern toggle
	.extern green_on
jt:
	.word case0
	.word case1



	.global toggle_green


toggle_green:

	cmp.b #2, &toggle
	jhs end			;state > 1


	mov &toggle,r12
	add.b r12,r12		;2 * state
	mov jt(r12),r0		;jump to jt

case0:
	mov.b 1, &green_on
	mov.b 1, &toggle
	jmp end			;break

case1:
	mov.b 0, &green_on
	mov.b 0, r12
	jmp end			;break

end:
	mov.b #1, r13		;return 1
	pop r0
