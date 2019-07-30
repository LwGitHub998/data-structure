typedef int BDataType;
typedef struct BTNode
{
	struct BTNode* pLeft; //左孩子
	struct BTNode* pRight; //右孩子
	BDataType data;
}BTNode, *pBTNode;

//在二叉树的一些操作中，需要使用一些栈和队列的操作
//顺序栈
#define MAXSIZE 10
typedef int SDataType;
typedef struct Stack
{
	SDataType array[MAXSIZE];
	int Top;
}Stack, *pStack;
//初始化
void StackInit(pStack pstack)
{
	assert(pstack);
	pstack->Top = 0;
}
//压栈
void StackPush(pStack pstack, SDataType d)
{
	assert(pstack);
	if (MAXSIZE == pstack->Top)
	{
		return;
	}
	pstack->array[pstack->Top] = d;
	pstack->Top++;
}
//出栈
void StackPop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		return;
	}
	pstack->Top--;
}
//求有效元素个数
int StackSize(pStack pstack)
{
	assert(pstack);
	return pstack->Top;
}
//栈是否为空
int StackEmpty(pStack pstack)
{
	assert(pstack);
	return pstack->Top == 0;
}
//查看栈顶元素
int StackTop(pStack pstack)
{
	assert(pstack);
	if (0 == pstack->Top)
	{
		return -1;
	}
	return pstack->array[pstack->Top - 1];
}

//队列
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
//判断队列是否为空 空返回1
int QueueEmpty(pQueue pqueue)
{
	assert(pqueue);
	if (pqueue->_pFront == pqueue->_pRear)
	{
		return 1;
	}
	return 0;
}



