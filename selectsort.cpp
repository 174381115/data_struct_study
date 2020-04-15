#include <iostream>
#include <sys/time.h>

using namespace std;

int MAX_DATA = 9999;

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

void PrintArray(const char* promt, int* arr, int len)
{
		cout << promt << ":" << endl;
		for(int i=0; i<len; i++)
		{
				cout << *(arr+i) << " ";
		}
		
		cout << endl;
}

void swap(int* arr, int i, int j)
{
		int tmp = arr[i];
		
		arr[i] = arr[j];
		arr[j] = tmp;
}


void sort(int* arr, int len)
{
		for(int i=0; i<len; i++)
		{	
				// 寻找[i, n)区间里的最小值
				for(int j=i+1; j<len; j++)
				{
						if(arr[i] > arr[j])
						{
								swap(arr, i, j);
						}
				}
		}
}

int main(int argc, char** argv)
{
		int array[10] = {0};
		
		generateRandom(array, sizeof(array));
		
		PrintArray("Before sort", array, sizeof(array));
		
		sort(array, sizeof(array));
		
		PrintArray("After sort", array, sizeof(array));
}