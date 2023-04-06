#include "Sim_Engine.h"
int inc, sequence;
int genCheckSum(struct pkt packet){
  int sum = 0;
  for(int i = 0; i < strlen(packet.payload); i++){
    sum += packet.payload[i];
  }
  return sum;
}

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
  /* TODO */
  /*Check corruption && seqnum*/
  if(packet.checksum == genCheckSum(packet) && packet.seqnum == sequence){
        
        sequence = inc % 2;
        inc++;
        tolayer3(B, packet);
        tolayer5(B, packet.payload);
  }
  else{
    tolayer3(B, packet);
  }
}
/* Called when B's timer goes off */
void B_timerinterrupt() {
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
  /* TODO */
  sequence = 1;
  inc = 0;
}
