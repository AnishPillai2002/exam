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



//Function to find shortest job
int shortestJob(process p[],int current_time,int n){
    int sj_index=-1;
    int sj_rt=9999;

    for(int i=0;i<n;i++){
        if(p[i].arrival_time<=current_time && p[i].remaining_time<sj_rt && p[i].remaining_time>0){
            sj_rt=p[i].remaining_time;
            sj_index=i;
        }
    }

    return sj_index;
}

//Function to perform Shortest Remaining Time First Scheduling

void SRTF(process p[],int n){

    int completed=0;
    int current_time=0;

    while(completed<n){

        int sj_index=shortestJob(p,current_time,n);

        if (sj_index==-1){
            current_time++;
            continue;
        }

        process *job=&p[sj_index];
        job->remaining_time--;
        

        if(job->remaining_time==0){
            completed++;
            job->completion_time=current_time+1;
            job->turnaround_time=job->completion_time-job->arrival_time;
            job->waiting_time=job->turnaround_time-job->burst_time;
        }
        current_time++;
    }
}

//Main Function
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
    

    SRTF(p,n);

    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for(int i=0;i<n;i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }

    return 0;

}