#include <iostream>
#include <stack>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <string>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
void PrintLink(ListNode *Link, int num)
{
    ListNode *p = Link;
    int i = 0;
    printf("--------link data---------\n");
    while(p != NULL)
    {
        printf("%d  ",p->val);
        p = p->next;
        i++;
        if(i == num)
            break;
    }
    printf("\n");
    printf("--------link data---------\n");
}
ListNode* InitLink(int add, int num)
{
    if(num < 1)
        return NULL;
    ListNode *stLink ;
    int i = 1;
    ListNode *tempNode = ( ListNode *)malloc(sizeof( ListNode));
    tempNode->val = i*add+i;
    tempNode->next = NULL;
    stLink = tempNode;
    //stLink->next = NULL;
    
    
    for(i = 2; i < num+1; ++i)
    {
        ListNode *newNode;
        newNode = ( ListNode *)malloc(sizeof( ListNode));
        newNode->val = i*add + i;
        tempNode->next = newNode;
        tempNode = tempNode->next;
    }
    tempNode->next = NULL;
    return stLink;
}
ListNode* CreateCircleLink(int add, int num)
{
    ListNode *stLink ;
    int i = 1;
    ListNode *tempNode = (ListNode *)malloc(sizeof( ListNode));
    tempNode->val = i*add+i;
    tempNode->next = NULL;
    stLink = tempNode;
    //stLink->next = NULL;
    
    
    for(i = 2; i < num+1; ++i)
    {
        ListNode *newNode;
        newNode = ( ListNode *)malloc(sizeof( ListNode));
        newNode->val = i*add + i;
        tempNode->next = newNode;
        tempNode = tempNode->next;
    }
    tempNode->next = stLink;
    return stLink;
}
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {

        if(NULL == pHead1)
        {
            return pHead2;
        }
        if(NULL == pHead2)
        {
            return pHead1;
        }
        
        //pHead1 = pHead1->next;
        //pHead2 = pHead2->next;
        //用于返回的链表
        ListNode *resLink = NULL;
        
        if(pHead1->val < pHead2->val)
        {
            resLink = pHead1;
            //resLink->next = NULL;
            pHead1 = pHead1->next;
        }
        else{
            resLink = pHead2;
            //resLink->next = NULL;
            pHead2 = pHead2->next;
        }
        //用于处理数据的暂时链表
        ListNode *tempLink;
        tempLink = resLink;
        //pHead1 = pHead1->next;
        //pHead2 = pHead2->next;
        while(pHead1!= NULL && pHead2!= NULL)
        {
            if((pHead1->val) > (pHead2->val))
            {
                tempLink->next = pHead2;
                pHead2 = pHead2->next;
                tempLink = tempLink->next;
                tempLink->next = NULL;
            }
            else{
                tempLink->next = pHead1;
                pHead1 = pHead1->next;
                tempLink = tempLink->next;
                tempLink->next = NULL;
            }
                        
        }
        
        if(pHead1 != NULL)
        {
            tempLink->next = pHead1;
            //break;
        }
        else
        {
            tempLink->next = pHead2;
            //break;
        }
        //printf("OK\n");
        return resLink;
    }
    
    ListNode* MergeRecursion(ListNode* pHead1, ListNode* pHead2)
    {

        if(NULL == pHead1)
        {
            return pHead2;
        }
        if(NULL == pHead2)
        {
            return pHead1;
        }
     
        //合并后的链表
        ListNode *resLink = NULL;
        
        if(pHead1->val < pHead2->val)
        {
            resLink = pHead1;
            resLink->next = MergeRecursion(pHead1->next, pHead2);
        }
        else{
            resLink = pHead2;
            resLink->next = MergeRecursion(pHead1, pHead2->next);
        }
       
        return resLink;
    }
    
};


void testMergeLink()
{
    ListNode *pHead1 = InitLink(1,5);
    PrintLink(pHead1,5);
    ListNode *pHead2 = InitLink(2,5);
    PrintLink(pHead2,5);
    ListNode *Res;
    Solution s;
    Res = s.MergeRecursion(pHead1, pHead2);
    printf("merge...\n");
    PrintLink(Res,10);
}
void judgeCircleInLink(ListNode *head)
{
    ListNode* pFast = head;
    ListNode* pSlow = head;
    while((pFast != NULL)&&(pFast->next != NULL))
    {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
        
        if(pFast == pSlow)
        {
            printf("circle exist\n");
            return;
        }
    }
    printf("no circle\n");
}

