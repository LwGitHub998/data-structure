//闭散列
#define MAX_SIZE 10   //初始大小
typedef int HDataType;
enum State
{
	EMPTY,  //空
	EXTXT,  //存储
	DELET,  //删除
};
typedef struct HTELEM  //哈希表中存储的元素数字及状态
{
	HDataType _data;  //数据
	enum State _state;  //状态
}HTELEM, *pHTELEM;

//静态
#if AAA
typedef struct HashTable
{
	HTELEM _ht[MAX_SIZE];  //哈希表
	int _size; //元素个数
}HashTable, *pHashTable;
int HashFun(HDataType data) //哈希函数
{
	return (data % 10);
}
//初始化
void HashInit(pHashTable phashtable)
{
	//静态
	assert(phashtable); //指针不能为空
	//状态置空
	for (int i = 0; i < MAX_SIZE; i++)
	{
		phashtable->_ht[i]._state = EMPTY;
	}
	//元素个数初始值为0
	phashtable->_size = 0;
}
//元素个数
int HashSize(pHashTable phashtable)
{
	assert(phashtable);
	return phashtable->_size;
}
//哈希表是否为空
int HashEmpty(pHashTable phashtable)
{
	assert(phashtable);
	return phashtable->_size == 0;
}
//插入
void HashInsert(pHashTable phashtable, HDataType data)
{
	//静态
	assert(phashtable);
	//计算哈希地址
	int address = HashFun(data);
	//找到存储位置，检测该位置状态是否为空
	//状态不为空，则找下一个位置
	//为空，则插入元素，改变状态
	int i = 1;
	while (phashtable->_ht[address]._state != EMPTY)
	{
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	//插入元素
	phashtable->_ht[address]._data = data;
	phashtable->_ht[address]._state = EXTXT;
	phashtable->_size++;

}
//查找
int HashFind(pHashTable phashtable, HDataType data)
{

	//静态
	assert(phashtable);
	//计算哈希地址
	int address = HashFun(data);
	//找到存储位置，检测该位置状态是否为空
	//状态不为空，则找下一个位置
	//为空，则插入元素，改变状态
	int i = 1;
	while (phashtable->_ht[address]._state != EMPTY)
	{
		//线性探测规则查找
		if (phashtable->_ht[address]._state == EXTXT)
		{
			if (phashtable->_ht[address]._data == data)
			{
				return address;
			}
		}
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	return -1;
}
//删除
int HashDelete(pHashTable phashtable, HDataType data)
{
	//静态
	assert(phashtable);
	//计算哈希地址
	int address = HashFun(data);
	//找到存储位置，检测该位置状态是否为空
	//状态不为空，则找下一个位置
	//为空，则插入元素，改变状态
	int i = 1;
	while (phashtable->_ht[address]._state != EMPTY)
	{
		//线性探测规则查找
		if (phashtable->_ht[address]._state == EXTXT)
		{
			if (phashtable->_ht[address]._data == data)
			{
				phashtable->_ht[address]._state = DELET;
				return 1;
			}
		}
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	return 0;
}
#endif

//动态
#if !AAA
typedef struct HashTableDy
{
	pHTELEM _ht;  //哈希链表表
	int _size; //元素个数
	int _capacity;  //容量  最大元素个数
	int _totly;  //已经使用位置个数
	//int (*DATATOINT)(HashTableDy) 函数指针  把数据转换为int  重命名  传参     初始化   哈希函数处使用
}HashTableDy, *pHashTableDy;

//初始化
void HashInit(pHashTableDy phashtabledy, int capacity)
{

	assert(phashtabledy); //指针不能为空
	//开辟空间
	pHTELEM ph = (pHTELEM)malloc(capacity * sizeof(HTELEM));
	if (NULL == ph)
	{
		assert(0);
	}
	//状态置空
	for (int i = 0; i < capacity; i++)
	{
		(ph + i)->_state = EMPTY;

	}
	phashtabledy->_ht = ph;
	//初始化容量
	phashtabledy->_capacity = capacity;	
	//元素个数初始值为0
	phashtabledy->_size = 0;
	phashtabledy->_totly = 0;
}
//元素个数
int HashSize(pHashTableDy phashtabledy)
{
	assert(phashtabledy);
	return phashtabledy->_size;
}
//哈希表是否为空
int HashEmpty(pHashTableDy phashtabledy)
{
	assert(phashtabledy);
	return phashtabledy->_size == 0;
}
//哈希函数
int HashFunDy(HDataType data, int capacity)
{
	//调用素数表，
	return data % capacity;
}
//扩容
void Dilatation(pHashTableDy *phashtabledy)
{
	//开辟新空间,为原空间的两倍
	int capacity = (*phashtabledy)->_capacity * 2;
	pHTELEM ph = (pHTELEM)malloc(capacity * sizeof(HTELEM));
	if (NULL == ph)
	{
		assert(0);
	}
	//新空间的状态为空
	for (int i = 0; i < capacity; i++)
	{
		(ph + i)->_state = EMPTY;
	}
	//拷贝元素
	for (int i = 0; i < (*phashtabledy)->_capacity; i++) //遍历原空间
	{
		if (((*phashtabledy)->_ht + i)->_state == EXTXT)  //存在元素
		{
			//插入到新空间
			int address = HashFunDy(((*phashtabledy)->_ht + i)->_data, capacity);
			while ((ph + address)->_state != EMPTY)
			{
				//线性探测
				address = address + 1;
				if (address == MAX_SIZE)
					address = 0;
				////二次探测
				//address = (address + i * i) % MAX_SIZE;
				//i++;
				//if (address == MAX_SIZE)
				//	address = 0;
			}
			//插入元素
			(ph + address)->_data = ((*phashtabledy)->_ht + i)->_data;
			(ph + address)->_state = EXTXT;
		}
	}

	//释放旧空间
	(*phashtabledy)->_capacity = capacity;
	(*phashtabledy)->_totly = (*phashtabledy)->_size;
	pHTELEM del = (*phashtabledy)->_ht;
	(*phashtabledy)->_ht = ph;
	free(del);
	del = NULL;
}
//插入
void HashInsert(pHashTableDy phashtabledy, HDataType data)
{
	//静态
	assert(phashtabledy);
	//判断是否需要开辟空间-负载因子
	if ((phashtabledy->_totly) * 10 / phashtabledy->_capacity >= 7)
	{
		//扩容
		Dilatation(&phashtabledy); //是否需要传输地址
	}
	//计算哈希地址
	int address = HashFunDy(data, phashtabledy->_capacity);
	//找到存储位置，检测该位置状态是否为空
	//状态不为空，则找下一个位置
	//为空，则插入元素，改变状态
	while ((phashtabledy->_ht + address)->_state != EMPTY)
	{
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	//插入元素
	(phashtabledy->_ht + address)->_data = data;
	(phashtabledy->_ht + address)->_state = EXTXT;
	phashtabledy->_size++;
	phashtabledy->_totly++;
}
//查找
int HashFind(pHashTableDy phashtabledy, HDataType data)
{
	assert(phashtabledy);
	//计算哈希地址
	int address = HashFunDy(data, phashtabledy->_capacity);
	//状态不为空
	while ((phashtabledy->_ht + address)->_state != EMPTY)
	{
		//线性探测规则查找
		if ((phashtabledy->_ht + address)->_state == EXTXT)
		{
			if ((phashtabledy->_ht + address)->_data == data)
			{
				return address;
			}
		}
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	return -1;
}
//删除
int HashDelete(pHashTableDy phashtabledy, HDataType data)
{
	assert(phashtabledy);
	//计算哈希地址
	int address = HashFunDy(data, phashtabledy->_capacity);
	//状态不为空
	while ((phashtabledy->_ht + address)->_state != EMPTY)
	{
		//线性探测规则查找
		if ((phashtabledy->_ht + address)->_state == EXTXT)
		{
			if ((phashtabledy->_ht + address)->_data == data)
			{
				(phashtabledy->_ht + address)->_state = DELET;
				return 1;
			}
		}
		//线性探测
		address = address + 1;
		if (address == MAX_SIZE)
			address = 0;
		////二次探测
		//address = (address + i * i) % MAX_SIZE;
		//i++;
		//if (address == MAX_SIZE)
		//	address = 0;
	}
	return -1;
}
//销毁
void HashDestroy(pHashTableDy phashtabledy)
{
	assert(phashtabledy);
	free(phashtabledy->_ht);
	phashtabledy->_ht = NULL;
	phashtabledy->_capacity = 0;
	phashtabledy->_size = 0;
	phashtabledy->_totly = 0;
}

#endif
