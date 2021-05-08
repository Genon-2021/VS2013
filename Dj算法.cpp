#include<iostream>
#include<map>
#include<vector>

using namespace std;

class LWPoint
{
public:
	int id;//·����id
	map<int, float> adj;//��ͨ���ӵ��id�Լ�����

	LWPoint();
	LWPoint(int idIn, const map<int, float>& adjIn);
};

LWPoint::LWPoint()
{
	 
}

LWPoint::LWPoint(int idIn, const map<int, float>& adjIn)
{
	this->id = idIn;
	this->adj = adjIn;
}


#define max 10000000

map<int, vector<int>> findPath
(
map<int, LWPoint>& graph,//Ҫ��������ͼ
int startId				//������
)
{
	//�����������
	map<int, vector<int>> result;
	//��ȡ��ͼ�е������
	int count = graph.size();
	//����s����
	vector<int> S;
	//�������ӵ�S������
	S.push_back(startId);
	//����V-S����
	vector<int> VminusS;

	//����D����
	map<int, float> D;
	//��D��ȥÿ��������ľ���ֵ��ʼ��Ϊ���ֵ
	map<int, LWPoint>::iterator iterGraph = graph.begin();
	for (; iterGraph != graph.end(); iterGraph++)
	{
		//���������ĵ㲻�����
		if (iterGraph->first != startId)
		{
			//�����˵�ľ�������Ϊ���ֵ
			D.insert(pair<int, float>(iterGraph->first, max));
			//���˵���ӵ�V-S������
			VminusS.push_back(iterGraph->first);
		}
	}
	//��ȡ���
	LWPoint lwp = graph[startId];
	//�õ������ֱ�Ӵﵽ����б�
	map<int, float> adj = lwp.adj;
	//���������ֱ�ӵ�����б�ı���������
	map<int, float>::iterator iter = adj.begin();
	//�������ֱ�ӵ������б���б���
	for (; iter != adj.end(); iter++)
	{
		//����㵽�˵�ľ������
		D[iter->first] = iter->second;
		//������㵽�˵�Ľ��·��
		result[iter->first].push_back(iter->first);
	}

	while (S.size() < count)
	{
		//����k
		int k = 0;
		float min = max;
		//����V-S���������еĵ�ĵ�����
		vector<int>::iterator iterVMS;
		//ɾ���õ�����
		vector<int>::iterator iterVMSForDelete;
		for (iterVMS = VminusS.begin(); iterVMS != VminusS.end(); iterVMS++)
		{
			//��ǰ����
			int idTemp = *iterVMS;
			//��ȡ�˵��Ӧ��D�еľ���ֵ
			float tempDis = D[idTemp];
			//���±������ľ���С����֪��Сֵ
			if (min > tempDis)
			{
				//������֪��Сֵ
				min = tempDis;
				//��¼k
				k = idTemp;
				//��¼ɾ��λ��
				iterVMSForDelete = iterVMS;
			}
		}
		//��¼�˴��ҵ���Dk
		float Dk = min;
		//��k�����s��
		S.push_back(k);
		//��k���V-S������ɾ��
		VminusS.erase(iterVMSForDelete);

		//ȡ��k��
		LWPoint lwpK = graph[k];
		//ȡ��k����ֱ�ӵ����ı�ż������б�
		map<int, float> adjK = lwpK.adj;

		//����Dk����D�����е�ֵ
		for (iter = D.begin(); iter != D.end(); iter++)
		{
			//��ȡ��ǰ�������ı��
			int idTemp = iter->first;
			//���������Ϊk���Թ�
			if (idTemp == k)
			{
				continue;
			}
			//��k�㵽��ǰ�������ľ����ʼ��Ϊ���ֵ
			float cost_kj = max;
			//�����k�����ֱ�ӵ��ﵱǰ�������
			if (adjK.find(idTemp) != adjK.end())
			{
				//���´�k�㵽��ǰ�������ľ���
				cost_kj = adjK[idTemp];
			}

			if (D[idTemp] > D[k] + cost_kj)
			{
				//����D�����еĶ�Ӧֵ
				D[idTemp] = D[k] + cost_kj;
				//��ȡ����������·�����б�
				vector<int>& pathTemp = result[idTemp];
				//��ȡ��k���·�����б�
				vector<int>& pathTempK = result[k];
				//��յ���������·�����б�
				pathTemp.clear();
				//���ӳ����㵽k��·������µ�·����
				for (int i = 0; i < pathTempK.size(); i++)
				{
					pathTemp.push_back(pathTempK[i]);
				}
				//����k�㵽��ǰ��������·����ӵ�·����
				pathTemp.push_back(idTemp);
			}
		}
	}
	return result;
}

//��֯����ͼ
void initTestData(map<int, LWPoint>& graph)
{
	//��֯1�ŵ�����
	map<int, float> adj1;
	adj1.insert(pair<int, float>(2, 10));
	adj1.insert(pair<int, float>(4, 30));
	adj1.insert(pair<int, float>(5, 100));
	LWPoint lwp1(1, adj1);
	graph.insert(pair<int, LWPoint>(1, lwp1));

	//��֯2�ŵ�����
	map<int, float> adj2;
	adj2.insert(pair<int, float>(3, 50));
	LWPoint lwp2(1, adj2);
	graph.insert(pair<int, LWPoint>(2, lwp2));

	//��֯3�ŵ�����
	map<int, float> adj3;
	adj3.insert(pair<int, float>(5, 10));
	LWPoint lwp3(3, adj3);
	graph.insert(pair<int, LWPoint>(3, lwp3));

	//��֯4�ŵ�����
	map<int, float> adj4;
	adj4.insert(pair<int, float>(3, 20));
	adj4.insert(pair<int, float>(5, 60));
	LWPoint lwp4(4, adj4);
	graph.insert(pair<int, LWPoint>(4, lwp4));

	//��֯5�ŵ�����
	map<int, float> adj5;
	LWPoint lwp5(5, adj5);
	graph.insert(pair<int, LWPoint>(5, lwp5));
}

int main(int argc, char *argv[])
{
	cout << "==========Djkstra���·��==========" << endl;
	
	//��֯����ͼ
	map<int, LWPoint> graph;
	initTestData(graph);

	//Ѱ�Ҵ�1�ŵ���������·��
	map<int, vector<int>> pathResult = findPath(graph,1);
	//��ӡ���
	map<int, vector<int>>::iterator iter = pathResult.begin();
	for (; iter != pathResult.end(); iter++)
	{
		int id = iter->first;
		cout << "·��������:" << id;
		vector<int> path = iter->second;
		cout << ", ·��Ϊ: [" << 1 << ",";
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << ((i == (path.size() - 1)) ? "" : ",");
		}
		cout << "]" << endl;
	}
	//��ӡ���

	return 0;
}