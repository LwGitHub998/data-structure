#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <malloc.h>

//开散列
#define MAX_SIZE 10
typedef int HBDdtaType;
typedef struct HashBuckNode  //结点
{
	struct HashBuckNode* _next;
	HBDdtaType _data;
}HashBuckNode, *pHashBuckNode;
//数组
typedef struct HashBuck  //哈希表
{
	pHashBuckNode _Hasharr;
	int _size;  //元素个数
	int _capacity;  //最大元素个数
}HashBuck, *pHashBuck;

void HashInit(pHashBuck phashbuck, int capacity)  //初始化
{
	assert(phashbuck);
	//开辟空间
	//在申请内存大小时不能直接将指针类型放到sizeof内部
	pHashBuckNode ph = (pHashBuckNode)malloc(capacity * sizeof(HashBuckNode));
	if (NULL == ph)
	{
		assert(0);
	}
	//赋初始值
	for (int i = 0; i < capacity; i++)
	{
		(ph + i)->_data = i;
		(ph + i)->_next = NULL;
	}
	phashbuck->_Hasharr = ph;
	phashbuck->_size = 0;
	phashbuck->_capacity = capacity;
}

int HashEmpty(pHashBuck phashbuck) //判空
{
	assert(phashbuck);
	return phashbuck->_size == 0;
}
int HashSize(pHashBuck phashbuck) //元素个数
{
	assert(phashbuck);
	return phashbuck->_size;
}
//哈希函数
int HashFun(HBDdtaType data, int capacity)
{
	return data % capacity;
}
pHashBuckNode HBByNode(HBDdtaType data)
{
	pHashBuckNode newnode = (pHashBuckNode)malloc(sizeof(HashBuckNode));
	if (NULL == newnode)
	{
		assert(0);
	}
	newnode->_data = data;
	newnode->_next = NULL;
	return newnode;
}
//扩容
void Dilatation(pHashBuck phashbuck)
{
	//开辟新空间,为原空间的两倍
	int capacity = phashbuck->_capacity * 2;
	pHashBuckNode ph = (pHashBuckNode)malloc(capacity * sizeof(HashBuckNode));
	if (NULL == ph)
	{
		assert(0);
	}
	//新空间的状态为空
	for (int i = 0; i < capacity; i++)
	{
		(ph + i)->_data = i;
		(ph + i)->_next = NULL;
	}
	//拷贝元素
	for (int i = 0; i < phashbuck->_capacity; i++)
	{
		
		if (((phashbuck->_Hasharr) + i)->_next)//存在元素
		{
			pHashBuckNode cur = ((phashbuck->_Hasharr) + i)->_next;  //原空间
			while (cur)
			{
				//拿出元素
				int data = cur->_data;
				//计算桶号
				int address = HashFun(data, capacity);//新空间的桶号
				//头插入到新空间
				pHashBuckNode newnode = HBByNode(data);
				if (NULL == (ph + address)->_next)
				{
					(ph + address)->_next = newnode;
				}
				else
				{
					newnode->_next = (ph + address)->_next;
					(ph + address)->_next = newnode;
				}
				//头删旧空间
				((phashbuck->_Hasharr) + i)->_next = cur->_next;
				free(cur);
				cur = NULL;
				cur = ((phashbuck->_Hasharr) + i)->_next;

			}
		}
	}
	//释放旧空间
	free(phashbuck->_Hasharr);
	phashbuck->_Hasharr = ph;
	phashbuck->_capacity = capacity;
}
void HashInsert(pHashBuck phashbuck, HBDdtaType data)//插入
{
	assert(phashbuck);


	//扩容
	if (phashbuck->_size == phashbuck->_capacity)
		Dilatation(phashbuck);


	//计算桶号
	int address = HashFun(data, phashbuck->_capacity);
	//查看元素是否存在
	//遍历桶号所在的链表，查看元素是否存在
	pHashBuckNode cur = ((phashbuck->_Hasharr) + address)->_next;  //从第一个元素开始
	while (cur)
	{
		if (cur->_data == data)
		{
			return;
		}
		cur = cur->_next;
	}
	//不存在
	//创建结点，开辟空间
	pHashBuckNode newnode = HBByNode(data);
	//头插入链表
	//第一个结点
	if (NULL == ((phashbuck->_Hasharr) + address)->_next)
	{
		((phashbuck->_Hasharr) + address)->_next = newnode;
	}
	else
	{
		newnode->_next = ((phashbuck->_Hasharr) + address)->_next;
		((phashbuck->_Hasharr) + address)->_next = newnode;
	}
	phashbuck->_size++;
}
//删除
int HashDelete(pHashBuck phashbuck, HBDdtaType data)
{
	assert(phashbuck);
	//计算桶号
	int address = HashFun(data, phashbuck->_capacity);
	//查看元素是否存在
	//遍历桶号所在的链表，查看元素是否存在
	pHashBuckNode cur = ((phashbuck->_Hasharr) + address)->_next;  //从第一个元素开始
	pHashBuckNode pre = ((phashbuck->_Hasharr) + address);  //上一个结点
	while (cur)
	{
		if (cur->_data == data)
		{
			pre->_next = cur->_next;
			free(cur);
			cur = NULL;
			phashbuck->_size--;
			return 1;
		}
		pre = cur;
		cur = cur->_next;
	}
	//不存在
	return 0;

}
//查找
int HashFind(pHashBuck phashbuck, HBDdtaType data)
{
	assert(phashbuck);
	//计算桶号
	int address = HashFun(data, phashbuck->_capacity);
	//查看元素是否存在
	//遍历桶号所在的链表，查看元素是否存在
	pHashBuckNode cur = ((phashbuck->_Hasharr) + address)->_next;  //从第一个元素开始
	while (cur)
	{
		if (cur->_data == data)
		{
			return address;
		}
		cur = cur->_next;
	}
	return 0;
}
//销毁
void HashDestroy(pHashBuck phashbuck)
{
	assert(phashbuck);
	//释放每个结点
	for (int i = 0; i < phashbuck->_capacity; i++)
	{

		if (((phashbuck->_Hasharr) + i)->_next)//存在元素
		{
			pHashBuckNode cur = ((phashbuck->_Hasharr) + i)->_next;
			while (cur)
			{
				//头删结点
				((phashbuck->_Hasharr) + i)->_next = cur->_next;
				free(cur);
				cur = NULL;
				cur = ((phashbuck->_Hasharr) + i)->_next;
			}
		}
	}
	//释放旧空间
	free(phashbuck->_Hasharr);
	phashbuck->_Hasharr = NULL;
	phashbuck->_capacity = 0;
	phashbuck->_size = 0;

}
