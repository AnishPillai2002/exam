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

    int head;
    printf("Enter the current head position: ");
    scanf("%d",&head);

    int serviced=0;
    int total_head_movement=0;

    printf("Service order: %d ",head);
    for(int i=head;i<200;i++){

        for(int j=0;j<p;j++){

            if(request[j]==i){

                total_head_movement+=abs(head-request[j]);
                head=request[j];
                request[j]=-1;
                serviced++;
                printf("%d ",head);
            }
        }

        if (i==199){
            total_head_movement+=abs(head-199);
            head=199;
            printf("%d ",head);
            total_head_movement+=abs(head-0);
            head=0;
            printf("%d ",head);
            i=-1;
        }
        
        if(serviced==p){
            break;
        }
    }

    printf("\nTotal head movement: %d\n",total_head_movement);
}