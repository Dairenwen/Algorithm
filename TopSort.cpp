#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
#include<bitset>
using namespace std;

//�������򣺣�Topological Sort �� Topological Ordering����� TopSort��
//
//һ�������޻�ͼ��Directed Acyclic Graph, DAG��
//���壺
//����ͼ���߾��з����ԣ�u��v ��ʾ u �� v �ĵ����ϵ����
//�޻����������κλ������޷���ĳ���ڵ�����������������ߺ�ص�������
//ͬʱ��Ҫ�˽���Ⱥͳ��ȣ���ɢ�Ѿ�ѧ����
//
//����AOV ����Activity On Vertex Network��
//���壺
//�ö����ʾ������񣩣��߱�ʾ�֮������ȹ�ϵ��
//�����ڱ� (u��v)���� u �����ڻ v ��ʼǰ��ɡ�
//
//�ཷ���⹤��ͼ��   
//׼�����ߩ������������������⩤�����������������˩���������������װ�̩����������������ɷ�
//��������������������������ͼ
//
//������������Topological Sort��
//���壺
//˵���˾��Ƕ�������ɵ��Ⱥ�˳�����һ���������ڵ�һ�����ܿ����ж��ѡ��
//���п��ܲ�Ψһ�������ڶ�����лʱ����
//�������
//1.�ҳ�ͼ�����Ϊ0�ĵ㣬Ȼ�����
//2.ɾ����õ������ӵıߣ�������Ѿ�������һ����
//3.һֱ�ظ�1��2������ֱ��ͼ��û�е����û�����Ϊ0�ĵ�Ϊֹ
//���ص����һ��Ϊʲô��Ҫû�����Ϊ0�ĵ㣩��ÿһ���ó����Ϊ0�ĵ�������ߣ�
//��ͼ�д��ڻ�ʱ���Ͳ��������Ϊ0�ĵ��ˣ���ʱҲ�޷�������˿��������ж�����ͼ���Ƿ���ڻ�
//�����Ѿ��ò������Ϊ0�ĵ㣬��ͼ�л��е㣬��ôһ�����ڻ���
//
//�ġ����������ʵ�ַ���
//�������У������й������������BFS��
//1.��ʼ�������������Ϊ0�ĵ���뵽���е���
//2.ɾ�����Ԫ�������ıߣ�
//3.�жϣ���ɾ���������ĵ㣬�Ƿ����Ϊ0��������Ϊ0�����뵽������
//
//���еĹؼ�������ǽ�ͼ���������ͼ��
//1.���Ƚ���һ���ڽӱ�a->b->c->d ��ʾa��һ������ڷֱ�ָ��bcd��·��
//2.����һ����abcd�ĸ��㣬ÿһ������ά��һ�������̬���飡
//�Ƽ������ݽṹ��vector<vector<int>> / unordered_map<int,vector<int>>
//ǰ�����±�ͬʱ���Դ���㣬��������������������ͣ��Ƽ��ڶ��֣�

//�㷨һ������ģ�壡һ����Ϊ�Ĳ����н��⣺
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    //��һ��������
    unordered_map<int,vector<int>> edges;//һ�������ӵ����е�
    vector<int> in(numCourses,0);//���������
    queue<int> q;//��������bfs

    //�ڶ�������ͼ
    for(const auto& e:prerequisites)
    {
        int first=e[0],second=e[1];
        //second->first
        edges[second].push_back(first);
        in[first]++;
    }

    //����������������
    //�����Ϊ0�ĵ������
    for(int i=0;i<numCourses;i++)
    {
        if(in[i]==0) q.push(i);
    }

    while(q.size())
    {
        int front=q.front();q.pop();
        //���Ҫ��������������У���ô��front���뵽���е��м���
        //�������ӵĵ����ȼ�һ���൱�ڼ���
        for(const auto&e: edges[front])
        {
            in[e]--;
            if(in[e]==0) q.push(e);
        }
    }

    //���Ĳ����ж��Ƿ��л������in���鼴�ɣ����������Ȳ�Ϊ0�ĵ㣬��ôһ���л���
    for(const auto&e:in)
    {
        if(e) return false;
    }
    return true;
}

//�㷨�����㷨һ�ĸı࣬��front���������������鼴��
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    //ǰ����ϰһ����������
    //��һ����ͼ
    unordered_map<int,vector<int>> edges;
    vector<int> in(numCourses,0);//��¼���
    queue<int> q;
    vector<int> ret;//���ص�����

    for(const auto&e:prerequisites)
    {
        int first=e[0],second=e[1];
        //����second->first
        edges[second].push_back(first);
        in[first]++;
    }

    //2.�����Ϊ0�ĵ����
    for(int i=0;i<numCourses;i++)
    {
        if(in[i]==0) q.push(i);
    }

    //3.��������
    while(q.size())
    {
        int front=q.front();q.pop();
        //������������
        ret.push_back(front);
        for(const auto&e:edges[front])
        {
            in[e]--;
            if(in[e]==0) q.push(e);
        }
    }

    //4.�ж��Ƿ��л�
    for(const auto&e:in)
    {
        if(e) return vector<int>();
    }
    return ret;

}

//�㷨����
string alienOrder(vector<string>& words) {
    //tips����һ��Ӻܶ࣬
    //1.�������ͼ��ð������һ������ѡȡ�ַ������бȽϣ�
    //��ȷ���ַ����Ⱥ�˳���Դ�Ϊ��������ͼ
    //2.��ͼʱ����Ҫ��unordered_map<char,set<char>>�����������
    //set��������ȥ�أ���Ϊ�����ж���ظ����
    //3.ͳ�������Ϣ������ʹ��unordered_map<char,int>�����棬������Ҫ���г�ʼ��
    //���ʹ��������Ϊ���ܲ�û����ȫ26����ĸ��ͳ�Ƴ���
    //4.�ڱȽ������ַ����ĵ�ʱ��ʹ��˫ָ�뷨�����ǰ�泤�ȶ���ͬ������Ϊ���ȵĹ�ϵ
    //���º�����ַ�������ʱ���Ϸ���ֱ�ӷ��ؿմ�
    unordered_map<char, unordered_set<char>> edges;
    unordered_map<char, int> in;
    queue<char> q; string ret;

    for (const auto& e1 : words)
    {
        //��ʼ��һ�����
        for (const auto& e2 : e1)
        {
            in[e2] = 0;
        }
    }

    //��ͼ
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
                        in[second]++;//ע������һ��Ҫ�ж��Ƿ��ظ���Ҳ���ǹ�ϣ�����Ƿ��Ѿ����ڣ�������ȳ���
                    }
                    break;
                }
                else
                {
                    cur1++; cur2++;
                }
            }
            if (cur1 == words[j].size() && cur1 < words[i].size()) return string();
            //��֤��ǰ��һ���ַ�����Ϊ���ȴ��ں�һ������Υ�������򣬲��Ϸ�
        }
    }

    //��������
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

    //�ж��Ƿ��л�
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