//
// Created by Eric Zhao on 19/5/2022.
//

#include <string.h>
#include "stdarg.h"
#include "func.h"


int min(int *array,int n){
  int result = array[0];
  for (int i = 1; i < n; ++i) {
    if(array[i] < result) result = array[i];
  }
  return result;
}


struct rtpkt generate_packet(int source,int dest, int *mincost){
  struct rtpkt packet;
  packet.sourceid = source;
  packet.destid = dest;
  memcpy(packet.mincost, mincost,sizeof(int) * 4);
  return packet;
}

void update_min_cost(int min_cost[4],int costs[4][4]){
  min_cost[0] = min(costs[0], 4);
  min_cost[1] = min(costs[1], 4);
  min_cost[2] = min(costs[2], 4);
  min_cost[3] = min(costs[3], 4);
}

void broadcast_with_ignore(int source, int *mincost,int ignore){
  for (int i = 0; i < 4; ++i) {
    if(i == source || i == ignore || mincost[i] == 999) continue;
    tolayer2(generate_packet(source,i,mincost));
  }
}

void broadcast(int source, int *mincost){
  for (int i = 0; i < 4; ++i) {
    if(i == source || mincost[i] == 999) continue;
    tolayer2(generate_packet(source,i,mincost));
  }
}