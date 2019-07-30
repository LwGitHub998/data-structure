#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

//堆
typedef int HPDataType;
typedef int(*pCompar)(HPDataType left, HPDataType right);
typedef struct Heap
{
	HPDataType* _hp; //保存堆的数组
	int _Capecity; //容量
	int _size;//元素个数
	pCompar _compar; //函数指针
}Heap, *pHeap;

// 小于比较 
int Less(HPDataType left, HPDataType right)//小堆
{
	return left < right;
}
// 大于比较 
int Greater(HPDataType left, HPDataType right)  
{
	return left > right;
}
//初始化
void Initheap(pHeap heap, HPDataType* arr, int size, pCompar compar)//初始化
{
	assert(heap);
	//开辟堆空间，将数组中的数据放入
	heap->_hp = (HPDataType*)malloc(size * sizeof(HPDataType));
	if (NULL == heap->_hp)
	{
		assert(0);
	}
	memcpy(heap->_hp, arr, size * sizeof(HPDataType));
	heap->_Capecity = size * sizeof(HPDataType);
	heap->_size = size;
	heap->_compar = compar;
}
//交换
void Swap(HPDataType* Left, HPDataType* Right)
{
	HPDataType tmp = 0;
	tmp = *Left;
	*Left = *Right;
	*Right = tmp;
}
//向下调整法
void AdjustDown(pHeap heap, int parent)
{
	assert(heap);
	int child; //标记最小的孩子，默认为左
	child = (parent << 1) + 1; //根据根结点计算孩子下标
	while (child <= heap->_size - 1)
	{
	//找到最小的孩子  

	//如何判断右孩子存在，如果数据小于0怎么办

	if (child + 1 < heap->_size)//右孩子存在
	{
		//child为较小的孩子的下标
		//if (heap->_hp[child] > heap->_hp[child + 1]) //左孩子大于右孩子
		if (heap->_compar((heap->_hp[child + 1]), (heap->_hp[child])))  //left < right  右孩子小于左孩子
			child = child + 1;
	}
	//检测parent是否满足堆的性质,parent>child  返回1  
	if (heap->_compar((heap->_hp[child]), (heap->_hp[parent])))  //孩子小于父母
	{
		Swap(&(heap->_hp[parent]), &(heap->_hp[child]));//交换
		//继续向下检测
		parent = child; //继续向下比较，直到都满足堆的性质
		child = (parent << 1) + 1;
	}
	else//根结点之下以及是小堆，根满足小堆性质即可
		return;
	}
}
//创建堆
void Createheap(pHeap heap)
{
	assert(heap);
	//构成堆(向下调整法)
	//从最后一个非叶子结点开始调整
	int root = (heap->_size - 2) >> 1; //size为数组元素个数
	for (; root >= 0; root--)
		AdjustDown(heap, root); //向下调整
}
//销毁堆
void Restoyheap(pHeap heap)
{
	assert(heap);
	free(heap->_hp);
	heap->_hp = NULL;
	heap->_Capecity = 0;
	heap->_size = 0;
}
//向上调整
void AdjustUp(pHeap heap, int child)
{
	assert(heap);
	int parent = (child - 1) >> 1;
	while(child > 0)
	{
		if (heap->_compar((heap->_hp[child]), (heap->_hp[parent])))//父母大于孩子   孩子小于父母
		{
			Swap(&(heap->_hp[parent]), &(heap->_hp[child]));//交换
			//继续向下检测
			child = parent; //继续向下比较，直到都满足堆的性质
			parent = (child - 1) >> 1;
		}
		else
			return;
	}
}
//堆插入元素
void Insertheap(pHeap heap, HPDataType d)
{
	assert(heap);
	//先将元素放入最后一个元素之后
	//查看空间是否充足
	if (heap->_Capecity < (int)((heap->_size + 1) * sizeof(HPDataType)))
	{
		HPDataType* hp = (HPDataType*)malloc(heap->_size * 2 * sizeof(HPDataType));
		if (NULL == heap->_hp)
		{
			assert(0);
		}
		memcpy(hp, heap->_hp, heap->_size * 2 * sizeof(HPDataType));
		heap->_hp = hp;
		heap->_Capecity = heap->_size * 2 * sizeof(HPDataType);
		heap->_size = heap->_size + 1;
	}
	heap->_hp[heap->_size - 1] = d;
	//堆向上调整
	int child = heap->_size - 1;
	AdjustUp(heap, child);
}
//删除堆顶元素
void Romoveheap(pHeap heap)
{
	assert(heap);
	if (heap->_size == 0)
	{
		return;
	}
	//交换堆顶与堆底元素
	Swap(&(heap->_hp[heap->_size - 1]), &(heap->_hp[0]));//交换
	//删除堆尾元素
	heap->_size--;
	//向下调整
	AdjustDown(heap, 0); //向下调整
}
//堆元素个数
int Sizeheap(pHeap heap)
{
	assert(heap);
	return heap->_size;
}
//堆是否为空
int Emptyheap(pHeap heap)
{
	assert(heap);
	return heap->_size == 0;
}
//堆顶元素
int Topheap(pHeap heap)
{
	assert(heap);
	return heap->_hp[0];
}
