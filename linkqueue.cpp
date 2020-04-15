#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;


//ѭ���������ݽṹ����
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

// ��ӡ��������Ԫ��
template<typename T>
void PrintQueue(LinkQueue<T>* q)
{
		// �ն���
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

// ��ʼ��һ���յĶ���
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

//���ٶ��У��ͷŶ��е��ڴ�ռ�
template<typename T>
void DestroyQueue(LinkQueue<T>* q)
{
		// ɾ������Ԫ��
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
		
		// ɾ�����б���
		delete q;
		q = NULL;
}

//��ն���
template<typename T>
void ClearQueue(LinkQueue<T>* q)
{
		// ɾ������Ԫ��
		QueueNode<T>* cur = q->front->next;
		QueueNode<T>* tmp = NULL;
		while(cur != NULL)
		{
				tmp = cur->next;
				delete cur;
				cur = NULL;
				cur = tmp;
		}
		
		// ע�⣺ ֮ǰд��q->front = q->rear�� ����DestroyQueue����
		// ����q->front ����ֵ����֮ǰ���е����һ��Ԫ��
		q->rear = q->front;
}

//�ж϶����Ƿ�Ϊ��
template<typename T>
bool QueueEmpty(LinkQueue<T>* q)
{
		return q->front == q->rear ? true : false;
}

//�ж϶����Ƿ�����
template<typename T>
bool QueueFull(LinkQueue<T>* q)
{
		return false;
}

//��ȡ����ͷ
template<typename T>
bool GetHead(LinkQueue<T>* q, T& e)
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
		
		QueueNode<T>* front = q->front->next;
		e = front->data;
		return true;
}

//���
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
		
		// �������һ��Ԫ��ʱ��front->next = rear->next��
		// ��������൱��Ҳ��frontָ���˵�һ��Ԫ��
		q->rear->next = qe;
		q->rear = qe;
		return true;
}

//���ӣ������س��ӵ�Ԫ��
template<typename T>
bool DeQueue(LinkQueue<T>* q, T& e)
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
		
		QueueNode<T>* qe = q->front->next;
		e = qe->data;
		
		q->front->next = qe->next;
		
		// ֻʣ�����һ��Ԫ��
		if(q->rear == qe)
		{
				q->rear = q->front;
		}
		
		delete qe;
		qe = NULL;
		return true;
}

//��ȡ���еĳ���
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

//������
int main(int argc, char** argv)
{
		LinkQueue<int>* q = NULL;
		
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
		//������ն���
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