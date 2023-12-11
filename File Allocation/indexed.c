#include<stdio.h>
#include<stdlib.h>


typedef struct{
    int num_blocks;
    int indexBlock;
    int blocks[50];

}block;




//Global Variables
int indexBlock;
int no_of_blocks;
int fileBlock[50];
int indexBlockArray[50];

block array[50];
int k=0;


//Function to read Index Block From User
void ReadIndexBlock(){

    printf("Enter the Index Block: ");
    scanf("%d", &indexBlock);

    if(fileBlock[indexBlock]==0){
        fileBlock[indexBlock]=1;
        printf("Enter the no of Blocks Required: ");
        scanf("%d", &no_of_blocks);

        int flag=0;

        //Ask the user to input block numbers to allocate the file
        printf("Enter the %d Blocks: ", no_of_blocks);
        for (int i = 0; i < no_of_blocks; i++){
            scanf("%d", &indexBlockArray[i]);
            
            // Check if the selected blocks are free
            if (fileBlock[indexBlockArray[i]]==0){
                flag++;
            }        
        } 

        //If all selected blocks (flag == n) are free, 
        //marks them as allocated by setting corresponding elements in the files[] array to 1.
        if(flag==no_of_blocks){

            for (int i = 0; i <no_of_blocks; i++){
                fileBlock[indexBlockArray[i]] = 1;
            }
            
            array[k].num_blocks = no_of_blocks;
            array[k].indexBlock = indexBlock;
            for (int i = 0; i < no_of_blocks; i++){
                array[k].blocks[i] = indexBlockArray[i];
            }
            k++;
            printf("File is allocated successfully\n");
        }
        else{
            printf("File is not allocated\n");
        }


    }
    else{
        printf("Index Block is already allocated\n");
    }
}



int main(){

    //initializing all file blocks to 0
    for(int i=0; i<50; i++){
        fileBlock[i] = 0;
    }


    while(1){
        printf("1. Allocate File\n");
        printf("2. Display Allocated Block\n");
        printf("3. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                ReadIndexBlock();
                break;
            case 2:
                int index;
                printf("Enter the index block of the file: ");
                scanf("%d", &index);
                printDetails(index);
                break;
            case 3:
                exit(0);
                break;
            
            default:
                printf("Invalid choice\n");
        }
    }
}