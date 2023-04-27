#include <stdio.h>

#include "sim_engine.h"
#include "otw.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt0;

void rtinit0() {
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      dt0.costs[i][j] = 999;     
    }
  }
  dt0.costs[0][0] = 0;
  dt0.costs[1][0] = 1;
  dt0.costs[2][0] = 3;
  dt0.costs[3][0] = 7;
  pkt_dispatcher3000(1, 0, dt0.costs);
  pkt_dispatcher3000(2, 0, dt0.costs);
  pkt_dispatcher3000(3, 0, dt0.costs);
}
void rtupdate0(struct rtpkt *rcvdpkt) {
  if(update(rcvdpkt->sourceid, &dt0, rcvdpkt)){
    pkt_dispatcher3000(1, 0, dt0.costs);
    pkt_dispatcher3000(2, 0, dt0.costs);
    pkt_dispatcher3000(3, 0, dt0.costs);
  }else{
    printMatrix(dt0.costs, 0);
  }
}
void printdt0(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}
void linkhandler0(int linkid, int newcost) {
  /* DON'T CHANGE */
}
