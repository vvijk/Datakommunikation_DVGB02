#include <stdio.h>

#include "sim_engine.h"
#include "otw.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt1;

void rtinit1() {
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      dt1.costs[i][j] = 999;     
    }
  }
  dt1.costs[0][1] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[2][1] = 1;
  pkt_dispatcher3000(0, 1, dt1.costs);
  pkt_dispatcher3000(2, 1, dt1.costs);
}
void rtupdate1(struct rtpkt *rcvdpkt) {
  if(update(rcvdpkt->sourceid, &dt1, rcvdpkt)){
    pkt_dispatcher3000(0, 1, dt1.costs);
    pkt_dispatcher3000(2, 1, dt1.costs);
  }else{
    printMatrix(dt1.costs, 1);
  }
}
void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}


