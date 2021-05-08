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
	set<int> vertices;//顶点的集合
	vector<Edge> edges;//边的集合

	Tree()
	{

	}
	Tree(int id)
	{
		vertices.insert(id);
	}
};

#define max_len 100000

//打印树信息的方法
void printTree(Tree& tt)
{
	//打印树中的所有顶点
	set<int>::iterator iip;
	for (iip = tt.vertices.begin(); iip != tt.vertices.end(); iip++)
	{
		cout << *iip<< ",";
	}
	cout << endl;
}

vector<Edge> kruskal(vector<int> vertices, vector<Edge> edges)
{
	//获取边的数量
	int ecount = edges.size();
	//声明升序排列的边的列表
	vector<Edge> edgesASC;
	//遍历生成升序排列的边的列表
	for (int i = 0; i < ecount; i++)
	{
		float minTemp = max_len;
		//遍历用迭代器
		vector<Edge>::iterator iterEdge;
		//删除用迭代器
		vector<Edge>::iterator iterEdgeForDel;
		//遍历边列表找最小的边
		for (iterEdge = edges.begin(); iterEdge != edges.end(); iterEdge++)
		{
			//取出一条边
			Edge tempEdge = *iterEdge;
			//若此边长度小于最小值
			if (minTemp > tempEdge.length)
			{
				//更新最小值
				minTemp = tempEdge.length;
				//记录位置
				iterEdgeForDel = iterEdge;
			}
		}
		//获取此轮最小长度的边
		Edge minEdge = *iterEdgeForDel;
		//从原列表中删除此边
		edges.erase(iterEdgeForDel);
		//将找到的最小长度边添加到升序列表中
		edgesASC.push_back(minEdge);
	}
	//打印结果
	//遍历用迭代器
	vector<Edge>::iterator iterEdge;
	cout << "边排序结果:" << endl;
	//遍历打印边
	for (iterEdge = edgesASC.begin(); iterEdge != edgesASC.end(); iterEdge++)
	{
		Edge et = *iterEdge;
		cout << "start: " << et.startId << ", end: " << et.endId << ", length: " << et.length << endl;
	}
	//打印按照边长度的排序结果

	//创建树的列表
	vector<Tree> trees;
	for (int i = 0; i < vertices.size(); i++)
	{
		trees.push_back(Tree(vertices[i]));
	}

	//遍历所有的边
	for (iterEdge = edgesASC.begin(); iterEdge != edgesASC.end(); iterEdge++)
	{
		cout << "==========================================" << endl;
		//取出当前长度最小的边
		Edge et = *iterEdge;
		cout << "当前考察的边 " << "start: " << et.startId << ", end: " << et.endId << ", length: " << et.length << endl;
		//遍历树用迭代器
		vector<Tree>::iterator iterTree;
		//删除起点树用迭代器
		vector<Tree>::iterator iterTreeStart;
		//删除终点树用迭代器
		vector<Tree>::iterator iterTreeEnd;
		//起点树
		Tree treeStart;
		//终点树
		Tree treeEnd;

		//遍历获取当前边的两个顶点对应的树
		cout << "此轮树的数量 " << trees.size() << endl;
		for (iterTree = trees.begin(); iterTree != trees.end(); iterTree++)
		{
			//取出当前树
			Tree tt = *iterTree;
			//获取起点树
			if (tt.vertices.find(et.startId) != tt.vertices.end())
			{
				treeStart = *iterTree;
				iterTreeStart = iterTree;
			}
			//获取终点树
			if (tt.vertices.find(et.endId) != tt.vertices.end())
			{
				treeEnd = *iterTree;
				iterTreeEnd = iterTree;
			}
		}
		//若起点终点在一棵树上的略过
		if (iterTreeStart == iterTreeEnd)
		{
			cout << "起点终点在一棵树上,略过..." << endl;
			continue;
		}
		//删除起点树.终点树
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
		//打印起点树.终点树
		cout << "起点树: ";
		printTree(treeStart);
		cout << "终点树: ";
		printTree(treeEnd);

		//将终点树的起点合并到起点树中
		treeStart.vertices.insert(treeEnd.vertices.begin(), treeEnd.vertices.end());
		//将终点树的边合并到起点树中
		vector<Edge>::iterator hbiter;
		for (hbiter = treeEnd.edges.begin(); hbiter != treeEnd.edges.end(); hbiter++)
		{
			Edge hbet = *hbiter;
			treeStart.edges.push_back(hbet);
		}
		//将此边添加到起点树中
		treeStart.edges.push_back(et);
		//将起点树添加到树集合中
		trees.push_back(treeStart);

		//打印此轮结束时所有树的情况
		cout << "--------------合并后的所有树--------------" << endl;
		for (iterTree = trees.begin(); iterTree != trees.end(); iterTree++)
		{
			//取出当前树
			Tree tt = *iterTree;
			printTree(tt);
		}

		//若集合长度为1则结束并返回结果
		if (trees.size() == 1)
		{
			return treeStart.edges;
		}
	}
}

int main(int argc, char *argv[])
{
	cout << "==========Kruskal最小生成树==========" << endl;
	
	//组织顶点的集合
	vector<int> vertices;
	vertices.push_back(1);
	vertices.push_back(2);
	vertices.push_back(3);
	vertices.push_back(4);
	vertices.push_back(5);
	vertices.push_back(6);

	//组织边的集合
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

	//计算最小生成树
	vector<Edge> minSpanTree = kruskal(vertices, edges);
	//打印结果
	cout << "==========最后结果==========" << endl;
	for (int i = 0; i < minSpanTree.size(); i++)
	{
		Edge& et = minSpanTree[i];
		cout << "起点: " << et.startId << ", 终点: " << et.endId << endl;
	}

	return 0;
}