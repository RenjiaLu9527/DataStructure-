#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 20
#define MAX_VERTEX_NUM 200

typedef char Vertex[MAX_NAME];
typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

struct MGraph
{
	Vertex vexs[MAX_NAME];
	AdjMatrix arcs;
	int vexnum;
	int arcnum;
};

typedef struct 
{
	Vertex adjvexs;
	int lowcost;
}minside[MAX_VERTEX_NUM];

int LocateVex(MGraph G,Vertex u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vexs[i])==0)
			return i;
		return -1;
}

int CreateGraph(MGraph & G)
{
	int i,j,k,w;
	Vertex a,b;
	printf("请输入无向图的边数与顶点数，用空格隔开\n");
	scanf("%d %d",&G.arcnum,&G.vexnum);
	if(G.vexnum<=1)
	{
		printf("\t\t最小生成树不存在");
		return 0;
	}
	printf("请输入%d个顶点的值\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i)
		for(j=0;j<G.vexnum;++j)
		   G.arcs[i][j]=0x7fffffff;
	printf("请输入%d条边的顶点，权值,用空格隔开\n",G.arcnum);
	for(k=0;k<G.arcnum;k++)
	{
		scanf("%s %s %d",a,b,&w);
		i=LocateVex(G,a);
		j=LocateVex(G,b);
		G.arcs[i][j]=G.arcs[j][i]=w;
	}
}


//求最小的边
int minimum(minside SZ,MGraph G)
{
	int i=0;
	int j,k,min;
	while(!SZ[i].lowcost) 
		i++;
	min=SZ[i].lowcost;
	k=i;
	for(j=i+1;j<G.vexnum;j++)
		if(SZ[j].lowcost>0 && min>SZ[j].lowcost)
		{
			min=SZ[j].lowcost;
			k=j;
		}
		return k;
}

void MiniSpanTree_PRIM(MGraph G,Vertex u)
{
	int i,j,k;
	minside closedge;
	k=LocateVex(G,u);
	for(j=0;j<G.vexnum;j++)
	{
		if(j!=k)
		{
			strcpy(closedge[j].adjvexs,u);
			closedge[j].lowcost=G.arcs[k][j];
		}
	}
	closedge[k].lowcost=0;
	printf("最小代价生成树的各条边为：\n");
	for(i=1;i<G.vexnum;i++)
	{
		k=minimum(closedge,G);
		printf("(%s-%s)",closedge[k].adjvexs,G.vexs[k]);
		closedge[k].lowcost=0;
		for(j=0;j<G.vexnum;++j)
			if(G.arcs[k][j]<closedge[j].lowcost)
			{
				strcpy(closedge[j].adjvexs,G.vexs[k]);
				closedge[j].lowcost=G.arcs[k][j];
			}
	}
}

void Display(MGraph G)
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
	{
		printf("\t\t");
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[i][j]>65535)
			{
				printf("\t无穷大");
			}
			else
			{
				printf("\t%d",G.arcs[i][j]);
			}
		printf("\n");
	}
}

int main()
{
	MGraph g;
	CreateGraph(g);
	Display(g);
	MiniSpanTree_PRIM(g,g.vexs[0]);
	return 0;
}


/*
#include<stdio.h>
#include<stdlib.h>

typedef int VertexType;
typedef int EdgeType;

#define MAXVEX 100
#define INF 65535

typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVex,numEdg;
}MGraph;

void Create(MGraph *G)
{
    int i,j,k,w;
    printf("输入顶点数和边数\n");
    scanf("%d%d",&G->numVex,&G->numEdg);
	printf("输入顶点\n");
    for(i=0;i<G->numVex;i++)
        //scanf(&G->vexs[i]);
		scanf("%d",&G->vexs[i]);
    for(i=0;i<G->numVex;i++)
    {
		for(j=0;j<G->numVex;j++)
            G->arc[i][j]=G->arc[j][i]=INF;
        
    }
    for(k=0;k<G->numEdg;k++)
    {
        printf("输入边（vi，vj）上的下标i，下标j，权w");
        scanf("%d%d%d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}
void Prim(MGraph G)
{
    int min,i,j,k;
    int adjvex[MAXVEX];
    int lowcost[MAXVEX];
    lowcost[0]=0;
    adjvex[0]=0;
    for(i=1;i<G.numVex;i++)
    {
        lowcost[i]=G.arc[0][i];
        adjvex[i]=0;
    }
    for(i=1;i<G.numVex;i++)
    {
        min=INF;
        j=1;k=0;
        while(j<G.numVex)
        {
            if(lowcost[j]!=0&&lowcost[j]<min)
            {
                min=lowcost[j];
                k=j;
            }
            j++;
        }
        printf("(%d,%d)",adjvex[k],k);
        lowcost[k]=0;
        for(j=1;j<G.numVex;j++)
        {
            if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j])
            {
                lowcost[j]=G.arc[k][j];
                adjvex[j]=k;
            }
        }
    }
}

int main()
{
    MGraph G;
    Create(&G);
    Prim(G);
    return 0;
}

  */
