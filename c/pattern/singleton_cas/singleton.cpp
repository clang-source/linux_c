#ifndef __SINGLETON_CCP_H__
#define  __SINGLETON_CCP_H__

#include <stdlib.h>

extern "C"{

//专门针对cpp的cas
	static void*  atomic_ptr_cas(void   ** addr,void*    old,void*  _new)
	{	
		//base on asm "cmpxchg"
		void* ret =0;
		__asm__ __volatile__(
			"lock;cmpxchg %3,%1;"
			:"=a"(ret)
			:"m"(*addr),"a"(old),"r"(_new)
			:"cc","memory"
		);
		return ret;
	}
}




template <class T>
class Singleton{

   typedef Singleton SelfValue;
   typedef T TargetValue;

   friend T;//REGISTER FRIEND
   private:
   	Singleton(){};
	Singleton(const SelfValue&);
	SelfValue& operator=(SelfValue&);
	~Singleton(){

		};

public:
	static TargetValue & getInstance(){
	#if STATIC_INSTANCE
	static TargetValue ret;
	trigger.nullAction();
	return ret;
	#else

	if (0==ins){
			 
			//void *mem = malloc(sizeof(SelfValue));
			SelfValue *mem= new SelfValue();
			if (0!=atomic_ptr_cas((void**)&ins,0,mem)){
					//free(mem);
					delete mem;
			}
			//force to initialize  creator 
			trigger.nullAction();
	}
	
	return *((TargetValue*)ins);

	#endif

	

	}

	class CreatorTriger{
	public:
			CreatorTriger(){
					SelfValue::getInstance();
			}
			void nullAction(){
				 //null
			}
	};


	private:
		static CreatorTriger trigger;
		static SelfValue *ins;

};

template <class T>
typename Singleton<T>::CreatorTriger  Singleton<T>::trigger;

template <class T>
typename Singleton<T>::SelfValue*  Singleton<T>::ins=0;


#endif














