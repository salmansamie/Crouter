
// Function: multiplex input Queues onto the main queue using a round robin like system.

#include <stdlib.h>
#include <stdio.h>
#include "multiplexer.h"
#include "queues.h"

int numOfChecksOf[6];

void multiplexer(int inptQSize, int mainQSize){

	enum inputQueues {inptQA, inptQB, inptQC, inptQD, inptQE, mainQ};
	int inputQueue[5] = {inptQA, inptQB, inptQC, inptQD, inptQE};		//for ease of understanding the for loop
	int dequedInputQ, loopControl, i;
	char waste;
	struct l2Packet *deqdPakt;

    #ifdef DEBUGMULTIPLEX
    	puts("I got here");
    #endif

//	Choose which input queue to dequeue onto the main queue.
//	Choice depends on size of input queues	
	for (i = 0; i < inptQE; i++){
		if(queueSize(inputQueue[i]) == inptQSize){
			dequedInputQ = inputQueue[i];
			break;
		}
		else if(queueSize(inputQueue[i]) < inptQSize && queueSize(inputQueue[i]) != 0 ){
			numOfChecksOf[inputQueue[i]]++;

			#ifdef DEBUGMULTIPLEX
			printf("%d\n", numOfChecksOf[inputQueue[i]] );
			#endif

			if(numOfChecksOf[inputQueue[i]] == inptQSize){

				dequedInputQ = inputQueue[i];
				numOfChecksOf[inputQueue[i]] = 0;

				#ifdef DEBUGMULTIPLEX
    				puts("I got in this if");
    			#endif
    			break;
			}
		}
	}
// end choosing

    #ifdef DEBUGMULTIPLEX
    	puts("I got here too");
    #endif


//Dequeue the chosen input queue.
		switch (dequedInputQ){
	  	case inptQA:

	   		if(queueSize(mainQ) < mainQSize){
	   			if(queueSize(inptQA)>0){
	   			deqdPakt = (struct l2Packet*) dequeue(inptQA);
	   			if(deqdPakt == NULL)
	   			{break;}
	   			enqueue(deqdPakt->srcAdrs, deqdPakt->dstAdrs, deqdPakt->l2PayLoad, mainQ);
	   			free(deqdPakt);
	   			}
	   		}
	   		break;

	   	case inptQB:

	   		if(queueSize(mainQ) < mainQSize){
	   			if(queueSize(inptQB)>0){
	   			deqdPakt = (struct l2Packet*) dequeue(inptQB);
	   			if(deqdPakt == NULL)
	   			{break;}
	   			enqueue(deqdPakt->srcAdrs, deqdPakt->dstAdrs, deqdPakt->l2PayLoad, mainQ);
	   			free(deqdPakt);
	   			}
		   	}
	   		break;

	   	case inptQC:

	   		if(queueSize(mainQ) < mainQSize){
	   			if(queueSize(inptQC)>0){
	   			deqdPakt = (struct l2Packet*) dequeue(inptQC);
	   			if(deqdPakt == NULL)
	   			{break;}
	   			enqueue(deqdPakt->srcAdrs, deqdPakt->dstAdrs, deqdPakt->l2PayLoad, mainQ);
	   			free(deqdPakt);
	   			}
	   		}
	   		break;

	   	case inptQD:

	   		if(queueSize(mainQ) < mainQSize){
	   			if(queueSize(inptQD)>0){
	   			deqdPakt = (struct l2Packet*) dequeue(inptQD);
	   			if(deqdPakt == NULL)
	   			{break;}
	   			enqueue(deqdPakt->srcAdrs, deqdPakt->dstAdrs, deqdPakt->l2PayLoad, mainQ);
	   			free(deqdPakt);
	   			}
	   		}
	   		break;

	   	case inptQE:

	   		if(queueSize(mainQ) < mainQ){
	   			if(queueSize(inptQE)>0){
	   			deqdPakt = (struct l2Packet*) dequeue(inptQE);
	   			if(deqdPakt == NULL)
	   			{break;}
	   			enqueue(deqdPakt->srcAdrs, deqdPakt->dstAdrs, deqdPakt->l2PayLoad, mainQ);
	   			free(deqdPakt);
	   			}		
	   		}
	   		break;	

	   	default:
	   		//puts("Error: Input Queue chosen does not exist or invalid option.");
	   		break;
	 	}
}

