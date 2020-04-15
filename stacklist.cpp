#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM 	10

//栈数据结构定义
template<typename T>
struct StackNode
{
		T data;	// 栈数据
		StackNode* next;					// 下一个结点指针
};


template<typename T>
struct Stack
{
		StackNode<T>* top;
		int count;
};

template<typename T>
void PrintStack(Stack<T>* s)
{
		if(s->count == 0)
		{
				cout << "Empty stack." << endl;
				return;
		}
		
		StackNode<T>* cur = s->top;
		while(cur != NULL)
		{
				cout << cur->data << " ";
				cur = cur->next;
		}
		
		cout << endl;
}

//初始化栈，分配内存
template<typename T>
void InitStack(Stack<T>** s)
{
		Stack<T> *newStack = new Stack<T>();
		
		newStack->count = 0;
		newStack->top = NULL;
		*s = newStack;
}


//销毁栈
template<typename T>
void DestroyStack(Stack<T>* s)
{
		StackNode<T>* cur = s->top;
		StackNode<T>* next = NULL;
		while(cur != NULL)
		{
				next = cur->next;
				delete cur;
				cur = NULL;
				cur = next;
		}
		
		delete s;
		s = NULL;
}

//清空栈
template<typename T>
void ClearStack(Stack<T>* s)
{
		StackNode<T>* cur = s->top;
		StackNode<T>* next = NULL;
		while(cur != NULL)
		{
				next = cur->next;
				delete cur;
				cur = NULL;
				cur = next;
		}
		
		s->count = 0;
}


// 栈是否为空
template<typename T>
bool EmptyStack(Stack<T>* s)
{
		return s->count == 0 ? true : false;
}

//获取栈顶元素
template<typename T>
bool GetTop(Stack<T>* s, T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		e = s->top->data;
		return true;
}

//入栈
template<typename T>
bool Push(Stack<T>* s, const T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		StackNode<T>* newNode = new StackNode<T>();
		
		newNode->data = e;
		newNode->next = s->top;
		s->top = newNode;
		s->count++;
		return true;
}

//出栈
template<typename T>
bool Pop(Stack<T>* s, T& e)
{
		if(s==NULL)
		{
				return false;
		}
		
		if(s->count == 0)
		{
				cout << "Empty stack" << endl;
				return false;
		}
		
		StackNode<T>* cur = s->top;
		e = cur->data;
		s->top = cur->next;
		s->count--;
		delete cur;
		cur = NULL;
		return true;
}

// 获取栈的长度
template<typename T>
int StackLength(Stack<T>* s)
{
		return s->count;
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
		for(int i=0; i<20; i++)
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