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


// ��ӡListԪ��
template<typename T>
void PrintList(SqList<T> list)
{
		if(list == NULL)
		{
				cout << "List is null" << endl;
				return;
		}

		
		Node<T>* cur = list->next;
		while(cur != NULL)
		{
				cout << cur->data << " ";
				cur = cur->next;
		}
		
		cout << endl;
}

//��ʼ�����Ա�����һ���ձ�
template<typename T>
void InitList(SqList<T>* list)
{
		if(list == NULL)
		{
				cout << "List is null" << endl;
				return;
		}
		
		// ����ͷ��㣬 ��ͷ��㷵�ػ�ȥ
		Node<T>* head = new Node<T>;
		head->data = 0;
		head->next = NULL;
		
		*list = head;
}

//�ж����Ա��Ƿ�Ϊ��
template<typename T>
bool ListEmpty(SqList<T> list)
{
	if(list == NULL)
	{
			return true;
	}
	
	return list->next == NULL ? true : false;	
}

//������Ա�
template<typename T>
void ClearList(SqList<T> list)
{
	if(list == NULL)
	{
			return;
	}
	
	Node<T>* cur = list->next;
	Node<T>* next = NULL;
	
	while(cur != NULL)
	{
			// ��ɾ��ǰ��������һ�����
			next = cur->next;
			
			// ɾ����ǰ���
			delete cur;
			cur = NULL;
			cur = next;
	}
	
	list->next = NULL;
}

//��ȡָ��λ�õ�Ԫ��
template<typename T>
bool GetElement(SqList<T> list, int pos, T& e)
{
		if(list == NULL)
		{
				return false;
		}
		
		int i=0;
		Node<T>* cur = list->next;
		
		while(cur != NULL && i<pos)
		{
				cur = cur->next;
				i++;
		}
		
		if(i<pos || cur == NULL)
		{
				return false;
		}
		
		e = cur->data;
		return true;
}

//��ȡ���Ա�ĳ���
template<typename T>
int ListLength(SqList<T> list)
{
	if(list == NULL)
	{
			return -1;
	}
	
	// ��ȡ��һ�����
	Node<T>* cur = list->next;
	int i=0;
	
	//�����ǰ��㲻Ϊ�գ������������һ�����
	while(cur != NULL)
	{
			i++;
			
			cur = cur->next;	
	}
	
	return i;
}

//��ָ��λ�ò�����Ԫ��
template<typename T>
bool ListInsert(SqList<T> list, const T& e, int pos)
{
	if(list == NULL)
	{
			return false;
	}
	
	Node<T>* cur = list;
	int i = 0;
	
	// �ҵ���pos�����
	while(i < pos && cur != NULL)
	{
			cur = cur->next;
			i++;
	}
	
	//�����µĽ��
	Node<T> *newNode = new Node<T>;
	
	//������Ԫ��
	newNode->data = e;
	newNode->next = cur->next;
	cur->next = newNode;
	return true;
}

//ɾ��ָ��λ�õ�Ԫ��
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
	
	// �ҵ���pos�����
	while(i< pos && cur != NULL)
	{
			i++;
			pre = cur;
			cur = cur->next;	
	}
	
	if(i<pos)
	{
			return false;
	}
	
	// ɾ����ǰ��㣬�����Ľ�����ӹ�ϵ
	pre->next = cur->next;
	delete cur;
	cur = NULL;
	return true;
}


// ����ֵΪe��Ԫ�ص�λ��
template<typename T>
bool FindElement(SqList<T> list, const T& e, int& pos)
{
		if(list == NULL)
		{
				return false;
		}
		
		Node<T>* cur = list->next;
		int i=0;
		while(cur != NULL)
		{
				if(cur->data == e)
				{
						pos = i;
						return true;
				}
		}
		
		return false;
}


int main(int argc, char** argv)
{
		SqList<int> lst;
		
		InitList(&lst);
		
		PrintList(lst);

		
		for(int i=0; i<128; i++)
		{
				ListInsert(lst, i+1, i);
		}
		
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
		
	//	cout << "EmptyList:" << ListEmpty(&lst) << endl;
		return 0;
}