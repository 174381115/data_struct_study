#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	11

//ѭ���������ݽṹ����
template<typename T>
struct Queue
{
		T data[MAX_ELEM];
		int front;
		int rear;
};

// ��ӡ��������Ԫ��
template<typename T>
void PrintQueue(Queue<T>* q)
{
		if(q == NULL || q->front == q->rear)
		{
				return;
		}
		
		for(int i=q->front; i != q->rear; i = (i+1)%MAX_ELEM)
		{
				cout << q->data[i] << " ";
		}
		
		cout << endl;
}

// ��ʼ��һ���յĶ���
template<typename T>
void InitQueue(Queue<T>** qo)
{
		Queue<T>* q = new Queue<T>();
		
		q->front = 0;
		q->rear = 0;
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
		q->front = 0;
		q->rear = 0;
}

//�ж϶����Ƿ�Ϊ��
template<typename T>
bool QueueEmpty(Queue<T>* q)
{
		return q->front == q->rear ? true : false;
}

//�ж϶����Ƿ�����
template<typename T>
bool QueueFull(Queue<T>* q)
{
		return (q->rear+1)%MAX_ELEM == q->front;
}

//��ȡ����ͷ
template<typename T>
bool GetHead(Queue<T>* q, T& e)
{
		if(q == NULL)
		{
				return false;
		}
		
		//�ж϶����Ƿ�Ϊ��
		if(QueueEmpty(q))
		{
				return false;
		}
		
		e = q->data[q->rear-1];
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
		
		if(QueueFull(q))
		{
				cout << "Queue is full" << endl;
				return false;
		}
		
		q->data[q->rear%MAX_ELEM] = e;
		q->rear = (q->rear+1)%MAX_ELEM;
		
		cout << "=================================" << endl;
		cout << "EnQueue: " << q->front << ":" << q->rear << endl;
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
		
		// �ж϶����Ƿ�Ϊ��
		if(QueueEmpty(q))
		{
				cout << "Queue is empty" << endl;
				return false;
		}
		
		e = q->data[q->front];
		q->front++;
		cout << "=================================" << endl;
		cout << "DeQueue: " << q->front << ":" << q->rear << endl;
		return true;
}

//��ȡ���еĳ���
template<typename T>
int QueueLength(Queue<T>* q)
{
	 return (q->rear-q->front+MAX_ELEM)%MAX_ELEM;
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
		
		cout << "Queue Element:" << endl;
		PrintQueue(q);
		
		int e = 0;
		GetHead(q, e);
		cout << "GetHead:" << e << endl; 
		
		for(int i=0; i<6; i++)
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