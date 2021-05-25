#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int key;
	struct vertex *next;
    struct vertex *edge[10];
} Vertex;

#define MAX_VERTEX_SIZE		10
int vertexcount = 0;

int freeVertex(Vertex* h);
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
            freeVertex(head);
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

int freeVertex(Vertex* h)
{
    Vertex* prevVertex = NULL;
    Vertex* tempVertex = h->next;

	while(tempVertex != NULL) {
		prevVertex = tempVertex;
		tempVertex = tempVertex->next;
		free(prevVertex);
	}
	free(h);
	return 0;
}

void InitializeGraph(Vertex** h)
{
    if(*h != NULL)
		freeVertex(*h);

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
    if(key > 9)
    {
        printf("ERROR");
        return 0;
    }
    int i;
    if(vertexcount > 10)
    {
        printf("\nMAX Vertax count\n");
        vertexcount--;
        return 0;
    }
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	newVertex->key = key;
    newVertex->next = NULL;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        newVertex->edge[i] = NULL;
    }

    Vertex* tempVertex = head->next;
    Vertex* checkVertex = head->next;
    
    if(checkVertex != NULL)
    {
        while(checkVertex != NULL)
        {
            if(checkVertex->key == key)
            {
                printf("Error\n");
                vertexcount--;
                return 0;
            }
            checkVertex = checkVertex->next;
        }
    }
    

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
    int i;
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
    
    if(tempVertex->key == edgekey)
    {
        printf("Error\n");
        return 0;
    }

    for(i = 0; i< MAX_VERTEX_SIZE; i++)
    {
        if(tempVertex->edge[i] != NULL)
        {
            if(tempVertex->edge[i]->key == edgekey)
            {
                printf("Error\n");
                return 0;
            }
        }
    }

    while(findVertex->next != NULL)
    {
        if(findVertex->key == edgekey)
            break;
        else
            findVertex = findVertex->next;
    }
    
    if(findVertex->key != edgekey)
    {
        printf("Error\n");
        return 0;
    }

    for(i = 0; i<MAX_VERTEX_SIZE; i++)
    {
        if(tempVertex->edge[i] ==NULL)
        {
            tempVertex->edge[i] = findVertex;
            break;
        }
            
    }
    
    for(i = 0; i<MAX_VERTEX_SIZE; i++)
    {
        if(findVertex->edge[i] ==NULL)
        {
            findVertex->edge[i] = tempVertex;
            break;
        }
    }
    
    return 0;
}

void printVertex(Vertex *head)
{
    int i;
    int j;
    Vertex* tempVertex = head->next;
    Vertex* tempEdge = NULL;
    printf("Vertxe\tEdge\n");
    for(i = 0 ; i < vertexcount; i++)
    {
        printf("[%d]\t",tempVertex->key);
        for(j=0; j< MAX_VERTEX_SIZE ; j++)
        {
            if(tempVertex->edge[j] != NULL)
            {
                printf("%d  ", tempVertex->edge[j]->key);
            }
            else
                break;   
        }
        
        tempVertex = tempVertex->next;
        printf("\n");
    }
}
