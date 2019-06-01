
#include <stdio.h>
#include <malloc.h>
#include <string.h>

static void * myalloc(int size){
	if (size<=0) return (void*)0;
	void * o = 0;
	do{
		o = malloc(size);
		memset(o,0,size);
		}while(o==0);
	return o;
}


#define NEW(type,...)\
	type##Construct((type*)myalloc(sizeof(type)),##__VA_ARGS__)


#define OO_SAFE_DELETE(ptr)\
	do{\
	if (ptr!=0)\
	{\
		ptr->destruct(ptr);\
		free(ptr);\
		ptr=0;\
	}\
	}while(0);



	
enum PlayerProperty_Enum_;
typedef enum PlayerProperty_Enum_  PlayerProperty;


struct Player_;
typedef struct Player_ Player;

struct Player_{
	int id;
	int type;
	int refCount;
	int index;

	//virt funcs
	void (*destruct)(Player*);
};

enum PlayerProperty_Enum_ {
	Pt_ID,
	Pt_TYPE,
	Pt_RefCount,
	Pt_INDEX,
};

void PlayerDestruct(Player*);
Player * PlayerConstruct(Player* this,int id,int type,int refCount,int index){
	this->id = id ;
	this->type =type;
	this->refCount = refCount;
	this->index = index;
	this->destruct = PlayerDestruct;


	return this;
}


#define PlayerGetProperty(playerPtr,propertyDataType,propertyName)\
	
	


void PlayerDestruct(Player* this){

	printf("release will ...\n");
}




int main(int argc,const char *argvs[]){


	return 0;
}





