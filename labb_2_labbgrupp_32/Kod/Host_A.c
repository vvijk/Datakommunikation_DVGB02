#include "Sim_Engine.h"
#define A 0
#define B 1
#define PSIZE 2048
bool sending;
int incrementer;
int rear;
int front;
int qsize;
int seq;
struct pkt currPacket;
struct msg packArr[PSIZE];
int generateCheckSum(struct msg msg){
  int sum = 0;
  for(int i = 0; i < strlen(msg.data); i++){
    sum += msg.data[i];
  }
  return sum;
}
void enQ(struct msg message){
  rear += 1;
  memcpy(packArr[rear].data, message.data, sizeof(message.data));
  qsize++;
}
struct msg pop(){
  qsize--;
  front += 1;
  return packArr[front];
}
/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
  if(sending){
    enQ(message);
    // printf("[A]Waiting for ack...\n");
  }
  else{
    sending = true;
    incrementer++;
    seq = incrementer % 2;
    currPacket.acknum = seq;
    currPacket.seqnum = seq;
    memcpy(currPacket.payload, message.data, sizeof(message.data));
    currPacket.checksum = generateCheckSum(message);
    // printf("\033[0;32m[A]Sending!\033[0m acknum:%d, seqnum:%d, msg:%s, checksum:%d\n", currPacket.acknum, currPacket.seqnum, currPacket.payload, currPacket.checksum);
    starttimer(A, 30);
    tolayer3(A, currPacket);
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
  /* TODO */
  /* corrupt || fel ack = gör ingenting ?????*/ 
  /* Timeout = skicka samma paket och starta timer igen*/
  /* !corrupt && rätt ack = stoppa timmer & sending = false*/
  stoptimer(A);
  if(packet.acknum == seq){
    // printf("\033[0;32m[A]Correct ack recived. ack:%d seq:%d\033[0m\n", packet.acknum, seq);
    /*STOP TIMER && sending = true*/
    sending = false;
    if(qsize > 0){
      A_output(pop());
    }
  }else{
    // printf("\033[0;31m[A]Wrong ack recived\nResending package... ack:%d, seq:%d\n\033[0m\n", packet.acknum, seq);
    starttimer(A, 30);
    tolayer3(A, currPacket);
  }
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
  /* TODO */
  /*skicka paket && starta timer*/
  // printf("\033[0;31m[A]TIMEOUT... RESENDING PACKAGE\n\033[0m");
  starttimer(A, 30);
  tolayer3(A, currPacket);
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
  /* TODO */
  seq = 0;
  sending = false;
  incrementer = 0;
  front = 0;
  rear = 0;
  qsize = 0;
}
