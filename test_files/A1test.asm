; A2 - test file
;
		org	#80
Data		word	#1234
moreData	word	#AA01
someData	word	#2222
number      word    #0003
;
; Code
;
	org	#1000
Start
;
    movlz   Data,A0     ; A0 <- &Data
    ld  A0,R0       ; R5 <- [Data]
    movlz   moreData,A1
    ld  A1,R1
    movlz   someData,A2
    ld  A2,R2
    movlz   number,A3
    ld  A3,R3
;
    addx.b  R3,R3
    ADDX    R3,A0
    addx    A0,R2
    ADDX    A3,A3
;
end	Start
