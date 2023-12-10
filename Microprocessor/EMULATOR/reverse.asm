DATA SEGMENT
    MSG DB 10,13,'ENTER STRING TO REVERSE: $' ; Prompt to enter the string
    MSG2 DB 10,13,'REVERSE STRING: $'         ; Prompt to display the reversed string
    
    REV DB 100 DUP($)                         ; Reversed string buffer
DATA ENDS

ASSUME CS:CODE, DS:DATA



READ MACRO
    MOV AH,01H      ; Function to read a character from STDIN
    INT 21H         ; DOS interrupt call
ENDM

CODE SEGMENT
START:
    MOV AX,DATA     ; Load data segment address into AX
    MOV DS,AX       ; Set data segment to DS

    MOV DI,OFFSET REV   ; Point DI to the end of the REV buffer
    ADD DI,100      ; Adjust DI to the end of buffer
    MOV [DI],'$'   ; Set null-terminator at the end of the buffer
    DEC DI         

    MOV AH,09H    ; Display "ENTER STRING TO REVERSE: $"
    LEA DX,MSG
    INT 21H
    
    READ           ; Read character from STDIN

NEXT:
    MOV [DI],AL    ; Store entered character in the buffer
    DEC DI         ; Move buffer pointer back
    READ           ; Read the next character

    CMP AL,0DH     ; Check for carriage return
    JNE NEXT       ; If not CR, continue reading characters

    INC DI         ; Move DI to the first character of the entered string  
    
    
    MOV AH,09H   ; Display "REVERSE STRING: $"   
    LEA DX,MSG2
    INT 21H
    
    
    MOV AH,09H     ; Display the address of the reversed string
    LEA DX,DI
    INT 21H
    
    
    
    MOV AH,4CH     ; DOS function to terminate program
    INT 21H
CODE ENDS
END START
