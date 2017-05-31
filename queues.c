
/*
Function: queues contains the implementation of the input queues to the router, which need 
to have a configurable maximum length, and be capable of storing the defined packets.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queues.h"

/*  
#define NUMOFQUEUES 11
I tried to use the above to set the no. of queues, currently 
set at 11 in the inputQueue.h headerfile by setting all the struct l2packet 
pointers to 11 - but it seems #define only works in functions and structures. 
*/

int L2MAXLOAD;

// creating an empty queue
void create(int packDstQ){
    // Read as front node of the queue that the packet is destined for gets the value
    front[packDstQ] = rear[packDstQ] = NULL;
}
//end create()


//enqueue adds a new node to the bottom of the queue
void enqueue(char srcAdrs, char dstAdrs, char l2PayLoad[], int packDstQ){
    #ifdef DEBUG
        puts(l2PayLoad);
    #endif


    if (rear[packDstQ] == NULL){
        rear[packDstQ] = malloc(sizeof(struct l2Packet) + L2MAXLOAD);
        rear[packDstQ]->ptr = NULL;
        rear[packDstQ]->srcAdrs = srcAdrs;
        rear[packDstQ]->dstAdrs = dstAdrs;
        strcpy(rear[packDstQ]->l2PayLoad, l2PayLoad);  /*  make sure to include string library*/
        rear[packDstQ]->l2PayLoad[L2MAXLOAD] = '\0';
        front[packDstQ] = rear[packDstQ];
    }
    else{
        temp[packDstQ] = malloc(sizeof(struct l2Packet) + L2MAXLOAD);
        rear[packDstQ]->ptr = temp[packDstQ];
        temp[packDstQ]->srcAdrs = srcAdrs;
        temp[packDstQ]->dstAdrs = dstAdrs;
        strcpy(temp[packDstQ]->l2PayLoad, l2PayLoad);
        temp[packDstQ]->l2PayLoad[L2MAXLOAD] = '\0';
        temp[packDstQ]->ptr =NULL;

        rear[packDstQ] = temp[packDstQ];
    }

    #ifdef DEBUG
    puts("I've loaded the structure");
    puts(rear -> l2PayLoad);
    #endif
} 
//end enqueue()



// dequeue removes a node from the top of the queue, and returns a pointer to it.
// this will have to return the structure so that it can be queued later on in the main queue
struct l2Packet* dequeue(int packDstQ){
    struct l2Packet *deqdNode = NULL;
    //deqdNode = malloc(sizeof(struct l2Packet) + L2MAXLOAD);
    front2[packDstQ] = front[packDstQ];

    if(front2[packDstQ] == NULL){
        printf("Do nothing because queue is empty\n");
    }
    else
        if (front2[packDstQ]->ptr != NULL){
            front2[packDstQ] =  front2[packDstQ]->ptr;
            front[packDstQ]->ptr = NULL;
            deqdNode = front[packDstQ];
            //printf("Dequeued values: %c, %c, %s\n", front[packDstQ]->srcAdrs, front[packDstQ]->dstAdrs, front[packDstQ]->l2PayLoad);
            front[packDstQ] = front2[packDstQ];
        }
        else{
            deqdNode = front[packDstQ];
            //printf("Dequeued values: %c, %c, %s\n", front[packDstQ]->srcAdrs, front[packDstQ]->dstAdrs, front[packDstQ]->l2PayLoad);
            front[packDstQ] = NULL;
            rear[packDstQ] = NULL;
        }
    return deqdNode;

}
//end dequeue()


// Display the queue nodes
void display(int packDstQ){
    front2[packDstQ] = front[packDstQ];
    if ((front2[packDstQ] == NULL) && (rear[packDstQ] == NULL)){
        printf("Error: cannot display empty queue\n");
        return;
    }
    while (front2[packDstQ] != rear[packDstQ]){
        printf("%c, %c, %s\n", front2[packDstQ]->srcAdrs, front2[packDstQ]->dstAdrs, front2[packDstQ]->l2PayLoad);
        front2[packDstQ] = front2[packDstQ]->ptr;
    }
    if (front2[packDstQ] == rear[packDstQ]){
        printf("%c, %c, %s\n", front2[packDstQ]->srcAdrs, front2[packDstQ]->dstAdrs, front2[packDstQ]->l2PayLoad);
    }
}
//end display()


//queueSize counts the number of nodes in the queue
int queueSize(int packDstQ){
    int count = 0;
    front2[packDstQ] = front[packDstQ];

    if ((front2[packDstQ] == NULL) && (rear[packDstQ] == NULL)){
        return count;
    }
    while (front2[packDstQ] != rear[packDstQ]){
        count++;
        front2[packDstQ] = front2[packDstQ]->ptr;
    }
    if (front2[packDstQ] == rear[packDstQ]){
        count++;
    }
    return count;
}
