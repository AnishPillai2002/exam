//PASS 1 OF 2 PASS ASSEMBLER

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){


    //creating file pointers and opening them
    FILE *in=fopen("assembly.txt","r");
    FILE *op=fopen("optab.txt","r");
    FILE *sym=fopen("symtab.txt","w");
    FILE *inter=fopen("intermediate.txt","w");
    FILE *len=fopen("length.txt","w");

    //variables to store label opcode and operand
    char label[10],opcode[10],operand[10];

    //variables to store length and size
    int length;
    int size;
    int bytelen;
    int locctr;
    int start_addr;

    //variables to store opcode and its value form optab
    char code[10],value[10];

    //reading first input line
    fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    //printf("%s\t%s\t%s\n",label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        start_addr=atoi(operand);
        locctr=start_addr;
        //writing into intermediate file
        fprintf(inter,"**\t%s\t%s\t%s\n",label,opcode,operand);
        //reading next line
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }
    else{
        locctr=0;
    }

    //reading assembly input program till the end
    while (strcmp(opcode,"END")!=0){
        //writing into intermediate file
        fprintf(inter,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

        //writing symbol into symtab
        if(strcmp(label,"**")!=0){
            fprintf(sym,"%s\t%d\n",label,locctr);
        }

        // reading the optab for opcode
        fscanf(op,"%s\t%s",code,value);
        while (strcmp(code,"END")!=0){
            
            if(strcmp(code,opcode)==0){
                locctr+=3;
                size+=3;
                break;
            }
            fscanf(op,"%s\t%s",code,value);
        }
        
        if(strcmp(opcode,"WORD")==0){
            locctr=locctr+3;
            size=size+3;
        }
        else if(strcmp(opcode,"BYTE")==0){

            bytelen=strlen(operand);

            if(operand[0]=='C'){ //for char
                locctr+=bytelen-3;
                size+=bytelen-3;
            }else{   //for hex
                locctr+=(bytelen-3)/2;
                size+=(bytelen-3)/2;
            }
        }
        else if(strcmp(opcode,"RESB")){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"RESW")){
            locctr+=3*atoi(operand);
            
        }
        else{
            printf("%s Operand Not found\n",operand);
        }

        // reading next line
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }

    //writing last line into intermediate file
    fprintf(inter,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

    length=locctr-start_addr;

    //writing length and size into length.txt
    fprintf(len,"%x\t%x\n",length,size);
    fprintf(sym,"END\t**\n");
}
