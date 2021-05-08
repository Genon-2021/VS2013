#include<iostream>
#include<vector>
#include<cstring>
#include<set>

using namespace std;

class ActivityEdge
{
public:
	//��������
	int start;
	//�������
	int end;
	//Ȩ��
	int weigh;

	ActivityEdge(int start, int end, int weight)
	{
		this->start = start;
		this->end = end;
		this->weigh = weight;
	}
};

//������������
void toplogicalSort(vector<ActivityEdge*> listE, vector<int>& result)
{
	//����յ�ļ���
	set<int> ends;
	//������ļ���
	set<int> starts;
	//�����㼯���õĵ�����
	set<int>::iterator it;

	//���ı��
	int final = -1;
	//��䵱ǰ����㣬�յ㼯��
	for (int i = 0; i < listE.size(); i++)
	{
		//ȡ��һ����
		ActivityEdge* currE = listE[i];
		//�������뼯��
		starts.insert(currE->start);
		//���յ���뼯��
		ends.insert(currE->end);
	}
	//�յ㼯������㼯��û�еľ��ǻ��
	for (it = ends.begin(); it != ends.end(); it++)
	{
		int curr = *it;
		if (starts.find(curr) == starts.end())
		{
			final = curr;
			break;
		}
	}

	while (!listE.empty())
	{
		//����Ŀǰ����㣬�յ㼯��
		starts.clear();
		ends.clear();
		for (int i = 0; i < listE.size(); i++)
		{
			//ȡ��һ����
			ActivityEdge* currE = listE[i];
			//�����뼯��
			starts.insert(currE->start);
			//�յ���뼯��
			ends.insert(currE->end);
		}
		//�ҵ���û��ǰ���ڵ�Ľڵ���
		int findV = -1;
		for (it = starts.begin(); it != starts.end(); it++)
		{
			int curr = *it;
			if (ends.find(curr) == ends.end())
			{
				findV = curr;
				break;
			}
		}
		//���˽ڵ�����ӵ�������������
		result.push_back(findV);
		//�����ߵ��б��˵�Ϊ���ı�ɾ��
		vector<ActivityEdge*>::iterator itE;
		for (itE = listE.begin(); itE != listE.end();)
		{
			//ȡ��һ����
			ActivityEdge* currE = *itE;
			if (currE->start == findV)
			{
				listE.erase(itE);
			}
			else
			{
				itE++;
			}
		} 
	}
	result.push_back(final);
}

//��ʼ�����бߺͶ���ķ���
void initGraph(vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//�������еı߲�����
	listE.push_back(new ActivityEdge(3, 5, 2));
	listE.push_back(new ActivityEdge(4, 6, 9));
	listE.push_back(new ActivityEdge(4, 7, 7));
	listE.push_back(new ActivityEdge(5, 7, 4));
	listE.push_back(new ActivityEdge(6, 8, 2));
	listE.push_back(new ActivityEdge(7, 8, 4));
	listE.push_back(new ActivityEdge(0, 1, 6));
	listE.push_back(new ActivityEdge(0, 2, 4));
	listE.push_back(new ActivityEdge(0, 3, 5));
	listE.push_back(new ActivityEdge(1, 4, 1));
	listE.push_back(new ActivityEdge(2, 4, 1));

	//�������еĶ��㲢���棨������������˳��
	toplogicalSort(listE, listV);
}

//����һ�����������ɱ�ֱ��Ķ�����б�������������˳��
vector<int> findNeighbors(int k, vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//ֱ��Ķ�����б�
	set<int> resultHelp;
	for (int i = 0; i < listE.size(); i++)
	{
		//ȡ��һ����
		ActivityEdge* currE = listE[i];
		//���˱ߵ������k���¼���յ�������б�
		if (currE->start == k)
		{
			resultHelp.insert(currE->end);
		}
	}
	//�����������������б�
	vector<int> result;
	for (int i = 0; i < listV.size(); i++)
	{
		if (resultHelp.find(listV[i]) != resultHelp.end())
		{
			result.push_back(listV[i]);
		}
	}
	return result;
}

//��ȡָ���ߵ�Ȩ��
int getweight(int start, int end, vector<ActivityEdge*>& listE)
{
	for (int i = 0; i < listE.size(); i++)
	{
		//ȡ��һ����
		ActivityEdge* currE = listE[i];
		//���˱ߵ������k���¼���յ�������б�
		if ((currE->start == start) && (currE->end == end))
		{
			return currE->weigh;
		}
	}
}

