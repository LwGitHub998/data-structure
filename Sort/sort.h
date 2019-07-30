//文字使用的stack相关函数，可查看文件Stack
typedef int DataType;

//插入排序
void InsertSort(DataType* arr, int size)
{
	for (int i = 1; i < size; i++) //默认手里有一张牌已经排好,即在0号位置
	{
		int key = arr[i];  //保存待排数据
		int end = i - 1;//拿到已经拍好的序列的最后一个元素的下标
		//找带插入元素的位置  搬移数据
		while (end >= 0 && key < arr[end])  //保证手中有牌  //若k小于end位置的元素，说明还未找到正确的位置
		{
			//所有元素向后挪移一个
			arr[end + 1] = arr[end];  //end+1位置的数据已保存  //最开始end+1的位置为i
			end--;  //end向前继续比较
		}
		arr[end + 1] = key;  //end<=key,找到位置，插入到end的后面
	}
}

//希尔排序
void ShellSort(DataType* arr, int size)
{
	int gap = 3;  //对数据分组
	while (gap > 0)
	{
		//插入排序
		for (int i = gap; i < size; i++) //从当前分组的第二个开始，默认第一个已经排好 //i++时，向后走一步，但是在不同分组之间排序
		{
			int key = arr[i];  //保存待排的数据
			int end = i - gap;//拿到已经拍好的序列的最后一个元素的下标
			while (end >= 0 && key < arr[end])  //保证手中有牌  //若k小于end位置的元素，说明还未找到正确的位置，把元素向后移动
			{
				arr[end + gap] = arr[end];  
				end -= gap;  //end向前继续比较
			}
			arr[end + gap] = key;  //end<=key,找到位置，插入到end的后面
		}
		gap--;	//每次把gap--，分组间距小于1，直到gap = 1 时则把所有的都放在一起排序
		//gap /= 2;
		//gap = 素数;
		//gap = gap / 3 + 1;	改变判断条件，防止+1后死循环
	}
}

//选择排序
void Swap(DataType * x, DataType* y)
{
	DataType tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
//找到最大的元素，与最后的元素交换
void SelectSort(DataType* arr, int size)  //每次所传的size-1
{
	for (int i = 0; i < size - 1; i++)  //遍历数组 //最后一次实际上不需要交换
	{
		int Maxpos = 0;  //默认开头位置元素最大
		for (int j = 1; j < size - 1 - i; j++)  //找到最大的元素
		{
			if (arr[Maxpos] < arr[j])  //不是最大元素的下标
				Maxpos = j;
		}
		if (Maxpos != size - 1 -i)
			Swap(&arr[Maxpos], &arr[size - 1 - i]); //每一次都需要向前挪动一个
	}
}
//选择排序优化
//一次遍历找到最大值和最小值，放在合适的位置
void SelectSort_OP(DataType* arr, int size)  //每次所传的size-1
{
	int begin = 0, end = size - 1;
	while (begin < end)
	{
		//从起始位置开始
		int Maxpos = begin;
		int Minpos = begin;
		int i = begin + 1;
		//找元素位置
		while (i <= end)
		{
			if (arr[Maxpos] < arr[i])  //不是最大元素的下标
				Maxpos = i;
			if (arr[Minpos] > arr[i])  //不是最小元素的下标
				Minpos = i;
			i++;
		}
		if (Maxpos != end)
			Swap(&arr[Maxpos], &arr[end]);
		//交换时，若最小元素的位置为最大元素所要交换的位置，最大元素交换完成后，再交换最小元素时回出现错误，所以需要进行判断，重新定位最小值的位置
		if (Minpos == end)
			Minpos  = Maxpos;
		if (Minpos != 0)
			Swap(&arr[Minpos], &arr[begin]);
		begin++;
		end--;

	}
}

//堆排序
void HeapAdust(DataType *arr, int  size, int parent)  //大堆   一次性只调整一个位置
{
	int child = (parent << 1) + 1;  //找到孩子
	while (child && child <= size - 1)
	{
		//左右孩子中找最大的
		if (child + 1 < size &&arr[child] < arr[child+1])  //右孩子存在且右孩子大于左孩子
		{
			child += 1;
		}
		//孩子大于双亲
		if (arr[parent] < arr[child])
		{
			//交换
			Swap(&arr[child], &arr[parent]);
			//继续向下判断
			parent = child;
			child = (parent << 1) + 1;
		}
		else
			return;
	}
}
void heap(DataType* arr, int size)
{
	//建堆
	int root = ((size - 2) >> 1);  //最后一个非叶子结点
	int end = size - 1;
	for (; root >= 0; root--)  //构建一个大堆
		HeapAdust(arr, size, root);
	//删除——每一次最大的元素在堆顶，然后把最大元素与最后一个元素交换
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);//交换堆顶与最后一个元素
		HeapAdust(arr, end, 0);  //只把end-1个元素再一次调整成堆  end相当于size 
		end--;
	}
}

