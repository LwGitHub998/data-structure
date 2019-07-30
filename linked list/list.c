//链表
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Node //一般链表
{
	DataType data;
	struct Node* next;
}Node, *pNode, List, *pList;

void InitLinkList(pList* pplist)//初始化
{
	if (*pplist != NULL)
	{
		*pplist = NULL;
	}
}
pNode LBuyNode(DataType d)//创建一个新节点
{
	pNode plist =(pNode)malloc(sizeof(Node));
	if (NULL == plist)
	{
		assert(0);
	}
	plist->data = d;
	plist->next = NULL;
	return plist;
}
void PrintLinkList(pList plist)//打印
{
	pList cur = plist;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
void DestroyLinkList(pList* pplist)//销毁
{
	assert(pplist);
	//让头指针指向第二个，释放第一个 从头释放

	while (*pplist != NULL)
	{
		pList cur = *pplist;
		*pplist = (*pplist)->next;
		free(cur);
		cur = NULL;
	}
}
void PushBack(pList* pplist, DataType d)//尾插
{
	assert(pplist);
	pNode plist = LBuyNode(d);

	if (*pplist == NULL)//第一个节点
	{
		*pplist = plist;
	}
	else//不是第一个节点
	{
		pList cur = *pplist;
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = plist;
	}
}
void PopBack(pList* pplist)//尾删
{
	assert(pplist);
	if(*pplist == NULL)//无节点
	{
		return;
	}
	else if ((*pplist)->next == NULL)//一个节点
	{
		free(*pplist);
		*pplist = NULL;
	}
	else//多个节点
	{
		pList cur = *pplist;
		while (cur->next->next != NULL)
		{
			cur = cur->next;
		}
		free(cur->next);
		cur->next = NULL;
	}
}
void PushFront(pList* pplist, DataType d)//头插
{
	assert(pplist);
	pNode plist = LBuyNode(d);
	plist->next = *pplist;
	*pplist = plist;
}
void PopFront(pList* pplist)//头删
{
	assert(pplist);
	pList cur = *pplist;
	*pplist = (*pplist)->next;
	free(cur);
	cur = NULL;
}
pNode Find(pList plist, DataType d)//查找
{
	assert(plist);
	pList cur = plist;
	while (cur != NULL)
	{
		if (cur->data == d)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
void Insert(pList* pplist, pNode pos, DataType d)//在指定位置之前插入一个值
{
	assert(pplist&&pos&&*pplist);
	pNode plist = LBuyNode(d); //创建新结点
	pList cur = *pplist;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	plist->next = cur->next;
	cur->next = plist;
}
void Erase(pList* pplist, pNode pos)//删除指定位置元素
{
	assert(pplist&&pos);
	if (*pplist == NULL)
	{
		return;
	}
	else if ((*pplist) == pos)
	{
		*pplist = (*pplist)->next;
	}
	else
	{
		pList cur = *pplist;
		while (cur &&cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = cur->next->next;
		free(pos);
		pos = NULL;
	}
}
void Remove(pList* pplist, DataType d)//删除指定元素
{
	assert(pplist);
	if (*pplist == NULL)//无节点
	{
		return;
	}
	else if ((*pplist)->data == d)//第一个节点
	{
		pList cur = *pplist;
		*pplist = (*pplist)->next;
		free(cur);
		cur = NULL;
	}
	else
	{
		pList cur = *pplist;
		while (cur->next && cur->next->data != d)
		{
			cur = cur->next;
		}
		if (cur->next != NULL)
		{
			pList del = cur->next;
			cur ->next= cur->next->next;
			free(del);
			del = NULL;
		}
	}
}
void RemoveAll(pList* pplist, DataType d)//删除指定的所有元素
{
	assert(pplist);
	if (*pplist == NULL)//无节点
	{
		return;
	}
	
	pList cur = *pplist;
	pList sen = NULL;
	while (cur)
	{
		if (cur->data == d)
		{
			if ((*pplist)==cur)//第一个节点
			{
				pList del = *pplist;
				*pplist = (*pplist)->next;
				cur = *pplist;
				free(del);
				del = NULL;
			}
			else
			{
				sen->next = cur->next;
				free(cur);
				cur= sen->next;
			}
		}
		else
		{
			sen = cur;
			cur = cur->next;
		}
		
	}	
}

//链表面试题

//1.从尾到头打印单链表
void PrintTailToHead(pList plist)//逆序打印单项链表 
{
	//递归
	//从最后一个开始打印，直到第一个
	//if (plist != NULL)
	//{
	//	PrintTailToHead(plist->next);
	//	printf("%d->", plist->data);
	//}

	//非递归
	//创建一个尾指针，每次遍历字符串，打印尾指针所指向结点的前一个，直到打印完
	pList Tail = NULL;  //尾指针
	while (plist != Tail)
	{
		pList cur = plist;
		while (cur->next != Tail)
		{
			cur = cur->next;
		}
		printf("%d->", cur->data);
		Tail = cur;
	}
}

//2.删除一个无头单链表的非尾结点
//复制非尾结点下一个结点的数据到非尾结点，删除下一个结点
void EraseNotTailNode(pNode pos)//删除非尾节点
{
	//把下一个复制过来，删除下一个
	assert(pos);
	pos->data = pos->next->data;
	pList del = pos->next;
	pos->next = pos->next->next;
	free(del);
	del = NULL;
}

//3.在无头单链表的一个结点前插入一个结点(不能遍历链表)
void InsertNonTailNode(pNode pos, DataType d)
{

	//在这个之后插入一个相同的，改变这一个
	assert(pos);
	pNode plist = LBuyNode(pos->data);
	plist->next = pos->next;
	pos->next = plist;
	pos->data = d;
}

//4.单链表实现约瑟夫环

//单链表成环
void LinkListFormRing(pList * pplist)
{
	//让尾节点指向头结点
	assert(pplist);
	pList cur = *pplist;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = *pplist;
}

//单链表实现约瑟夫环
pNode LinkListToJoseph(pList * pplist)
{
	assert(pplist);
	int N = 2; //报数
	//1.先将链表变成环
	LinkListFormRing(pplist);
	//2.编号为1的人开始报数，删除数到N的结点
	pList cur = *pplist;
	while (cur != cur->next)
	{
		//报数
		for (int i = 1; i < N; i++)
		{
			cur = cur->next;
		}
		//删除
		cur->data = cur->next->data;//把下一个的值赋给这一个
		pList del = cur->next;//保存下一个
		cur->next = cur->next->next;//指向下一个的下一个
		free(del);
		del = NULL;
	}
	//4.直到只剩下一个结点(结点自己指向自己),返回
	return cur;
}

//5.逆置单链表
//创建一个新链表，将原链表按顺序头插入新链表
void InverseBuyLinkList(pList * pplist)
{
	assert(pplist);
	pList p = NULL;
	pList cur = *pplist;
	while (NULL != cur)
	{
		pNode plist = LBuyNode(cur->data);//创建新结点

		//头插
		plist->next = p;
		p = plist;
		cur = cur->next;
	}
	//把新创建的链表赋给原链表
	pList del = *pplist;
	*pplist = p;
	p = NULL;
	DestroyLinkList(&del);//销毁原链表
}

//6.单链表排序(冒泡排序升序)
void SortLinkList(pList * pplist)
{
	assert(pplist && *pplist); //头指针及第一个结点不能为空
	pList tail = NULL;//尾指针
	while ((*pplist) != tail ) //头指针==尾指针
	{
		pList str1 = *pplist;//第一个结点
		pList str2 = (*pplist)->next;//第二个结点
		while (str2 != tail) // 升序:按从小到大的顺序排列  降序:就是按从大到小的顺序排列
		{
			//比较
			if (str1->data > str2->data)
			{
				//交换
				int tmp = str1->data;
				str1->data = str2->data;
				str2->data = tmp;
			}
			str1 = str2;
			str2 = str2->next;
		}
		//尾指针向前移动
		tail = str1;
	}
}

//7.查找单链表的中间结点，要求只遍历一次
pNode FindLinkListMidNode(pList plist)
{
	assert(plist);
	pList str1 = plist;//快指针
	pList str2 = plist;//慢指针
	while (NULL != str1 && NULL != str1->next) //结点奇数或为偶数时条件不同
	{
		str1 = str1->next->next;
		str2 = str2->next;
	}
	return str2;
}

//8.查找单链表的倒数第k个结点，要求只遍历一次
pNode FindLinkListK(pList plist, DataType k)
{
	assert(plist);
	pList str1 = plist;//快指针
	pList str2 = plist;//慢指针
	for (int i = 0; i < k; i++) //k-1
	{
		str1 = str1->next;
	}
	while (NULL != str1)//str->next != NULL
	{
		str1 = str1->next;
		str2 = str2->next;
	}
	return str2;
}

//9.删除链表的倒树第k个结点
void DeleteLinkListK(pList * pplist, DataType k)
{
	assert(pplist && *pplist);
	pList str = FindLinkListK(*pplist, k);//查找倒数第k个结点
	//删除倒数第k个结点,防止其是尾结点
	if (str == *pplist)//str是第一个结点
	{
		pList del = *pplist;
		*pplist = (*pplist)->next;
		free(del);
		del = NULL;
	}
	else
	{
		pList cur = *pplist;
		while (cur->next != str)
		{
			cur = cur->next;
		}
		cur->next = cur->next->next;
		free(str);
		str = NULL;
	}
}

//10.判断链表是否带环,若带环，求环长度，求环入口点
pList LinkListRing(pList plist) //判断链表是否带环
{
	assert(plist);
	pList str1 = plist;//快指针
	pList str2 = plist;//慢指针
	while (NULL != str1)
	{
		str1 = str1->next->next;
		str2 = str2->next;
		if (str1 == str2) //两个指针相遇
		{
			return str1;
		}
	}
	return NULL;
}
//返回结点个数：相遇点，慢指针再相遇点不动，快指针走并计数，直到再次相遇时返回
int LinkListRingLength(pList plist, pList cur)//求链表环长度
{
	assert(plist && cur);
	pList str1 = cur->next;//快指针
	int count = 0;
	while (str1 != cur)
	{
		str1 = str1->next;
		count++;
	}
	return count + 1; //加上相遇点
}
//入口点：一个指针在起始位置，一个指针在相遇点，两指针同时走，相遇时，即为环起始点
pList LinkListRingEntrance(pList plist, pList cur)//求链表环入口点
{
	pList str1 = plist;//快指针
	while (str1 != cur)//两指针没相遇
	{
		str1 = str1->next;
		cur = cur->next;
	}
	
	return str1;//两指针相遇返回
}

//11.判断两个链表是否相交，若相交，求交点
int LinkListIntersect(pList plist1, pList plist2)//判断两个链表是否相交
{
	assert(plist1 && plist2);
	while (NULL != plist1->next) //找到最后一个结点
	{
		plist1 = plist1->next;
	}
	while (NULL != plist2->next) //找到最后一个结点
	{
		plist2 = plist2->next;
	}
	if (plist1 == plist2)
	{
		return 1;
	}
	return 0;
}
//交点：求两个链表长度，长的走两个链表之差，再两个同时走
pList LinkListIntersection(pList plist1, pList plist2)//求两个链表交点
{
	assert(plist1 && plist2);
	int count1 = 0;
	int count2 = 0;
	pList cur1 = plist1;
	pList cur2 = plist2;
	while (NULL != cur1) //求链表1的长度
	{
		cur1 = cur1->next;
		count1++;
	}
	while (NULL != cur2) //求链表2的长度
	{
		cur2 = cur2->next;
		count2++;
	}
	cur1 = plist1;
	cur2 = plist2;
	if (count1 > count2)//长的走两链表个数之差
	{
		for (int i = 0; i < count1 - count2; i++)
		{
			cur1 = cur1->next;
		}
	}
	else
	{
		for (int i = 0; i < count2 - count1; i++)
		{
			cur2 = cur2->next;
		}
	}
	while (cur1 != cur2)//两个同时走
	{
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}


//链表可能带环
//相交(两个链表均带环,交点在环外)
pList LinkListRingIntersect(pList plist1, pList plist2)
{
	//判断链表1，2是否带环
	pList cur1 = LinkListRing(plist1);//返回交点
	pList cur2 = LinkListRing(plist2);
	if (cur1 && cur2)//都带环
	{
		//求环入口点
		pList str1 = LinkListRingEntrance(plist1, cur1);//返回入口点
		pList str2 = LinkListRingEntrance(plist2, cur2);
		//判断入口点是否相等
		if (str1 == str2) //相等，相交，交点在环外,开头到入口点改造成Y形
		{
			str1->next = NULL;
			str2->next = NULL;
			//求两个链表交点
			return LinkListIntersection(plist1, plist2);
		}
		else //不相等，判断是否相交
		{
			//从入口点开始遍历链表1，看会不会遇到链表2的入口点
			pList str11 = str1->next;
			while (str11 != str1)
			{
				if (str11 == str2)
				{
					return str2;//交点在环上
				}
				str11 = str11->next;
			}
			return NULL;
		}
	}
	else if (cur1 == NULL && cur1 == NULL)//不带环
	{
		if (LinkListIntersect(plist1, plist2))//判断两个链表是否相交
		{
			return LinkListIntersection(plist1, plist2);//交点
		}	
		return NULL;
	}
	else
	{
		return NULL;
	}
}

//12.复杂链表的复制
typedef struct CLNode //复杂链表
{
	DataType data;
	struct CLNode* next;
	struct CLNode* random; //随机域
}clNode, *clpNode, clList, *clpList;
clpNode CLBuyNode(DataType d)//创建一个新节点
{
	clpNode clplist = (clpNode)malloc(sizeof(clNode));
	if (NULL == clplist)
	{
		assert(0);
	}
	clplist->data = d;
	clplist->next = NULL;
	clplist->random = NULL;
	return clplist;
}
void CLPushBack(clpList* clpplist, DataType d)//复杂链表尾插
{
	clpNode clplist = CLBuyNode(d);

	if (NULL == *clpplist)//第一个结点
	{
		*clpplist = clplist;
	}
	else//不是第一个结点
	{
		clpList cur = *clpplist;
		while (NULL != cur->next)
		{
			cur = cur->next;
		}
		cur->next = clplist;
	}
}
clpList ComplexLinkListCopy(clpList* clpplist)//复杂链表的复制
{
	assert(clpplist);
	//在原链表的每个结点之后插入一个相等的新结点
	clpList cur = *clpplist;
	while (NULL != cur)
	{
		clpNode clplist = CLBuyNode(cur->data);
		clplist->next = cur->next;
		cur->next = clplist;
		cur = cur->next->next;
	}
	//给新结点的随机域赋值
	cur = *clpplist;//遍历原链表结点
	clpList str = NULL;//遍历新创建的结点
	while (NULL != cur)
	{
		str = cur->next;
		if (NULL == cur->random)//原结点的随机指针域为空，则新节点随机指针域为空 
		{
			str->random = NULL;
		}
		else//原结点的随机指针域不为空，则新节点随机指针域为原结点的随机指针域的next
		{
			str->random = cur->random->next;
		}
		cur = cur->next->next;//指向下下一个结点
	}
	//将新结点从原链表中摘除
	cur = *clpplist;
	str = cur->next;
	clpList ret = str;//返回新创建的链表
	while (NULL != cur)
	{
		cur->next = str->next;
		cur = str->next;
		if (NULL != cur)//防止指针越界访问
		{
			str->next = cur->next;
			str = cur->next;
		}
	}
	return ret;
}

//13.合并两个有序链表，合并成功后依然有序 
pList MergeList(pList plist1, pList plist2) //从小到大
{
	pList str1 = plist1;
	pList str2 = plist2;
	pList ret = NULL; //新链表
	pList tmp = NULL;
	while (str1 && str2)
	{
		if (str1->data > str2->data)
		{
			PushBack(&ret, str2->data);//尾插
			str2 = str2->next;
		}
		else
		{
			PushBack(&ret, str1->data);//尾插
			str1 = str1->next;
		}
	}
	while (str1)
	{
		PushBack(&ret, str1->data);//尾插
		str1 = str1->next;
	}
	while (str2)
	{
		PushBack(&ret, str2->data);//尾插
		str2 = str2->next;
	}
	return ret;
}
