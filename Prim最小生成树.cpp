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
		cout << *iip << ",";
	}
	cout << endl;
}

vector<Edge> prim(vector<int> vertices, vector<Edge>edges)
{
	//获得顶点的数量
	int vcount = vertices.size();
	//取出一个顶点
	int id = vertices[0];
	//将此点送入生成树中
	Tree tree(id);

	//当生成树中的顶点数量小于总顶点数量时不断重复
	while (true)
	{
		cout << "====================" << endl;
		//边长此轮最小值
		float min = max_len;
		//选中的边
		Edge edgeSelected;
		//选中边的迭代器
		vector<Edge>::iterator edgeIterSelected;
		//选中的非树中顶点
		int lwId = 0;
		//获取生成树上的所有顶点集合
		set<int>& vertices = tree.vertices;
		//遍历生成树上所有顶点用迭代器
		set<int>::iterator iterV;
		//遍历生成树上所有顶点
		for (iterV = vertices.begin(); iterV != vertices.end(); iterV++)
		{
			//得到一个顶点
			int idCurr = *iterV;
			//遍历所有的边的迭代器
			vector<Edge>::iterator edgeIter;
			//遍历所有的不变，找到其中含有此顶点的
			for (edgeIter = edges.begin(); edgeIter != edges.end(); edgeIter++)
			{
				//取出一条边
				Edge et = *edgeIter;
				//若此边的终点或起点包含当前考察的顶点
				if (et.startId == idCurr || et.endId == idCurr)
				{
					//此边的选中点
					int lwIdTemp = 0;
					//箬起点在树中，终点不在是树中
					if (vertices.find(et.startId) != vertices.end() && vertices.find(et.endId) == vertices.end())
					{
						//另外点为终点
						lwIdTemp = et.endId;
					}
					else if (vertices.find(et.startId) == vertices.end() && vertices.find(et.endId) != vertices.end())
					{
						//另外点为起点
						lwIdTemp = et.startId;
					}
					//箬起点，终点都在树中或都在树外
					else
					{
						continue;
					}

					if (min > et.length)
					{
						//更新当前最小值
						min = et.length;
						//记录此边为选中边
						edgeSelected = et;
						//记录此边的迭代器
						edgeIterSelected = edgeIter;
						//记录另外的点
						lwId = lwIdTemp;
					}
				}
			}
		}

		//答应此论边长最小值
		cout << "此轮边长最小值: " << min << endl;
		//打印选中的边
		cout << "选中的边 [" << "start: " << edgeSelected.startId << ", end: " <<
			edgeSelected.endId << ", length: " << edgeSelected.length << "]" << endl;
		//打印此边从待处理边列表中删除
		edges.erase(edgeIterSelected);
		//将此边添加到生成树中
		tree.edges.push_back(edgeSelected);
		//将对应的点添加到生成树中
		tree.vertices.insert(lwId);
		//打印生成树
		printTree(tree);

		if (tree.vertices.size() == vcount)
		{
			return tree.edges;
		}
	}
}

int main(int argc, char *argv[])
{
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

	//调用Prim算法计算最小生成树
	vector<Edge> minSpanTree = prim(vertices, edges);
	//打印结果
	cout << "==========最后结果=========" << endl;
	for (int i = 0; i < minSpanTree.size(); i++)
	{
		Edge& et = minSpanTree[i];
		cout << "起点: " << et.startId << ", 终点: " << et.endId << endl;
	}
	cout << "=====================" << endl;

	return 0;
}
