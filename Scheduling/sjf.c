#include<stdio.h>

typedef struct{

    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completion_time;
    
}process;


void SJF(process p[],int n){

    int current_time=0;
    int completed=0;

    while (completed<n){
        int shortest_job=9999;
        int sjf_index=-1;
        
        //searching each process
        for (int i = 0; i < n; i++){
            
            if (p[i].arrival_time<=current_time && p[i].remaining_time>0 && p[i].remaining_time<shortest_job){
                
                shortest_job=p[i].remaining_time;
                sjf_index=i;
            }   
        }

        //checking if dont have sjf process at this current_time
        if (sjf_index==-1){
            current_time++;
            continue;
        }

        // we got sjf_index
        p[sjf_index].completion_time=current_time+p[sjf_index].burst_time;
        p[sjf_index].turnaround_time=p[sjf_index].completion_time-p[sjf_index].arrival_time;
        p[sjf_index].waiting_time=p[sjf_index].turnaround_time-p[sjf_index].burst_time;

        p[sjf_index].remaining_time=0;
        current_time=p[sjf_index].completion_time;
        completed++;
    }
}


int main(){
    process p[10];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    //read process details
    printf("Enter the process details (AT BT): \n");
    for (int i = 0; i < n; i++){
        printf("Process %d: ",i+1);
        scanf("%d %d",&p[i].arrival_time,&p[i].burst_time);
        p[i].pid=i+1;
        p[i].remaining_time=p[i].burst_time;
    }

    SJF(p,n);

    //printing details
    printf("\n\nProcess Details: \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    printf("\n");

}