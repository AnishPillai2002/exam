#include <stdio.h>

int main(){

    int numPage, numFrame, pageRequests[20],frame[20],pageFaults=0,currentIndex;
    
    int leastUsed[20],sortedLU[20];
    
    printf("Enter the number of frames: ");
    scanf("%d", &numFrame);
    printf("Enter the number of pages: ");
    scanf("%d", &numPage);

    
    printf("Enter the reference string: ");
    for (int i = 0; i < numPage; i++){
        scanf("%d", &pageRequests[i]);
    }

    //initilizing frame
    for(int i=0;i<numFrame;i++){
        frame[i]=-1; // -1 means empty frame
    }

    //initilizing
    int k=0;
    frame[k]=pageRequests[k];
    k++;
    pageFaults++;

    //printing frame
    for(int j=0;j<numFrame;j++){
        if(frame[j]==-1){
            printf("x ");
        }
        else{
            printf("%d ",frame[j]);
        }
    }
    printf("\n");

    //main loop
    for (int i = 1; i < numPage; i++){
        
        currentIndex=0;
        for (int j= 0; j < numFrame; j++){
            
            if (frame[j]!=pageRequests[i]){
                currentIndex++;
            }   
        }

        //pageFault occurs
        if (currentIndex==numFrame){
            
            pageFaults++;

            if (k<numFrame){
                frame[k]=pageRequests[i];
                k++;
            }
            else{

                // Calculate the least used page using LRU algorithm

                // Calculate least used count for each page in frames
                for (int r = 0; r < numFrame; r++) {     //iterate through frames
                    leastUsed[r] = 0;
                    for (int j = i - 1; j >= 0; j--) {    //previous page request (i - 1) and goes backward through the page requests array 
                        if (frame[r] != pageRequests[j]) {

                            //If the page in the frame does not match the page at index j in the request sequence, it increments the leastUsed count for that page.
                            leastUsed[r]++;
                        } else {
                            break;
                        }
                    }
                }

                //finding the least used page
                int lru_index=-1;
                int least=-1;

                for(int i=0;i<numFrame;i++){

                    if(leastUsed[i]>least){
                        least=leastUsed[i];
                        lru_index=i;
                    }
                }

                //replacing
                frame[lru_index]=pageRequests[i];                
            }   
        }

        //printing frame
        for(int j=0;j<numFrame;j++){
            if(frame[j]==-1){
                printf("x ");
            }
            else{
                printf("%d ",frame[j]);
            }
        }
        printf("\n");
        
    } 
    printf("Page Fault= %d \n",pageFaults);
    return 0;
}