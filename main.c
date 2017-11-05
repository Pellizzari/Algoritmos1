#include <stdio.h>
#include <stdlib.h>
#define SIZE 2000000

//implementacion de cola-------------------------------
struct queue {
    int items[SIZE];
    int front;
    int rear;
};

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value){
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }
}

//-----------------------------------------------------------

struct node{
    int vertex;
    struct node* next;
};

struct Graph{
    int numVertices;
    struct node** adjLists;
    int* visited;
};

struct node* createNode(int v){
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++){
        graph->adjLists[i] = NULL;
        graph->visited[i]=0;
    }

    return graph;
}
void addEdge(struct Graph* graph, int src, int dest){
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph){
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

//sort of bfs-------------------------------------------------

void bfs(struct Graph* graph, int startVertex) {
    struct queue* q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while(!isEmpty(q)){
        printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);

       struct node* temp = graph->adjLists[currentVertex];

       while(temp) {
            int adjVertex = temp->vertex;
            printf("%d\n",adjVertex);

            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                printf("%d\n",adjVertex);
            }
            //AQUI HAY SEG FAULT!!!!!!!!!!!!!!!!!!!!!!!
            temp = temp->next;
       }
    }
}

//-------------------------------------





// Driver program to test above functions
int main()
{
	int N, M;
	int i = 0;
	int entrada1, entrada2;

	//printf("Ingrese cantidad usuarios:\n");
	scanf("\n %d[^\n]",&N);

  //usuarios posee la fobia de cada usuario
	int usuarios[N];
	while(i<N){
		//printf("Ingrese fobia del usuario %d:\n",i+1);
		scanf("\n %d[^\n]",&entrada1);
		usuarios[i] = entrada1;
		i++;
	}

	i = 0 ;

	//printf("Ingrese cantidad relaciones:\n");
	scanf("\n %d[^\n]",&M);

	struct Graph* graph = createGraph(N);
	while(i<M){
		//printf("Ingrese relacion %d:\n",i+1);
		scanf("\n%d %d[^\n]", &entrada1, &entrada2);
		addEdge(graph, entrada1, entrada2);
		i++;
	}
	printGraph(graph);
  bfs(graph,1);

    return 0;
}
