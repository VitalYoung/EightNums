#include<iostream>
#include<time.h>
#define NUM 9

using namespace std;

template<class Type> class CQueue
{
private:
	Type *First, *Last;
	//int Length;
public:
	CQueue(){ Last = First = NULL; }	//构造函数
	//int Getlen()const{ return Length; }			//返回线性表长度
	bool  isEmpty(){
		if (First == NULL)
		{
			return true;
		}
		return false;
	}
	Type *ExitQueue();								//出队列
	int EnterQueue(const Type& T);					//进队列
	void ReserveQueue();							//队列反转
	Type *GetFirst(){
		return First;
	}
	void SetFirst(Type *p){
		First = p;
	}
	Type *GetLast(){
		return Last;
	}
	void SetLast(Type* p){
		Last = p;
	}
};


static int MHT[NUM][NUM] = {//manhattan距离表
	{ 0, 1, 2, 1, 2, 3, 2, 3, 4 },
	{ 1, 0, 1, 2, 1, 2, 3, 2, 3 },
	{ 2, 1, 0, 3, 2, 1, 4, 3, 2 },
	{ 1, 2, 3, 0, 1, 2, 1, 2, 3 },
	{ 2, 1, 2, 1, 0, 1, 2, 1, 2 },
	{ 3, 2, 1, 2, 1, 0, 3, 2, 1 },
	{ 2, 3, 4, 1, 2, 3, 0, 1, 2 },
	{ 3, 2, 3, 2, 1, 2, 1, 0, 1 },
	{ 4, 3, 2, 3, 2, 1, 2, 1, 0 },
};
static int detal[4] = { -1, -3, 1, 3 };//0移动后 位置的变化detal[i] i-0 左移，i-1 上，i-2 右 i-3 下
class CStateNode
{
public:
	int f, g, h;				//估价函数
	int state[NUM];				//状态
	int state_p[NUM];			//此状态中各个数字位置，state_p[5]=7 5所在位置为7
	static int target_p[NUM];	//目标状态中各个数字位置
	int zero_p;					//zero_p 0的位置

	CStateNode *Parent;
	CStateNode *Next;
	CStateNode *Pre;

	CStateNode();
	CStateNode(const CStateNode& T);
	CStateNode(int source[NUM], int target[NUM]);
	bool operator==(const CStateNode &T);
	CStateNode& operator=(const CStateNode &T);
	CQueue<CStateNode>& Search();
	~CStateNode();

	CQueue<CStateNode>* CreateResultQueue();		//根据搜索路径 导出结果
	bool Expend(int i);								//A*算法的状态扩展函数
	int Calcuf();									//计算估价
	void InsertQueue(CQueue<CStateNode> &Q);		//根据g大小插入结点
	CStateNode* isRepeat(CQueue<CStateNode> &Q);	//检查结点是否重复
};


class CEightNums
{
public:
	CEightNums();
	//CEightNums(CEightNums &T);
	CEightNums(int s[NUM], int t[NUM]);
	bool isCanSolved();
	void random();
	void SetTarget(int t[]);
	void SetSource(int s[]);
	void GetSource(int s[]);
	CQueue<CStateNode>* Search();
	~CEightNums();

private:
	int target[NUM];		//目标状态
	int source[NUM];		//起始状态
};

