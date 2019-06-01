#ifndef __SINGLETON2_H__
#define __SINGLETON2_H__

//代码复用
//逻辑复用
//模板不用考虑多处重复包含问题，因为模板是抽象的并没有实现

template <class T>

class Singleton2 {
	typedef Singleton2 ProxyType;
	typedef T TargetType;

	friend T;
private:
	Singleton2(ProxyType&);
	Singleton2();
	ProxyType& operator= (const ProxyType&);
	
public:
	static TargetType& getInstance()
	{
		static TargetType instance;
		//2 回调
		creator.nullCallback();
		return  instance;
	}
private:
	class CreatorTriiger {
	public:
		CreatorTriiger() {
			//1 触发实例化 单例容器
			//initailize target instance
			ProxyType::getInstance();
		}
		//ensure trigger  CreatorTriiger instance intialize
		void nullCallback() {
		}

	};

	static CreatorTriiger creator;

};
 
template<class T>
typename Singleton2<T>::CreatorTriiger Singleton2<T>::creator;


#endif

