#include<stdio.h>
#include<stdlib.h>


int main(){

    int p;
    printf("Enter the number of requests: ");
    scanf("%d",&p);

    int request[10];
    printf("Enter the request sequence: ");
    for(int i=0;i<p;i++){
        scanf("%d",&request[i]);
    }

    //Result
    int total_head_movement = 0;
    int head;
    int serviced=0;
    printf("Enter the current head position: ");
    scanf("%d",&head);


    printf("Service order: %d ",head);

    int direction=1;//head moving towards right
    for(int i=head;i<200;i+=direction){

        // Traversing Request queue
        for(int j=0;j<p;j++){
            if(request[j]==i){
                total_head_movement+=abs(head-request[j]);
                head=request[j];
                serviced++;
                printf("%d ",head);
                request[j]=-1;
            }     
        }
        if(i==199){
                direction=-1;
                total_head_movement+=abs(head-199);
                head=199;
                printf("%d ",head);
        }

        if (serviced==p){
            break;
        }
        
    }
    printf("\nTotal head movement: %d\n",total_head_movement);
}