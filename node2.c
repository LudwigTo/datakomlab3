#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;
extern int NODEAMOUNT;
extern int INFINITY;


struct distance_table
{
  int costs[4][4];
} dt2;

int optimal2[4];

/* students to write the following two routines, and maybe some others */

void updateNeighbors2()
{
  struct rtpkt* pkt_to_0 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_1 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_3 = malloc(sizeof(struct rtpkt));

  creatertpkt(pkt_to_0, 2, 0, optimal2);
  creatertpkt(pkt_to_1, 2, 1, optimal2);
  creatertpkt(pkt_to_3, 2, 3, optimal2);

  tolayer2(*pkt_to_0);
  tolayer2(*pkt_to_1);
  tolayer2(*pkt_to_3);

  free(pkt_to_0);
  free(pkt_to_1);
  free(pkt_to_3);
}

int generateOptimal2(int costs[4][4])
{
  int changed = 0; //If there has been a change to the optimal paths
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    int lowest = INFINITY;
    int current = optimal2[i]; //Old optimal path
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      if(costs[i][j] < lowest) lowest = costs[i][j];
    }
    optimal2[i] = lowest;
    if(current != optimal2[i]) changed = 1; //If there has been a change
  }
  return changed;
}

void rtinit2()
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      dt2.costs[i][j] = INFINITY;
    }
  }
  dt2.costs[0][0] = 3;
  dt2.costs[1][1] = 1;
  dt2.costs[3][3] = 2;

  generateOptimal2(dt2.costs);
  updateNeighbors2();
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    dt2.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + optimal2[rcvdpkt->sourceid];
  }
  if(generateOptimal2(dt2.costs))
  {
    updateNeighbors2(optimal2);
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
