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

template<typename T>
void shellSort(T arr[], int n){

    // ���� increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    while( h < n/3 )
        h = 3 * h + 1;

    while( h >= 1 ){

        // h-sort the array
        for( int i = h ; i < n ; i ++ ){

            // �� arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... ʹ�ò�������
            T e = arr[i];
            int j;
            for( j = i ; j >= h && e < arr[j-h] ; j -= h )
                arr[j] = arr[j-h];
            arr[j] = e;
        }

        h /= 3;
    }
}


// ����������ȥ
void sort(int* arr, int len)
{
		int inserted = 0;
		int j=0;
		
		int h = 1;
		while(h < len/3)
		{
				h = h*3 + 1;
		}
		
		
		while(h>=1)
		{
				cout << "h=" << h << endl;
				// �ӵڶ���Ԫ�ؿ�ʼ����
				for(int i=h; i<len; i++)
				{
						// ���ȣ���ʱ���浱ǰԪ����Ϊ�ڱ�ֵ
						inserted = arr[i];
						
						// �����ߵ�Ԫ��С���ڱ�ֵ���򽻻�����λ�õ�ֵ
						// ���Ʋ����µ��˿ˣ����µ��˿˲�����ʵ�λ�ã�֮ǰ���˿�ȫ������ƶ�
						for(j=i; j>=h && arr[j-h] > inserted; j-=h)
						{
								arr[j] = arr[j-h];
						}
						
						// �ҵ��˺��ʵ�λ�ã����µ��˿˲��뵽���ʵ�λ��
						arr[j] = inserted;
						
						PrintArray("inner", arr, len);
				}
				
				h/=3;
		}
}



int main(int argc, char** argv)
{
		int array[10] = {0};
		int array_cp[10] = {0};
		
		generateRandom(array, sizeof(array)/sizeof(int));
		memcpy(array_cp, array, sizeof(array));
		
		PrintArray("Before sort", array, sizeof(array)/sizeof(int));
		
		sort(array, sizeof(array)/sizeof(int));
		
		//shellSort(array, sizeof(array)/sizeof(int));
		
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