//冒泡排序
void BubbleSort(DataType *arr, int size)
{
	for (int i = 0; i < size - 1; i++)  //最后一个元素不需要比较
	{
		int ISChange = 0;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j]> arr[j + 1])
			{
				ISChange = 1;
				Swap(&arr[j], &arr[j + 1]);
			}
		}
		/*for (int j = 1; j < size - i; j++)
		{
			if (arr[j]> arr[j - 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}*/
		//在一次排序中，若未发生交换，则说明已经有序
		if (!ISChange)
		{
			return;
		}
	}
}

//快速排序
//以最右侧数据为基准值

int Partion1(DataType *arr, int left, int right)
{
	//找基准值
	DataType key = arr[right - 1];
	
	//双指针，一指针从头开始，二从尾开始
	int begin = left, end = right - 1;
	//一指针从头向后找一个比基准值大的，二指针从后向前找一个比基准值小的
	while (begin< end)
	{
		//防止越界访问
		while (begin < end && arr[begin] <= key) //确定begin的值
			begin++;
		while (begin < end && arr[end] >= key) //确定end的值
			end--;
		//交换一二指针,重复上一步，直到两指针相遇
		if (begin < end)	//区间有效
			Swap(&arr[begin], &arr[end]);
	}
	//交换相遇位置与最右位置（基准值）的数据交换     //划分两个区间
	if (begin != right - 1)
	Swap(&arr[begin], &arr[right - 1]);
	//返回基准值的位置
	return begin;
}
//挖坑法
int Partion2(DataType *arr, int left, int right)
{
	//找基准值
	DataType key = arr[right - 1];   //end的位置为坑
	//双指针，一指针从头开始，二从尾开始
	int begin = left, end = right - 1;
	while (begin < end)
	{
		//从左向右找比基准值大的位置
		while (begin < end && arr[begin] <= key) //确定begin的值
			begin++;
		//把end的值换成begin
		if (begin < end)	//区间有效
		{
			arr[end] = arr[begin];     //填坑，begin的位置成新坑
			end--;
		}
		//从右向左找比基准值小的位置
		while (begin < end && arr[end] >= key) //确定end的值
			begin++;
		//把begin的值换成end
		if (begin < end)	//区间有效
		{
			arr[begin] = arr[end];     //填坑，end的位置成新坑
			begin++;
		}
	}
	//相遇，用key填最后的坑
	arr[begin] = key;
	//返回
	return begin;
}
int Partion3(DataType *arr, int left, int right)
{
	//找基准值
	DataType key = arr[right - 1];
	//双指针
	int cur = left, prev = cur -1;
	while (cur < right)  //cur未越界
	{
		
		//cur比key大，则prev不动      第一个条件不成立则第二个不判断
		//cur比key小，prev向后走一步看是否在一个位置，
			//若在一个位置，则cur之前没有比key大的元素
			//若不再一个位置，则prev向后走过的位置肯定比cur大，需要交换
		if (arr[cur] <= key && ++prev != cur)  
		{
			Swap(&arr[cur], &arr[prev]); 
		}
		++cur;
	}
	if (++prev != right - 1)
		Swap(&arr[prev], &arr[right - 1]);
	return prev;
}
//优化——降低每次划分后取到极大值或极小值的概率
int GetMiddleIndex(DataType *arr, int left, int right)//三数取中间
{
	//返回中间值的一个数
	int mid = left + (right - left) / 2;
	if (arr[left] < arr[right - 1])
	{
		if (arr[mid] < arr[left])
			return left;
		else if (arr[mid] > arr[right - 1])
			return right - 1;
		else    //mid位于中间
			return mid;
	}
	else
	{
		if (arr[mid] > arr[left])
			return left;
		else if (arr[mid] < arr[right - 1])
			return right - 1;
		else    //mid位于中间
			return mid;
	}
}
int Partion_OP(DataType *arr, int left, int right)
{
	//找基准值,找到中间的
	DataType index = GetMiddleIndex(arr, left, right);
	if (index != right - 1)
	{
		Swap(&arr[index], &arr[right]);
	}

	//改变基准值的找法
	DataType key = arr[right - 1];
	//双指针，一指针从头开始，二从尾开始
	int begin = left, end = right - 1;
	//一指针从头向后找一个比基准值大的，二指针从后向前找一个比基准值小的
	while (begin< end)
	{
		//防止越界访问
		while (begin < end && arr[begin] <= key) //确定begin的值
			begin++;
		while (begin < end && arr[end] >= key) //确定end的值
			end--;
		//交换一二指针,重复上一步，直到两指针相遇
		if (begin < end)	//区间有效
			Swap(&arr[begin], &arr[end]);
	}
	//交换相遇位置与最右位置（基准值）的数据交换     //划分两个区间
	if (begin != right - 1)
		Swap(&arr[begin], &arr[right - 1]);
	//返回基准值的位置
	return begin;
}
//递归
void QuickSort(DataType *arr, int left, int right)
{
	//划分道一定数据量（16）时，可以直接使用插入排序
	if (right - left > 1)  //只剩一个元素时不需要排序
	{
		//在待排序列中找一个基准值——区间   在left，right找基准值划分区间，最后返回基准值在区间中的位置
		int boundary = Partion1(arr, left, right);
		//排基准值左边
		QuickSort(arr, left, boundary);
		//排基准值左边
		QuickSort(arr, boundary + 1, right);
	}
}
//循环
void QuickSortNor(DataType *arr,int size)
{
	int left = 0;
	int right = size;
	Stack s;
	StackInit(&s);
	StackPush(&s, right);
	StackPush(&s, left);
	while (!StackEmpty(&s))
	{
		left = StackTop(&s);		//左边界
		StackPop(&s);
		right = StackTop(&s);		//右边界
		StackPop(&s);
		if (left < right)
		{
			int boundary = Partion_OP(arr, left, right);
			//排左侧， 把右半部分区间压栈
			StackPush(&s, right);
			StackPush(&s, boundary + 1);
			//排右侧   把左半部分区间压栈
			StackPush(&s, boundary);
			StackPush(&s, left);
		}
	}
}

