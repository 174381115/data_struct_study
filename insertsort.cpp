#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

int MAX_DATA = 9999;

int alg_count = 0;

bool cmp(int a,int b)//intΪ������������
{
	//return a>b;//��������
	return a<b;//Ĭ�ϵ���������
}

void PrintArray(const char* promt, int* arr, int len)
{
		cout << promt << ":" << endl;
		for(int i=0; i<len; i++)
		{
				cout << *(arr+i) << " ";
		}
		
		cout << endl;
}


bool verify(int* arr_origin, int* arr_verify, int len)
{
		bool check = true;
		
		int *arr = new int[len];
		
		memcpy(arr, arr_origin, len*sizeof(int));
		
		sort(arr , arr+len, cmp);
		
		for(int i=0; i<len; i++)
		{
				if(arr[i] != arr_verify[i])
				{
						check = false;
						break;
				}
		}
		
		return check;
}

void generateRandom(int* arr, int len)
{
		struct  timeval    tv;
	
		gettimeofday(&tv, NULL);
		srand((unsigned)tv.tv_usec);
		
		for(int i=0; i<len; i++)
		{
				*(arr + i) = rand()%(MAX_DATA);
		}
}


void swap(int* arr, int i, int j)
{
		int tmp = arr[i];
		
		arr[i] = arr[j];
		arr[j] = tmp;
}


// ��������
void sort(int* arr, int len)
{
		int inserted = 0;
		int j=0;
		
		// �ӵڶ���Ԫ�ؿ�ʼ����
		for(int i=1; i<len; i++)
		{
				// �����ǰԪ��С����ߵ�����Ԫ��
				if(arr[i] < arr[i-1])
				{
					// ���ȣ���ʱ���浱ǰԪ����Ϊ�ڱ�ֵ
					inserted = arr[i];
					
					// �����ߵ�Ԫ��С���ڱ�ֵ���򽻻�����λ�õ�ֵ
					// ���Ʋ����µ��˿ˣ����µ��˿˲�����ʵ�λ�ã�֮ǰ���˿�ȫ������ƶ�
					for(j=i; j>0 && arr[j-1] > inserted; j--)
					{
							arr[j] = arr[j-1];
					}
					
					// �ҵ��˺��ʵ�λ�ã����µ��˿˲��뵽���ʵ�λ��
					arr[j] = inserted;
				}
				
				PrintArray("inner", arr, len);
		}
}

void move(int* arr, int pos, int newItem)
{
	 int j=0;
	 
	 for(j=pos; j>0 && arr[j-1] > newItem; j--)
	 {
	 		swap(arr, j, j-1);
	 }
	 
	 arr[j] = newItem;		
}

// ��������
void sort3(int* arr, int len)
{
		int inserted = 0;
		int j=0;
		
		// �ӵڶ���Ԫ�ؿ�ʼ����
		for(int i=1; i<len; i++)
		{
					// �����ߵ�Ԫ��С���ڱ�ֵ���򽻻�����λ�õ�ֵ
					// ���Ʋ����µ��˿ˣ����µ��˿˲�����ʵ�λ�ã�֮ǰ���˿�ȫ������ƶ�
				move(arr, i, arr[i]);
				
				PrintArray("inner", arr, len);
		}
}

void sort2(int* arr, int len)
{
		int i=0, j=0;
		
		// �ӵڶ���Ԫ�ؿ�ʼ����
		for(int i=1; i<len; i++)
		{
				// ����ǰλ�õ�ֵ�����뵽ǰ�벿�ֵ����򼯺��У�����ð������
				for(j=i; j>0 && arr[j] < arr[j-1]; j--)
				{
						swap(arr, j, j-1);
				}
				
				PrintArray("inner", arr, len);
		}
}


int main(int argc, char** argv)
{
		int array[10] = {0};
		int array_cp[10] = {0};
		
		generateRandom(array, sizeof(array)/sizeof(int));
		memcpy(array_cp, array, sizeof(array));
		
		PrintArray("Before sort", array, sizeof(array)/sizeof(int));
		
		sort3(array, sizeof(array)/sizeof(int));
		
		PrintArray("After sort", array, sizeof(array)/sizeof(int));
		
		cout << "Count:" << alg_count << endl;
		
		if(!verify(array_cp, array, sizeof(array)/sizeof(int)))
		{
				cout << "verify failed" << endl;
				exit(-1);
		}
		
		cout << "Verify success." << endl;
		return 0;
}