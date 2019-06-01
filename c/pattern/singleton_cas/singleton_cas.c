#include <unistd.h>
#include <malloc.h>
#include <pthread.h>


int atomic_int_inc(int* addr,int delta){
	//base on asm "xaddl delta,[ptr]"
	int ret =0;
	__asm__ __volatile__(
		"lock;xaddl %2,%1;"
		:"=a"(ret)
		:"m"(*addr),"0"(delta)
		:"cc","memory"

	);
	return ret;
}


unsigned long  atomic_ulong_cas(unsigned long *addr,unsigned long old,unsigned long new){
	//base on asm "cmpxchg new,[ptr]"

	unsigned long ret=0;
	__asm__ __volatile__(
		"lock;cmpxchg %3,%1;"
		:"=a" (ret)
		:"m"(*addr),"0"(old),"r"(new)
		:"cc","memory"
	);
	return ret;
}


struct Singleton_;
typedef 
struct Singleton_ Singleton;

struct Singleton_{

};

static Singleton* ins=0;

void __attribute__ ((destructor))  release(){
	if (0!=ins){
		free(ins);
		ins=0;
		printf("release ...\n");
	}

}
static Singleton* getInstance(){

	if (ins==0){
		void *memptr= malloc(sizeof(Singleton));
		if(0!=atomic_ulong_cas((unsigned long*)&ins, 0, memptr))
		{
			//第二次以上赋值失败情况
			free(memptr);
			memptr = NULL;
		}
	}
	return ins;

}


#define WORKER_SIZE 100
#define TIMES 100


void* workerRoutine(void* arg){
	void * ins =0;
	int i ;
	for (i=0;i<TIMES;++i){	
		ins = getInstance();
		usleep(300);
		printf("ins=%p \n",ins);
	}

	return (void*)0;
}






int main(int argc,const char*argvs[])
{

	pthread_t workers[WORKER_SIZE]={0};

	int i;
	for (i=0;i<WORKER_SIZE;++i){
			
		pthread_create(&workers[i],0,workerRoutine,0);
	}

	for (i=0;i<WORKER_SIZE;++i){
		pthread_join(workers[i],0);			
	}


	


}





























