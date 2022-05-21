#include <stdio.h>
#include "func.h"



extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt2;

int connectcosts2[] = {3,1,0,2};
const int physical2[] = {3,1,0,2};


void printdt2(struct distance_table *dtptr);
/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
  int i,j;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      dt2.costs[i][j]=999;
    }
  }

  for(int i=0;i<4;i++){
    dt2.costs[i][i]=connectcosts2[i];
  }

  broadcast(2,connectcosts2);
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
  int source = rcvdpkt->sourceid;
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if(i == source) continue;
    if (dt2.costs[i][source] > rcvdpkt->mincost[i] + physical2[source]){
      dt2.costs[i][source] = rcvdpkt->mincost[i] + physical2[source];
      flag = 1;
    }
  }
  if (flag){
    update_min_cost(connectcosts2,dt2.costs);
    broadcast(2,connectcosts2);
    printdt2(&dt2);
  }
}


void printdt2(struct distance_table *dtptr)
{
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







