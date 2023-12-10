#include<Stdio.h>




int main(){


    int block_size[10];
    int starting_block[10];
    int block_occupied[10][10];


    //reading data from user
    int no_of_files;
    printf("Enter the number of files: ");
    scanf("%d",&no_of_files);

    printf("Enter the File Details: \n");
    for (int i = 0; i < no_of_files; i++){
        
        printf("Enter the starting block of file %d: ",i+1);
        scanf("%d",&starting_block[i]);
        printf("Enter the block size of file %d: ",i+1);
        scanf("%d",&block_size[i]);
    }
    

    //temporary array to hold starting block
    int temp[10];
    for (int i = 0; i < no_of_files; i++){
        temp[i] = starting_block[i];
    }

    //initializing block_occupied array
    for(int i=0;i<no_of_files;i++){
        for (int j = 0; j < block_size[i]; j++){
            block_occupied[i][j] = temp[i];
            temp[i]=temp[i]+1;
        }
    }

    //printing the block_occupied array
    printf("\n\n");
    printf("File Name\tStarting Block\tBlock Length\n");
    for (int i = 0; i < no_of_files; i++){
        printf("File %d\t\t%d\t\t%d\n",i+1,starting_block[i],block_size[i]);
    }

    //printing details of block given by user
    printf("\n\n");
    int n;
    printf("Enter File Name: ");
    scanf("%d",&n);

    printf("Starting Block: %d\n",starting_block[n-1]);
    printf("Block Length: %d\n",block_size[n-1]);
    printf("Block Occupied: ");
    for (int i = 0; i < block_size[n-1]; i++){
         printf("%d ",block_occupied[n-1][i]);
    }
    
}