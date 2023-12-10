#include<Stdio.h>
#include<stdlib.h>

int main(){

    int fsize;
    printf("Enter the total number of frames: ");
    scanf("%d",&fsize);


    int psize;
    printf("Enter the total number of pages: ");
    scanf("%d",&psize);

    // reading page reference string
    int string[10];
    printf("Enter the page reference string: ");
    for (int i = 0; i < psize; i++){
        scanf("%d",&string[i]);
    }

    //initilizing frame
    int counter=0;
    int frame[10];
    for(int i=0;i<fsize;i++){
        frame[i]=-1; // -1 means empty frame
    }


    int page_fault=0;
    int hit=0;
    


    for(int i=0;i<psize;i++){

        int found=0;
        for(int j=0;j<fsize;j++){

            if(frame[j]==string[i]){       
                found=1;
                break;
            }
        }

        if(found==0){       
            
            frame[counter]=string[i];
            counter=(counter+1)%fsize;
            page_fault++;
        }
        else{
            hit++;
        }

        //printing frame
        for(int j=0;j<fsize;j++){
                if(frame[j]==-1){
                    printf("x ");
                }
                else{
                    printf("%d ",frame[j]);
                }        
        }
        printf("\n");
    }
    
    printf("Number of page faults: %d\n",page_fault);
}