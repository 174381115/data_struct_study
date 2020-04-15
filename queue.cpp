#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	10

//栈数据结构定义
template<typename T>
struct Queue
{
		T data[MAX_ELEM];
		int count;
};

// 初始化一个空的队列
template<typename T>
void InitQueue(Queue<T>** qo)
{
		Queue<T>* q = new Queue<T>();
		
		q->count = 0;
		*qo = q;
}

//销毁队列，释放队列的内存空间
template<typename T>
void DestroyQueue(Queue<T>* q)
{
		delete q;
		q = NULL;
}

//清空队列
template<typename T>
void ClearQueue(Queue<T>* q)
{
		q->count = 0;
}

//判断队列是否为空
template<typename T>
bool QueueEmpty(Queue<T>* q)
{
		return q->count == 0 ? true : false;
}

//获取队列头
template<typename T>
bool GetHead(Queue<T>* q, T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		if(q->count == 0)
		{
				return false;
		}
		
		e = q->data[q->count-1];
		return true;
}

//入队
template<typename T>
bool EnQueue(Queue<T>* q, const T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		if(q->count >= MAX_ELEM)
		{
				cout << "Queue is full" << endl;
				return false;
		}
		
		q->data[q->count] = e;
		q->count++;
		return true;
}

//出队，并返回出队的元素
template<typename T>
bool DeQueue(Queue<T>* q, T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		if(q->count == 0)
		{
				cout << "Queue is empty" << endl;
				return false;
		}
		
		e = q->data[0];
		
		// 移动元素
		for(int i=1; i<q->count; i++)
		{
				q->data[i-1] = q->data[i];
		}
		
		q->count--;
		return true;
}

//获取队列的长度
template<typename T>
int QueueLength(Queue<T>* q)
{
	 return q->count;
}

//主程序
int main(int argc, char** argv)
{
		Queue<int>* q = NULL;
		
		// 初始化队列
		cout << "Init queue ..." << endl;
		InitQueue(&q);
		
		if(q == NULL)
		{
				cout << "New queue failed" << endl;
				exit(-1);
		}
		
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		
		cout << "Test EnQueue ..." << endl;
		for(int i=0; i<15; i++)
		{
				cout << "EnQueue:" << i << endl;
				EnQueue(q, i+1);
		}
		
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		
		int e = 0;
		GetHead(q, e);
		cout << "GetHead:" << e << endl; 
		
		for(int i=0; i<15; i++)
		{
				if(DeQueue(q, e))
					cout << "DeQueue[" << i << "]: " << e << endl; 
		}
		
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		
		//测试清空队列
		for(int i=0; i<MAX_ELEM; i++)
		{
				cout << "EnQueue:" << i << endl;
				EnQueue(q, i+1);
		}
		
		cout << "After EnQueue ..." << endl;
		ClearQueue(q);
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		
		DestroyQueue(q);
		cout << "Test end" << endl;
		return 0;
}