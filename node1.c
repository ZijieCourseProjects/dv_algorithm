#include <stdio.h>
#include "func.h"


extern int TRACE;
extern int YES;
extern int NO;

int connectcosts1[4] = { 1,  0,  1, 999 };
const int physical1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;


void printdt1(struct distance_table *dtptr);
/* students to write the following two routines, and maybe some others */


void rtinit1(){
  int i,j;
  for(i=0;i<4;i++){
      for(j=0;j<4;j++){
          dt1.costs[i][j]=999;
      }
  }

  for(int i=0;i<4;i++){
    dt1.costs[i][i]=connectcosts1[i];
  }

  broadcast_with_ignore(1,connectcosts1,3);
}

void rtupdate1(struct rtpkt *rcvdpkt){
  int source = rcvdpkt->sourceid;
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if(i == source) continue;
    if (dt1.costs[i][source] > rcvdpkt->mincost[i] + physical1[source]){
      dt1.costs[i][source] = rcvdpkt->mincost[i] + physical1[source];
      flag = 1;
    }
  }
  if(flag){
    update_min_cost(connectcosts1,dt1.costs);
    broadcast_with_ignore(1,connectcosts1,3);
    printdt1(&dt1);
  }
}


void printdt1(struct distance_table *dtptr)
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}



void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


