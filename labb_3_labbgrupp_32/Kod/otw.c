#include "sim_engine.h"
#include "otw.h"
#include <stdio.h>
#include <stdbool.h>

/*pkt.destid = to
pkt.sourceid = from
pkt.mincost[] = dt[1-4][from]
tolayer2(pkt)*/
// struct distance_table {
//   int costs[4][4];
// };

void pkt_dispatcher3000(int to, int from, int dt[4][4]){
  struct rtpkt pkt;
  pkt.sourceid = from;
  pkt.destid = to;
  for(int i = 0; i < 4; i++){
    pkt.mincost[i] = dt[i][from];
  }
  tolayer2(pkt);
}

bool update(int src_id, struct distance_table *dt, struct rtpkt *r_packet){
  bool updated = false;

  for(int i = 0; i < 4; i++){
    if(i != src_id){
      for(int j = 0; j < 4; j++){
        if(dt->costs[i][j] > r_packet->mincost[i] + dt->costs[src_id][j]){
          dt->costs[i][j] = r_packet->mincost[i] + dt->costs[src_id][j];
          updated = true;
        }
      }      
    }
  }
  return updated;
}
//KIRE
void printMatrix(int costs[4][4], int node){
     for(int i=0; i<4; i++){
      g_dt.costs[i][node] = costs[i][node];
    }
    printf("\n   D%d |    0    1    2    3 \n", node);
    printf("------|---------------------\n", node);
    printf("     0|  %3d  %3d  %3d  %3d \n", g_dt.costs[0][0], g_dt.costs[0][1], g_dt.costs[0][2], g_dt.costs[0][3]);
    printf("     1|  %3d  %3d  %3d  %3d \n", g_dt.costs[1][0], g_dt.costs[1][1], g_dt.costs[1][2], g_dt.costs[1][3]);
    printf("     2|  %3d  %3d  %3d  %3d \n", g_dt.costs[2][0], g_dt.costs[2][1], g_dt.costs[2][2], g_dt.costs[2][3]);
    printf("     3|  %3d  %3d  %3d  %3d \n", g_dt.costs[3][0], g_dt.costs[3][1], g_dt.costs[3][2], g_dt.costs[3][3]);
}