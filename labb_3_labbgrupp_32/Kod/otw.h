#ifndef OTW_H
#define OTW_H

#include <stdbool.h>
struct distance_table {
  int costs[4][4];
};

struct distance_table g_dt; 

void pkt_dispatcher3000(int to, int from, int dt[4][4]);
bool update(int src_id, struct distance_table *dt, struct rtpkt *r_packet);
void printMatrix(int costs[4][4], int node);

#endif