//��ؼ�·���ķ���
void findCriticalPath(vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//���������
	int n = listV.size();
	//ÿ����������Ŀ�ʼʱ��
	int ve[n];
	//ÿ���������������Ŀ�ʼʱ��
	int vl[n];
	//��ÿ����������Ŀ�ʼʱ���ʼ��Ϊ0
	memset(ve, 0, n*sizeof(int));
	//�����������Դ�㡾����������㡿������
	//��������ж�������翪ʼʱ��
	for (int k = 0; k < n; k++)
	{
		//��ȡ��ǰ������
		int i = listV[k];
		//��ȡ�˶�������ڶ����б�������������˳��
		vector<int> nl = findNeighbors(i, listE, listV);
		//���������ڶ�����б���
		for (int p = 0; p < nl.size(); p++)
		{
			//ȡ��һ�����ڶ�����
			int j = nl[p];
			//��ȡ��i��j������ߵ�Ȩ��
			int w = getweight(i, j, listE);
			//�����i��j�õ���ve��j����ԭ����ve��j����
			//�����ve��j���������ʼ��ʱ�����������ǰ���ڵ�����ˣ�
			if (ve[i] + w > ve[j]){ ve[j] = ve[i] + w; }
		}
	} 
		cout << "==========VE==========" << endl;
		//��vl[i]�ĳ�ʼֵˢ�ɶ�Ӧ��ve[i],����ӡve[i]
		for (int i = 0; i < n; i++)
		{
			//�����յ��VL����VE
			if (i == n - 1 || i == 0)
			{
				vl[i] = ve[i];
			}
			else//�����������ʱ������Ϊ����󣬵��ŵ������
			{
				vl[i] = 9999;
			}
			cout << "ve[" << i << "]" << ve[i] << endl;
		}

		//����������ӻ�㣨���������յ�ǰ��һ���㣩����
		//������Դ�����һ����
		for (int i = 2; i < n; i++)
		{
			//ȡ��һ����
			int j = listV[n - i];
			//��ȡ�˶�������ڶ����б�������������˳��
			vector<int> nl = findNeighbors(j, listE, listV);
			//���������ڶ�����б���
			for (int p = 0; p < nl.size(); p++)
			{
				//ȡ��һ�����ڶ�����
				int k = nl[p];
				//��ȡ��j�㵽k������ߵ�Ȩ��
				int w = getweight(j, k, listE);
				//�����k��j�õ���vl[j]��ԭ����vl[j]С
				//�����vl[j]����������Ҳ����Ӱ�������£�
				if (vl[k] - w < vl[j]){vl[j] = vl[k] - w;}
			}
		}
		//��ӡvl[i]
		cout << "==========VL=========" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "vl[" << i << "]=" << vl[i] << endl;
		}
		cout << "=========�ؼ�·��========" << endl;
		//�����������㣬��������AE��AL
		for (int k = 0; k < n; k++)
		{
			// ��ȡ��ǰ������
			int i = listV[k];
			//��ȡ�˶�������ڶ��б�������������˳��
			vector<int> nl = findNeighbors(i, listE, listV);
			//���������ڶ�����б���
			for (int p = 0; p < nl.size(); p++)
			{
				//ȡ��һ�����ڶ�����
				int j = nl[p];
				//��ȡ��i�㵽j��������ߵ�Ȩ��
				int w = getweight(i, j, listE);
				//��i-j������翪ʼʱ��
				int ae = ve[i];
				//��i-j�������ʼʱ��
				int al = vl[j] - w;
				//������翪ʼʱ�������ʼʱ����ͬ
				//˵��Ϊ�ؼ�·���ϵĻ��һ��Ҳ���ܵ���
				if (ae == al)
				{
					cout << i << "->" << j << endl;
				}
			}
		}
}



int main(int argc, char *argv[])
{
	//���AOEͼ�����бߵ��б�
	vector<ActivityEdge*> listE;
	//���AOEͼ�����ж�����б�
	vector<int> listV;
	//��ʼ��ͼ�еıߺͶ���
	initGraph(listE, listV);
	//Ѱ�ҹؼ�·��
	findCriticalPath(listE, listV);

	return 0;
}