#include <stdio.h>
#include <windows.h>
#include <assert.h>

typedef int QDataNode;
typedef struct QListNode
{
	struct QListNode * _next;
	QDataNode _data;

}QListNode, *pQListNode;
typedef struct Queue
{
	pQListNode _pFront;//队头指针
	pQListNode _pRear;//队尾指针
}Queue, *pQueue;

//创建一个头结点
pQListNode QBuyNode(QDataNode d)
{
	pQListNode newNode = (pQListNode)malloc(sizeof(QListNode));
	if (NULL == newNode)
	{
		assert(0);
	}
	newNode->_data = d;
	newNode->_next = NULL;
	return newNode;
}
//初始化
void QueueInit(pQueue pqueue)
{
	assert(pqueue);
	//创建一个头结点
	pQListNode newNode = QBuyNode(0);
	//让队头队尾指向头结点
	pqueue->_pFront = newNode;
	pqueue->_pRear = newNode;
}
//尾插
void QueuePush(pQueue pqueue, QDataNode d)
{
	assert(pqueue);
	pQListNode newNode = QBuyNode(d);
	pqueue->_pRear->_next = newNode;
	pqueue->_pRear = pqueue->_pRear->_next;
}
//头删
void QueuePop(pQueue pqueue)
{
	//当删除到只剩一个结点是在删除需要改变尾指针的指向
	assert(pqueue);
	//不能只有头结点
	if (NULL == pqueue->_pFront->_next)
	{
		assert(0);
	}
	pQListNode del = pqueue->_pFront->_next;
	//带头结点
	pqueue->_pFront->_next = pqueue->_pFront->_next->_next;
	free(del);
	del = NULL;
	//当删除到只剩头结点时，需要改变尾指针的指向
	if (NULL == pqueue->_pFront->_next)
	{
		pqueue->_pRear = pqueue->_pFront;
	}
}

//获取队头元素
pQListNode QueueFront(pQueue pqueue)
{
	assert(pqueue);
	if (pqueue->_pFront == pqueue->_pRear)
	{
		return NULL;
	}
	return pqueue->_pFront->_next;
}
//获取队尾元素
pQListNode QueueRear(pQueue pqueue)
{
	assert(pqueue);
	if (pqueue->_pFront == pqueue->_pRear)
	{
		return NULL;
	}
	return pqueue->_pRear;
}
//求队列长度
int QueueSize(pQueue pqueue)
{
	assert(pqueue);
	if (pqueue->_pFront == pqueue->_pRear)
	{
		return 0;
	}
	int count = 0;
	pQListNode cur = pqueue->_pFront->_next;
	while(cur != pqueue->_pRear)
	{
		count++;
		cur = cur->_next;
	}
	return count + 1;
}
//判断队列是否为空
int QueueEmpty(pQueue pqueue)
{
	assert(pqueue);
	if (pqueue->_pFront == pqueue->_pRear)
	{
		return 0;
	}
	return 1;
}
