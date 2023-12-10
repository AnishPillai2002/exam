#include<stdio.h>
#include<stdlib.h>

struct block{
    int file_num; //to store the file number to which the block belongs
    int block_num;//to store the block number
    struct block *next;//pointer to the next block
};

int fileBlock[50];//array to store the status of the blocks
int blocks_to_Allocate[50];//array to store the blocks to allocate

//array to store allocated blocks
struct block *allocatedBlocks[50]; //array of pointers to the head of the linked list of blocks
int k=0;

void ReadBlock(){

    printf("Enter the starting block: ");
    int start_block;
    scanf("%d", &start_block);

    //check if the block is free
    if (fileBlock[start_block]==0){

        //read the number of blocks to allocate
        printf("Enter the number of blocks to allocate: ");
        int num_blocks;
        scanf("%d", &num_blocks);
        
        int flag=0; //to check if the blocks are free
        //read the blocks to allocate
        printf("Enter the blocks to allocate: ");
        for (int i = 0; i < num_blocks; i++){
            scanf("%d", &blocks_to_Allocate[i]);

            if(fileBlock[blocks_to_Allocate[i]]==0){
                flag++;
            }       
        }

        //if all the blocks are free
        if(flag==num_blocks){
            //mark the blocks as allocated
            fileBlock[start_block] = 1;
            for (int i = 0; i < num_blocks; i++){
                fileBlock[blocks_to_Allocate[i]] = 1;
            }

            //creating a newblock
            struct block *head = (struct block*)malloc(sizeof(struct block));
            head->block_num = start_block;
            head->next=NULL;
                 
            for (int i = 0; i < num_blocks; i++){
                
                //creating a pointer to next block
                struct block *nextBlock = (struct block*)malloc(sizeof(struct block));
                nextBlock->block_num = blocks_to_Allocate[i];
                nextBlock->next = NULL;
                
                //traversing the LinkedList to the end and adding the nextBlock
                struct block*temp = head;
                while (temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = nextBlock;       
            }
            
            //Inserting the head of the linked list in the allocatedBlocks array
            head->file_num = k;
            allocatedBlocks[k] = head;
            k++;
            printf("Blocks Allocated\n");
        }
        else{
            printf("Some of the blocks are already allocated\n");
            return;
        }
    }
    else{
        printf("Starting Block is already allocated\n");
        return;
    } 
}

void printDetails(int index){

    int found=0;
    int foundIndex;
    for (int i = 0; i < k; i++){
        
        if (allocatedBlocks[i]->block_num==index){
            found=1;
            foundIndex=i;
            break;
        }
    }

    if (found==0){
        printf("Block not Allocated\n");
    }
    else{

        //pointer to the head of the linked list
        struct block *temp = allocatedBlocks[foundIndex];

        printf("Block for File%d: ",allocatedBlocks[foundIndex]->file_num+1);
        while (temp!=NULL){
            printf("%d -->",temp->block_num);
            temp = temp->next;
        } 
        printf("\n"); 
    }
    
    
}
int main(){

    //Initialize the fileBlock array to 0
    for (int i = 0; i < 50; i++){
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
                ReadBlock();
                break;
            case 2:
                int index;
                printf("Enter the index block of the file: ");
                scanf("%d", &index);
                printDetails(index);
                break;
            case 3:
                exit(0);
        }
    }


}