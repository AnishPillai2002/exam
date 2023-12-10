#include<stdio.h>


typedef struct{

    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completion_time;
    int status;//checking if its in ready queue or not
}process;

//Global Ready Queue
int queue[10];
int front=-1;
int rear=-1;


//Function to Enqueue
void Enqueue(int n){
    if (front==-1 && rear==-1){
        front=0;
        rear=0;
        queue[rear]=n;
    }
    else
    {
        rear++;
        queue[rear]=n;
    } 
}

//Function to Dequeue
int Dequeue(){

    //Empty Queue
    if(front==-1 && rear==-1){
        return -1;
    }
    else if(front==rear){
        int temp=queue[front];
        front=-1;
        rear=-1;
        return temp;
    }
    else{
        int temp=queue[front];
        front++;
        return temp;
    }
}

//Function to Perform Round Robin Scheduling
void RoundRobin(process p[],int quantum,int n){

    int quantum_count=0;
    int dequeued_process=-1;
    int current_time=0;
    int count=0;

    //if current time != arrival time of first process
    while(current_time!=p[0].arrival_time){
        current_time++;
    }

    //initilizing first process
    Enqueue(0);
    p[0].status=1;

    while (count<n){

        if (dequeued_process==-1){
            dequeued_process=Dequeue();
        }

        current_time++;

        //Checking for new process to be moved to ready queue
        for (int i = 0; i < n; i++){
            if (p[i].arrival_time<current_time && p[i].status==0){
                Enqueue(i);
                p[i].status=1;
            }        
        }

        //Checking if the dequeued process is completed or not
        if(dequeued_process!=-1){
            if( quantum_count<quantum && p[dequeued_process].remaining_time>0){
                p[dequeued_process].remaining_time--;
                quantum_count++;
            }
            if(p[dequeued_process].remaining_time==0){
                p[dequeued_process].completion_time=current_time;
                p[dequeued_process].turnaround_time=p[dequeued_process].completion_time-p[dequeued_process].arrival_time;
                p[dequeued_process].waiting_time=p[dequeued_process].turnaround_time-p[dequeued_process].burst_time;
                count++;
                dequeued_process=-1;
                quantum_count=0;
            }
            else if(quantum_count==quantum){
                Enqueue(dequeued_process);
                dequeued_process=-1;
                quantum_count=0;
            }
        }     
    }  
}

//MAIN
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
        p[i].status=0;
    }

    int quantum;
    printf("Enter the quantum time: ");
    scanf("%d",&quantum);

    //Round Robin
    RoundRobin(p,quantum,n);

    // Printing the Process Details
    printf("\n\nProcess Details: \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    printf("\n");
}