#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;


template<typename T>
struct Node
{
		T data;
		struct Node* next;
};

template<typename T>
using SqList = Node<T>* ;


// 打印List元素
template<typename T>
void PrintList(SqList<T> head)
{
		if(head == NULL)
		{
				cout << "List is null" << endl;
				return;
		}

		
		Node<T>* cur = head->next;
		while(cur != head)
		{
				cout << cur->data << " ";
				cur = cur->next;
		}
		
		cout << endl;
}

//初始化线性表，建立一个空表
template<typename T>
void InitList(SqList<T>* list)
{
		if(list == NULL)
		{
				cout << "List is null" << endl;
				return;
		}
		
		// 创建头结点， 将头结点返回回去
		Node<T>* head = new Node<T>;
		head->data = 0;
		head->next = head;
		
		*list = head;
}

//判断线性表是否为空
template<typename T>
bool ListEmpty(SqList<T> list)
{
	if(list == NULL)
	{
			return true;
	}
	
	return list->next == list ? true : false;	
}

//清空线性表
template<typename T>
void ClearList(SqList<T> list)
{
	if(list == NULL)
	{
			return;
	}
	
	Node<T>* cur = list->next;
	Node<T>* next = NULL;
	
	while(cur != list)
	{
			// 在删除前，保存下一个结点
			next = cur->next;
			
			// 删除当前结点
			delete cur;
			cur = NULL;
			cur = next;
	}
	
	list->next = list;
}

//获取指定位置的元素
template<typename T>
bool GetElement(SqList<T> list, int pos, T& e)
{
		if(list == NULL)
		{
				return false;
		}
		
		int i=0;
		Node<T>* cur = list->next;
		
		while(cur != list && i<pos)
		{
				cur = cur->next;
				i++;
		}
		
		if(i<pos || cur == list)
		{
				return false;
		}
		
		e = cur->data;
		return true;
}

//获取线性表的长度
template<typename T>
int ListLength(SqList<T> list)
{
	if(list == NULL)
	{
			return -1;
	}
	
	// 获取第一个结点
	Node<T>* cur = list->next;
	int i=0;
	
	//如果当前结点不为空，则继续计数下一个结点
	while(cur != list)
	{
			i++;
			
			cur = cur->next;	
	}
	
	return i;
}

//在指定位置插入新元素
template<typename T>
bool ListInsert(SqList<T> list, const T& e, int pos)
{
	if(list == NULL)
	{
			return false;
	}
	
	Node<T>* cur = list->next;
	Node<T>* pre = list;
	int i = 0;
	
	// 找到第pos个结点
	while(i < pos && cur != list)
	{
			pre = cur;
			cur = cur->next;
			i++;
	}
	
	//创建新的结点
	Node<T> *newNode = new Node<T>;
	
	//插入新元素
	newNode->data = e;
	newNode->next = cur;
	pre->next = newNode;
	return true;
}

//删除指定位置的元素
template<typename T>
bool ListDelete(SqList<T> list, T& e, int pos)
{
	if(list == NULL)
	{
			return false;
	}
	
	Node<T>* cur = list->next;
	Node<T>* pre = list;
	int i=0;
	
	// 找到第pos个结点
	while(i< pos && cur != list)
	{
			i++;
			pre = cur;
			cur = cur->next;	
	}
	
	if(i<pos)
	{
			return false;
	}
	
	// 删除当前结点，并更改结点连接关系
	pre->next = cur->next;
	delete cur;
	cur = NULL;
	return true;
}


// 查找值为e的元素的位置
template<typename T>
bool FindElement(SqList<T> list, const T& e, int& pos)
{
		if(list == NULL)
		{
				return false;
		}
		
		Node<T>* cur = list->next;
		int i=0;
		while(cur != list)
		{
				if(cur->data == e)
				{
						pos = i;
						return true;
				}
		}
		
		return false;
}

// 合并两个链表
template<typename T>
bool UnionList(SqList<T> list, SqList<T> merge)
{
		if(merge == NULL || ListEmpty(merge))
		{
				return false;
		}
		
		//1. find tail of head list
		Node<T>* tail_first = list->next;
		while(tail_first->next != list)
		{
				tail_first = tail_first->next;
		}
		
		//2. find tail of merge
		Node<T>* tail_second = merge->next;
		while(tail_second->next != merge)
		{
				tail_second = tail_second->next;
		}
		
		cout << "tail first:" << tail_first->data << endl;
		cout << "tail second:" << tail_second->data << endl;		
		
		//2. union
		tail_first->next = merge->next;;
		tail_second->next = list;
		return true;
}


int main(int argc, char** argv)
{
		SqList<int> lst, merge;
		
		InitList(&lst);
		InitList(&merge);
		
		PrintList(lst);

		
		for(int i=0; i<10; i++)
		{
				ListInsert(lst, i+1, i);
		}
		
		cout << "List1: " << endl;
		PrintList(lst);
		
		for(int i=20; i<30; i++)
		{
				ListInsert(merge, i+1, i);
		}
		
		cout << "List2: " << endl;
		PrintList(merge);
		
		UnionList(lst, merge);
		cout << "List after union: " << endl;
		PrintList(lst);
		
		int e;
		ListDelete(lst, e, 2);
		PrintList(lst);
		
		ListDelete(lst, e, 0);
		
		PrintList(lst);
		
		cout << "List length:" << ListLength(lst) << endl;
		
		GetElement(lst, 8, e);
		cout << "Element[8]= " << e << endl;
		
		ClearList(lst);
		PrintList(lst);
		
		cout << "EmptyList:" << ListEmpty(lst) << endl;
		return 0;
}