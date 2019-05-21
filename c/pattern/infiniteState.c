#include <stdio.h>
#include <string.h>
#include <malloc.h>
static void *mymalloc(int size){
	if (size<=0) return 0;
	void * o = 0;
	do{
		o = malloc(size);
		memset(o,0,size);
	}while(o==0);
	return o;
}



#define SAFE_DELETE(ptr)\
	do{\
		if (ptr!=0){\
			free(ptr);\
			ptr=0;\
		}\
		}while(0);


#define OO_SAFE_DELETE(ptr)\
	do{\
		if (ptr!=0){\
			ptr->destruct(ptr);\
			free(ptr);\
			ptr=0;\
		}\
		}while(0);



#ifdef _WIN32
	#define NEW(type,...)\
		type##Construct(mymalloc(sizeof(type)),##__VA_ARGS__)

#elif _WIN64
#define NEW(type,...)\
		type##Construct(mymalloc(sizeof(type)),##__VA_ARGS__)

#elif __linux__
#define NEW(type,...)\
({\
	type * o = mymalloc(sizeof(type));\
	type##Construct(o,##__VA_ARGS__);\
	o;\
})

#elif __unix__
#define NEW(type,...)\
({\
	type * o = mymalloc(sizeof(type));\
	type##Construct(o,##__VA_ARGS__);\
	o;\
})


#endif









enum State_Enum_;
typedef enum State_Enum_ State;
enum State_Enum_{
	STATE_START,
	STATE_STOP,
	STATE_PAUSE,
	STATE_INIT,
};
struct Player_struct_;
typedef struct Player_struct_ Player;

enum Player_Property_Enum_;
typedef enum Player_Property_Enum_ PlayerProperty;

enum Player_Property_Enum_{
	Pt_Id,
	Pt_Age,
};
struct Player_struct_{
	int id;
	int age;

	//virt funs
	void (*destruct)(Player* this);
};

int PlayerGetIntProperty(Player *this,PlayerProperty pt);

typedef void*(*StateHandler)(int doType,void *ptr);


void *StateInit(int doType,void *ptr)
{


	return (void*)0;
}

void *StateStop(int doType,void *ptr)
{


	return (void*)0;
}


void *StatePause(int doType,void *ptr)
{


	return (void*)0;
}


void *StateStart(int doType,void *ptr)
{
	Player* p = (Player*) ptr;
	int id =PlayerGetIntProperty(p,Pt_Id);
	int age =PlayerGetIntProperty(p,Pt_Age);
	printf("id=%d, age=%d \n",id,age);
	
	return (void*)0;
}

void changeState(State s, int doType,void *ptr){
	static StateHandler handlers[]={StateStart,StateStop,StatePause,StateInit};
	StateHandler h = handlers[s];
	h(doType,ptr);
}

static void typeModelizeMem(){
	//type is to construct memory model； type是对原子类型的建模
	int arr[4]={0,1,2,3}; //arr-->type int[4]

	int (*ptr)[4] = &arr;

	int res = *(((int*)(ptr+1))-1);
	printf("res=%d \n",res);

}
//enum and layout memory

void PlayerDestruct(Player *this);

Player* PlayerConstruct(Player *this,int id,int age){
	this->id =id;
	this->age =age;
	this->destruct = PlayerDestruct;
	return this;
}



int PlayerGetIntProperty(Player *this,PlayerProperty pt){
	int * pts = (int*)this;
	return pts[pt];
}

void PlayerDestruct(Player *this){
	printf("Player =%p will release\n",this);

}
int main(int argc,const char *argvs[])
{
	State s =STATE_START;

	Player *p = NEW(Player,10,10000);
	
	changeState(s,1,p);
	
	//SAFE_DELETE(p);
	OO_SAFE_DELETE(p);

	return 0;
}







