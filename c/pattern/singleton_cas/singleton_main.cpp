
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "singleton.cpp"


class AssetManager{

private:
		int id;
		
public:
	int getAsset();
	int releaseAsset();
	
};
int AssetManager::getAsset(){
	printf("getAsset self=%p...\n",this);
}

int AssetManager::releaseAsset(){
	printf("releaseAsset self=%p...\n",this);

}

#define WORKER_SIZE 100
#define TIMES 100

void* routine(void* arg)
{
	int i;
	for (i=0;i<TIMES;++i){
			AssetManager& ins = Singleton<AssetManager>::getInstance();
			ins.getAsset();
			ins.releaseAsset();
			usleep(100);
	}

	return (void*)0;
	
}


int main(int argc, const char * argvs [ ]){

	pthread_t workers[WORKER_SIZE]={0};

	int i;
    for (i=0;i<WORKER_SIZE;++i)
    {

		pthread_create(&workers[i],0,routine,0);
	}
    for (i=0;i<WORKER_SIZE;++i)
    {

		pthread_join(workers[i],0);
	}





	return 0;
}










