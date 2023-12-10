#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure to store optab
struct{
    char opcode[20];
    char hex[20];
}optab[20];

//structure to store symtab
struct{
    char symbol[20];
    char value[20];
}symtab[20];


//Function to read optab
void readOptab(){
    FILE *op=fopen("optab.txt","r");
    int i=0;
    fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    while(strcmp(optab[i].opcode,"END")!=0){
        i++;
        fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    }
    fclose(op);
}

//Function to read symtab
void readSymtab(){

    FILE *sym=fopen("symtab.txt","r");
    int i=0;
    fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);

    while(strcmp(symtab[i].symbol,"END")!=0){
        i++;
        fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);
    }
    fclose(sym);
}



int main(){
    readOptab();
    readSymtab();


    // file pointers
    FILE *obj=fopen("object.txt","w");
    FILE *listing=fopen("listing.txt","w");
    FILE *len=fopen("length.txt","r");
    FILE *inter=fopen("intermediate.txt","r");

    //variables
    char label[20],opcode[20],operand[20];

    int addr;
    int length;
    int size;
    int bytelen;
    int start_addr;

    //reading first line
    fscanf(inter,"%s\t%s\t%s\t%s",&addr,label,opcode,operand);
    start_addr=atoi(operand);

    //reading length and size of object code
    fscanf(len,"%x\t%x",&length,&size);

    if (strcmp(opcode,"START")==0){
        
        //writing assembly listing
        fprintf(listing,"**\t**\t%s\t%s",opcode,operand);

        //writing object code header record
        fprintf(obj,"H^ANISH  ^00%d^0000%x\n",start_addr,length);
        
        //initilizing first text record
        fprintf(obj,"T^00%d^%x",start_addr,size);

        //reading next input line
        fscanf(inter,"%d\t%s\t%s\t%s",&addr,label,opcode,operand);
    }
    

    while (strcmp(opcode,"END")!=0){
        
        if (strcmp(opcode,"BYTE")==0){
            
            bytelen=strlen(operand)-1;

            fprintf(listing,"%d\t%s\t%s\t%s\t",addr,label,opcode,operand);
            fprintf(obj,"^");

            if (operand[0]=='C'||operand[0]=='c'){
                
                for (int i = 2; i < bytelen; i++){
                    fprintf(listing,"%x",operand[i]);
                    fprintf(obj,"%x",operand[i]);
                    
                }  
            }
            else{
                operand[bytelen]='\0';
                fprintf(listing,"%s",operand+2);
                fprintf(obj,"%s",operand+2);
            }
            fprintf(listing,"\n");
        }
        else if(strcmp(operand,"WORD")==0){
            fprintf(listing,"%x\t%s\t%s\t%s\t%x\n",addr,label,opcode,operand,atoi(operand));
            fprintf(obj,"^00000%x",atoi(operand));
        }
        else if(strcmp(operand,"RESW")==0||strcmp(operand,"RESB")==0){
            fprintf(listing,"%x\t%s\t%s\t%s\n",addr,label,opcode,operand);
        }
        else{
          
            int i=0;
            int j=0;

            while (strcmp(optab[i].opcode,opcode)!=0){
                i++;
            }

            while (strcmp(symtab[j].symbol,operand)!=0){
                j++;
            }
            printf("done\n");
            fprintf(obj,"^%s%s",optab[i].hex,symtab[j].value);
            fprintf(listing,"%x\t%s\t%s\t%s\t%s%s\n",addr,label,opcode,operand,optab[i].hex,symtab[j].value);      
        
        }
        //reading next input line
        fscanf(inter,"%d\t%s\t%s\t%s",&addr,label,opcode,operand);
    }
    

  
}