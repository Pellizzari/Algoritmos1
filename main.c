#include <stdio.h>
#include <stdlib.h>

struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int);

struct Graph
{
    int numVertices;
    struct node** adjLists;
};

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);



struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
//#include "bfs.h"

// Driver program to test above functions
int main()
{
	int N, M;
	int i = 0;
	int entrada1, entrada2;

	//printf("Ingrese cantidad usuarios:\n");
	scanf("\n %d[^\n]",&N);

	int usuarios[N];

	while(i<N){
		//printf("Ingrese fobia del usuario %d:\n",i+1);
		scanf("\n %d[^\n]",&entrada1);
		usuarios[i] = entrada1;
		i++;
	}

	i = 0;

	//printf("Ingrese cantidad relaciones:\n");
	scanf("\n %d[^\n]",&M);

	struct Graph* graph = createGraph(N);
	//struct subset* subsetFinal = (struct subset*) malloc( N * sizeof(struct subset) );

	while(i<M){
		//printf("Ingrese relacion %d:\n",i+1);
		scanf("\n%d %d[^\n]", &entrada1, &entrada2);
		addEdge(graph, entrada1-1, entrada2-1);
		i++;
	}


	//isCycle(graph, usuarios);
	printGraph(graph);

    return 0;
}
