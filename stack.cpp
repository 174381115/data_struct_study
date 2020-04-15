#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	10

//ջ���ݽṹ����
template<typename T>
struct Stack
{
		T data[MAX_ELEM];	// ջ����
		int top;					// ջ��λ��
};

template<typename T>
void PrintStack(Stack<T>* s)
{
		if(s->top < 0)
		{
				cout << "Empty stack." << endl;
				return;
		}
		
		for(int i=0; i<=s->top; i++)
		{
				cout << s->data[i] << " ";
		}
		
		cout << endl;
}

//��ʼ��ջ�������ڴ�
template<typename T>
void InitStack(Stack<T>** s)
{
		Stack<T> *newStack = new Stack<T>();
		
		newStack->top = -1;
		*s = newStack;
}


//����ջ
template<typename T>
void DestroyStack(Stack<T>* s)
{
		delete s;
		s = NULL;
}

//���ջ
template<typename T>
void ClearStack(Stack<T>* s)
{
		s->top = -1;
}


// ջ�Ƿ�Ϊ��
template<typename T>
bool EmptyStack(Stack<T>* s)
{
		return s->top < 0 ? true : false;
}

//��ȡջ��Ԫ��
template<typename T>
bool GetTop(Stack<T>* s, T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		e = s->data[s->top];
		return true;
}

//��ջ
template<typename T>
bool Push(Stack<T>* s, const T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		if(s->top >= MAX_ELEM-1)
		{
				cout << "Full stack." << endl;
				return false;
		}
		
		s->data[s->top+1] = e;
		s->top++;
		return true;
}

//��ջ
template<typename T>
bool Pop(Stack<T>* s, T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		if(s->top < 0)
		{
				cout << "Empty stack." << endl;
				return false;
		}
		
		e = s->data[s->top];
		s->top--;
		return true;
}

// ��ȡջ�ĳ���
template<typename T>
int StackLength(Stack<T>* s)
{
		return s->top+1;
}

int main(int argc, char** argv)
{
		Stack<int>* s1;
		
		InitStack(&s1);
		
		PrintStack(s1);
		
		cout << "Stack Empty:" << EmptyStack(s1) << endl;
		cout << "Stack Length:" << StackLength(s1) << endl;
		
		for(int i=0; i<15; i++)
		{
				Push(s1, i+1);
		}
		
		PrintStack(s1);
		cout << "Stack Empty:" << EmptyStack(s1) << endl;
		cout << "Stack Length:" << StackLength(s1) << endl;
		
		int e = 0;
		GetTop(s1, e);
		cout << "Stack Top:" << e << endl;
		
		//
		for(int i=0; i<15; i++)
		{
				if(Pop(s1, e))
				{
					cout << "Stack Pop:" << e << endl;
				}
		}
		
		cout << "After pop:" << endl;
		cout << "Stack Empty:" << EmptyStack(s1) << endl;
		PrintStack(s1);
		return 0;
}