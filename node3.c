#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;
extern int NODEAMOUNT;
extern int INFINITY;


struct distance_table
{
  int costs[4][4];
} dt3;

int optimal3[4];

/* students to write the following two routines, and maybe some others */

void updateNeighbors3()
{
  struct rtpkt* pkt_to_0 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_2 = malloc(sizeof(struct rtpkt));

  creatertpkt(pkt_to_0, 3, 0, optimal3);
  creatertpkt(pkt_to_2, 3, 2, optimal3);

  tolayer2(*pkt_to_0);
  tolayer2(*pkt_to_2);

  free(pkt_to_0);
  free(pkt_to_2);
}

int generateOptimal3(int costs[4][4])
{
  int changed = 0; //If there has been a change to the optimal paths
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    int lowest = INFINITY;
    int current = optimal3[i]; //Old optimal path
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      if(costs[i][j] < lowest) lowest = costs[i][j];
    }
    optimal3[i] = lowest;
    if(current != optimal3[i]) changed = 1; //If there has been a change
  }
  return changed;
}

void rtinit3()
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      dt3.costs[i][j] = INFINITY;
    }
  }
  dt3.costs[0][0] = 7;
  dt3.costs[2][2] = 2;

  generateOptimal3(dt3.costs);
  updateNeighbors3();
}


void rtupdate3(struct rtpkt *rcvdpkt)
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    dt3.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + optimal3[rcvdpkt->sourceid];
  }
  if(generateOptimal3(dt3.costs))
  {
    updateNeighbors3(optimal3);
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
