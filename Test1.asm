.include <tn12def.inc>

	; линия PB2 - выход
	ldi r16, (1<<DDB2)
	out DDRB, r16

	ldi r16, 0x7f
	out OSCCAL, r16

loop:
	
	sbi PORTB, PORTB2
	nop
	cbi PORTB, PORTB2
	
	rjmp loop
