#include <stdio.h>
#include <stdlib.h>
#define NUM 10
//交换数组
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//调整堆
void heapAdjust(int array[], int i, int size)
{
	int lchild = 2 * i;
	int rchild = 2*i + 1;
	int max = i;
	if(i <= size/2)
	{
		if(lchild <= size&&array[lchild]>array[max])
		{
			max = lchild;
		}
		if(rchild <= size&&array[rchild]>array[max])
		{
			max = rchild;
		}
		if(max != i)
		{
			swap(&array[i],&array[max]);
			heapAdjust(array,max,size);
		}
	}
}
//构建堆
void buildHeap(int array[], int size)
{
	int i = 0;
	for(i = size/2;i>=1;i--)
	{
		heapAdjust(array,i,size);
	}
}

//堆排序
void heapSort(int array[], int size)
{
	int i = 0;
	buildHeap(array, size);
	for(i = size; i>=1;i--)
	{
		swap(&array[1],&array[i]);
		heapAdjust(array,1, i-1);
	}
}
//生成随机数字的数组
void randNumGenerator(int array[], int num)
{
    int i;
    srand( (unsigned)time( NULL ) ); 
	int j = 1;
    for (i = 1; i <= num; ++i)
    {
        array[i] = rand()%(num*2);
		for(j = 1;j < i;++j)
		{
			if(array[j] == array[i])
			{
				--i;
			}
		}
    }
}
//打印数组
void printArray(int array[], int num)
{
	int i = 1;
	for(i = 1; i <= num; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n\n");
}
//单元测试
void unitTestHeapSort()
{
	int array[NUM];
	randNumGenerator(array,NUM);
	printArray(array, NUM);
	heapSort(array,NUM);
	printArray(array, NUM);
}

void main()
{
	unitTestHeapSort();
}
