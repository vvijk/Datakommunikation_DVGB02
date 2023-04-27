#include <stdio.h>

#include "sim_engine.h"
#include "otw.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt2;

void rtinit2() {
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      dt2.costs[i][j] = 999;     
    }
  }
  dt2.costs[0][2] = 3;
  dt2.costs[1][2] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[3][2] = 2;
  pkt_dispatcher3000(0, 2, dt2.costs);
  pkt_dispatcher3000(1, 2, dt2.costs);
  pkt_dispatcher3000(3, 2, dt2.costs);
}
void rtupdate2(struct rtpkt *rcvdpkt) {
  if(update(rcvdpkt->sourceid, &dt2, rcvdpkt)){
    pkt_dispatcher3000(0, 2, dt2.costs);  
    pkt_dispatcher3000(1, 2, dt2.costs);
    pkt_dispatcher3000(3, 2, dt2.costs);
  }else{
    printMatrix(dt2.costs, 2);
  }
}
void printdt2(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}