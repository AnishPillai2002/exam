#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){

    //File Pointer
    FILE *f1=fopen("input.txt","r");

    char line[100];
    char addr[6];
    int i,j;
    int hexaddr;
    int prevAddr=0xFFFF;
    //Reading first input line
    fscanf(f1,"%s",line);

    //while recordtype!=E
    while (line[0]!='E'){
        
        if(line[0]=='T'){
            //starting reading the address of instruction
            for(i=2,j=0;i<=7;i++,j++){
                addr[j]=line[i];
            }
            addr[j]='\0';
        
            
            //address in hex
            hexaddr=strtol(addr,NULL,16);
        
            while(prevAddr<hexaddr){
                printf("%x: XX\n",prevAddr);
                prevAddr++;
            }

            //i points to start of instruction
            i=i+4;

            //till the end of line
            while (line[i]!='\0'){
            
                printf("%x : %c%c\n",hexaddr,line[i],line[i+1]);
                i+=2;

                hexaddr+=0x1;

                if (line[i]=='^'){
                    i++;
                }
            }
            prevAddr=hexaddr;
        }
        //Reading next input line
        fscanf(f1,"%s",line);            
    }
}