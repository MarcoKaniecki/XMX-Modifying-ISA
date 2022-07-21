; A2 - test file for ADDX
;
		org	#80
Data		word	#1234
moreData	word	#0202
;
; Code
;
	org	#1000
Start
;
    movlz   Data,A0     ; A0 <- &Data
    ld  A0,R0       ; R0 <- [Data]
    movlz   moreData,A1
    ld  A1,R1
;
someLabel   addx.b  R1,R1
    ADDX    A0,R1
anotherLabel
    addx    R0,A0
    ADDX.b  A1,A1
    addx    #FF,A1
    addx.b  $16,A1
;
end	Start
