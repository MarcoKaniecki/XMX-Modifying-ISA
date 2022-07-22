; A2 - test file
;
org #80
Data word #1234
moreData word #0202
numData word #0402
;
; Code
;
org #1000
Start
;
movlz Data,A0 ; A0 <- #80
ld A0,R0 ; R0 <- #1234
ld A0,R3 ; R3 <- #1234
movlz moreData,A1 ; A1 <- #82
ld A1,R1 ; R1 <- #0202
ld A1,R4 ; R4 <- #0202
ld A1,R6 ; R6 <- #0202
movlz numData,A2 ; A2 <- #84
ld A2,R7 ; R6 <- #0402
;
;
; new add extension
;
someLabel WORD #6049	; #0202 + #0202 = #0204 -> R1
WORD #6201	; #80 + #0204 = #0284 -> R1
anotherLabel
WORD #6100	; #1234 + #80 = #12B4 -> A0
WORD #6309	; #82 + #82 = #104 -> A1
WORD #6189	; #01 + #F4 = #105 -> A1
WORD #61E9	; #10 + #F3 = #115 -> A1
;
;
; new sub extension
;
label2 WORD #6613	; #1234 - #84 = #11B0 -> R3
WORD #6749	; #0115 - #0115 = #0100 -> A1
WORD #6423	; #11B0 - #0202 = #0FAE -> R3
label400
WORD #6540	; #12B4 - #1234 = #1280 -> A0
;
;
; new cmp extension
; initialize R2 and R5 to 0
movlz #0,R2
movlz #0,R5
;
WORD #6983	; A3 == 0 ? TRUE
cex EQ,#1,#1 ; skip next line
add #1,R2
add #1,R5 ; R5 + 1
;
WORD #6877	; low byte: #0402 == #0202 ? TRUE
cex EQ,#1,#1 ; skip next line
add #1,R2
add #1,R5 ; R5 + 1 = 2
;
WORD #6837	; #0402 == #0202 ? FALSE
cex EQ,#1,#1 ; execute next line
add #1,R2 ; #1 + #0 = #1 -> R2
add #1,R5
;
end Start
