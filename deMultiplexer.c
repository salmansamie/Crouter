
/*
Function: deMultiplex packets from the main queue to their output Queues.

Definition of layer 3 structure:
NOTE: Layer 3's packet is the payload of layer 2. It is stored in an array of defineable length

using the extern variable L2MAXLOAD
Structure of L2PAYLOAD[L2MAXLOAD]
L2PAYLOAD[0][1]: Layer 3 source address      //needs to be changed to an int
L2PAYLOAD[2][3]: Layer 3 destination address // also needs to be changed to an int
L2PAYLOAD[4]: priority
L2PAYLOAD[5] and above: Layer 3 payload

*/

	
#include <stdio.h>
#include "queues.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern int L3MAXLOAD;
int numOfChecksOf[6];


void deMultiplexer(int mainQSize){


 		enum inputQueues { mainQ = 5, outPtQA, outPtQB, outPtQC, outPtQD, outPtQE };	
 		struct l2Packet *deqdPakt = NULL;
 		int srcAdrsL3, dstAdrsL3, l2PayLoadLen, i, l3LoadLen, rndmNum;
 		char l3SrcAdrs[3] = {'0','0','\0'};
 		char l3DstAdrs[3] = {'0','0', '\0'};

 		char l3Payload[L3MAXLOAD];

    //return after doing nothing if main queue is empty, but increment the no. of times that main queue has been checked. 
    if (queueSize(mainQ) == 0){
      numOfChecksOf[mainQ]++;
      #ifdef DEBUGDEMUL
      printf("if no of checks: %d\n", numOfChecksOf[mainQ] );
      display(mainQ);
      #endif

      return;
    }
    else{
      numOfChecksOf[mainQ]++;

      #ifdef DEBUGDEMUL  
      printf("num of checks: %d\n", numOfChecksOf[mainQ] );
      display(mainQ); 
      puts("I got here in deMultiplexer");
      #endif


      if(queueSize(mainQ) == mainQSize){
        deqdPakt = (struct l2Packet*) dequeue(mainQ);  //!!!!Remember to free deqdPakt
        numOfChecksOf[mainQ] = 0;
      }
      else if(queueSize(mainQ) < mainQSize){
        if(numOfChecksOf[mainQ] == mainQSize){
          deqdPakt = (struct l2Packet*) dequeue(mainQ);
          numOfChecksOf[mainQ] = 0;
        }
      }

      #ifdef DEBUGDEMUL
      puts("I also got here in deMultiplexer");
      #endif


/*
EXTRACT LAYER 3 PACKET:

Extract l3 packet from l2 packet, only if the de-queued packet has information in it.
l3 source and destination address are converted from characters to integers
*/
      if ( deqdPakt != NULL){
     		l3SrcAdrs[0] = deqdPakt->l2PayLoad[0];
     		l3SrcAdrs[1] = deqdPakt->l2PayLoad[1];
     		sscanf(l3SrcAdrs, "%d", &srcAdrsL3);

     		l3DstAdrs[0] = deqdPakt->l2PayLoad[2];
     		l3DstAdrs[1] = deqdPakt->l2PayLoad[3];
        dstAdrsL3 = atoi(l3DstAdrs);

    	//end conversion
        #ifdef DEBUGDEMUL
        puts("I got here as well in deMultiplexer");
        #endif


/*
EXTRACT LAYER 3 PAYLOAD:
Copy the portion of layer 2's payload, which contains layer 3's payload, 
into the array which stores layer 3's payload
*/
    		l2PayLoadLen = strlen(deqdPakt->l2PayLoad);

        #ifdef DEBUGDEMUL
        puts(deqdPakt->l2PayLoad);
        #endif

        l3LoadLen = l2PayLoadLen - 4;
        char fullL3Load[l3LoadLen];

    		for (i = 0; i < l3LoadLen; i++){
          fullL3Load[i] = deqdPakt->l2PayLoad[i + 4];
    		}
        
        strcpy(l3Payload, fullL3Load);
        l3Payload[L3MAXLOAD] = '\0';

// End extraction of payload
// End extraction of packet
      

        #ifdef DEBUGDEMUL
        puts("I got here in deMultiplexer, past payload extraction");
        printf("%s\n", deqdPakt->l2PayLoad);   
        #endif
        //printf("Source address: %d | destination address: %d | %s\n", srcAdrsL3, dstAdrsL3, l3Payload);


/*
Final part of function:
Enqueue packets onto correct output queue.
Using original L2 payload in case user did not enter sufficient l3payload size
*/
        srand(time(NULL));
        switch(dstAdrsL3){
        case 1:
          enqueue('R','A', deqdPakt->l2PayLoad, outPtQA);
          break;
        case 2:
          enqueue('R','A', deqdPakt->l2PayLoad, outPtQA);
          break;
        case 3:
          enqueue('R','A', deqdPakt->l2PayLoad, outPtQA);
          break;
        case 4:
          enqueue('R','B', deqdPakt->l2PayLoad, outPtQB);
          break;
        case 5:
          enqueue('R','B', deqdPakt->l2PayLoad, outPtQB);
          break;
        case 6:
          enqueue('R','B', deqdPakt->l2PayLoad, outPtQB);
          break;
        case 7:
          rndmNum = 1 + (rand() % 2);
          if (rndmNum == 1){
          enqueue('R', 'C', deqdPakt->l2PayLoad, outPtQC);
          }
          else{
          enqueue('R', 'D', deqdPakt->l2PayLoad, outPtQD);
          }
          break;
        case 8:
          rndmNum = 1 + (rand() % 2);
          if (rndmNum == 1){
          enqueue('R', 'C', deqdPakt->l2PayLoad, outPtQC);
          }
          else{
          enqueue('R', 'D', deqdPakt->l2PayLoad, outPtQD);
          }
          break;
        case 9:
          rndmNum = 1 + (rand() % 2);
          if (rndmNum == 1){
          enqueue('R', 'C', deqdPakt->l2PayLoad, outPtQC);
          }
          else{
          enqueue('R', 'D', deqdPakt->l2PayLoad, outPtQD);
          }
          break;
        case 10:
          enqueue('R','D', deqdPakt->l2PayLoad, outPtQD);
          break;
        case 11:
          enqueue('R','D', deqdPakt->l2PayLoad, outPtQD);
          break;
        case 12:
          enqueue('R','D', deqdPakt->l2PayLoad, outPtQD);
          break;
        default:
        {break;}
        //puts("Oh boy, what a mistake you've made!");
        }

    }
    else{       //if the dequeued packet was empty, return without doing anything
      return;
    }

  }

 }
//end deMultiplexer
