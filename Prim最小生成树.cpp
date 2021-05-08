#include<iostream>
#include<vector>
#include<set>

using namespace std;

class Edge
{
public:
	int startId;
	int endId;
	float length;

	Edge()
	{

	}

	Edge(int startId, int endId, float length)
	{
		this->startId = startId;
		this->endId = endId;
		this->length = length;
	}
};

class Tree
{
public:
	set<int> vertices;//����ļ���
	vector<Edge> edges;//�ߵļ���

	Tree()
	{

	}
	Tree(int id)
	{
		vertices.insert(id);
	}
};

#define max_len 100000
//��ӡ����Ϣ�ķ���
void printTree(Tree& tt)
{
	//��ӡ���е����ж���
	set<int>::iterator iip;
	for (iip = tt.vertices.begin(); iip != tt.vertices.end(); iip++)
	{
		cout << *iip << ",";
	}
	cout << endl;
}

vector<Edge> prim(vector<int> vertices, vector<Edge>edges)
{
	//��ö��������
	int vcount = vertices.size();
	//ȡ��һ������
	int id = vertices[0];
	//���˵�������������
	Tree tree(id);

	//���������еĶ�������С���ܶ�������ʱ�����ظ�
	while (true)
	{
		cout << "====================" << endl;
		//�߳�������Сֵ
		float min = max_len;
		//ѡ�еı�
		Edge edgeSelected;
		//ѡ�бߵĵ�����
		vector<Edge>::iterator edgeIterSelected;
		//ѡ�еķ����ж���
		int lwId = 0;
		//��ȡ�������ϵ����ж��㼯��
		set<int>& vertices = tree.vertices;
		//���������������ж����õ�����
		set<int>::iterator iterV;
		//���������������ж���
		for (iterV = vertices.begin(); iterV != vertices.end(); iterV++)
		{
			//�õ�һ������
			int idCurr = *iterV;
			//�������еıߵĵ�����
			vector<Edge>::iterator edgeIter;
			//�������еĲ��䣬�ҵ����к��д˶����
			for (edgeIter = edges.begin(); edgeIter != edges.end(); edgeIter++)
			{
				//ȡ��һ����
				Edge et = *edgeIter;
				//���˱ߵ��յ����������ǰ����Ķ���
				if (et.startId == idCurr || et.endId == idCurr)
				{
					//�˱ߵ�ѡ�е�
					int lwIdTemp = 0;
					//����������У��յ㲻��������
					if (vertices.find(et.startId) != vertices.end() && vertices.find(et.endId) == vertices.end())
					{
						//�����Ϊ�յ�
						lwIdTemp = et.endId;
					}
					else if (vertices.find(et.startId) == vertices.end() && vertices.find(et.endId) != vertices.end())
					{
						//�����Ϊ���
						lwIdTemp = et.startId;
					}
					//����㣬�յ㶼�����л�������
					else
					{
						continue;
					}

					if (min > et.length)
					{
						//���µ�ǰ��Сֵ
						min = et.length;
						//��¼�˱�Ϊѡ�б�
						edgeSelected = et;
						//��¼�˱ߵĵ�����
						edgeIterSelected = edgeIter;
						//��¼����ĵ�
						lwId = lwIdTemp;
					}
				}
			}
		}

		//��Ӧ���۱߳���Сֵ
		cout << "���ֱ߳���Сֵ: " << min << endl;
		//��ӡѡ�еı�
		cout << "ѡ�еı� [" << "start: " << edgeSelected.startId << ", end: " <<
			edgeSelected.endId << ", length: " << edgeSelected.length << "]" << endl;
		//��ӡ�˱ߴӴ�������б���ɾ��
		edges.erase(edgeIterSelected);
		//���˱���ӵ���������
		tree.edges.push_back(edgeSelected);
		//����Ӧ�ĵ���ӵ���������
		tree.vertices.insert(lwId);
		//��ӡ������
		printTree(tree);

		if (tree.vertices.size() == vcount)
		{
			return tree.edges;
		}
	}
}

int main(int argc, char *argv[])
{
	//��֯����ļ���
	vector<int> vertices;
	vertices.push_back(1);
	vertices.push_back(2);
	vertices.push_back(3);
	vertices.push_back(4);
	vertices.push_back(5);
	vertices.push_back(6);

	//��֯�ߵļ���
	vector<Edge> edges;
	edges.push_back(Edge(1, 2, 6));
	edges.push_back(Edge(1, 3, 1));
	edges.push_back(Edge(1, 4, 5));
	edges.push_back(Edge(2, 3, 5));
	edges.push_back(Edge(2, 5, 3));
	edges.push_back(Edge(3, 4, 5));
	edges.push_back(Edge(3, 5, 6));
	edges.push_back(Edge(4, 6, 2));
	edges.push_back(Edge(3, 6, 4));
	edges.push_back(Edge(5, 6, 6));

	//����Prim�㷨������С������
	vector<Edge> minSpanTree = prim(vertices, edges);
	//��ӡ���
	cout << "==========�����=========" << endl;
	for (int i = 0; i < minSpanTree.size(); i++)
	{
		Edge& et = minSpanTree[i];
		cout << "���: " << et.startId << ", �յ�: " << et.endId << endl;
	}
	cout << "=====================" << endl;

	return 0;
}
