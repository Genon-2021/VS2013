#include<iostream>
#include<map>
#include<vector>

using namespace std;

class LWPoint
{
public:
	int id;//路网点id
	map<int, float> adj;//能通连接点的id以及距离

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
map<int, LWPoint>& graph,//要搜索的子图
int startId				//出发点
)
{
	//声明结果对象
	map<int, vector<int>> result;
	//获取子图中点的数量
	int count = graph.size();
	//创建s集合
	vector<int> S;
	//将起点添加到S集合中
	S.push_back(startId);
	//创建V-S集合
	vector<int> VminusS;

	//创建D数组
	map<int, float> D;
	//将D中去每个其他点的距离值初始化为最大值
	map<int, LWPoint>::iterator iterGraph = graph.begin();
	for (; iterGraph != graph.end(); iterGraph++)
	{
		//若遍历到的点不是起点
		if (iterGraph->first != startId)
		{
			//将到此点的距离设置为最大值
			D.insert(pair<int, float>(iterGraph->first, max));
			//将此点添加到V-S集合中
			VminusS.push_back(iterGraph->first);
		}
	}
	//获取起点
	LWPoint lwp = graph[startId];
	//拿到起点能直接达到点的列表
	map<int, float> adj = lwp.adj;
	//声明起点能直接到达点列表的遍历迭代器
	map<int, float>::iterator iter = adj.begin();
	//对起点能直接到达点的列表进行遍历
	for (; iter != adj.end(); iter++)
	{
		//将起点到此点的距离更新
		D[iter->first] = iter->second;
		//更新起点到此点的结果路径
		result[iter->first].push_back(iter->first);
	}

	while (S.size() < count)
	{
		//声明k
		int k = 0;
		float min = max;
		//遍历V-S集合中所有的点的迭代器
		vector<int>::iterator iterVMS;
		//删除用迭代器
		vector<int>::iterator iterVMSForDelete;
		for (iterVMS = VminusS.begin(); iterVMS != VminusS.end(); iterVMS++)
		{
			//当前点编号
			int idTemp = *iterVMS;
			//获取此点对应的D中的距离值
			float tempDis = D[idTemp];
			//若新遍历到的距离小于已知最小值
			if (min > tempDis)
			{
				//更新已知最小值
				min = tempDis;
				//记录k
				k = idTemp;
				//记录删除位置
				iterVMSForDelete = iterVMS;
			}
		}
		//记录此次找到的Dk
		float Dk = min;
		//将k点加入s中
		S.push_back(k);
		//将k点从V-S集合中删除
		VminusS.erase(iterVMSForDelete);

		//取出k点
		LWPoint lwpK = graph[k];
		//取出k点能直接到达点的编号及距离列表
		map<int, float> adjK = lwpK.adj;

		//根据Dk更新D数组中的值
		for (iter = D.begin(); iter != D.end(); iter++)
		{
			//获取当前被考察点的编号
			int idTemp = iter->first;
			//若被考察点为k则略过
			if (idTemp == k)
			{
				continue;
			}
			//从k点到当前被考察点的距离初始化为最大值
			float cost_kj = max;
			//如果从k点可以直接到达当前被考察点
			if (adjK.find(idTemp) != adjK.end())
			{
				//更新从k点到当前被考察点的距离
				cost_kj = adjK[idTemp];
			}

			if (D[idTemp] > D[k] + cost_kj)
			{
				//更新D数组中的对应值
				D[idTemp] = D[k] + cost_kj;
				//获取到被考察点的路径点列表
				vector<int>& pathTemp = result[idTemp];
				//获取到k点的路径点列表
				vector<int>& pathTempK = result[k];
				//清空到被考察点的路径点列表
				pathTemp.clear();
				//将从出发点到k的路径点更新到路径中
				for (int i = 0; i < pathTempK.size(); i++)
				{
					pathTemp.push_back(pathTempK[i]);
				}
				//将从k点到当前被考察点的路径添加到路径中
				pathTemp.push_back(idTemp);
			}
		}
	}
	return result;
}

//组织侧视图
void initTestData(map<int, LWPoint>& graph)
{
	//组织1号点数据
	map<int, float> adj1;
	adj1.insert(pair<int, float>(2, 10));
	adj1.insert(pair<int, float>(4, 30));
	adj1.insert(pair<int, float>(5, 100));
	LWPoint lwp1(1, adj1);
	graph.insert(pair<int, LWPoint>(1, lwp1));

	//组织2号点数据
	map<int, float> adj2;
	adj2.insert(pair<int, float>(3, 50));
	LWPoint lwp2(1, adj2);
	graph.insert(pair<int, LWPoint>(2, lwp2));

	//组织3号点数据
	map<int, float> adj3;
	adj3.insert(pair<int, float>(5, 10));
	LWPoint lwp3(3, adj3);
	graph.insert(pair<int, LWPoint>(3, lwp3));

	//组织4号点数据
	map<int, float> adj4;
	adj4.insert(pair<int, float>(3, 20));
	adj4.insert(pair<int, float>(5, 60));
	LWPoint lwp4(4, adj4);
	graph.insert(pair<int, LWPoint>(4, lwp4));

	//组织5号点数据
	map<int, float> adj5;
	LWPoint lwp5(5, adj5);
	graph.insert(pair<int, LWPoint>(5, lwp5));
}

int main(int argc, char *argv[])
{
	cout << "==========Djkstra最短路径==========" << endl;
	
	//组织测试图
	map<int, LWPoint> graph;
	initTestData(graph);

	//寻找从1号点出发的最短路径
	map<int, vector<int>> pathResult = findPath(graph,1);
	//打印结果
	map<int, vector<int>>::iterator iter = pathResult.begin();
	for (; iter != pathResult.end(); iter++)
	{
		int id = iter->first;
		cout << "路径结束点:" << id;
		vector<int> path = iter->second;
		cout << ", 路径为: [" << 1 << ",";
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << ((i == (path.size() - 1)) ? "" : ",");
		}
		cout << "]" << endl;
	}
	//打印结果

	return 0;
}