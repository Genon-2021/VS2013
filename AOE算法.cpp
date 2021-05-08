#include<iostream>
#include<vector>
#include<cstring>
#include<set>

using namespace std;

class ActivityEdge
{
public:
	//活动的起点编号
	int start;
	//结束编号
	int end;
	//权重
	int weigh;

	ActivityEdge(int start, int end, int weight)
	{
		this->start = start;
		this->end = end;
		this->weigh = weight;
	}
};

//进行拓扑排序
void toplogicalSort(vector<ActivityEdge*> listE, vector<int>& result)
{
	//存放终点的集合
	set<int> ends;
	//存放起点的集合
	set<int> starts;
	//遍历点集合用的迭代器
	set<int>::iterator it;

	//汇点的编号
	int final = -1;
	//填充当前的起点，终点集合
	for (int i = 0; i < listE.size(); i++)
	{
		//取出一跳边
		ActivityEdge* currE = listE[i];
		//将起点加入集合
		starts.insert(currE->start);
		//将终点加入集合
		ends.insert(currE->end);
	}
	//终点集合有起点集合没有的就是汇点
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
		//生成目前的起点，终点集合
		starts.clear();
		ends.clear();
		for (int i = 0; i < listE.size(); i++)
		{
			//取出一条边
			ActivityEdge* currE = listE[i];
			//起点加入集合
			starts.insert(currE->start);
			//终点加入集合
			ends.insert(currE->end);
		}
		//找到的没有前驱节点的节点编号
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
		//将此节点编号添加到拓扑排序结果中
		result.push_back(findV);
		//遍历边的列表将此点为起点的边删除
		vector<ActivityEdge*>::iterator itE;
		for (itE = listE.begin(); itE != listE.end();)
		{
			//取出一条边
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

//初始化所有边和顶点的方法
void initGraph(vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//生成所有的边并保存
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

	//生成所有的顶点并保存（按照拓扑排序顺序）
	toplogicalSort(listE, listV);
}

//返回一个顶点所有由边直达的顶点的列表（按照拓扑排序顺序）
vector<int> findNeighbors(int k, vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//直达的顶点的列表
	set<int> resultHelp;
	for (int i = 0; i < listE.size(); i++)
	{
		//取出一条边
		ActivityEdge* currE = listE[i];
		//若此边的起点是k则记录器终点进入结果列表
		if (currE->start == k)
		{
			resultHelp.insert(currE->end);
		}
	}
	//符合拓扑排序结果的列表
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

//获取指定边的权重
int getweight(int start, int end, vector<ActivityEdge*>& listE)
{
	for (int i = 0; i < listE.size(); i++)
	{
		//取出一条边
		ActivityEdge* currE = listE[i];
		//若此边的起点是k则记录器终点进入结果列表
		if ((currE->start == start) && (currE->end == end))
		{
			return currE->weigh;
		}
	}
}

//求关键路径的方法
void findCriticalPath(vector<ActivityEdge*>& listE, vector<int>& listV)
{
	//顶点的数量
	int n = listV.size();
	//每个顶点最早的开始时间
	int ve[n];
	//每个顶点允许的最晚的开始时间
	int vl[n];
	//将每个顶点最早的开始时间初始化为0
	memset(ve, 0, n*sizeof(int));
	//正向迭代（从源点【拓扑排序起点】出发）
	//计算出所有顶点的最早开始时间
	for (int k = 0; k < n; k++)
	{
		//获取当前顶点编号
		int i = listV[k];
		//获取此顶点的相邻顶点列表（按照拓扑排序顺序）
		vector<int> nl = findNeighbors(i, listE, listV);
		//对所有相邻顶点进行遍历
		for (int p = 0; p < nl.size(); p++)
		{
			//取出一个相邻顶点编号
			int j = nl[p];
			//获取从i到j点有向边的权重
			int w = getweight(i, j, listE);
			//如果从i到j得到的ve【j】比原来的ve【j】大
			//则更新ve【j】（体现最开始的时间必须是所有前驱节点完成了）
			if (ve[i] + w > ve[j]){ ve[j] = ve[i] + w; }
		}
	} 
		cout << "==========VE==========" << endl;
		//将vl[i]的初始值刷成对应的ve[i],并打印ve[i]
		for (int i = 0; i < n; i++)
		{
			//起点和终点的VL等于VE
			if (i == n - 1 || i == 0)
			{
				vl[i] = ve[i];
			}
			else//其他点的最晚时间设置为无穷大，等着迭代求解
			{
				vl[i] = 9999;
			}
			cout << "ve[" << i << "]" << ve[i] << endl;
		}

		//逆向迭代，从汇点（拓扑排序终点前面一个点）出发
		//迭代到源点后面一个点
		for (int i = 2; i < n; i++)
		{
			//取出一个点
			int j = listV[n - i];
			//获取此顶点的相邻顶点列表（按照拓扑排序顺序）
			vector<int> nl = findNeighbors(j, listE, listV);
			//对所有相邻顶点进行遍历
			for (int p = 0; p < nl.size(); p++)
			{
				//取出一个相邻顶点编号
				int k = nl[p];
				//获取从j点到k点有向边的权重
				int w = getweight(j, k, listE);
				//如果从k到j得到的vl[j]比原来的vl[j]小
				//则更新vl[j]（体现最晚也不能影响后面的事）
				if (vl[k] - w < vl[j]){vl[j] = vl[k] - w;}
			}
		}
		//打印vl[i]
		cout << "==========VL=========" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "vl[" << i << "]=" << vl[i] << endl;
		}
		cout << "=========关键路径========" << endl;
		//遍历各个顶点，求各个活动的AE，AL
		for (int k = 0; k < n; k++)
		{
			// 获取当前顶点编号
			int i = listV[k];
			//获取此顶点的相邻顶列表（按照拓扑排序顺序）
			vector<int> nl = findNeighbors(i, listE, listV);
			//对所有相邻顶点进行遍历
			for (int p = 0; p < nl.size(); p++)
			{
				//取出一个相邻顶点编号
				int j = nl[p];
				//获取从i点到j带你有向边的权重
				int w = getweight(i, j, listE);
				//求i-j活动的最早开始时间
				int ae = ve[i];
				//求i-j活动的最晚开始时间
				int al = vl[j] - w;
				//如果最早开始时间和最晚开始时间相同
				//说明为关键路径上的活动，一刻也不能耽误
				if (ae == al)
				{
					cout << i << "->" << j << endl;
				}
			}
		}
}



int main(int argc, char *argv[])
{
	//存放AOE图中所有边的列表
	vector<ActivityEdge*> listE;
	//存放AOE图中所有顶点的列表
	vector<int> listV;
	//初始化图中的边和顶点
	initGraph(listE, listV);
	//寻找关键路径
	findCriticalPath(listE, listV);

	return 0;
}