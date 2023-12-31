DATA SEGMENT
    
    MESS1 DB 10,13,"ENTER THE STRING: $"
    MESS2 DB 10,13,"STRING IS PALINDROME$"
    MESS3 DB 10,13,"STRING IS NOT PALINDROME$"
    
    STR DB 50 DUP(0)
DATA ENDS

ASSUME CS:CODE,DS:DATA

CODE SEGMENT
    
START:
    
    MOV AX,DATA
    MOV DS, AX
    
    MOV SI,OFFSET STR
    MOV DI,OFFSET STR
    
    LEA DX,MESS1
    MOV AH,09H
    INT 21H
    
    
    MOV AH,01;
    
READ:

    INT 21H
    
    CMP AL,0DH
    
    JE TERMINATE
    
    MOV [DI],AL
    
    INC DI
    JMP READ

TERMINATE:

    MOV AL,'$'
    MOV [DI],AL
    

CHECK:
    
    DEC DI
    MOV AL,[SI]
    MOV BL,[DI]
    CMP AL,BL
    JNE NOTPALIN
    
    INC SI   
    CMP SI,DI
    JL CHECK

PALINDROME:
    LEA DX,MESS2
    MOV AH,09H
    INT 21H
    
    JMP XX

NOTPALIN:
    
    LEA DX,MESS3
    MOV AH,09H
    INT 21H
    
XX: 
    MOV AH,4CH
    INT 21H
    


CODE ENDS
END START