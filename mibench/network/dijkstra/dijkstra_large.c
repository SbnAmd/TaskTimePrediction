#include <stdio.h>
#include "dijkstra.h"

#define NUM_NODES                          100
#define NONE                               9999

struct _NODE
{
  int iDist_large;
  int iPrev_large;
};
typedef struct _NODE NODE;

struct _QITEM
{
  int iNode_large;
  int iDist_large;
  int iPrev_large;
  struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;

QITEM *qHead_large = NULL;

             
             
             
int AdjMatrix_large[NUM_NODES][NUM_NODES];

int g_qCount_large = 0;
NODE rgnNodes_large[NUM_NODES];
int ch_large;
int iPrev_large, iNode_large;
int i_large, iCost_large, iDist_large;


void print_path_large (NODE *rgnNodes_large, int chNode)
{
  if (rgnNodes_large[chNode].iPrev_large != NONE)
    {
      print_path_large(rgnNodes_large, rgnNodes_large[chNode].iPrev_large);
    }
  printf (" %d", chNode);
  fflush(stdout);
}


void enqueue_large (int iNode_large, int iDist_large, int iPrev_large)
{
  QITEM *qNew = (QITEM *) malloc(sizeof(QITEM));
  QITEM *qLast = qHead_large;
  
  if (!qNew) 
    {
      fprintf(stderr, "Out of memory.\n");
      exit(1);
    }
  qNew->iNode_large = iNode_large;
  qNew->iDist_large = iDist_large;
  qNew->iPrev_large = iPrev_large;
  qNew->qNext = NULL;
  
  if (!qLast) 
    {
      qHead_large = qNew;
    }
  else
    {
      while (qLast->qNext) qLast = qLast->qNext;
      qLast->qNext = qNew;
    }
  g_qCount_large++;
  //               ASSERT(g_qCount_large);
}


void dequeue_large (int *piNode, int *piDist, int *piPrev)
{
  QITEM *qKill = qHead_large;
  
  if (qHead_large)
    {
      //                 ASSERT(g_qCount_large);
      *piNode = qHead_large->iNode_large;
      *piDist = qHead_large->iDist_large;
      *piPrev = qHead_large->iPrev_large;
      qHead_large = qHead_large->qNext;
      free(qKill);
      g_qCount_large--;
    }
}


int qcount_large (void)
{
  return(g_qCount_large);
}

int dijkstra_l(int chStart, int chEnd)
{
  

  
  for (ch_large = 0; ch_large < NUM_NODES; ch_large++)
    {
      rgnNodes_large[ch_large].iDist_large = NONE;
      rgnNodes_large[ch_large].iPrev_large = NONE;
    }

  if (chStart == chEnd) 
    {
      #ifdef PRINT_LOG
      printf("Shortest path is 0 in cost. Just stay where you are.\n");
      #endif
    }
  else
    {
      rgnNodes_large[chStart].iDist_large = 0;
      rgnNodes_large[chStart].iPrev_large = NONE;
      
      enqueue_large (chStart, 0, NONE);
      
     while (qcount_large() > 0)
	{
	  dequeue_large (&iNode_large, &iDist_large, &iPrev_large);
	  for (i_large = 0; i_large < NUM_NODES; i_large++)
	    {
	      if ((iCost_large = AdjMatrix_large[iNode_large][i_large]) != NONE)
		{
		  if ((NONE == rgnNodes_large[i_large].iDist_large) ||
		      (rgnNodes_large[i_large].iDist_large > (iCost_large + iDist_large)))
		    {
		      rgnNodes_large[i_large].iDist_large = iDist_large + iCost_large;
		      rgnNodes_large[i_large].iPrev_large = iNode_large;
		      enqueue_large (i_large, iDist_large + iCost_large, iNode_large);
		    }
		}
	    }
	}
      #ifdef PRINT_LOG
      printf("Shortest path is %d in cost. ", rgnNodes_large[chEnd].iDist_large);
      printf("Path is: ");
      print_path_large(rgnNodes_large, chEnd);
      printf("\n");
      #endif
    }
}

// int main(int argc, char *argv[]) {
int __dijkstra_large(int argc, char *argv[]) {
  int i,j,k;
  FILE *fp;
  
  #ifdef PRINT_LOG
  if (argc<2) {
    fprintf(stderr, "Usage: dijkstra_l <filename>\n");
    fprintf(stderr, "Only supports matrix size is #define'd.\n");
  }
  #endif

  /* open the adjacency matrix file */
  fp = fopen (argv[1],"r");

  /* make a fully connected matrix */
  for (i=0;i<NUM_NODES;i++) {
    for (j=0;j<NUM_NODES;j++) {
      /* make it more sparce */
      fscanf(fp,"%d",&k);
			AdjMatrix_large[i][j]= k;
    }
  }

  /* finds 10 shortest paths between nodes */
  for (i=0,j=NUM_NODES/2;i<100;i++,j++) {
			j=j%NUM_NODES;
      dijkstra_l(i,j);
  }
  exit(0);
  

}