bool IsIntersected(ListNode*pHead1, ListNode*pHead2)
{
    ListNode * pa = pHead1;
    ListNode* pb = pHead2;
    
    while(pa->next != NULL)
        pa = pa->next;
    while(pb->next != NULL)
        pb = pb->next;
    if(pa == pb)
        printf("They are intersected\n");
    return pa == pb;
}
void GetFirstNodeIntersected(ListNode*pHead1, ListNode*pHead2)
{
    ListNode * pa = pHead1;
    ListNode* pb = pHead2;

    while(pa != NULL)
    {
        pb = pHead2;
        while(pb != NULL)
        {
            if(pa == pb)
            {
                printf("first intersected node : %d\n", pa->val);
                return;
            }
            pb = pb->next;
        }
        pa = pa->next;
    }
}

void GetFirstNodeInCircle(ListNode *pHead)
{
    ListNode* pFast  = pHead;
    ListNode* pSlow  = pHead;
    ListNode* pSecond = pHead;
    ListNode* pSecondTmp = pSecond;
    //检查是否有环，有环后就破环，然后形成两个新链表，求两个新链表的第一个相交点就是链表第一个进环的节点
    while(pFast != NULL && pFast->next != NULL)
    {
       pFast = pFast->next->next;
       pSlow = pSlow->next;
       
       if(pFast == pSlow)//确认有环，然后破环
       {
           pSecondTmp = pFast;
           pSecond = pFast->next;
           pSecondTmp->next = NULL;//破环
           GetFirstNodeIntersected(pHead, pSecond);//获取两个链表第一个相交的的节点，即第一个进环的节点
           return;
       }
    }        
}
void Delete(ListNode* pHead, ListNode* pNodeToDel)
{
    if(NULL == pHead||NULL == pNodeToDel)
        return;
    printf("====node to be del is %d\n====",pNodeToDel->val);
    if(pNodeToDel->next != NULL)
    {
        pNodeToDel->val = pNodeToDel->next->val;
        pNodeToDel->next = pNodeToDel->next->next;
        delete pNodeToDel->next;
    }
    else{
        delete pNodeToDel;
        //pNodeToDel = NULL;
    }
}

void testCircleLink()
{
    ListNode *pHead1 = CreateCircleLink(2,100);
    PrintLink(pHead1, 2);
    ListNode *pHead2 = InitLink(5,2);
    //PrintLink(pHead2, 1);
    pHead2->next->next = pHead1;
    //judgeCircleInLink(pHead1);
    //judgeCircleInLink(pHead2);
    PrintLink(pHead2, 4);
    GetFirstNodeInCircle(pHead2);
}
void testIntersected()
{
    ListNode *pHead1 = InitLink(1,1);
    ListNode *pHead2 = InitLink(2,3);
    PrintLink(pHead2, 3);
    pHead1->next = pHead2->next;
    PrintLink(pHead1, 1);
    IsIntersected(pHead1, pHead2);
    GetFirstNodeIntersected(pHead1, pHead2);
}

void testDelNode()
{
     ListNode *pHead = InitLink(2,3);
     PrintLink(pHead, 3);
     Delete(pHead, pHead->next->next->next);
     PrintLink(pHead, 3);
}

ListNode *RGetKthNode(ListNode*pHead, unsigned int k)
{
    if(k == 0 || pHead == NULL)
        return NULL;
    ListNode *pAhead = pHead;
    ListNode *pRes   = pHead;
    int count = 0;
    while(pAhead != NULL)
    {
        count++;
        pAhead = pAhead->next;
    }
    if(k > count)
    {
        return NULL;
    }
  
    int pos = count - k;
    int i = 0;
    while(pRes != NULL)
    {
        if(i == pos)
            return pRes;
        i++;
        pRes = pRes->next;
    }
}

void testRGetKthNode()
{
    ListNode *pHead = InitLink(2,30);
    PrintLink(pHead,5);
    ListNode *pNode = NULL;
    pNode = RGetKthNode(pHead,30);
    printf("pNode is %d\n", pNode->val);
}

ListNode *getMiddleNode(ListNode* pHead)
{
    if(pHead == NULL)
        return NULL;
    ListNode *pStart = pHead;
    ListNode *pRes = pHead;
    int count = 0;
    while(pStart != NULL)
    {
        count++;
        pStart = pStart->next;
    }
    int num = count/2 + count%2;
    int i = 1;
    while(pRes != NULL)
    {
        if(i == num)
            return pRes;
        i++;
        pRes = pRes->next;
    }
}
void testGetMiddleNode()
{
    ListNode *pHead = InitLink(2,4);
    PrintLink(pHead,5);
    ListNode *pNode = NULL;
    pNode = getMiddleNode(pHead);
    printf("getMiddleNode : %d\n", pNode->val);
}
void RPrintList(ListNode *pHead)
{
    stack<ListNode *> s;
    ListNode *pNode = pHead;
    while(pNode != NULL)
    {
        s.push(pNode);
        pNode = pNode->next;
    }
    while(!s.empty())
    {
        pNode = s.top();
        printf("%d  ",pNode->val);
        s.pop();
    }
    printf("\n");
}
void testRPrintList()
{
    ListNode *pHead = InitLink(2,4);
    PrintLink(pHead,5);
    RPrintList(pHead);
}

