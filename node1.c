#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;
extern int NODEAMOUNT;
extern int INFINITY;


struct distance_table
{
  int costs[4][4];
} dt1;

int optimal1[4];

/* students to write the following two routines, and maybe some others */

void updateNeighbors1()
{
  struct rtpkt* pkt_to_0 = malloc(sizeof(struct rtpkt));
  struct rtpkt* pkt_to_2 = malloc(sizeof(struct rtpkt));

  creatertpkt(pkt_to_0, 1, 0, optimal1);
  creatertpkt(pkt_to_2, 1, 2, optimal1);

  tolayer2(*pkt_to_0);
  tolayer2(*pkt_to_2);

  free(pkt_to_0);
  free(pkt_to_2);
}

int generateOptimal1(int costs[4][4])
{
  int changed = 0; //If there has been a change to the optimal paths
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    int lowest = INFINITY;
    int current = optimal1[i]; //Old optimal path
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      if(costs[i][j] < lowest) lowest = costs[i][j];
    }
    optimal1[i] = lowest;
    if(current != optimal1[i]) changed = 1; //If there has been a change
  }
  return changed;
}

void rtinit1()
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    for(int j = 0; j < NODEAMOUNT; j++)
    {
      dt1.costs[i][j] = INFINITY;
    }
  }

  dt1.costs[1][1] = 1;
  dt1.costs[2][2] = 1;
  generateOptimal1(dt1.costs);
  updateNeighbors1();
}


void rtupdate1(struct rtpkt *rcvdpkt)
{
  for(int i = 0; i < NODEAMOUNT; i++)
  {
    dt1.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + optimal1[rcvdpkt->sourceid];
  }
  if(generateOptimal1(dt1.costs))
  {
    updateNeighbors1(optimal1);
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
