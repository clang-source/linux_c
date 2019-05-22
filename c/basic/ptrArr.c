#include <stdio.h>

struct Element_;
typedef struct Element_ Element;

struct Element_{
	
	int id;
	int age;

};


int main(int argc,const char*argvs[]){
	Element  e1 = {1,20};
	Element  e2 = {2,20};
	Element  e3 = {3,20};

	Element * eptArr[] = {&e1,&e2,&e3};

	Element** ptr = eptArr;

	int n= 3;
		int i=0;
		for (;i<n;i++){
			printf("id=%d , age=%d \n",ptr[i]->id,ptr[i]->age);
		}

		

	Element * eptArr2[] = {&e2,&e1,&e3};
	
	Element** ptr2 = eptArr2;
	
	Element * eptArr3[] = {&e2,&e3,&e1};
		
	Element** ptr3 = eptArr3;
		

//如何管理 Element** ptr  ptr2 ptr3。as atomic
	printf("==============================\n");

	Element**  ptrsArr []={ptr,ptr2,ptr3};

    int arrsize=3;
	int j=0;
	int lowI = 0;
	int lowFields =3;
	for (j=0;j<arrsize;j++){
	   Element** p = ptrsArr[j];//取出的时候，它管理的是什么？
	for (lowI=0;lowI<lowFields;lowI++){
		printf("id=%d , age=%d \n",p[lowI]->id,p[lowI]->age);
	}
	printf("***************************\n");
	}
	
	
	return 0;
}



