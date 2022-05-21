#include <stdio.h>
#include "func.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt0;

void printdt0(struct distance_table *dtptr);

int connectcosts0[4] = {0,1,3,7};
const int physical0[4] = {0,1,3,7};

/* students to write the following two routines, and maybe some others */

void rtinit0()
{
  int i,j;
  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      dt0.costs[i][j] = 999;
  for (int k = 0; k < 4; ++k) {
    dt0.costs[k][k] = connectcosts0[k];
  }
  broadcast(0,connectcosts0);
}



void rtupdate0(struct rtpkt *rcvdpkt) {
  int source = rcvdpkt->sourceid;
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if(i == source) continue;
    if (dt0.costs[i][source] > rcvdpkt->mincost[i] + physical0[source]){
      flag  = 1;
      dt0.costs[i][source] = rcvdpkt->mincost[i] + physical0[source];
    }
  }
  if(flag){
    update_min_cost(connectcosts0,dt0.costs);
    broadcast(0,connectcosts0);
    printdt0(&dt0);
  }
}


void printdt0(struct distance_table *dtptr)
{
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

void linkhandler0(int linkid, int newcost)

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

