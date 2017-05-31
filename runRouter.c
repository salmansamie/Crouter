
// runRouter runs the whole program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "externVariables.h"

int L2MAXLOAD;
int L3MAXLOAD;
void main(){	 
  enum inputQueues {inptQA, inptQB, inptQC, inptQD, inptQE, mainQ, outPtQA, outPtQB, outPtQC, outPtQD, outPtQE };

     // This piece of code sets the length of layer two's payload array.
     int l2PayLoadLength;
     int l3PayLoadLength;
     int out = 0;
     int out1 = 0;

     while(out == 0){
        puts("Enter layer 2 pay load array length | Must not be < 5 or > 30");
        scanf("%d", &l2PayLoadLength);

        if(l2PayLoadLength >= 4 && l2PayLoadLength <= 30){
           L2MAXLOAD = l2PayLoadLength;
           out = 1;
        }
        else{
           out = 0;
        }
     }

     while(out1 == 0){
        puts("Enter layer 3 pay load array length | Must not be > 28");
        scanf("%d", &l3PayLoadLength);

        if(l3PayLoadLength <= 28 && l3PayLoadLength > -1){
           L3MAXLOAD = l3PayLoadLength;
           out1 = 1;
        }
        else{
           out1 = 0;
        }
     }      //end setting of layer two array length.
    feeder();

puts("\n\nPackets in ecs501's input Queue A");
puts("------------------------------------");
display(inptQA);

puts("\n\nPackets in ecs501's input Queue B");
puts("------------------------------------");
display(inptQB);

puts("\n\nPackets in ecs501's input Queue C");
puts("------------------------------------");
display(inptQC);

puts("\n\nPackets in ecs501's input Queue D");
puts("------------------------------------");
display(inptQD);

puts("\n\nPackets in ecs501's input Queue E");
puts("------------------------------------");
display(inptQE);

puts("\n\nPackets in ecs501's main Queue");
puts("------------------------------------");
display(mainQ);

puts("\n\nPackets in ecs501's output Queue A");
puts("------------------------------------");
display(outPtQA);

puts("\n\nPackets in ecs501's output Queue B");
puts("------------------------------------");
display(outPtQB);

puts("\n\nPackets in ecs501's output Queue C");
puts("------------------------------------");
display(outPtQC);

puts("\n\nPackets in ecs501's output Queue D");
puts("------------------------------------");
display(outPtQD);

puts("\n\nPackets in ecs501's output Queue E");
puts("------------------------------------");
display(outPtQE);

}
//end main()


/********************************************************/

/*
Tester function;  part of the user interface
and placed here for conveinience. This piece of
code is no longer used in this program. 
*/
void testerFunction(){
    int choice, control, Q;
    char waste;
    struct l2Packet *deqdPakt;

    //User interface for debugging queues.
    control = 1;
    while(control){
        puts("Choose queue:");
        puts("0 - inputQueueA");
        puts("1 - inputQueueB");
        puts("2 - inputQueueC");
        puts("3 - inputQueueD");
        puts("4 - inputQueueE");
        puts("5 - mainQueue");
        scanf("%d", &Q);
        waste = getchar();

        printf("1 - Dequeue\n");
        printf("2 - Queue Size\n");
        printf("3 - Display queue\n");
        printf("4 - stop and exit\n");
        printf("Enter choice: \n");
        scanf("%d", &choice);
        waste = getchar();

        switch (choice){
        case 1:
            deqdPakt = (struct l2Packet*) dequeue(Q);
            free(deqdPakt);
            break;
        case 2:
            printf("The queue has %d nodes.\n", queueSize(Q));
            break;
        case 3:
            display(Q);
            break;
        case 4:
            //I need to empty the queue on exit
            control = 0;
        default:
            break;
        }   //end queue control switch statement
    }   //end queue control while loop and GUI
}//end testerFunction()


