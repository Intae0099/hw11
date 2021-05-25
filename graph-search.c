#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int key;
	struct vertex *next;
    struct vertex *edge[10];
} Vertex;

#define MAX_VERTEX_SIZE		10
int vertexcount = 0;

void InitializeGraph(Vertex** h);
int InsertVertex(Vertex *head, int key);
int InsertEdge(Vertex *head, int key);
void printVertex(Vertex *head);

int main()
{
    int key;
    Vertex* head = NULL;
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
            printf("프로그램 종료");
            break;
        case 'v': case 'V':
            printf("Insert Vertex : ");
            scanf("%d", &key);
            vertexcount++;
            InsertVertex(head, key);
            break;
        case 'd': case 'D':
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

void InitializeGraph(Vertex** h)
{
    int i;
	*h = (Vertex*)malloc(sizeof(Vertex));
	(*h)->next = NULL;	
	(*h)->key = -1;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        (*h)->edge[i] = NULL;
    }
}

int InsertVertex(Vertex *head, int key)
{
    if(vertexcount > 10)
    {
        printf("\nMAX Vertax count\n");
        vertexcount--;
        return 0;
    }
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	newVertex->key = key;
    newVertex->next = NULL;
    newVertex->edge[0] = NULL;
    Vertex* tempVertex = head->next;
    Vertex* prevVertex = NULL;
        
    if (head->next == NULL)
    {
        head->next = newVertex;
        return 0;
    }
    else if (head->next != NULL)
    {
        if (tempVertex->key > newVertex ->key)
        {
            newVertex->next = tempVertex;
            head->next = newVertex;
            return 0;
        }
        else if (tempVertex->key < newVertex->key)
        {
            while(tempVertex->next != NULL)
            {
                if(tempVertex->key < newVertex->key)
                {
                    prevVertex = tempVertex;
                    tempVertex = tempVertex ->next;
                }   
                else
                    break;
            }
            
            if(tempVertex->next == NULL)
            {
                tempVertex->next = newVertex;
                return 0;
            }
            else if (tempVertex ->next != NULL)
            {
                tempVertex->next = newVertex;
                newVertex->next = tempVertex->next->next;
                return 0;
            }
        }
    }
    return 0;
}

int InsertEdge(Vertex *head, int key)
{
    int edgekey;
    int j = 0;
    Vertex* tempVertex = head->next;
    Vertex* findVertex = head->next;
    Vertex* tempEdge = NULL;

    while(tempVertex->next != NULL)
    {
        if(tempVertex->key == key)
            break;
        else
            tempVertex = tempVertex -> next;
    }
    printf("Insert Edge : ");
    scanf("%d", &edgekey);


    while(findVertex->next != NULL)
    {
        if(findVertex->key == edgekey)
            break;
        else
            findVertex = findVertex->next;
    }

    j = findVertex->key;

    if(tempVertex->edge[j] == NULL)
    {
        tempVertex->edge[j] = findVertex;
        return 0;
    }
    else
    {
        tempEdge = tempVertex->edge[j];
        while(tempVertex->edge[j] != NULL)
        {
            if(tempVertex->edge[j] == NULL)
            {
                break;
            }
            else
            {
                tempEdge = tempEdge->edge[j];
            }
                

        }
        tempEdge->edge[j] = findVertex;
    }
    
    return 0;
}

void printVertex(Vertex *head)
{
    int i = 0;
    int j = 0;
    Vertex* tempVertex = head->next;
    Vertex* tempEdge = NULL;
    printf("Vertxe\tEdge\n");
    for(i ; i < vertexcount; i++)
    {
        printf("[%d]\t",tempVertex->key);
        tempEdge = tempVertex->edge[i];
        for(j; j < MAX_VERTEX_SIZE; j++)
        {
            if(tempVertex->edge[i] != NULL)
                printf("%d\t", tempEdge->key);
            
            if(tempEdge->edge[i] != NULL)
                tempEdge = tempEdge->edge[i];
        }
        tempVertex = tempVertex->next;
        printf("\n");
    }
}
