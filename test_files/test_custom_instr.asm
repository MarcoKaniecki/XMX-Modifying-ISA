; A2 - test file
;
		org	#80
Data		word	#1234
moreData	word	#0202
numData     word    #0402
;
; Code
;
	org	#1000
Start
;
    movlz   Data,A0     ; A0 <- #80
    ld  A0,R0       ; R0 <- #1234
    ld  A0,R3       ; R3 <- #1234
    movlz   moreData,A1 ; A1 <- #82
    ld  A1,R1       ; R1 <- #0202
    ld  A1,R4       ; R4 <- #0202
    ld  A1,R6       ; R6 <- #0202
    movlz   numData,A2 ; A2 <- #84
    ld  A2,R7       ; R6 <- #0402
;
;
; new add extension
;
someLabel   addx.b  R1,R1   ; #0202 + #0202 = #0204 -> R1
    ADDX    A0,R1   ; #80 + #0204 = #0284 -> R1
anotherLabel
    addx    R0,A0   ; #1234 + #80 = #12B4 -> A0
    ADDX    A1,A1   ; #82 + #82 = #104 -> A1
    addx.w  #1,A1  ; #01 + #F4 = #105 -> A1
    addx.b  $16,A1  ; #10 + #F3 = #115 -> A1
;
;
; new sub extension
;
label2  subx    A2,R3   ; #1234 - #84 = #11B0 -> R3
    subx.b  A1,A1   ; #0115 - #0115 = #0100 -> A1
    SUBX.w  R4,R3   ; #11B0 - #0202 = #0FAE -> R3
label400
    subx.b  R0,A0   ; #12B4 - #1234 = #1280 -> A0
;
;
; new cmp extension
; initialize R2 and R5 to 0
    movlz #0,R2
    movlz #0,R5
;
    CMPX    #0,A3   ; A3 == 0 ? TRUE
    cex EQ,#1,#1    ;
    add    #1,R2    ; R2 = R2 + 1
    add    #1,R5    ; skip
;
    cmpx.b R6,R7    ; low byte: #0402 == #0202 ? TRUE
    cex EQ,#1,#1    ;
    add    #1,R2    ; R2 = R2 + 1
    add    #1,R5    ; skip
;
    cmpx    R6,R7   ; #0402 == #0202 ? FALSE
    cex EQ,#1,#1    ;
    add    #1,R2    ; skip
    add    #1,R5    ; R5 = R5 + 1
;
end	Start
