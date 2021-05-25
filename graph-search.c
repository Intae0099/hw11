#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_SIZE		10

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


int freeVertex(Graph* h);
void InitializeGraph(Graph** h);
void InsertVertex(Graph *head, int key);
int InsertEdge(Graph *head, int key);
void printVertex(Graph *head);
void DepthFirstSearch(Graph *head);
void DFS(Graph *head, int v);
void BreathFirstSearch();
void BFS();

int main()
{
    int key;
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
            printf("Insert Vertex : ");
            scanf("%d", &key);
            vertexcount++;
            InsertVertex(head, key);
            break;
        case 'd': case 'D':
            DepthFirstSearch(head);
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

void InsertVertex(Graph *head, int key)
{
    head->graphEdge[head->num] = (Vertex*)malloc(sizeof(Vertex));
    head->graphEdge[head->num]->key = -1;
    head->graphEdge[head->num]->next = NULL;
    head->num++;
}

int InsertEdge(Graph *head, int key)
{


    int edgekey;
    printf("Insert Edge : ");
    scanf("%d", &edgekey);

    Vertex* tempVertex1 = (Vertex*)malloc(sizeof(Vertex));
    Vertex* tempVertex2 = (Vertex*)malloc(sizeof(Vertex));

    tempVertex1->key = key;
    tempVertex1->next = NULL;
    tempVertex2->key = edgekey;
    tempVertex2->next = NULL;

    if(head->graphEdge[key] == NULL)
        head->graphEdge[key] = tempVertex2;
    else
    {
        tempVertex2->next = head->graphEdge[key];
        head->graphEdge[key] = tempVertex2;
    }

    if(head->graphEdge[edgekey] == NULL)
        head->graphEdge[edgekey] = tempVertex1;
    else
    {
        tempVertex1->next = head->graphEdge[edgekey];
        head->graphEdge[edgekey] = tempVertex1;
    }

}

void printVertex(Graph *head)
{
    int i, j;
    printf("Vertex\tEdge\n");
    for(i = 0; i < head->num; i++)
    {
        printf("[%d]\t", i);
        for(j = 0; j < MAX_VERTEX_SIZE; j++)
        {
            if(head->graphEdge[j] == NULL)
                break;
            printf("%d  ",head->graphEdge[j]->key);
        }
        printf("\n");
    }
}

void DepthFirstSearch(Graph *head)
{
    int v;
    printf("Vertax Number : ");
    scanf("%d", &v);
    DFS(head, v);
    printf("\n");
}

void DFS(Graph *graph,int v)
{
    Vertex *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph->graphEdge[v]; w; w = w -> next)
        if (!visited[w->key])
            DFS(w->next, v);

}

void BreathFirstSearch()
{

}

void BFS()
{
    
}
