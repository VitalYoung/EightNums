#include "CEightNums.h"

/*CQueueʵ��*/
template<class Type> Type* CQueue<Type>::ExitQueue()
{
	if (First == NULL)
		return NULL;
	Type *p = First;
	First = First->Next;
	
	if (First == NULL)
	{
		Last = NULL;
	}
	else
	{
		First->Pre = NULL;
	}

	return p;
}
template<class Type> int CQueue<Type>::EnterQueue(const Type& T)
{
	Type *enterState = new Type(T);
	if (First == NULL)
	{
		First = Last = enterState;
	}
	else
	{
		enterState->Next = NULL;
		enterState->Pre = Last;
		Last->Next = enterState;
		Last = Last->Next;
	}
	return 1;
}

template<class Type>void CQueue<Type>::ReserveQueue()
{
	if (First != NULL)
	{
		Type *p = First;
		Type *q = NULL;
		while (p != NULL)
		{
			q = p->Next;
			p->Next = p->Pre;
			p->Pre = q;
			p = q;
		}
		q = First;
		First = Last;
		Last = q;
	}
}
/*CStateNode ʵ��*/
int CStateNode::target_p[NUM];
CStateNode::CStateNode()
{
	f = g = h = 0;
	for (int i = 0; i < NUM; i++)
	{
		state[i] = i;
		state_p[i] = i;
	}
	zero_p = 0;
	Parent = Pre = Next = NULL;
}

CStateNode::CStateNode(const CStateNode &T)
{
	this->f = T.f;
	this->g = T.g;
	this->h = T.h;
	for (int i = 0; i < NUM; i++)
	{
		this->state[i] = T.state[i];
		this->state_p[i] = T.state_p[i];
	}
	this->zero_p = T.zero_p;
	this->Parent = T.Parent;
	this->Next = this->Pre = NULL;
}
CStateNode::~CStateNode()
{
}

CStateNode::CStateNode(int s[NUM], int t[NUM])
{
	for (int i = 0; i < NUM; i++)
	{
		state[i] = s[i];
		state_p[s[i]] = i;
		target_p[t[i]] = i;
	}
	zero_p = state_p[0];
	f = h = 0;
	g = -1;
}
bool CStateNode::operator==(const CStateNode &T)
{
	for (int i = 0; i < NUM; i++)
	{
		if (this->state[i] != T.state[i])
		{
			return false;
		}
	}
	return true;
}

CStateNode& CStateNode::operator=(const CStateNode &T)
{
	this->f = T.f;
	this->g = T.g;
	this->h = T.h;
	for (int i = 0; i < NUM; i++)
	{
		this->state[i] = T.state[i];
		this->state_p[i] = T.state_p[i];
	}
	this->zero_p = T.zero_p;
	this->Parent = T.Parent;
	return *this;
}

CQueue<CStateNode>* CStateNode::CreateResultQueue()
{
	CQueue<CStateNode> *resultQueue = new CQueue<CStateNode>;
	CStateNode *p = this;
	
	while (p != NULL)
	{
		resultQueue->EnterQueue(*p);
		p = p->Parent;
	}
	resultQueue->ReserveQueue();

	return resultQueue;
}

bool CStateNode::Expend(int i)//i-0 ���ƣ�i-1 �ϣ�i-2 �� i-3 ��
{
	if (i == 0 && zero_p % 3 == 0 || i == 1 && zero_p<3
		|| i == 2 && zero_p % 3 == 2 || i == 3 && zero_p>5)
	{
		return false;
	}
	else
	{
		int zero_p_t = zero_p;
		zero_p += detal[i];
		state[zero_p_t] = state[zero_p];
		state[zero_p] = 0;

		int t = state_p[state[state_p[0]]];
		state_p[state[state_p[0]]] = state_p[0];
		state_p[0] = t;
		return true;
	}
}

int CStateNode::Calcuf()
{
	h = 0;
	for (int i = 0; i < NUM; i++)
	{
		h += MHT[state_p[i]][target_p[i]];
	}
	g++;
	f = g + h;
	return f;
}
CStateNode* CStateNode::isRepeat(CQueue<CStateNode> &T)
{
	CStateNode *p = T.GetFirst();
	while (p != NULL)
	{
		if (*p == *this)
		{
			return p;
		}
		p = p->Next;
	}
	return NULL;
}

