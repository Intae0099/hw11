#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_SIZE		10
#define MAX_QUEUE_SIZE      10

typedef struct vertex 
{
	int key;
	struct vertex *next;
} Vertex;

typedef struct graph
{
    int num;
    Vertex* graphEdge[MAX_VERTEX_SIZE];
} Graph;


int vertexcount = 0;
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTEX_SIZE];

int front = 0;
int rear = 0;
int queue[MAX_QUEUE_SIZE];


int freeGraph(Graph* h);
void InitializeGraph(Graph** h);
void InsertVertex(Graph *head);
int InsertEdge(Graph *head, int key);
void printVertex(Graph *head);
void DepthFirstSearch(Graph *head, int v);
void DFS(Vertex *head, int v);
void BreathFirstSearch();
void BFS(Graph *head, int v);
void enQueue(int n);
int deQueue();

int main()
{
    int key, v;
    Graph* head = NULL;
    char command;
    printf("\t\t[----- [Kim Tae In]] [2018038033] -----]\n");

    do
    { 
    printf("----------------------------------------------------------------\n");
    printf(                       "Graph Searches                           \n");
    printf("----------------------------------------------------------------\n");
    printf(" Initialize Graph     = z                                       \n");
    printf(" Insert Vertex        = v       Insert Edge               = e   \n");
    printf(" Depth First Search   = d       Breath First Search       = b   \n");
    printf(" Print Graph          = p       Quit                      = q   \n");
    printf("----------------------------------------------------------------\n");

    printf("Command = ");
	scanf(" %c", &command);

    switch(command)
    {
        case 'z': case 'Z':
            InitializeGraph(&head);
            break;
        case 'q': case 'Q':
            freeGraph(head);
            break;
        case 'v': case 'V':
            vertexcount++;
            InsertVertex(head);
            break;
        case 'd': case 'D':
            printf("Vertax Number : ");
            scanf("%d", &v);
            DepthFirstSearch(head, v);
            break;
        case 'p': case 'P':
            printVertex(head);
            break;
        case 'e': case 'E':
            printf("Find Vertex : ");
            scanf("%d", &key);
            InsertEdge(head, key);
            break;
        case 'b': case 'B':
            printf("Vertax Number : ");
            scanf("%d", &v);
            BFS(head, v);
            break;

    }

    } while(command != 'q' || command != 'Q');

    return 1;
}

int freeGraph(Graph* h)
{
    int i; 

    for(i = 0; i < h->num; i++)
        free(h->graphEdge[i]);

    free(h);
	return 0;

}

void InitializeGraph(Graph** h)
{
    int i;

    if(*h != NULL)
		freeGraph(*h);

	*h = (Graph*)malloc(sizeof(Graph));
    (*h)->num = 0;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
        (*h)->graphEdge[i] = NULL;

}

void InsertVertex(Graph *head)
{
    if(head->num > 9)
    {
        printf("Error\n");
        return ;
    }
    head->graphEdge[head->num] = (Vertex*)malloc(sizeof(Vertex));
    head->graphEdge[head->num]->key = -1;
    head->graphEdge[head->num]->next = NULL;
    head->num++;
}

int InsertEdge(Graph *head, int v)
{


    int u, i;
    printf("Insert Edge : ");
    scanf("%d", &u);

    if(v == u)
    {
        printf("Error\n");
        return 0;
    }

    Vertex* check = head->graphEdge[v];

    if(check != NULL)
    {
        while(check != NULL)
        {
            if(check->key == u)
            {
                printf("Error\n");
                return 0;
            }
            check = check->next;
        }
    }
    
    Vertex* tempVertex_v = (Vertex*)malloc(sizeof(Vertex));
    Vertex* tempVertex_u = (Vertex*)malloc(sizeof(Vertex));

    tempVertex_v->key = v;
    tempVertex_v->next = NULL;
    tempVertex_u->key = u;
    tempVertex_u->next = NULL;

    if(head->graphEdge[v] == NULL)
        head->graphEdge[v] = tempVertex_u;
    else
    {
        tempVertex_u->next = head->graphEdge[v];
        head->graphEdge[v] = tempVertex_u;
    }

    if(head->graphEdge[u] == NULL)
        head->graphEdge[u] = tempVertex_v;
    else
    {
        tempVertex_v->next = head->graphEdge[u];
        head->graphEdge[u] = tempVertex_v;
    }

}

void printVertex(Graph *head)
{
    int i, j;
    Vertex *tempVertex = NULL;
    printf("Vertex\tEdge\n");
    for(i = 0; i < head->num; i++)
    {
        printf("[%d]\t", i);
        tempVertex = head->graphEdge[i];
        for(j = 0; j < MAX_VERTEX_SIZE; j++)
        {
            if(tempVertex -> next == NULL)
                break;
            else
            {
                printf("%d  ",tempVertex->key);
                tempVertex = tempVertex -> next;
            }
                
        }
        printf("\n");
    }
}

void DepthFirstSearch(Graph *head, int v)
{
    int i;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        visited[i] = FALSE;
    }
    
    DFS(head->graphEdge[v], v);
    printf("\n");
}

void DFS(Vertex *head,int v)
{
    Vertex *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = head; w; w = w -> next)
        if (!visited[w->key])
            DFS(w, w->key);

}

void BreathFirstSearch()
{
    int i;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        visited[i] = FALSE;
    }
}

void BFS(Graph *head, int v)
{
    int i;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        visited[i] = FALSE;
    }
    Vertex *w;
    front = -1;
    rear = -1;
    
    printf("%5d", v); /* print */
    visited[v] = TRUE; /* visit marking */
    enQueue(v); /* enqueue */
    
    while (front)
    {
        v = deQueue(&front); /* dequeue */
        for (w=head->graphEdge[v]; w; w = w->next)
        if (!visited[w->key]) 
        {
            printf("%5d", w->key);
            enQueue(w->key);
            visited[w->key] = TRUE;
        }
    }

}

void enQueue(int v)
{
    if((rear+1)%MAX_QUEUE_SIZE == front)
    {
        printf("Full");
        return ;
    }
    else
    {
        rear = (rear+1) % MAX_QUEUE_SIZE;
        queue[rear] = v;
    }
}

int deQueue()
{
    int temp = -1;

    if(front == rear)
    {
        printf("Empty");
        return 0;
    }
    else
    {
        front = (front + 1)%MAX_QUEUE_SIZE;
        temp = queue[front];
    }
    return temp;
}
