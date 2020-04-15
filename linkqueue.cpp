#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;


//循环队列数据结构定义
template<typename T>
struct QueueNode
{
		T data;
		QueueNode* next;
};

template<typename T>
struct LinkQueue
{
		QueueNode<T>* front;
		QueueNode<T>* rear;
};

// 打印队列所有元素
template<typename T>
void PrintQueue(LinkQueue<T>* q)
{
		// 空队列
		if(q == NULL || q->front == q->rear)
		{
				return;
		}
		
		QueueNode<T>* cur = q->front->next;
		while(cur != NULL)
		{
				cout << cur->data << " ";
				cur = cur->next;
		}
		
		cout << endl;
}

// 初始化一个空的队列
template<typename T>
void InitQueue(LinkQueue<T>** qo)
{
		LinkQueue<T>* q = new LinkQueue<T>();
		
		q->front = new QueueNode<T>();
		q->front->next = NULL;
		q->front->data = 0;
		
		q->rear = q->front;
		*qo = q;
}

//销毁队列，释放队列的内存空间
template<typename T>
void DestroyQueue(LinkQueue<T>* q)
{
		// 删除所有元素
		QueueNode<T>* cur = q->front;
		QueueNode<T>* tmp = NULL;
		while(cur != NULL)
		{
				tmp = cur->next;
				
				cout << "delete:" << cur << endl;
				delete cur;
				cur = NULL;
				cur = tmp;
		}
		
		// 删除队列本身
		delete q;
		q = NULL;
}

//清空队列
template<typename T>
void ClearQueue(LinkQueue<T>* q)
{
		// 删除所有元素
		QueueNode<T>* cur = q->front->next;
		QueueNode<T>* tmp = NULL;
		while(cur != NULL)
		{
				tmp = cur->next;
				delete cur;
				cur = NULL;
				cur = tmp;
		}
		
		// 注意： 之前写成q->front = q->rear； 导致DestroyQueue崩溃
		// 由于q->front 被赋值成了之前队列的最后一个元素
		q->rear = q->front;
}

//判断队列是否为空
template<typename T>
bool QueueEmpty(LinkQueue<T>* q)
{
		return q->front == q->rear ? true : false;
}

//判断队列是否已满
template<typename T>
bool QueueFull(LinkQueue<T>* q)
{
		return false;
}

//获取队列头
template<typename T>
bool GetHead(LinkQueue<T>* q, T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		//判断队列是否为空
		if(QueueEmpty(q))
		{
				return false;
		}
		
		QueueNode<T>* front = q->front->next;
		e = front->data;
		return true;
}

//入队
template<typename T>
bool EnQueue(LinkQueue<T>* q, const T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		if(QueueFull(q))
		{
				cout << "Queue is full" << endl;
				return false;
		}
		
		QueueNode<T>* qe = new QueueNode<T>();
		qe->data = e;
		qe->next = NULL;
		
		// 当插入第一个元素时，front->next = rear->next；
		// 所以这里，相当于也给front指向了第一个元素
		q->rear->next = qe;
		q->rear = qe;
		return true;
}

//出队，并返回出队的元素
template<typename T>
bool DeQueue(LinkQueue<T>* q, T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		// 判断队列是否为空
		if(QueueEmpty(q))
		{
				cout << "Queue is empty" << endl;
				return false;
		}
		
		QueueNode<T>* qe = q->front->next;
		e = qe->data;
		
		q->front->next = qe->next;
		
		// 只剩下最后一个元素
		if(q->rear == qe)
		{
				q->rear = q->front;
		}
		
		delete qe;
		qe = NULL;
		return true;
}

//获取队列的长度
template<typename T>
int QueueLength(LinkQueue<T>* q)
{
	 int i=0;
	 
	 if(q->front == q->rear)
	 {
	 		return 0;
	 }
	 
	 QueueNode<T>* cur = q->front->next;
	 while(cur != NULL)
	 {
	 		i++;
	 		cur = cur->next;
	 }
	 
	 return i;
}

//主程序
int main(int argc, char** argv)
{
		LinkQueue<int>* q = NULL;
		
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
		
		getchar();
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		getchar();
		cout << "Queue Element:" << endl;
		PrintQueue(q);
		
		int e = 0;
		GetHead(q, e);
		cout << "GetHead:" << e << endl; 
		getchar();
		for(int i=0; i<6; i++)
		{
				if(DeQueue(q, e))
					cout << "DeQueue[" << i << "]: " << e << endl; 
		}
		
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		getchar();
		//测试清空队列
		for(int i=0; i<10; i++)
		{
				cout << "EnQueue:" << i << endl;
				EnQueue(q, i+1);
		}
		
		cout << "Queue Element:" << endl;
		PrintQueue(q);
		
		cout << "After EnQueue ..." << endl;
		ClearQueue(q);
		cout << "QueueEmpty: " << QueueEmpty(q) << endl;
		cout << "QueueLength:" << QueueLength(q) << endl;
		
		DestroyQueue(q);
		cout << "Test end" << endl;
		return 0;
}