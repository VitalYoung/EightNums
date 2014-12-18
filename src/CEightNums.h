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
	CQueue(){ Last = First = NULL; }	//���캯��
	//int Getlen()const{ return Length; }			//�������Ա���
	bool  isEmpty(){
		if (First == NULL)
		{
			return true;
		}
		return false;
	}
	Type *ExitQueue();								//������
	int EnterQueue(const Type& T);					//������
	void ReserveQueue();							//���з�ת
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


static int MHT[NUM][NUM] = {//manhattan�����
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
static int detal[4] = { -1, -3, 1, 3 };//0�ƶ��� λ�õı仯detal[i] i-0 ���ƣ�i-1 �ϣ�i-2 �� i-3 ��
class CStateNode
{
public:
	int f, g, h;				//���ۺ���
	int state[NUM];				//״̬
	int state_p[NUM];			//��״̬�и�������λ�ã�state_p[5]=7 5����λ��Ϊ7
	static int target_p[NUM];	//Ŀ��״̬�и�������λ��
	int zero_p;					//zero_p 0��λ��

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

	CQueue<CStateNode>* CreateResultQueue();		//��������·�� �������
	bool Expend(int i);								//A*�㷨��״̬��չ����
	int Calcuf();									//�������
	void InsertQueue(CQueue<CStateNode> &Q);		//����g��С������
	CStateNode* isRepeat(CQueue<CStateNode> &Q);	//������Ƿ��ظ�
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
	int target[NUM];		//Ŀ��״̬
	int source[NUM];		//��ʼ״̬
};