//二叉树
//创建新结点
pBTNode BTBuyNode(BDataType d)
{
	pBTNode newNode = (pBTNode)malloc(sizeof(BTNode));
	if (NULL == newNode)
	{
		assert(0);
	}
	newNode->data = d;
	newNode->pLeft = NULL;
	newNode->pRight = NULL;
	return newNode;
}
//遍历二叉树
//前序遍历-递归
void PreOrder(pBTNode pbtree)
{
	//树不为空
	if (pbtree)
	{
		printf("%d ", pbtree->data);//遍历根节点
		PreOrder(pbtree->pLeft);//遍历左孩子
		PreOrder(pbtree->pRight);//遍历右孩子
	}
}
//前序遍历-非递归1
void PreOrderNor1(pBTNode pbtree)
{
	//树不为空
	if (NULL == pbtree)
	{
		return;
	}
	Stack stack;
	StackInit(&stack);//初始化
	//根结点入栈
	StackPush(&stack, (int)pbtree);//压栈
	while (!StackEmpty(&stack))//栈是否为空 栈为空，返回1
	{
		pBTNode btnode = (pBTNode)StackTop(&stack);//查看栈顶元素
		printf("%d ", btnode->data);
		StackPop(&stack);//出栈
		if (btnode->pRight) //右孩子存在
		{
			StackPush(&stack, (int)(btnode->pRight));//压栈
		}
		if (btnode->pLeft) //左孩子存在
		{
			StackPush(&stack, (int)(btnode->pLeft));//压栈
		}
	}
}
//前序遍历-非递归2
void PreOrderNor2(pBTNode pbtree)
{
	//树不为空
	if (NULL == pbtree)
	{
		return;
	}
	Stack stack;
	StackInit(&stack);//初始化
	StackPush(&stack, (int)pbtree);//压栈
	while (!StackEmpty(&stack))//栈是否为空 栈为空，返回1
	{
		pBTNode btnode = (pBTNode)StackTop(&stack);//查看栈顶元素
		StackPop(&stack);//出栈
		while (btnode)
		{
			printf("%d ", btnode->data);
			if (btnode->pRight) //右孩子存在
			{
				StackPush(&stack, (int)(btnode->pRight));//压栈
			}
			btnode = btnode->pLeft;
		}
	}
}
//中序遍历-递归
void InOrder(pBTNode pbtree)
{
	//树不为空
	if (pbtree)
	{
		InOrder(pbtree->pLeft);//遍历左孩子
		printf("%d ", pbtree->data);//打印根节点
		InOrder(pbtree->pRight);//遍历右孩子
	}
}
//中序遍历-非递归
void InOrderNor(pBTNode pbtree)
{
	//树不为空
	if (NULL == pbtree)
	{
		return;
	}
	Stack stack;
	StackInit(&stack);//初始化
	pBTNode cur = pbtree;
	//找到最左端的结点
	while (!StackEmpty(&stack) || NULL != cur)//根结点
	{
		while (NULL != cur) //遍历左子树
		{
			StackPush(&stack, (int)cur);//压栈
			cur = cur->pLeft;
		}
		cur = (pBTNode)StackTop(&stack);//查看栈顶元素
		printf("%d ", cur->data);//遍历根节点
		StackPop(&stack);//出栈
		cur = cur->pRight;//以右子树为根节点
	}
}
//后序遍历
void PostOrder(pBTNode pbtree)
{
	//树不为空
	if (pbtree)
	{
		PostOrder(pbtree->pLeft);//遍历左孩子
		PostOrder(pbtree->pRight);//遍历右孩子
		printf("%d ", pbtree->data);//遍历根节点
	}
}
//后序遍历-非递归
void PostOrderNor(pBTNode pbtree)
{
	//树不为空
	if (NULL == pbtree)
	{
		return;
	}
	Stack stack;
	StackInit(&stack);//初始化
	pBTNode cur = pbtree;
	pBTNode pPrev = NULL; //标记
	while (!StackEmpty(&stack) || NULL != cur)
	{
		while (NULL != cur) //遍历左子树
		{
			StackPush(&stack, (int)cur);//压栈
			cur = cur->pLeft;
		}
		pBTNode pTop = (pBTNode)StackTop(&stack);//查看栈顶元素
		if (NULL == pTop->pRight || pTop->pRight == pPrev) //不能直接遍历根结点，需要右子树为空或者右子树已经遍历过
		{
			printf("%d ", pTop->data);//遍历根节点
			pPrev = pTop;
			StackPop(&stack);//出栈
		}
		else
		{
			cur = pTop->pRight; //遍历右节点
		}
	}
}
//创建二叉树
void CreateBinTree(pBTNode* pbtree, const char* str, int size, int* count)
{
	if (size > *count && *(str + (*count)) != '#')
	{
		*pbtree = BTBuyNode(*(str + (*count)++)); //创建根结点
		CreateBinTree(&((*pbtree)->pLeft), str, size, count); //创建左子树
		CreateBinTree(&((*pbtree)->pRight), str, size, count); //创建右子树
	}
	else
	{
		(*count)++;
	}
}
//拷贝二叉树
void CopyeBinTree(pBTNode pbtree, pBTNode* pnewbtree)
{
	if (pbtree)
	{
		*pnewbtree = BTBuyNode(pbtree->data); //创建根结点
		CopyeBinTree(pbtree->pLeft, &((*pnewbtree)->pLeft));
		CopyeBinTree(pbtree->pRight, &((*pnewbtree)->pRight));
	}
}
//销毁二叉树
void DestnyBinTree(pBTNode* pbtree)
{
	if (*pbtree)
	{
		DestnyBinTree(&((*pbtree)->pLeft));
		DestnyBinTree(&((*pbtree)->pRight));
		free(*pbtree);
		*pbtree = NULL;
	}
}
//结点个数
int GetBTNodeCount(pBTNode pbtree)
{
	if (pbtree == NULL)//根结点不存在
		return 0;
	return GetBTNodeCount(pbtree->pLeft) + GetBTNodeCount(pbtree->pRight) + 1;//根结点存在
}
//叶子结点个数
int GetLeafBTNodeCount(pBTNode pbtree)
{
	if (pbtree == NULL)//根结点不存在
		return 0;
	if (NULL == pbtree->pLeft &&NULL == pbtree->pRight) //左右孩子不存在
		return 1;
	return GetLeafBTNodeCount(pbtree->pLeft) + GetLeafBTNodeCount(pbtree->pRight);
}
//第k层结点
int GetKLevelBTNodeCount(pBTNode pbtree, BDataType k)
{
	if (pbtree == NULL)//根结点不存在
		return 0;
	if (k <= 0)
		return 0;
	if (1 == k)
		return 1;
	return GetKLevelBTNodeCount(pbtree->pLeft, k - 1) + GetKLevelBTNodeCount(pbtree->pRight, k - 1);
}
//树的高度
int Height(pBTNode pbtree)
{
	if (NULL == pbtree)
		return 0;
	int highL = Height(pbtree->pLeft);
	int highR = Height(pbtree->pRight);
	return highL > highR ? highL + 1 : highR + 1;
}
//获取左孩子结点
pBTNode BTNodeLeft(pBTNode pNode)
{
	if (NULL == pNode)
		return NULL;
	return pNode->pLeft;
}
//获取右孩子结点
pBTNode BTNodeRight(pBTNode pNode)
{
	if (NULL == pNode)
		return NULL;
	return pNode->pRight;
}
//判断一个结点是否在一颗二叉树上
int IsBTNodeInBintree(pBTNode pbtree, pBTNode pNode)
{
	if (NULL == pbtree || NULL == pNode) //树为空或结点为空
	{
		return 0;
	}
	if (pNode == pbtree) //结点为根
	{
		return 1;
	}
	if (IsBTNodeInBintree(pbtree->pLeft, pNode)) //结点在左子树
	{
		return 1;
	}
	if (IsBTNodeInBintree(pbtree->pRight, pNode)) //结点在右子树
	{
		return 1; //可以直接返回此次调用的返回值
		//return IsBTNodeInBintree(pbtree->pRight, pNode);
	}
	return 0;
}
//获得一个结点的双亲结点
pBTNode GetNodeParent(pBTNode pbtree, pBTNode pNode)
{
	pBTNode parent = NULL;
	if (NULL == pbtree || NULL == pNode) //树为空或结点为空
	{
		return NULL;
	}
	if (pNode == pbtree) //结点为根
	{
		return NULL;
	}
	if (pNode == pbtree->pLeft || pNode == pbtree->pRight) //为根的左孩子或者右孩子
	{
		return pbtree;
	}
	if (parent = GetNodeParent(pbtree->pLeft, pNode)) //以根的左孩子为根结点
	{
		return parent;
	}
	if (parent = GetNodeParent(pbtree->pRight, pNode)) //以根的右孩子为根结点
	{
		return parent; //可以直接返回此次调用的返回值
		//return GetNodeParent(pbtree->pRight, pNode);
	}
	return NULL;
}
//求二叉树的镜像
void Swap(pBTNode* pLeft, pBTNode* pRight)
{
	assert(pLeft && pRight);
	pBTNode tmp = NULL;
	tmp = *pLeft;
	*pLeft = *pRight;
	*pRight = tmp;
}
//递归
void MirrorBinTree(pBTNode* pbtree) //pbtree只是根结点，但没有改变根结点
{
	if (NULL != *pbtree)
	{
		Swap(&((*pbtree)->pLeft), &((*pbtree)->pRight));//交换
		MirrorBinTree(&((*pbtree)->pLeft));
		MirrorBinTree(&((*pbtree)->pRight));
	}
}
//非递归
void MirrorBinTreeNor(pBTNode* pbtree)
{
	if (NULL == *pbtree)
	{
		return;
	}
	Queue queue;
	QueueInit(&queue);//初始化
	QueuePush(&queue, (int)(*pbtree));//根节点入队列
	while (!QueueEmpty(&queue))//判断队列是否为空  空返回1
	{
		//压入队列一个地址，保存在data中，取时，直接取的化是第一个结点的地址，而非data中保存的值
		pQListNode cur = QueueFront(&queue);//获取队头元素
		pBTNode btnode = (pBTNode)(cur->_data);
		Swap(&(btnode->pLeft), &(btnode->pRight));//交换
		if (btnode->pLeft)
		{
			QueuePush(&queue, (int)(btnode->pLeft));//左孩子入队列
		}
		if (btnode->pRight)
		{
			QueuePush(&queue, (int)(btnode->pRight));//右孩子入队列
		}
		QueuePop(&queue);//头删
	}
}
//二叉树的层序遍历
void LevelOrder(pBTNode pbtree)
{
	if (NULL == pbtree)
	{
		return;
	}
	Queue queue;
	QueueInit(&queue);//初始化
	QueuePush(&queue, (int)pbtree);//根节点入队列
	while (!QueueEmpty(&queue))//判断队列是否为空  空返回1
	{
		//压入队列一个地址，保存在data中，取时，直接取的化是第一个结点的地址，而非data中保存的值
		pQListNode cur = QueueFront(&queue);//获取队头元素
		pBTNode btnode = (pBTNode)(cur->_data);
		printf("%c", btnode->data);
		if (btnode->pLeft)
		{
			QueuePush(&queue, (int)(btnode->pLeft));//左孩子入队列
		}
		if (btnode->pRight)
		{
			QueuePush(&queue, (int)(btnode->pRight));//右孩子入队列
		}
		QueuePop(&queue);//头删
	}
}
//判断一棵二叉树是否为完全二叉树
int IsCompIeteBinTree(pBTNode pbtree)
{
	if (NULL == pbtree)
	{
		return 1;
	}
	int flag = 0;//标记
	Queue queue;
	QueueInit(&queue);//初始化
	QueuePush(&queue, (int)pbtree);//根节点入队列
	while (!QueueEmpty(&queue))//判断队列是否为空  空返回1
	{
		pQListNode cur = QueueFront(&queue);//获取队头元素
		pBTNode btnode = (pBTNode)(cur->_data);
		if (flag == 1) //找到倒数第一个不为叶子结点的结点
		{
			//之后的结点均不能有孩子
			if (NULL != btnode->pLeft || NULL != btnode->pRight)
			{
				return 0;
			}
		}
		else
		{
			if (btnode->pLeft && btnode->pRight) //左右孩子均存在
			{
				QueuePush(&queue, (int)(btnode->pLeft));//左孩子入队列
				QueuePush(&queue, (int)(btnode->pRight));//右孩子入队列
			}
			else if (btnode->pLeft && NULL == btnode->pRight) //左孩子存在右孩子不存在
			{
				QueuePush(&queue, (int)(btnode->pLeft));//左孩子入队列
				flag = 1;
			}
			else if (NULL == btnode->pLeft && btnode->pRight) //左孩子不存在右孩子存在
			{
				return 0;
			}
			else
			{
				flag = 1;
			}
		}
		QueuePop(&queue);//头删
	}
	return 1;
}

//判断一颗二叉树是否为平衡数
void BSTreeToDList(pBTNode pbtree, pBTNode *prev)	//prev: 标记最近修改过的结点
{
	if (NULL == pbtree)
	{
		return;
	}
	BSTreeToDList(pbtree->pLeft, prev);	//左子树
	//根
	pbtree->pLeft = *prev;
	if (NULL != (*prev))
		(*prev)->pRight = pbtree;
	*prev = pbtree;
	BSTreeToDList(pbtree->pRight, prev);
}
