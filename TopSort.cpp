#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
#include<bitset>
using namespace std;

//拓扑排序：（Topological Sort 或 Topological Ordering，简称 TopSort）
//
//一、有向无环图（Directed Acyclic Graph, DAG）
//定义：
//有向图：边具有方向性（u→v 表示 u 到 v 的单向关系）。
//无环：不存在任何环（即无法从某个节点出发，经过若干条边后回到自身）。
//同时还要了解入度和出度，离散已经学过！
//
//二、AOV 网（Activity On Vertex Network）
//定义：
//用顶点表示活动（任务），边表示活动之间的优先关系。
//若存在边 (u→v)，则活动 u 必须在活动 v 开始前完成。
//
//青椒炒肉工程图：   
//准备厨具────────腌肉────────炒菜────────装盘────────干饭
//类似于这样，像事情的完成流程图
//
//三、拓扑排序（Topological Sort）
//定义：
//说白了就是对事情完成的先后顺序进行一个排序，由于第一件可能可以有多个选择
//序列可能不唯一（当存在多个并行活动时）。
//如何排序？
//1.找出图中入度为0的点，然后输出
//2.删除与该点相连接的边，相等于已经解锁了一件事
//3.一直重复1、2操作，直到图中没有点或者没有入度为0的点为止
//（重点介绍一下为什么需要没有入度为0的点）：每一次拿出入度为0的点进行消边，
//当图中存在环时，就不存在入度为0的点了，此时也无法排序，因此可以用来判断有向图中是否存在环
//（当已经拿不出入度为0的点，而图中还有点，那么一定存在环）
//
//四、拓扑排序的实现方法
//借助队列，来进行广度优先搜索（BFS）
//1.初始化：将所有入度为0的点加入到队列当中
//2.删除与该元素相连的边，
//3.判断：与删除边相连的点，是否入度为0，如果入度为0，加入到队列中
//
//其中的关键步骤就是建图：如何来建图？
//1.首先介绍一下邻接表：a->b->c->d 表示a这一个点存在分别指向bcd的路径
//2.假设一共有abcd四个点，每一个顶点维护一个链表或动态数组！
//推荐的数据结构：vector<vector<int>> / unordered_map<int,vector<int>>
//前者是下标同时可以代表点，后者则可以适用所有类型，推荐第二种！

//算法一：例题模板！一共分为四步进行讲解：
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    //第一步：定义
    unordered_map<int,vector<int>> edges;//一个点连接的所有点
    vector<int> in(numCourses,0);//点的入度情况
    queue<int> q;//队列用于bfs

    //第二步：建图
    for(const auto& e:prerequisites)
    {
        int first=e[0],second=e[1];
        //second->first
        edges[second].push_back(first);
        in[first]++;
    }

    //第三步：拓扑排序
    //将入度为0的点入队列
    for(int i=0;i<numCourses;i++)
    {
        if(in[i]==0) q.push(i);
    }

    while(q.size())
    {
        int front=q.front();q.pop();
        //如果要求得拓扑排序序列，那么将front加入到序列当中即可
        //将所连接的点的入度减一，相当于减边
        for(const auto&e: edges[front])
        {
            in[e]--;
            if(in[e]==0) q.push(e);
        }
    }

    //第四步：判断是否有环（检查in数组即可，如果存在入度不为0的点，那么一定有环）
    for(const auto&e:in)
    {
        if(e) return false;
    }
    return true;
}

//算法二：算法一的改编，将front出来的数据入数组即可
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    //前来复习一下拓扑排序
    //第一步建图
    unordered_map<int,vector<int>> edges;
    vector<int> in(numCourses,0);//记录入度
    queue<int> q;
    vector<int> ret;//返回的数组

    for(const auto&e:prerequisites)
    {
        int first=e[0],second=e[1];
        //代表second->first
        edges[second].push_back(first);
        in[first]++;
    }

    //2.将入度为0的点加入
    for(int i=0;i<numCourses;i++)
    {
        if(in[i]==0) q.push(i);
    }

    //3.拓扑排序
    while(q.size())
    {
        int front=q.front();q.pop();
        //这里来入数组
        ret.push_back(front);
        for(const auto&e:edges[front])
        {
            in[e]--;
            if(in[e]==0) q.push(e);
        }
    }

    //4.判断是否有环
    for(const auto&e:in)
    {
        if(e) return vector<int>();
    }
    return ret;

}

//算法三：
string alienOrder(vector<string>& words) {
    //tips：这一题坑很多，
    //1.如何来建图？冒泡排序一般两两选取字符串进行比较，
    //来确定字符的先后顺序，以此为基础来建图
    //2.建图时，需要用unordered_map<char,set<char>>来保存关联点
    //set的作用是去重，因为可能有多个重复情况
    //3.统计入度信息，建议使用unordered_map<char,int>来保存，而且需要进行初始化
    //如果使用数组因为可能并没有用全26个字母，统计出错
    //4.在比较两个字符串的的时候，使用双指针法，如果前面长度都相同，但因为长度的关系
    //导致后面的字符串大，这时不合法，直接返回空串
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    queue<char> q; string ret;

    for (const auto& e1 : words)
    {
        //初始化一下入度
        for (const auto& e2 : e1)
        {
            in[e2] = 0;
        }
    }

    //建图
    int n = words.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int lenga = words[i].size(), lengb = words[j].size();
            int cur1 = 0, cur2 = 0;
            while (cur1 < lenga && cur2 < lengb)
            {
                char first = words[i][cur1], second = words[j][cur2];
                if (first != second)
                {
                    if (!edges.count(first) || !edges[first].count(second))
                    {
                        edges[first].insert(second);
                        in[second]++;//注意这里一定要判断是否重复，也就是哈希表中是否已经存在，否则入度出错！
                    }
                    break;
                }
                else
                {
                    cur1++; cur2++;
                }
            }
            if (cur1 == words[j].size() && cur1 < words[i].size()) return string();
            //这证明前面一个字符串因为长度大于后一个，这违反了升序，不合法
        }
    }

    //拓扑排序
    for (const auto& e : in)
    {
        if (e.second == 0) q.push(e.first);
    }

    while (q.size())
    {
        char front = q.front(); q.pop();
        ret += front;
        for (const auto& e : edges[front])
        {
            in[e]--;
            if (in[e] == 0) q.push(e);
        }
    }

    //判断是否有环
    for (const auto& e : in)
    {
        if (e.second) return string();
    }
    return ret;
}

int main()
{
   
    return 0;
}