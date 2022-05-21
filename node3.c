#include <stdio.h>
#include "func.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt3;

int connectcosts3[4] = {7,999,2,0};
const int physical3[4] = {7,999,2,0};
/* students to write the following two routines, and maybe some others */
void printdt3(struct distance_table *dtptr);

void rtinit3()
{
  int i,j;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      dt3.costs[i][j]=999;
    }
  }

  for(int i=0;i<4;i++){
    dt3.costs[i][i]=connectcosts3[i];
  }

  broadcast_with_ignore(3,connectcosts3,1);
}


void rtupdate3(struct rtpkt *rcvdpkt)
{
  int source = rcvdpkt->sourceid;
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if(i == source) continue;
    if (dt3.costs[i][source] > rcvdpkt->mincost[i] + physical3[source]){
      dt3.costs[i][source] = rcvdpkt->mincost[i] + physical3[source];
      flag  = 1;
    }
  }
  if (flag){
    update_min_cost(connectcosts3,dt3.costs);
    broadcast_with_ignore(3,connectcosts3,1);
    printdt3(&dt3);
  }
}


void printdt3(struct distance_table *dtptr)
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