class Zipper {
public:
    string zipString(string iniString) {
        // write code here
        string res;
        //use for transfer from int to string
        char Temp[100];
        int i = 0;
        int pos = 0;
        //遍历指针
        string::iterator iter = iniString.begin();
        
        while(iter != iniString.end())
        {
            memset(&Temp, 0, sizeof(Temp));
            //
            if(*iter == *(iter+1))
            {
                //find the char not equal to *iter from i
                pos = iniString.find_first_not_of(*iter, i);
                if(pos < 0)
                {
                    string newStr;
                    newStr.append(iter, iniString.end());
                    sprintf(Temp, "%d", newStr.size());
                    res.append(iniString,i,1);
                    res.append(Temp);
                    break;
                }
                res.append(iniString, i,1);
                sprintf(Temp, "%d", pos-i);
                res.append(Temp);
                iter = iniString.begin()+pos;
                i = pos;
            }
            else{
                res.append(iniString, i,1);
                sprintf(Temp,"%d", 1);
                res.append(Temp);
                iter++;
                i++;
            }
        }
        //cout<<"After zipString "<<res<<endl;
        //
        if(res.size()>= iniString.size())
        {
            return iniString;
        }
        return res;
    }
};
void testZipper()
{
    string initString("abc");
    Zipper z;
    string s = z.zipString(initString);
    cout << "s = "<<s<<endl;
}
class Different {
public:
    bool checkDifferent(string iniString) {
        // write code here
        string::iterator iter = iniString.begin();
        int pos = 0;
        int i = 1;
        while(iter != iniString.end())
        {
            pos = iniString.find_first_of(*iter,i);
            if(pos >= 0)
                return false;
            i++;
            iter++;
        }
        return true; 
    }
};
void testDifferent()
{
    Different d;
    string testStr("heloo");
    if(d.checkDifferent(testStr))
    {
        cout<<"no same"<<endl;
    }
    else{
        cout<<"same"<<endl;
    }
}

class Reverse {
public:
    string reverseString(string iniString) {
        // write code here
        string res;
        int len = iniString.length();
        int i = 0;
        int j = len;
        while(i < len)
        {
            res = iniString[i] + res;
            i++;
        }

        return res;
    }
};

void testReverse()
{
    string s("hello");
    Reverse r;
    cout<<r.reverseString(s)<<endl;
}

class A
{
    public:
         virtual void f() {cout << "A::f()"<<endl;}
         virtual void g() {cout << "A::g()"<<endl;}
};
class B: public A{
    public:
    void f() {cout << "B::f()"<<endl;}
    void g() {cout << "B::g()"<<endl;}
};
void testVirtualTable()
{
   void(*fun)(A*);
   A *p = new B;
   p->g();
   long lVptrAddr;
   memcpy(&lVptrAddr, p, sizeof(p));
   cout<<reinterpret_cast<long*>(lVptrAddr)<<endl;
   memcpy(&fun, reinterpret_cast<long*>(lVptrAddr),sizeof(p));
   fun(p);
   //B *b = new A; 
   delete p;

}
class Same {
public:
    bool checkSam2(string stringA, string stringB) {
        // write code here
        if(stringA.length() != stringB.length())
            return false;
        int posA = 0;
        int posB = 0;
        int i = 0;
        
        while(true)
        {
            posA = stringA.find_first_of(' ',i);
            if(posA < 0)
            {
                string subStr = stringA.substr(i, stringA.length()-i);
                posB = stringB.find(subStr);
                if(posB < 0)
                    return false;
                break;
            }
            string subStr = stringA.substr(i,posA-i);
            posB = stringB.find(subStr);
            if(posB < 0)
            {
                return false;
            }
            else{
                i = stringA.find_first_not_of(' ',posA);
                if(i < 0)
                    break;
            }

        }
        return true;
    }
    //统计stringA中每个字符出现的次数，然后与stringB中该字符对应的次数进行对比，如果都相等返回true,否则返回false
    bool checkSam(string stringA, string stringB) {
        // write code here
        if(stringA.length() != stringB.length())
            return false;
        int len = stringA.length();
        int i = 0;
        int iA = 0;
        int iB = 0;
        char c;
        int countA = 0;
        int countB = 0;
        while(i < len)
        {
            c = stringA[i];
            iA = 0;
            countA = 0;
            countB = 0;
            iB = 0;
            while(iA < len)
            {
                if(c == stringA[iA])
                {
                    countA++;
                }
                ++iA;
            }
            
            while(iB < len)
            {
                if(c == stringB[iB])
                {
                    countB++;
                }
                ++iB;
            }
            if(countB != countA)
            {
                return false;
            }
            ++i;
        }
        return true;
    }
};

