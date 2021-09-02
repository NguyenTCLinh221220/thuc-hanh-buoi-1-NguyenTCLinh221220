#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <queue>

#define succhua_x 9
#define succhua_y 4
#define empty 0
#define goal 6
using namespace std;
#define Maxlength 500

typedef struct{
	int x;
	int y;
}State;
//khoi tao X=0 Y=0
void makenullState(State* state){
	state->x=0;
	state->y=0;
}
//In trang thai
void print_State(State state){
	printf("/n		X:%d----Y:%d",state.x,state.y);
}
//kiem tra trang thai goal
int goalcheck(State state){
	return (state.x==goal || state.y==goal);
}
//lam day binh X
int dayX(State cur_state, State *result){
	if (cur_state.x<succhua_x){
		result->x=succhua_x;
		result->y=cur_state.y;
		return 1;
	}
	return 1;
}
//lam day Y
int dayY(State cur_state, State *result){
	if (cur_state.y<succhua_y){
		result->y=succhua_y;
		result->x=cur_state.x;
		return 1;
	}
	return 1;
}
//lam rong X
int rongX(State cur_state, State *result){
	if(cur_state.x>0){
		result->x=empty;
		result->y=cur_state.y;
		return 1;
	}
	return 1;
}
//lam rong Y
int rongY(State cur_state, State *result){
	if(cur_state.y>0){
		result->y=empty;
		result->x=cur_state.x;
		return 1;
	}
	return 1;
}
//max
int max(int so1, int so2) {
   int max;
   if (so1 > so2)
      max = so1;
   else
      max = so2;
   return max; 
}
//min
int min(int so1, int so2) {
   int min;
   if (so1 < so2)
      min = so1;
   else
      min = so2;
   return min; 
}
//chuyen X->Y
int chuyenXY(State cur_state, State *result){
	if(cur_state.x>0&&cur_state.y<succhua_y){
		result->x=max(cur_state.x-(succhua_y-cur_state.y),empty);
		result->y=min(cur_state.x+cur_state.y,succhua_y);
		return 1;
	}
	return 1;
}
//chuyen Y->X
int chuyenYX(State cur_state, State *result){
	if(cur_state.y>0&&cur_state.x<succhua_x){
		result->y=max(cur_state.y-(succhua_x-cur_state.x),empty);
		result->x=min(cur_state.x+cur_state.y,succhua_x);
		return 1;
	}
	return 1;
}
//Goi cac hanh dong
int call_hd(State cur_state, State* result,int option){
		switch(option){
			case 1: return dayX(cur_state,result);
			case 2: return dayY(cur_state,result);
			case 3: return rongX(cur_state,result);
			case 4: return rongY(cur_state,result);
			case 5: return chuyenXY(cur_state,result);
			case 6: return chuyenYX(cur_state,result);
			default: printf("Loi goi hanh dong!");
			return 0;
		}
}
//khai bao cau truc nut
typedef struct Node{
	State state;
	struct Node* Parent;
	int no_function;
}Node;
// cai dat cau truc Queue
typedef struct{
	Node* Elements[Maxlength];
	int Front, Rear;
}Queue;
void MakeNull_Queue(Queue *Q){
		Q->Front=-1;
		Q->Rear=-1;
}
int Empty_Queue(Queue Q)
{	
		return (Q.Front ==-1);
}
int Full_Queue(Queue Q)
{	 
	return ((Q.Rear-Q.Front+1)==Maxlength);
} 
Node* get_Front(Queue Q){
 	if (Empty_Queue (Q))       
	 	printf ("Hang rong");
    else  
       return Q.Elements[Q.Front];
} 
void Del_Queue(Queue *Q){	
	if (!Empty_Queue(*Q)){	
		if(Q->Front==Q->Rear)
		 MakeNull_Queue(Q);//Dat lai hang rong
		else Q->Front=(Q->Front+1)%Maxlength;
	}else printf("Loi: Hang rong!");
} 
void push_Queue(Node* x,Queue *Q){
	if(!Full_Queue(*Q)){
		if(Empty_Queue(*Q))
			Q->Front=0;
		Q->Rear=(Q->Rear+1)%Maxlength;
		Q->Elements[Q->Rear]=x;
	}
	else printf("Loi them!");
}
int find_State(State state, Queue openQueue){
	while(!Empty_Queue(openQueue)){
		if(compareQueue(get_Front(openQueue)->state,state))
			return 1;
		Del_Queue(&openQueue);
	}
	return 0;
}
Node* BFS_duyetrong(State state){
	Queue Open_BFS;
	Queue Close_BFS;
	MakeNull_Queue(&Open_BFS);
	MakeNull_Queue(&Close_BFS);
	//nut trang thia cha
	Node* root=(Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->no_function=0;
	push_Queue(root,&Open_BFS);
	while(!Empty_Queue(Open_BFS)){
		//lay 1 dinh trong hang doi
		Node* node=get_Front(Open_BFS);
		Del_Queue(&Open_BFS);
		push_Queue(node,&Close_BFS);
		//Kiem tra dinh lay ra co phai goal
		if(goalcheck(node->state))
			return node;
		int opt;
		//goi hoat dong
		for(opt=1;opt<=6;opt++){
			State newstate;
			makenullState(&newstate);
			if(call_hd(node->state,&newstate,opt)){
				//neu state moi sinh da ton tai thi next
				if(find_State(newstate,Close_BFS)||find_State(newstate,Open_BFS))
					continue;
				//neu state moi sinh chua ton tai thi them vao Q
				Node* newNode=(Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				push_Queue(newNode,&Open_BFS);
			}
		}
	}
	return NULL;
}
//in ket qua duyet rong
void print_kqchuyen(Node* node){
	Queue queuePrint;
	MakeNull_Queue(&queuePrint);
	while(node->Parent!=NULL){
		push_Queue(node,&queuePrint);
		node-node->Parent;
	}
	
	push_Queue(node,&queuePrint);
	int no_action=0;
	while(!Empty_Queue(queuePrint)){
		printf("\nAction %d: %s",no_action,action[get_Front(queuePrint)->no_function]);
		print_State(get_Front(queuePrint)->state);
		Del_Queue(&queuePrint);
		no_action++;
	}
}

int main(){
	State cur_state={0,0};
	Node* p=BFS_duyetrong(cur_state);
	print_kqchuyen(p);
	return 0;
}
