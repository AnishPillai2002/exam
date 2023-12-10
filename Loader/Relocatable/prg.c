#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char bit_mask_binary[50];
char bit_mask[50];

//Function to convert bitmask into its binary format
void convert(char mask[]){

    int len=strlen(mask);

    //initilizing bit_mask_binary
    strcpy(bit_mask_binary,"");

    //traversing the bitmask
    for(int i=0;i<len;++i){

        switch (mask[i]){
        case '0':
            strcpy(bit_mask_binary,"0000");
            break;
        case '1':
            strcpy(bit_mask_binary,"0001");
            break;
        case '2':
            strcpy(bit_mask_binary,"0010");
            break;
        case '3':
            strcpy(bit_mask_binary,"0011");
            break;
        case '4':
            strcpy(bit_mask_binary,"0100");
            break;
        case '5':
            strcpy(bit_mask_binary,"0101");
            break;
        case '6':
            strcpy(bit_mask_binary,"0110");
            break;
        case '7':
            strcpy(bit_mask_binary,"0111");
            break;
        case '8':
            strcpy(bit_mask_binary,"1000");
            break;
        case '9':
            strcpy(bit_mask_binary,"1001");
            break;
        case 'A':
            strcpy(bit_mask_binary,"1010");
            break;
        case 'B':
            strcpy(bit_mask_binary,"1011");
            break;
        case 'C':
            strcpy(bit_mask_binary,"1100");
            break;
        case 'D':
            strcpy(bit_mask_binary,"1101");
            break;
        case 'E':
            strcpy(bit_mask_binary,"1110");
            break;
        case 'F':
            strcpy(bit_mask_binary,"1111");
            break;
        default:
            break;
        }
    }
}


void main(){

    //File Pointer
    FILE *fp=fopen("input.txt","r");

    //variables
    char line[20];//used to store each line in the object code   
    int specified_address;//used to store the specified address of instruction
    
    

    int modified_operand;//used to store the modified operand value
    char first[3];//used to store the first part of the object code
    char second[4];//used to store the second part of the object code

    int bit_mask_index=0;

    //read PROGADDR
    int start_address;//used to store the starting address/PROGADDR
    printf("Enter the Starting Address: ");
    scanf("%x",&start_address);


    //read the first line
    fscanf(fp,"%s",line);
    char program_name[20];//used to store the program name
    int length;//used to store program length

    if (strcmp(line,"H")==0){
        
        //reading other details from header record
        fscanf(fp,"%s",program_name);
        fscanf(fp,"%x",&specified_address);
        fscanf(fp,"%x",&length);
        printf("Program Name: %s\n",program_name);
    }
    
    strcpy(line,"");

    //reading next line
    fscanf(fp,"%s",line);
    while (strcmp(line,"E")!=0){
        

        if (strcmp(line,"T")==0){
            
            //reading the details of instruction
            fscanf(fp,"%x",&specified_address);
            fscanf(fp,"%x",&length);

            //reading bitmask
            fscanf(fp,"%s",bit_mask);

            //converting bitmask to binary representation
            bit_mask_index=0;
            convert(bit_mask);

            specified_address=specified_address+start_address;

            //read next instruction
            fscanf(fp,"%s",line);
        }

        
        if(bit_mask_binary[bit_mask_index]=='1'){

            //dividing the instruction into 2 parts(opcode and operand)
            //opcode
            for(int i=0;i<2;i++){
                first[i]=line[i];
            }
            //operand
            for(int i=2;i<6;i++){
                second[i-2]=line[i];
            }

            //new operand
            first[2]='\0';
            second[4]='\0';

            modified_operand=strtol(second,NULL,16);
            modified_operand+=start_address;

            //printing
            printf("%x : %s%x\n",specified_address,first,modified_operand);


        }else{

            printf("%x : %s\n",specified_address,line);
        }

        specified_address+=3;
        bit_mask_index++;
        
        //reading next instruction
        fscanf(fp,"%s",line);
    }
    


}