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

// ����������ȥ
void sort(int* arr, int len)
{
		for(int i=1; i<len; i++)
		{
				// ��[0~len-i]֮��� ���ֵ�Ƶ����
				for(int j=0; j<len-i; j++)
				{
					//cout << "j=" << j << endl;
					if(arr[j] > arr[j+1])
					{
							swap(arr, j, j+1);
					}
				}
				
				PrintArray("inner", arr, len);
		}
}

// ����С��������
void sort_push_min(int* arr, int len)
{
		for(int i=1; i<len; i++)
		{
				//// ��[i~len-1]֮�����Сֵ�Ƶ���ײ�
				for(int j=len-1; j>=i; j--)
				{
					//cout << "j=" << j << endl;
					if(arr[j] < arr[j-1])
					{
							swap(arr, j, j-1);
					}
					alg_count++;
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
		
		sort_push_min(array, sizeof(array)/sizeof(int));
		
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