void CStateNode::InsertQueue(CQueue<CStateNode> &Q)
{
	CStateNode *p = Q.GetFirst();
	if (p == NULL)
	{
		Q.SetFirst(this);
		Q.SetLast(this);
		this->Next = this->Pre = NULL;
		return;
	}
	while (p != NULL)
	{
		if (this->f < p->f)
		{
			//����pǰ��
			if (p->Pre == NULL)
			{
				this->Next = p;
				p->Pre = this;
				this->Pre = NULL;
				Q.SetFirst(this);
			}
			else
			{
				p->Pre->Next = this;
				this->Pre = p->Pre;
				p->Pre = this;
				this->Next = p;
			}
			break;
		}
		p = p->Next;
	}
	//�������
	if (p == NULL)
	{
		p = Q.GetLast();
		p->Next = this;
		this->Pre = p;
		this->Next = NULL;
		Q.SetLast(this);
	}
}
/* CEightNums ʵ��*/
CEightNums::CEightNums()
{
	for (int i = 0; i < NUM; i++)
	{
		source[i] = i;
		target[i] = i;
	}
}

CEightNums::CEightNums(int s[NUM], int t[NUM])
{
	for (int i = 0; i < NUM; i++)
	{
		source[i] = s[i];
		target[i] = t[i];
	}
}
bool CEightNums::isCanSolved()
{
	int i, j;
	int count_source = 0, count_target = 0;
	for (i = 0; i<NUM; i++)
		for (j = 0; j<i; j++)
		{
			if (source[j]<source[i] && source[j] != 0)
				count_source++;
			if (target[j]<target[i] && target[j] != 0)
				count_target++;
		}
		if ((count_source + count_target) % 2 == 0)
		return true;
	else
		return false;
}

void CEightNums::random()
{
	srand((unsigned)time(NULL));
	for (int k = 0; k < NUM; k++)
	{
		bool Isexist = false;
		source[k] = rand() % 9;                //�������0-8����
		for (int l = 0; l < k; l++)     //�ж�ͼ���Ƿ��Ѿ����ڸ���
		{
			if (source[k] == source[l])              //�����������ڣ�������ʼ����һ��λ��
			{
				Isexist = true;
				break;
			}
		}
		if (Isexist)                       //�������Ѿ����ڣ������������һ��0-8����
		{
			k = k - 1;
			continue;
		}
	}
}

void CEightNums::SetTarget(int t[NUM])
{
	for (int i = 0; i < NUM; i++)
	{
		target[i] = t[i];
	}
}
void CEightNums::SetSource(int s[NUM])
{
	for (int i = 0; i < NUM; i++)
	{
		source[i] = s[i];
	}
}
void CEightNums::GetSource(int s[NUM])
{
	for (int i = 0; i < NUM; i++)
	{
		s[i] = source[i];
	}
}
CQueue<CStateNode>* CEightNums::Search()
{
	CStateNode *State = new CStateNode(this->source, this->target);
	State->Calcuf();               //��ʼ���Ĺ��ۺ���
	CQueue<CStateNode> cExpendQ;
	CQueue<CStateNode> uExpendQ;
	cExpendQ.EnterQueue(*State);

	CStateNode *parent = NULL;
	CStateNode *p;
	while (!cExpendQ.isEmpty())
	{
		//840617253  071356842
		parent = cExpendQ.GetFirst();
		p = cExpendQ.ExitQueue();
		for (int i = 0; i<4; i++)            //�ո�����ƶ�����
		{
			State = new CStateNode(*p);
			if (State->h == 0)                   //��Ŀ����
			{ 
				return State->CreateResultQueue(); //����
			}
			if (State->Expend(i))				//��������չ
			{
				if (State->isRepeat(uExpendQ) != NULL)
				{
					continue;				//������չ�Ľ��
				}
				State->Parent = parent;		//����չ�Ľ�㣬��¼�����
				State->Calcuf();				//���¼���f
				CStateNode *repeatState = NULL;
				if ((repeatState = State->isRepeat(cExpendQ)) != NULL)//�½�������չ����ظ�
				{
					if (State->g < repeatState->g)
					{
						//����gֵС��״̬
						*repeatState = *State;
					}
					continue;
				}
				State->InsertQueue(cExpendQ);
			}
			/*
			else
			{
				delete State;
			}
			*/
		}
		uExpendQ.EnterQueue(*p);
	}
}
CEightNums::~CEightNums()
{

}