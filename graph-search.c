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

    } while(command != 'q' && command != 'Q');

    return 1;
}

int freeGraph(Graph* h) //그래프를 동적할당 해제함으로서 삭제
{
    int i; 

    for(i = 0; i < h->num; i++)
        free(h->graphEdge[i]); //각 Vertex들을 반복문을 통해 삭제한다

    free(h); //그래프삭제
	return 0;

}

void InitializeGraph(Graph** h) //그래프를 초기화한다
{
    int i;

    if(*h != NULL)
		freeGraph(*h); //그래프가 존재한 상태에서 초기화를 한번 더 하면 그래프를 동적할당 해제후 다시 초기화

	*h = (Graph*)malloc(sizeof(Graph)); //그래프를 동적할당한다
    (*h)->num = 0; //vertex수를 0개로 설정
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
        (*h)->graphEdge[i] = NULL; //그래프의 vertex들을 NULL로 설정한다

}

void InsertVertex(Graph *head) //Vertex 추가 함수
{
    if(head->num > 9)
    {
        printf("Error\n"); //vertex개수가 9개가 넘어가면 에러 출력후 함수 종료
        return ;
    }
    head->graphEdge[head->num] = (Vertex*)malloc(sizeof(Vertex)); //새로운 vertex를 동적할당한다
    head->graphEdge[head->num]->key = -1; //vertex의 값을 -1로 임시설정
    head->graphEdge[head->num]->next = NULL; //vertex의 edge를 NULL로 설정
    head->num++; //vertex의 개수를 1개 추가한다
}

int InsertEdge(Graph *head, int v)
{


    int u, i;
    printf("Insert Edge : ");
    scanf("%d", &u);

    if(v == u) //vertex값과 edge로 설정할 vertex의 값이 같을경우
    {
        printf("Error\n"); //에러 출력 후 함수 종료
        return 0;
    }

    Vertex* check = head->graphEdge[v]; //vertex의 edge 중 같은 edge가 한개 더있는지 체크한다

    if(check != NULL)
    {
        while(check != NULL)
        {
            if(check->key == u) //vertex의 edge 중 u가 존재시
            {
                printf("Error\n"); //에러 출력 후 함수 종료
                return 0;
            }
            check = check->next; //vertex의 edge로 이동
        }
    }
    
    Vertex* tempVertex_v = (Vertex*)malloc(sizeof(Vertex));
    Vertex* tempVertex_u = (Vertex*)malloc(sizeof(Vertex));

    tempVertex_v->key = v; //새로 추가할 edge에 v값 대입
    tempVertex_v->next = NULL; //
    tempVertex_u->key = u; //새로 추가할 edge에 u값 대입
    tempVertex_u->next = NULL;

    if(head->graphEdge[v] == NULL) //vertex v의 edge가 존재하지 않으면
        head->graphEdge[v] = tempVertex_u; //vertex v의 edge로 vertex u 로 설정
    else
    {
        tempVertex_u->next = head->graphEdge[v];
        head->graphEdge[v] = tempVertex_u;
    }

    if(head->graphEdge[u] == NULL) //vertex u의 edge가 존재하지 않으면
        head->graphEdge[u] = tempVertex_v; //vertex u의 edge로 vertex v로 설정
    else
    {
        tempVertex_v->next = head->graphEdge[u];
        head->graphEdge[u] = tempVertex_v;
    }

}

void printVertex(Graph *head) //vertex와 각 edge를 출력
{
    int i, j;
    Vertex *tempVertex = NULL;
    printf("Vertex\tEdge\n");
    for(i = 0; i < head->num; i++)
    {
        printf("[%d]\t", i); //vertex들 출력
        tempVertex = head->graphEdge[i]; //tempVertex를 vertex의 edge로 이동하기위해 설정
        for(j = 0; j < MAX_VERTEX_SIZE; j++)
        {
            if(tempVertex -> next == NULL) //edge가 없는 경우 다음 반복문 종료 후 다음vertex로 이동
                break;
            else
            {
                printf("%d  ",tempVertex->key); //edge 출력
                tempVertex = tempVertex -> next; //vertex의 edge로 이동
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
        visited[i] = FALSE; //함수 반복시 방문한 vertex들 확인하기 위해 visited 초기화
    }
    
    DFS(head->graphEdge[v], v); //깊이 우선탐색 방식으로 탐색
    printf("\n");
}

void DFS(Vertex *head,int v) //깊이 우선 탐색 함수
{
    Vertex *w;
    visited[v] = TRUE; //visited를 방문했으므로 TRUE 로 바꾼다
    printf("%5d", v);
    for (w = head; w; w = w -> next) //vertex w를 head로 설정, w가 널이 아닐때는 반복, w를 edge로 이동
        if (!visited[w->key]) //방문한적이 있으면
            DFS(w, w->key); //재귀함수로 다시 접근

}

void BFS(Graph *head, int v) //너비 우선 탐색 함수
{
    int i;
    for(i = 0; i < MAX_VERTEX_SIZE; i++)
    {
        visited[i] = FALSE; //함수 반복시 방문한 vertex들 확인하기 위해 visited 초기화
    }
    Vertex *w;
    front = -1; //함수 실행마다 front값을 -1로 선언
    rear = -1; //함수 실행마다 rear값을 -1로 선언
    
    printf("%5d", v); 
    visited[v] = TRUE;  //visited를 방문했으므로 TRUE 로 바꾼다
    enQueue(v); //큐를 하나 추가한다
    
    while (front) 
    {
        v = deQueue(); //큐를 하나 빼온다
        for (w=head->graphEdge[v]; w; w = w->next) //vertex w를 head로 설정, w가 널이 아닐때는 반복, w를 edge로 이동
            if (!visited[w->key]) //방문한적이 있으면
            {
                printf("%5d", w->key); //출력
                enQueue(w->key); //큐를 하나 추가한다
                visited[w->key] = TRUE; //visited를 방문했으므로 TRUE 로 바꾼다
            }
    }
    printf("\n");
}

void enQueue(int v) //큐를 하나 추가하는 함수
{
    if((rear+1)%MAX_QUEUE_SIZE == front) //(rear+1)%MAX_QUEUE_SIZE이 front와 같은경우
    {
        printf("Full"); //큐가 꽉참 출력 후 함수 종료
        return ;
    }
    else //그렇지 않은 경우
    {
        rear = (rear+1) % MAX_QUEUE_SIZE; //rear를 (rear+1)%MAX_QUEUE_SIZE로 설정
        queue[rear] = v; //큐에 v하나 추가한다
    }
}

int deQueue() //큐의 앞부분을 하나 빼오는 함수
{
    int temp = -1;

    if(front == rear) //front와 rear이 같은 경우
    {
        printf("Empty"); //큐가 비었음을 출력 하고 함수 종료
        return 0;
    }
    else //그렇지 않은 경우
    {
        front = (front + 1)%MAX_QUEUE_SIZE; //front를 (front + 1)%MAX_QUEUE_SIZE로 설정
        temp = queue[front]; //큐의 앞부분을 temp로 설정
    }
    return temp; //큐의 앞부분을 빼온다
}
