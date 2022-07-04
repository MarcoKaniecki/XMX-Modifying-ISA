;
; A1 test program
; Count number of set and clear bits in Data
; Exercise 14 XMX instructions
;
; ECED 3403
; 22 06 07
;
	org	#FFC0
STKTOP
;
		org	#80
Data		word	#FEDC	; Pattern to examine
SetCount	word	#AA00	; Total bits set in Data (#AAxx; AA0C)
ClrCount	word	#BB00	; Total bits clear in Data (#BBxx; BB04)
;
; Code
;
	org	#1000
Start
;
	movls	STKTOP,SP	; SP <- &FFC0
;
	movlz	Data,A0		; A0 <- &Data
	ld	A0,R5		; R5 <- [Data]
;
	movls	#0,R6		; R6 <- #FF00 (Set count)
	movls	#0,R7		; R7 <- #FF00 (Clear count)
;
Loop
	cmp	#0,R5		; Finished when R5 is zero
	cex	eq,$1,$0	;
	br	DoneLoop
	bl	Subr
	br	Loop
;
DoneLoop    ADDX    A6,A7 ; THIS IS A COMMENT
;
; Handle case when MSbit is zero
;
	movl	#10,R7		; R7 <- 16 (upper byte should be untouched FFxx)
	sub.b	R6,R7		; R7 <- R7 - R6
;
	ADDX    A6,A7       ; THIS IS A COMMENT
	ADDX.b  A6,A7
	SUBX.w  A6,A7
	CMPX.b  A6,A7
;
    ADDX    $2,R0
    ADDX    $-1,A0
;
;
	str.b	R6,A0,$2	; Setcount <- R6
	str.b	R7,A0,$4	; Clrcount <- R7
;
BusyWait
	br	BusyWait
;
; Checks LSbit for zero/one
; Shifts R5 right (MSbit <- 0)
;
Subr	bit	#1,R5		; Bit 0 state?
	cex	ne,$1,$1
; Bit 0 set
	add.b	#1,R6
; Bit 0 clear
	add.b	#1,R7		; Ignored
;
; Assume that C is clear from either add
;
	rrc	R5		; R5 >> 1
;
	swap	LR,PC
;
	end	Start