void testSame()
{
    string s1("Heh|");
    string s2("he|H");
    Same s;
    
    if(s.checkSam(s1, s2))
    {
        cout<<"same"<<endl;
    }
    else{
        cout<<"different"<<endl;
    }
}
class Solution2 {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() == 0)
            return 0;
        vector<int>::iterator iter = rotateArray.begin();
        int min = 0;
        min = *iter;
        while(iter != rotateArray.end())
        {
            if(min > *iter)
            {
                //cout<<min<<endl;
                min = *iter;
            }
            ++iter;
            
        }
        //cout<<min<<endl;
        return min;
    }
};
void testminNumberInRotateArray()
{
    Solution2 s;
    vector<int> rotateArray;
    
    rotateArray.push_back(3);
    rotateArray.push_back(4);
    rotateArray.push_back(5);
    rotateArray.push_back(2);
    cout<<"min = "<<s.minNumberInRotateArray(rotateArray)<<endl;
}
ListNode* LinkReverse(ListNode *pHead)
{
	if(NULL == pHead|| NULL == pHead->next)
		return pHead;
	//ListNode *pRes = pHead;
	ListNode *pCur = pHead;
	ListNode *pTemp;
	while(pCur != NULL)
	{
		//往下试探，指针是通过链表的位置变化而移动的
		//
		if(pCur->next != NULL)
		{
			pTemp = pCur->next;
			pCur->next = pCur->next->next;
			pTemp->next = pHead;
			pHead = pTemp;
		}
		else
		{
			break;
		}
		
		//pCur = pCur->next;
	}
	return pHead;
	
}
/*
+--------+
|node01  |
+--------+
*/
//在新的节点pRes构建反转链表，遍历pHead,每遍历一个节点把它插在pRes节点的前面，依次排列实现反转
ListNode * LinkReverse2(ListNode *pHead)
{
	if(NULL == pHead|| NULL == pHead->next)
		return pHead;
	ListNode *pRes = NULL;
	ListNode *pTemp;
	ListNode *pCur = pHead;
	
	while(pCur != NULL)
	{
		pTemp = pCur;
		pCur = pCur->next;//先让pCur指针指向下一个位置，再做插入，不然会出错
		pTemp->next = pRes;
		pRes = pTemp;
	}
	
	return pRes;
}
void testLinkReverse()
{
    ListNode *pHead = InitLink(2,10);
	PrintLink(pHead,10);
	ListNode *pRes = LinkReverse2(pHead);
	PrintLink(pRes,10);
}

class Bonus {
public:
    int getMost(vector<vector<int> > board) {
        // write code here
		int boardXsize = board.size();
		int boardYsize = board[0].size();
		int boardX = 0;
		int boardY = 0;
		int giftValue = 0;
		giftValue =  board[0][0];
		while(!(boardX == boardXsize&&boardY == boardYsize))
		{
			
			if(boardX <= boardXsize)
			{
				boardX++;
				giftValue += board[boardX][boardY];
			}
			if(boardY <= boardYsize)
			{
				boardY++;
				giftValue += board[boardX][boardY];
			}
			
		}
		return 0;
    }
};

class Balls {
public:
    int calcDistance(int A, int B, int C, int D) {
        // write code here
		int sum = 3*(A + B + C + D);
		return sum;
    }
};

class Apples {
public:
    int getInitial(int n) {
        // write code here
		int numOfApples = n + 1;
		int numRecord;
		int averageApples = 0;
		int bearCount = n;
		while(1)
		{
			numRecord = numOfApples; 
			while(bearCout > 0)
			{
				if(numOfApples/n == 1)
				{
					numOfApples = numOfApples - numOfApples/n -1;
					bearCount--;
				}
				else{
					break;
				}
			}
			if(bear == 0)
			{
				return numRecord;
			}
			numOfApples++;
		}
    }
};

int main()
{
   //testLinkReverse();
   int a = 2/3;
   cout <<a <<endl;
   return 0;
}