#include <stdio.h>
#include <windows.h>
#include <assert.h>

#define MAX 10
typedef int DataType;
typedef struct SeqList
{
	DataType data[MAX];
	DataType size;
}SeqList, *PSeqList;

//初始化 
void InitSeqList(PSeqList pSeq)
{
	assert(pSeq != NULL);
	pSeq->size = 0;
	memset(pSeq->data, 0, sizeof(pSeq->data));
}
//打印 
void PrintSeqList(PSeqList pSeq)
{
	for (int i = 0; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->data[i]);
	}
	printf("\n");
}
//尾部插入 
void PushBack(PSeqList pSeq, DataType data)
{
	assert(pSeq != NULL);
	if (pSeq->size == MAX)
	{
		printf("error");
		return;
	}
	pSeq->data[pSeq->size] = data;
	pSeq->size++;
}
//尾部删除 
void PopBack(PSeqList pSeq)
{
	assert(pSeq != NULL);
	if (pSeq->size == 0)
	{
		printf("error");
		return;
	}
	pSeq->size--;
}
//头部插入 
void PushFront(PSeqList pSeq, DataType data)
{
	assert(pSeq != NULL);
	if (pSeq->size == MAX)
	{
		printf("error");
		return;
	}
	int i = 0;
	for (i = pSeq->size; i > 0; i--)
	{
		pSeq->data[i] = pSeq->data[i - 1];
	}
	pSeq->data[0] = data;
	pSeq->size++;
}
//头部删除 
void PopFront(PSeqList pSeq)
{
	assert(pSeq != NULL);
	if (pSeq->size == 0)
	{
		printf("error");
		return;
	}
	int i = 0;
	for (i = 0; i < pSeq->size - 1; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}
//查找指定元素 
int Find(PSeqList pSeq, DataType data)
{
	assert(pSeq != NULL);
	if (pSeq->size == 0)
	{
		printf("error");
		return -1;
	}
	int i = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == data)
		{
			return i;
		}
	}
	return -1;
}
//指定位置插入 
void Insert(PSeqList pSeq, int pos, DataType data)
{
	assert(pSeq != NULL);
	if (pSeq->size == MAX)
	{
		printf("error");
		return;
	}
	int i = 0;
	for (i = pSeq->size; i > pos; i--)
	{
		pSeq->data[i] = pSeq->data[i - 1];
	}
	pSeq->data[pos] = data;
	pSeq->size++;
}
//删除指定位置元素 
void Erase(PSeqList pSeq, int pos)
{
	assert(pSeq != NULL);
	if (pSeq->size == 0)
	{
		printf("error");
		return;
	}
	int i = 0;
	for (i = pos; i < pSeq->size - 1; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}
//删除指定元素 
void Remove(PSeqList pSeq, DataType data)
{
	assert(pSeq != NULL);
	if (pSeq->size == 0)
	{
		printf("error");
		return;
	}
	int i = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == data)
		{
			break;
		}
	}
	if (i < pSeq->size)
	{
		int j = 0;
		for (int j = i; j < pSeq->size - 1; j++)
		{
			pSeq->data[j] = pSeq->data[j + 1];
		}
		pSeq->size--;
	}
}
//删除所有的指定元素 
void RemoveAll(PSeqList pSeq, DataType data)
{
	int i = 0;
	int count = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] != data)
		{
			pSeq->data[count] = pSeq->data[i];
			count++;
		}
	}
	pSeq->size = count;
}
//返回顺序表的大小 
int Size(PSeqList pSeq)
{
	return pSeq->size;
}
//判断顺序表是否为空 
int Empty(PSeqList pSeq)
{
	if (pSeq->size == 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
//冒泡排序 
void BubbleSort(PSeqList pSeq)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < pSeq->size - 1; i++)
	{
		for (j = 0; j < pSeq->size - i - 1; j++)
		{
			if (pSeq->data[j] > pSeq->data[j + 1])
			{
				DataType tmp = pSeq->data[j];
				pSeq->data[j] = pSeq->data[j + 1];
				pSeq->data[j + 1] = tmp;
			}
		}
	}
}
//选择排序 
void SelectSort(PSeqList pSeq)
{
	int i = 0;
	int j = 0;
	int min = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		min = i; //k保存最小元素的下标
		for (j = i; j < pSeq->size; j++)
		{
			if (pSeq->data[min] > pSeq->data[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			//把最小的放在第i个上去
			DataType tmp = pSeq->data[min];
			pSeq->data[min] = pSeq->data[i];
			pSeq->data[i] = tmp;
		}
	}
}
//选择排序的优化 
void SelectSortOP(PSeqList pSeq)
{
	int left = 0;
	int right = pSeq->size - 1;
	while (left <= right)
	{
		int i = 0;
		int min = left;
		int max = right;
		for (i = left; i <= right; i++)
		{
			if (pSeq->data[min] > pSeq->data[i])
			{
				min = i;
			}
			if (pSeq->data[max] < pSeq->data[i])
			{
				max = i;
			}
		}
		if (min != left)
		{
			DataType tmp = pSeq->data[min];
			pSeq->data[min] = pSeq->data[left];
			pSeq->data[left] = tmp;
		}
		//考虑修正的情况，最大值在最小位置，最小值在最大位置。
		if (max == left)
		{
			max = min;
		}
		if (max != right)
		{
			DataType tmp = pSeq->data[max];
			pSeq->data[max] = pSeq->data[right];
			pSeq->data[right] = tmp;
		}
		left++;
		right--;
	}
}
//二分查找 
int BinarySearch(PSeqList pSeq, DataType data)
{
	int left = 0;
	int right = pSeq->size - 1;
	while (left <= right)
	{
		int mid = (left + right) >> 1;
		if (pSeq->data[mid] > data)
		{
			right = mid - 1;
		}
		else if (pSeq->data[mid] < data)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
//二分查找递归写法 
int BinarySearch_R(PSeqList pSeq, int left, int right, DataType data)
{
	if (left > right)
	{
		return -1;
	}
	else
	{
		int mid = (left + right) / 2;
		if (pSeq->data[mid] > data)
		{
			BinarySearch_R(pSeq, left, mid - 1, data);
		}
		else if (pSeq->data[mid] < data)
		{
			BinarySearch_R(pSeq, mid + 1, right, data);
		}
		else
		{
			return mid;
		}
	}
	return -1;
}



