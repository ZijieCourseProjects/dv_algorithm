//
// Created by Eric Zhao on 19/5/2022.
//

#ifndef DV__FUNC_H_
#define DV__FUNC_H_

struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
};

struct event {
  double evtime;           /* event time */
  int evtype;             /* event type code */
  int eventity;           /* entity where event occurs */
  struct rtpkt *rtpktptr; /* ptr to packet (if any) assoc w/ this event */
  struct event *prev;
  struct event *next;
};

void rtupdate0(struct rtpkt *rcvdpkt);
void rtupdate1(struct rtpkt *rcvdpkt);
void rtupdate2(struct rtpkt *rcvdpkt);
void rtupdate3(struct rtpkt *rcvdpkt);

void linkhandler0(int linkid, int newcost);
void linkhandler1(int linkid, int newcost);

void rtinit0();
void rtinit1();
void rtinit2();
void rtinit3();

void insertevent(struct event *p);

double jimsrand();

void tolayer2(struct rtpkt packet);

int min(int *array,int n);

struct rtpkt generate_packet(int source,int dest, int *mincost);
void update_min_cost(int *min_cost,int costs[4][4]);
void broadcast_with_ignore(int source, int *mincost, int ignore);
void broadcast(int source, int *mincost);


#endif //DV__FUNC_H_