//归并排序
void MergeData(DataType *arr, int left, int mid, int right, DataType* temp)
{
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;
	while (begin1 < end1 && begin2 < end2)
	{
		if (arr[begin1] <= arr[begin2])
		{
			temp[index++] = arr[begin1++];
		}
		else
		{
			temp[index++] = arr[begin2++];
		}
	}
	while (begin1 < end1)
	{
		temp[index++] = arr[begin1++];
	}
	while (begin2 < end2)
	{
		temp[index++] = arr[begin2++];
	}
}
void _MergeSort(DataType *arr, int left, int right, DataType* temp)
{
	if (right - left > 1)
	{
		int mid = left + (right - left) / 2;   //划分区间
		_MergeSort(arr, left, mid, temp);
		_MergeSort(arr, mid, right, temp);
		MergeData(arr, left, mid, right, temp);
		memcpy(arr+left, temp+left, right - left);
	}
}
void MergeSort(DataType *arr, int size)
{
	int *temp = (DataType*)malloc(sizeof(DataType)* size);
	if (temp == NULL)
	{
		assert(0);
	}
	_MergeSort(arr, 0, size, temp);
	free(temp);
	temp = NULL;  //栈上空间可以不释放，函数调用结束后自动释放
}
//循环——二路归并
void MergeSortNor(DataType *arr, int size)
{
	int *temp = (DataType*)malloc(sizeof(DataType)* size);
	if (temp == NULL)
	{
		assert(0);
	}
	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			//计算左右两半部分区间
			int left = i;
			int mid = i + gap;
			int right = mid + gap;
			//检测左右半部分区间的合法性
			if (mid > size)
			{
				mid = size;
			}
			if (right > size)
			{
				right = size;
			}
			MergeData(arr, left, mid, right, temp);
		}
		memcpy(arr , temp, size*arr[0]);
		gap *= 2;
	}	
	free(temp);
	temp = NULL;
}
