#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	10

//ջ���ݽṹ����
template<typename T>
struct Queue
{
		T data[MAX_ELEM];
		int count;
};

// ��ʼ��һ���յĶ���
template<typename T>
void InitQueue(Queue<T>** qo)
{
		Queue<T>* q = new Queue<T>();
		
		q->count = 0;
		*qo = q;
}

//���ٶ��У��ͷŶ��е��ڴ�ռ�
template<typename T>
void DestroyQueue(Queue<T>* q)
{
		delete q;
		q = NULL;
}

//��ն���
template<typename T>
void ClearQueue(Queue<T>* q)
{
		q->count = 0;
}

//�ж϶����Ƿ�Ϊ��
template<typename T>
bool QueueEmpty(Queue<T>* q)
{
		return q->count == 0 ? true : false;
}

//��ȡ����ͷ
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

//���
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

//���ӣ������س��ӵ�Ԫ��
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
		
		// �ƶ�Ԫ��
		for(int i=1; i<q->count; i++)
		{
				q->data[i-1] = q->data[i];
		}
		
		q->count--;
		return true;
}

//��ȡ���еĳ���
template<typename T>
int QueueLength(Queue<T>* q)
{
	 return q->count;
}

//������
int main(int argc, char** argv)
{
		Queue<int>* q = NULL;
		
		// ��ʼ������
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
		
		//������ն���
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