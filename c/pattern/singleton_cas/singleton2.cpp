#include <iostream>
#include<stdio.h>
#include "singleton2.h"

using namespace std;

class A {

public:

	A() {
		cout << "person create ..." << endl;
	};
	void getAge() {
	};
private:

};


int process_out_API(A &p) {

	printf("instance=%p \n", &p);
	cout << "person process_out_API ..." << endl;
	return 0;
}


class AbstractMessageProxy {
public:
	virtual void send()=0;
	virtual void recv()=0;
	virtual ~AbstractMessageProxy() { cout << "AbstractMessageProxy 释放了... " << endl; };
};

class Point2PointMessageProxy:public AbstractMessageProxy{
public:
	Point2PointMessageProxy();
	virtual void send() ;
	virtual void recv() ;

};
Point2PointMessageProxy::Point2PointMessageProxy() {
	cout << "Point2PointMessageProxy constructor" << endl;
}
void Point2PointMessageProxy::recv() {
	cout << "Point2PointMessageProxy 接受信息了... " << endl;
}
void Point2PointMessageProxy::send() {
	cout << "Point2PointMessageProxy 发送信息了... " << endl;
}

class PubSubMessageProxy :public AbstractMessageProxy {
public:
	PubSubMessageProxy();
	virtual void send();
	virtual void recv();

};

PubSubMessageProxy::PubSubMessageProxy() {
	cout << "PubSubMessageProxy constructor " << endl;

}
void PubSubMessageProxy::recv() {
	cout << "PubSubMessageProxy 接受信息了... " << endl;
}

void PubSubMessageProxy::send() {

	cout << "PubSubMessageProxy 发送信息了... " << endl;

}



int main(int argc, const char *arvgs[]) {
	cout<<"main start"<<endl;

	A &p = Singleton2<A>::getInstance();
	process_out_API(p);


	p = Singleton2<A>::getInstance();
	process_out_API(p);

	//cout << p.getAge << endl;


	AbstractMessageProxy & instance = Singleton2<Point2PointMessageProxy>::getInstance();
	instance.send();
	instance = Singleton2<Point2PointMessageProxy>::getInstance();
	instance.send();

	instance = Singleton2<PubSubMessageProxy>::getInstance();
	instance.send();
	instance.recv();


	//system("pause");

	return 0;
}

