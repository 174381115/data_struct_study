#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ELEM	1024

//patch test message

int MAX_DATA = 999;

template<typename T>
struct SqList
{
		T data[MAX_ELEM];
		int length;
};

void printHello()
{
    cout << "Hello" << endl;
}

// ��ӡListԪ��
template<typename T>
void PrintList(SqList<T>* list)
{
		if(list == NULL)
		{
				cout << "List is null" << endl;
				return;
		}
		
		cout << "List size:" << list->length << endl;
		for(int i=0; i<list->length; i++)
		{
				cout << list->data[i] << " ";
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
		
		memset(list->data, 0, sizeof(T)*MAX_ELEM);
		list->length = 0;
}

//�ж����Ա��Ƿ�Ϊ��
template<typename T>
bool ListEmpty(SqList<T>* list)
{
	if(list == NULL)
	{
			return true;
	}
	
	return list->length == 0 ? true : false;	
}

//������Ա�
template<typename T>
void ClearList(SqList<T>* list)
{
	if(list == NULL)
	{
			return;
	}
	
	memset(list->data, 0, sizeof(T)*MAX_ELEM);
	list->length = 0;
}

//��ȡָ��λ�õ�Ԫ��
template<typename T>
bool GetElement(SqList<T>* list, int pos, T& e)
{
		if(list == NULL)
		{
				return false;
		}
		
		if(pos > list->length-1)
		{
				return false;
		}
		
		e = list->data[pos];
		return true;
}

//��ȡ���Ա�ĳ���
template<typename T>
int ListLength(SqList<T>* list)
{
	if(list == NULL)
	{
			return -1;
	}
	
	return list->length;
}

//��ָ��λ�ò�����Ԫ��
template<typename T>
bool ListInsert(SqList<T>* list, const T& e, int pos)
{
	if(list == NULL)
	{
			return false;
	}
	
	if(pos > MAX_ELEM - 1)
	{
			return false;		
	}
	
	if(list->length >= MAX_ELEM)
	{
			cout << "List is full" << endl;
			return false;	
	}
	
	if(list->length == 0 || pos > list->length-1)
	{
			list->data[pos] = e;
			list->length++;
			return true;
	}
	
	// �ƶ�Ԫ��
	for(int i=list->length - 1; i>pos; i--)
	{
			list->data[i+1] = list->data[i];
	}
	
	//������Ԫ��
	list->data[pos] = e;
	list->length++;
	return true;
}

//ɾ��ָ��λ�õ�Ԫ��
template<typename T>
bool ListDelete(SqList<T>* list, T& e, int pos)
{
	if(list == NULL)
	{
			return false;
	}
	
	if(pos > list->length - 1)
	{
			return false;		
	}
	
	e = list->data[pos];
	// �ƶ�Ԫ��
	for(int i=pos; i<list->length-1; i++)
	{
			list->data[i] = list->data[i+1];
	}
	
	list->length--;
	return true;
}


// ����ֵΪe��Ԫ�ص�λ��
template<typename T>
bool FindElement(SqList<T>* list, const T& e, int& pos)
{
		if(list == NULL)
		{
				return false;
		}
		
		if(list->length == 0)
		{
				return false;
		}
		
		for(int i=0; i<list->length; i++)
		{
				if(e == list->data[i])
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
		
		PrintList(&lst);

		
		for(int i=0; i<128; i++)
		{
				ListInsert(&lst, i+1, i);
		}
		
		PrintList(&lst);
		
		int e;
		ListDelete(&lst, e, 2);
		PrintList(&lst);
		
		ListDelete(&lst, e, 0);
		
		PrintList(&lst);
		
		cout << "List length:" << ListLength(&lst) << endl;
		
		GetElement(&lst, 8, e);
		cout << "Element[8]= " << e << endl;
		
		ClearList(&lst);
		PrintList(&lst);
		
	//	cout << "EmptyList:" << ListEmpty(&lst) << endl;
		return 0;
}