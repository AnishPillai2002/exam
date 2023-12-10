//single level directory contain only  1 directory inside which all the files are stored


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//structure for directory
typedef struct{

    char dirname[10];
    char filename[10][10];
    char file_count;
}directory;


int main(){

    //creating a directory
    directory dir;
    dir.file_count=0;

    //reading the directory name from user
    char dname[10];
    printf("Enter the directory name: ");
    scanf("%s",dir.dirname);


    //reading the file names from user
    while (1){
        int ch;
        printf("\n\n1 : Add file\n2 : Delete file\n3 : Display files\n4 : Exit\n");
        scanf("Enter Choice: %d",&ch);

        switch (ch){
        case 1:
            printf("Enter the file name: ");
            scanf("%s",dir.filename[dir.file_count]);
            dir.file_count++;
            break;
        case 2:
            printf("Enter the file name: ");
            scanf("%s",dname);

            for(int i=0;i<dir.file_count;i++){

                if(strcmp(dir.filename[i],dname)==0){
                    printf("Deleted File %s\n",dname);
                    strcpy(dir.filename[i],dir.filename[dir.file_count-1]);
                    dir.file_count--;
                    break;
                }
            }
            break;
        case 3:
            if(dir.file_count==0){
                printf("Directory is Empty\n");
            }
            else{
                printf("Files Are: \n");
                for (int i = 0; i <dir.file_count; i++){
                    printf("%s\n",dir.filename[i]);
                }
            }
            
            break;
        case 4:
            exit(0);
            break;  
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    
    


}