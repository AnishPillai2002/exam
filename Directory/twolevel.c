// In two level directory there will be a single master directory which contain several subdirectories and files

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure of Directory
typedef struct{
    char dirname[10];
    char filename[10][10];
    int file_count;
}directory[10];


int main(){

    char dname[10];
    int directory_count=0;

    //directory
    directory dir;

    //Providing options to user
    while(1){
        int ch;
        printf("\n\n1: Create Directory\n");
        printf("2: Create File\n");
        printf("3: Display\n");
        printf("4: Delete File\n"); 
        printf("5: Search Directory\n");
        printf("6: Exit\n");

        printf("Enter Your Choice: ");
        scanf("%d",&ch);

        switch (ch)
        {
        case 1: //create directory

            printf("Enter Directory Name: ");
            scanf("%s",dir[directory_count].dirname);
            dir[directory_count].file_count=0;
            directory_count++;
            printf("Directory Created\n");
            break;
        case 2: //create file
            printf("Enter Directory Name: ");
            scanf("%s",dname);

            //searching directory name
            int found=0;
            int dir_index;
            for(int i=0;i<directory_count;i++){
                if(strcmp(dir[i].dirname,dname)==0){
                    found=1;
                    dir_index=i;
                    break;
                }
            }

            if(found==0){
                printf("Directory Not Found");
            }
            else{

                printf("Enter File Name: ");
                scanf("%s",dir[dir_index].filename[dir[dir_index].file_count]);
                dir[dir_index].file_count++;

                printf("File Created Successfully\n");
            }          
            break;
        case 3: //display

            printf("The Directory Structure is: \n");
            printf("Main Directory \n");

            for(int i=0;i<directory_count;i++){

                printf(" %s\n",dir[i].dirname);

                //printing files
                for(int j=0;j<dir[i].file_count;j++){
                    printf("   %s\n",dir[i].filename[j]);        
                }
            }
            printf("\n");
            break;
        case 4: //delete file

            printf("Enter Directory Name: ");
            scanf("%s",dname);
            for(int i=0;i<directory_count;i++){
                if(strcmp(dir[i].dirname,dname)==0){
                    found=1;
                    dir_index=i;
                    break;
                }
            }

            if(found==0){
                printf("Directory Not Found");
            }
            else{
                char fname[10];
                printf("Enter File Name to Delete: ");
                scanf("%s",fname);

                for(int i=0;i<dir[dir_index].file_count;i++){
                    int found=0;
                    if(strcmp(fname,dir[dir_index].filename[i])==0){
                        found=1;
                        strcpy(dir[dir_index].filename[i],dir[dir_index].filename[dir[dir_index].file_count-1]);
                        dir[dir_index].file_count--;
                        printf("File Deleted\n");
                    }
                }

                if(found==0){
                    printf("File Not Found\n");
                }
            }
            
            break;
        case 5: //Search File

            printf("Enter Directory Name: ");
            scanf("%s",dname);
            for(int i=0;i<directory_count;i++){
                if(strcmp(dir[i].dirname,dname)==0){
                    found=1;
                    dir_index=i;
                    break;
                }
            }

            if(found==0){
                printf("Directory Not Found");
            }
            else{
                char fname[10];
                printf("Enter File Name to Search: ");
                scanf("%s",fname);

                for(int i=0;i<dir[dir_index].file_count;i++){
                    int found=0;
                    if(strcmp(fname,dir[dir_index].filename[i])==0){
                        found=1;
                    }
                }

                if(found==0){
                    printf("File Not Found\n");
                }
                else{
                    printf("File Found\n");
                }
            }


            
            break;
        case 6:
            exit(0);
            break;
        default:
            break;
        }

    }
}
