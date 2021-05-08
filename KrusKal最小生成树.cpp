#include<iostream>
#include<vector>
#include<set>
#include<stdio.h>

using namespace std;

class Edge
{
public:
	int startId;
	int endId;
	float length;

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
		cout << *iip<< ",";
	}
	cout << endl;
}

vector<Edge> kruskal(vector<int> vertices, vector<Edge> edges)
{
	//��ȡ�ߵ�����
	int ecount = edges.size();
	//�����������еıߵ��б�
	vector<Edge> edgesASC;
	//���������������еıߵ��б�
	for (int i = 0; i < ecount; i++)
	{
		float minTemp = max_len;
		//�����õ�����
		vector<Edge>::iterator iterEdge;
		//ɾ���õ�����
		vector<Edge>::iterator iterEdgeForDel;
		//�������б�����С�ı�
		for (iterEdge = edges.begin(); iterEdge != edges.end(); iterEdge++)
		{
			//ȡ��һ����
			Edge tempEdge = *iterEdge;
			//���˱߳���С����Сֵ
			if (minTemp > tempEdge.length)
			{
				//������Сֵ
				minTemp = tempEdge.length;
				//��¼λ��
				iterEdgeForDel = iterEdge;
			}
		}
		//��ȡ������С���ȵı�
		Edge minEdge = *iterEdgeForDel;
		//��ԭ�б���ɾ���˱�
		edges.erase(iterEdgeForDel);
		//���ҵ�����С���ȱ���ӵ������б���
		edgesASC.push_back(minEdge);
	}
	//��ӡ���
	//�����õ�����
	vector<Edge>::iterator iterEdge;
	cout << "��������:" << endl;
	//������ӡ��
	for (iterEdge = edgesASC.begin(); iterEdge != edgesASC.end(); iterEdge++)
	{
		Edge et = *iterEdge;
		cout << "start: " << et.startId << ", end: " << et.endId << ", length: " << et.length << endl;
	}
	//��ӡ���ձ߳��ȵ�������

	//���������б�
	vector<Tree> trees;
	for (int i = 0; i < vertices.size(); i++)
	{
		trees.push_back(Tree(vertices[i]));
	}

	//�������еı�
	for (iterEdge = edgesASC.begin(); iterEdge != edgesASC.end(); iterEdge++)
	{
		cout << "==========================================" << endl;
		//ȡ����ǰ������С�ı�
		Edge et = *iterEdge;
		cout << "��ǰ����ı� " << "start: " << et.startId << ", end: " << et.endId << ", length: " << et.length << endl;
		//�������õ�����
		vector<Tree>::iterator iterTree;
		//ɾ��������õ�����
		vector<Tree>::iterator iterTreeStart;
		//ɾ���յ����õ�����
		vector<Tree>::iterator iterTreeEnd;
		//�����
		Tree treeStart;
		//�յ���
		Tree treeEnd;

		//������ȡ��ǰ�ߵ����������Ӧ����
		cout << "������������ " << trees.size() << endl;
		for (iterTree = trees.begin(); iterTree != trees.end(); iterTree++)
		{
			//ȡ����ǰ��
			Tree tt = *iterTree;
			//��ȡ�����
			if (tt.vertices.find(et.startId) != tt.vertices.end())
			{
				treeStart = *iterTree;
				iterTreeStart = iterTree;
			}
			//��ȡ�յ���
			if (tt.vertices.find(et.endId) != tt.vertices.end())
			{
				treeEnd = *iterTree;
				iterTreeEnd = iterTree;
			}
		}
		//������յ���һ�����ϵ��Թ�
		if (iterTreeStart == iterTreeEnd)
		{
			cout << "����յ���һ������,�Թ�..." << endl;
			continue;
		}
		//ɾ�������.�յ���
		if (iterTreeStart > iterTreeEnd)
		{
			trees.erase(iterTreeStart);
			trees.erase(iterTreeEnd);
		}
		else
		{
			trees.erase(iterTreeEnd);
			trees.erase(iterTreeStart);
		}
		//��ӡ�����.�յ���
		cout << "�����: ";
		printTree(treeStart);
		cout << "�յ���: ";
		printTree(treeEnd);

		//���յ��������ϲ����������
		treeStart.vertices.insert(treeEnd.vertices.begin(), treeEnd.vertices.end());
		//���յ����ıߺϲ����������
		vector<Edge>::iterator hbiter;
		for (hbiter = treeEnd.edges.begin(); hbiter != treeEnd.edges.end(); hbiter++)
		{
			Edge hbet = *hbiter;
			treeStart.edges.push_back(hbet);
		}
		//���˱���ӵ��������
		treeStart.edges.push_back(et);
		//���������ӵ���������
		trees.push_back(treeStart);

		//��ӡ���ֽ���ʱ�����������
		cout << "--------------�ϲ����������--------------" << endl;
		for (iterTree = trees.begin(); iterTree != trees.end(); iterTree++)
		{
			//ȡ����ǰ��
			Tree tt = *iterTree;
			printTree(tt);
		}

		//�����ϳ���Ϊ1����������ؽ��
		if (trees.size() == 1)
		{
			return treeStart.edges;
		}
	}
}

int main(int argc, char *argv[])
{
	cout << "==========Kruskal��С������==========" << endl;
	
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

	//������С������
	vector<Edge> minSpanTree = kruskal(vertices, edges);
	//��ӡ���
	cout << "==========�����==========" << endl;
	for (int i = 0; i < minSpanTree.size(); i++)
	{
		Edge& et = minSpanTree[i];
		cout << "���: " << et.startId << ", �յ�: " << et.endId << endl;
	}

	return 0;
}