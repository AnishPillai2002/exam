DATA SEGMENT
    
    STR DB "anish$"
    SUBSTR DB "Di$"
    
    MSG1 DB 10,13,"FOUND$"
    MSG2 DB 10,13,"NOT FOUND$"
    
DATA ENDS

ASSUME CS:CODE DS:DATA

CODE SEGMENT
    
    
START:
    
    MOV AX,DATA
    MOV DS,AX
    
    LEA SI,STR

RESET:
    
    LEA DI,SUBSTR
    
FIRSTFIND:
    
    MOV AL,[SI]
    CMP AL,'$'
    JE NOTFOUND
    
    CMP AL,[DI]
    JE SEARCH
    INC SI
    JMP FIRSTFIND
SEARCH:
    
    INC SI
    INC DI
    MOV AL,[SI]
    MOV BL,[DI]
    CMP AL,BL
    JE SEARCH
    CMP BL,'$'
    JE FOUND
    JNE RESET
    



FOUND:
    
    MOV AH,09H
    LEA DX,MSG1
    INT 21H
    JMP FINISH
    
NOTFOUND:
    
    MOV AH,09H
    LEA DX,MSG2
    INT 21H

FINISH:
    
    MOV AH,4CH
    INT 21H
    
    
    
CODE ENDS
END START