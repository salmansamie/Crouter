
// Struct of the layer 2 packet

struct l2Packet{
  char srcAdrs;   //source address
  char dstAdrs;   //destination address
  struct l2Packet *ptr;
  char l2PayLoad[];
  
} *front[11], *rear[11], *temp[11], *front2[11];

void enqueue(char srcAdrs, char dstAdrs, char l2PayLoad[], int packDstQ);
struct l2Packet* dequeue(int packDstQ);
void create(int packDstQ);
int queuesize(int packDstQ);
void display(int packDstQ);
    