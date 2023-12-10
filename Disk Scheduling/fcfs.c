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
    int current_head;
    printf("Enter the current head position: ");
    scanf("%d",&current_head);
    printf("Service order: %d ",current_head);
    for(int i=0;i<p;i++){
        total_head_movement+=abs(current_head-request[i]);
        current_head=request[i];
        printf("%d ",current_head);
    }

    printf("\nTotal head movement: %d\n",total_head_movement);
}