#include <stdio.h>
#include <stdlib.h>
#define SIZE 2000000

//Implementacion de cola-------------------------------
struct queue {
    int items[SIZE];
    int front;
    int rear;
};

//Generador de cola------------------------------------
struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

//Revisa si la cola q esta vacia o no, retorna 0 ó 1---
int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

//Encola value en la cola q, advierte en caso de no poder encolar
void enqueue(struct queue* q, int value){
    if(q->rear == SIZE-1)
        printf("\nCola llena");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

//Quita un elemento de la cola q, adviete en el caso de esta vacia
int dequeue(struct queue* q){
    int item;
    if(isEmpty(q)){
        printf("Cola vacia");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            q->front = q->rear = -1;
        }
    }
    return item;
}

/*Representacion de un nodo en la estructura,
posee numero de vertice que lo representa y puntero al siguiente nodo*/
struct node{
    int vertex;
    struct node* next;
};

/*Representacion de un grafo en la estructura,
posee numero de vertices, puntero al puntero
de los elemento del arreglo de adyacencia de cada nodo y puntero
al estado de cada nodo*/
struct Graph{
    int numVertices;
    struct node** adjLists;
    int* visited;
};

//Creador de nodos, define al nodo con v y al siguiente nodo con NULL
struct node* createNode(int v){
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

/*Creador de grafos, recibe el numero de vertices,
define el arreglo de arreglos de adyacencia segun la cantidad de nodos
al igual que el arreglo de visitados, definiendo un valor para cada nodo en 0*/
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

/*Agregar las relaciones entre los nodos de un grafo,
agregando source y destino e incluyendo en el arreglo de adyacencia
a ambos como adyacentes al otro*/
void addEdge(struct Graph* graph, int src, int dest){
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

/*Busqueda en profundidad sobre un vertice de un grafo, buscará a traves de todo
un grafo conexo cual fobia es la mas repetida a la asociada a cada vertice realizando
busqueda en profundidad*/
int bfs(struct Graph* graph, int startVertex,int *fobiasusuarios) {
    struct queue* q=createQueue();
    enqueue(q, startVertex);
    graph->visited[startVertex] = 1;
    int fobiaganadora=fobiasusuarios[startVertex];
    int maxfobia=1;
    int *fobias=(int *) malloc(10000*sizeof(int));
    for(int i=0;i<10000;i++){
      fobias[i]=0;
    }
    fobias[fobiasusuarios[startVertex]]+=1;
    while(!isEmpty(q)){
        int currentVertex = dequeue(q);
        struct node* temp = graph->adjLists[currentVertex];
        while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
                fobias[fobiasusuarios[adjVertex]]+=1;
                if(fobias[fobiasusuarios[adjVertex]]>maxfobia){
                  fobiaganadora=fobiasusuarios[adjVertex];
                  maxfobia=fobias[fobiasusuarios[adjVertex]];
                }
            }
            temp = temp->next;
       }
    }
    return fobiaganadora;
    free(fobias);
}

//Main del programa-------------------------------------

int main()
{
	int N, M;
	int i = 0;
	int entrada1, entrada2;
//Ingreso de la cantidad de usuarios, generara un arreglo del tamaño de la
//cantidad de usuarios.
	scanf("\n %d[^\n]",&N);

	int usuarios[N];

/*En cada espacio del arreglo ingresara
la fobia del usuario enumerado segun el arreglo*/
	while(i<N){
		scanf("\n %d[^\n]",&entrada1);
		usuarios[i] = entrada1;
		i++;
	}

	i = 0 ;
/*Recibe el numero de relaciones, itera sobre ese numero para añadir relaciones
a un grafo de nombre graph*/
	scanf("\n %d[^\n]",&M);
	struct Graph* graph = createGraph(N);
	while(i<M){
		scanf("%d %d", &entrada1, &entrada2);
/*Se considera que los usuarios parten de 0
por lo que a las entradas se les resta 1*/
		addEdge(graph, entrada1-1, entrada2-1);
		i++;
	}
/*Se genera una cola para retornar en orden los valores que bfs() retorne
para ir recorriendo entre grafos conexo se itera sobre el numero de usuarios
revisando si es que alguno aun no esta marcado despues de cada iteracion*/
  int grupos=0;
  struct queue* queueA=createQueue();
  for(int i=0;i<N;i++){
    if(graph->visited[i] == 0){
      grupos++;
      enqueue(queueA, bfs(graph,i,usuarios));
    }
  }
/*Finalmente se muestra por pantalla la cantidad de grupos encontrados y se
desencola la cola QueueA para mostrar en orden las fobias mas comunes*/
  printf("%d\n",grupos);
  while (!isEmpty(queueA)) {
    printf("%d\n",dequeue(queueA));
  }
    return 0;
}
