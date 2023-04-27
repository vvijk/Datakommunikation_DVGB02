#include <stdio.h>

#include "sim_engine.h"
#include "otw.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt3;

void rtinit3() {
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      dt3.costs[i][j] = 999;     
    }
  }
  dt3.costs[0][3] = 7;
  dt3.costs[2][3] = 2;
  dt3.costs[3][3] = 0;
  pkt_dispatcher3000(0, 3, dt3.costs);
  pkt_dispatcher3000(2, 3, dt3.costs);
}
void rtupdate3(struct rtpkt *rcvdpkt) {
  if(update(rcvdpkt->sourceid, &dt3, rcvdpkt)){
    pkt_dispatcher3000(0, 3, dt3.costs);
    pkt_dispatcher3000(2, 3, dt3.costs);
  }else{
    printMatrix(dt3.costs, 3);
  }
}
void printdt3(struct distance_table *dtptr) {
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}







