#include "prog3.h"

extern int NODEAMOUNT;
extern int INFINITY;
extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt0;

int optimal0[4]; //The array showing the optimal weights to each node

/* students to write the following two routines, and maybe some others */

void updateNeighbors0()
{
  struct rtpkt* pkt_to_1 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_2 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_3 = malloc(sizeof(struct rtpkt));

  creatertpkt(pkt_to_1, 0, 1, optimal0);
  creatertpkt(pkt_to_2, 0, 2, optimal0);
  creatertpkt(pkt_to_3, 0, 3, optimal0);

  tolayer2(*pkt_to_1);
  tolayer2(*pkt_to_2);
  tolayer2(*pkt_to_3);

  free(pkt_to_1);
  free(pkt_to_2);
  free(pkt_to_3);
}

int generateOptimal0(int costs[4][4])
{
  int changed = 0; //If there has been a change to the optimal paths
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    int lowest = INFINITY;
    int current = optimal0[i]; //Old optimal path
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      if(costs[i][j] < lowest) lowest = costs[i][j];
    }
    optimal0[i] = lowest;
    if(current != optimal0[i]) changed = 1; //If there has been a change
  }
  return changed;
}


void rtinit0()
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      dt0.costs[i][j] = INFINITY;
    }
  }
  dt0.costs[1][1] = 1;
  dt0.costs[2][2] = 3;
  dt0.costs[3][3] = 7;

  generateOptimal0(dt0.costs);
  updateNeighbors0();
}


void rtupdate0(struct rtpkt *rcvdpkt)
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    dt0.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + optimal0[rcvdpkt->sourceid];
  }
  if(generateOptimal0(dt0.costs))
  {
    updateNeighbors0(optimal0);
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
