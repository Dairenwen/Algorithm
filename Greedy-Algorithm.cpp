#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<stack>
#include<queue>
#include<functional>
#include<cstring>
using namespace std;

//贪心算法是一种在每一步选择中都采取在当前状态下最优的选择，从而希望导致全局最优解的算法。
//1. 找零问题（Coin Change Problem）
//问题：给定不同面额的硬币和一个总金额，如何用最少的硬币凑出这个金额？
//解法：
//贪心算法（适用于标准面值，如 1、5、10、25 分）：每次选择最大面值的硬币，直到凑够金额。
//时间复杂度：O (n)，n 为硬币数量。
//局限性：若面值非标准（如 1、3、4），贪心可能失效（如金额为 6 时，贪心选 4+1+1，最优解为 3+3）。
//动态规划（通用解法）：保存每个金额所需的最少硬币数。
//时间复杂度：O(amount × coins)。
//示例：金额 11，硬币 [1,5,10] → 贪心策略：10+1，共 2 枚。

//2. 最小路径和（Minimum Path Sum）
//问题：在一个二维网格中，从左上角到右下角的路径中，数字之和最小的路径是多少？每次只能向下或向右移动。
//解法：
//动态规划：
//状态定义：dp [i][j] 表示到达 (i,j) 的最小路径和。
//状态转移：dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])。
//时间复杂度：O (m×n)，m 和 n 为网格的行数和列数。
//示例：
//[1,3,1]
//[1,5,1]
//[4,2,1]
//最小路径：1→3→1→1→1，和为7。

//3. 背包问题（Knapsack Problem）
//分类：
//0-1 背包：每个物品只能选一次。
//完全背包：每个物品可选无限次。
//解法：
//动态规划（通用解法）：
//状态定义：dp [i][w] 表示前 i 个物品放入容量为 w 的背包的最大价值。
//
//# 完全背包：选0次或多次第i个物品
//dp[i][w] = max(dp[i-1][w], dp[i][w-weight[i]] + value[i])
//
//时间复杂度：O (n×W)，n 为物品数，W 为背包容量。
//贪心算法（仅适用于分数背包）：按单位价值降序选择物品，可拆分。
//局限性：不适用于 0-1 背包（如物品价值 [6,10,12]，重量 [1,2,3]，背包容量 5，贪心选第三个物品，最优解为选前两个）。

//4. 最小生成树（Minimum Spanning Tree, MST）
//问题：在一个带权无向图中，找到连接所有节点且边权和最小的树。
//解法：
//Kruskal 算法（贪心）：
//将所有边按权值升序排序。
//依次选择最小边，若加入后不形成环，则保留。
//时间复杂度：O (E log E)，E 为边数。
//Prim 算法（贪心）：
//从任意节点开始，每次选择连接已选节点和未选节点的最小边。
//时间复杂度：O (E log V)，V 为节点数。
//适用场景：网络布线、电路设计等。

//5. 霍夫曼编码（Huffman Coding）
//问题：构造最优前缀编码，用于数据压缩。
//解法：
//贪心算法：
//根据字符频率构建霍夫曼树：每次合并频率最低的两个节点。
//左路径编码为 0，右路径编码为 1，生成每个字符的编码。
//时间复杂度：O (n log n)，n 为字符数。

//找零问题！贪心的策略是尽量使用面额最大的硬币来找零。
//将面额最小的硬币留到最后，能少使用就少使用。
bool lemonadeChange(vector<int>& bills) {
    int price=5,five=0,ten=0,twenty=0;
    for(const auto&e:bills)
    {
        if(e==5) five++;
        else if(e==10) ten++;
        else twenty++;

        if(e-5==5)
        {
            if(five) five--;
            else return false;
        }
        else if(e-5==10)
        {
            if(ten) ten--;
            else if(five>=2) five-=2;
            else return false;
        }
        else if(e-5==15)
        {
            if(ten&&five)
            {
                ten--;five--;
            }
            else if(five>=3) five-=3;
            else return false;
        }
    }
    return true;
}

//选用一个堆，每次对最大的元素进行减半操作，直到数组的和小于等于原数组和的一半。
int halveArray(vector<int>& nums) {
    double judge=0,sum=0;int ret=0;
    for(const auto&e:nums) judge+=e;
    sum=judge;judge/=2;
    priority_queue<double> heap(nums.begin(),nums.end());
    while(sum>judge)
    {
        double num=heap.top();heap.pop();
        sum-=num/2;
        num/=2;
        ret++;
        heap.push(num);
    }
    return ret;
}

//找出最大数字，按照贪心更改比较方法就行，记住要对ab和ba的拼接进行比较。
class Compare
{
public:
    bool operator()(const string& s1,const string& s2)
    {
        return s1+s2<=s2+s1;
    }
};
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string ret;
        priority_queue<string,vector<string>,Compare> heap;
        for(const auto&e:nums)
        {
            heap.push(to_string(e));
        }
        while(heap.size())
        {
            ret+=heap.top();heap.pop();
        }
        if(ret[0]=='0') return "0";
        else return ret;
    }
};

//用left记录上一个差值，right记录当前差值。
//遍历数组，计算相邻元素的差值right。
//如果right==0，跳过（相等不算摆动）。
//如果left*right<=0，说明出现了摆动（正负号发生变化或初始），计数器ret++。
//更新left=right，继续判断下一个差值。
//最后返回ret+1，因为子序列长度比摆动次数多1。
int wiggleMaxLength(vector<int>& nums) {
    int ret=0,left=0,right=0;
    for(int i=0;i<nums.size();i++)
    {
        if(i+1<nums.size()) right=nums[i+1]-nums[i];
        if(right==0) continue;//说明右点与此点相同
        if(left*right<=0) ret++;
        left=right;//代表左边的增减情况
    }
    return ret+1;//
}

//这个题是“最长递增子序列”（LIS），用贪心+二分优化。
//
//为什么可以用贪心：
//每次遍历到一个新元素时：
//
//如果比当前“序列”末尾大，直接加到末尾（贪心选更大的，保证递增）。
//如果比末尾小，用二分找到第一个不小于它的位置，替换掉（贪心让“结尾”尽量小，为后续留更大上升空间）。
//这样做不会影响最终长度，因为我们只关心能组成多长的递增序列，结尾越小越容易接上后面的更大数。
//本质是维护一个“可能的递增序列结尾”，每次都让它最优（最小），所以可以用贪心。
//
//二分查找是为了加速找到替换位置，整体时间复杂度 O(n log n)。
int bs(vector<int>& tmp,int e)
{
    int left=0,right=tmp.size()-1;
    while(left<right)
    {
        int mid=left+(right-left)/2;
        if(tmp[mid]<e) left=mid+1;
        else right=mid;
    }
    return left;
}

int lengthOfLIS(vector<int>& nums) {
    vector<int> tmp; tmp.push_back(nums[0]);
    for(int i=1;i<nums.size();i++)
    {
        if(nums[i]>tmp.back()) tmp.push_back(nums[i]);
        else
        {
            int index=bs(tmp,nums[i]);
            tmp[index]=nums[i];
        }
    }
    return tmp.size();
}

//最长连续递增子序列（LCIS）问题：注意是连续的子序列，也可以理解为字串
//那么动态规划版本就不需要一直维护一个数组了，而是维护一个dp数组，表示以当前元素结尾的最长连续递增子序列长度。
int findLengthOfLCIS(vector<int>& nums) {
    vector<int> dp(nums.size(),1);
    int ret=0;
    for(int i=nums.size()-1;i>=0;i--)
    {
        if(i+1<nums.size()&&nums[i]<nums[i+1])
        {
            dp[i]=max(dp[i],dp[i+1]+1);
        }
        ret=max(ret,dp[i]);
    }
    return ret;
}
//提醒：不能用比当前“序列”末尾大，直接加到末尾（贪心选更大的，保证递增），末尾小，用二分找到第一个不小于它的位置！

//经典题目：买卖股票的最佳时机
//frontmin 记录目前为止遇到的最小价格（买入的最低点）。
//遍历每一天的价格，计算如果今天卖出，能获得的最大利润 prices[i] - frontmin。
//用 ret 记录全程中的最大利润。
//如果遇到更低的价格，就更新 frontmin，为后续可能的更大利润做准备。
int maxProfit(vector<int>& prices) {
    int frontmin=prices[0],ret=0;
    for(int i=1;i<prices.size();i++)
    {
        ret=max(ret,prices[i]-frontmin);
        if(prices[i]<frontmin) frontmin=prices[i];
    }
    return ret;
}

//还是关于股票的问题，但是这次是可以多次买卖的。
int maxProfitII(vector<int>& prices) {
    //采用贪心策略，只要是上升趋势，就买入卖出
    //1.双指针策略
    // int ret=0;
    // for(int i=0;i<prices.size();i++)
    // {
    //     int left=i;
    //     while(i+1<prices.size()&&prices[i+1]>=prices[i]) i++;
    //     ret+=prices[i]-prices[left];
    // }
    // return ret;
    //2.按照相邻两天为一个周期，判断是否加到ret
    int ret=0;
    for(int i=0;i<prices.size();i++)
    {
        if(i+1<prices.size()&&prices[i+1]>=prices[i]) ret+=prices[i+1]-prices[i];
    }
    return ret;
}

//K次取反后最大化的数组和
//贪心方法：
//a. m > k ：把前 k ?负数，全部变成正数；
//b. m == k ：把所有的负数全部转化成正数；
//c. m < k ：
//i. 先把所有的负数变成正数；
//ii. 然后根据 k - m 的奇偶分情况讨论：
//1. 如果是偶数，直接忽略；
//2. 如果是奇数，挑选当前数组中最?的数，变成负数
int largestSumAfterKNegations(vector<int>& nums, int k) {
    int m = 0, minElem = INT_MAX, n = nums.size();
    for(auto x : nums)
    {
        if(x < 0) m++;
        minElem = min(minElem, abs(x)); // 求绝对值最?的那个数
    }
    // 分类讨论
    int ret = 0;
    if(m > k)
    {
        sort(nums.begin(), nums.end());
        for(int i = 0; i < k; i++) // 前 k ?个负数，变成正数
        {
            ret += -nums[i];
        }
        for(int i = k; i < n; i++) // 后?的数不变
        {
            ret += nums[i];
        }
    }
    else
    {
        // 把所有的负数变成正数
        for(auto x : nums) ret += abs(x);

        if((k - m) % 2) // 判断是否处理最?的正数
        {
            ret -= minElem * 2;
        }
    }
    return ret;
    // //使用堆的方式，更加容易想到！
    // priority_queue<int,vector<int>,greater<int>> heap(nums.begin(),nums.end());
    // while(k)
    // {
    //     int top=heap.top();heap.pop();
    //     heap.push(-top);
    //     k--;
    // }
    // int ret=0;
    // while(heap.size())
    // {
    //     ret+=heap.top();heap.pop();
    // }
    // return ret;
}

//按照身高排序，不知道这一个排序题与贪心有什么关系，哎！
//本人直接按照map的方式进行排序，按照身高从大到小排序，然后将名字放入vector中返回即可。
vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
    //这个方法非常重要，对下标进行排序，然后根据下标返回对应的名字！
    vector<int> tmp;
    for(int i=0;i<names.size();i++)
    {
        tmp.push_back(i);
    }
    sort(tmp.begin(),tmp.end(),[&](const int& i1,const int& i2){ return heights[i1]>heights[i2];});
    vector<string> ret;
    for(const auto&e:tmp)
    {
        ret.push_back(names[e]);
    }
    return ret;

    //这是对身高进行排序，然后按照身高从大到小的顺序返回名字。
//    map<int,string> hash;
//    for(int i=0;i<names.size();i++) hash[heights[i]]=names[i];
//    vector<string> ret;
//    for(const auto&e:hash)
//    {
//        ret.push_back(e.second);
//    }
//    return vector<string>(ret.rbegin(),ret.rend());

    //也可以将身高和名字放入一个pair中，然后按照身高进行排序。
//    vector<pair<int,string>> v;
//    for(int i=0;i<names.size();i++)
//    {
//        v.push_back({heights[i],names[i]});
//    }
//    sort(v.begin(),v.end(),[]
//            (const pair<int,string>& p1,const pair<int,string>& p2)
//    { return p1.first>p2.first;});
//    vector<string> ret;
//    for(const auto&e:v)
//    {
//        ret.push_back(e.second);
//    }
//    return ret;
}

//最长回文串
//贪心策略：
//1.统计每个字符的出现次数
//2.统计出现次数为偶数的字符的总长度
//3.如果有出现次数为奇数的字符，取其中的最大偶数部分
//4.如果有出现次数为奇数的字符，在中间再添加一个字符
int longestPalindrome(string s) {
    unordered_map<char,int> hash;
    for(const auto&e:s) hash[e]++;
    int mid=-1,len=0;
    bool hasOdd=false;
    for (const auto& e : hash) {
        if (e.second % 2 == 0) {
            // 偶数次数的字符可以全部使用
            len += e.second;
        } else {
            // 奇数字符可以使用其偶数部分（次数-1）
            len += e.second - 1;
            hasOdd = true;  // 存在奇数字符
        }
    }

    // 如果有奇数字符，可以在中间再添加一个字符
    if (hasOdd) {
        len += 1;
    }
    return len;
}

//经典的田忌赛马问题，使用贪心算法来最大化优势。
//思路：
//1.先对 nums1 和 nums2 进行排序。
//2.使用双指针遍历 nums1 和 nums2，比较当前 nums1 的元素和 nums2 的元素。
//3.如果 nums1[i] > nums2[left]，说明 nums1[i] 可以战胜 nums2[left]，将 nums1[i] 放入结果数组，并将 left 指针向右移动。
//4.如果 nums1[i] <= nums2[left]，说明 nums1[i] 无法战胜 nums2[left]，将 nums1[i] 放入结果数组，并将 right 指针向左移动。
vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    //田忌赛马的翻版，想要以最大化优势赢得比赛：
    //1.先排序 2.用双指针一一进行比较，如果不满足nums1[i] > nums2[i]，将这个数换掉num2中最大的数
    //如果满足nums1[i] > nums2[i]直接加入即可
    vector<pair<int,int>> num2;
    vector<int> ret(nums2.size());
    for(int i=0;i<nums2.size();i++)
    {
        num2.push_back({nums2[i],i});
    }
    sort(nums1.begin(),nums1.end());
    sort(num2.begin(),num2.end(),[](const pair<int,int>& p1,const pair<int,int>& p2)
    { return p1.first<p2.first;});
    int left=0,right=nums1.size()-1;
    for(int i=0;i<nums1.size();i++)
    {
        if(nums1[i]>num2[left].first)
        {
            ret[num2[left++].second]=nums1[i];
        }
        else
        {
            ret[num2[right--].second]=nums1[i];
        }
    }
    return ret;
}

//增减字符串匹配问题，给定一个字符串 s，包含 'I' 和 'D'，表示增减关系。
//'I' 表示当前数字比前一个数字大，'D' 表示当前数字比前一个数字小。
//贪心策略：I代表增加，D代表减少，每次都选择当前最小或最大可用数字。
vector<int> diStringMatch(string s) {
    //标记一下最大可用数字&最小可用数字
    int minnum=0,maxnum=s.size();
    vector<int> ret;
    for(const auto&e:s)
    {
        if(e=='I') ret.push_back(minnum++);
        else ret.push_back(maxnum--);
    }
    ret.push_back(minnum++);
    return ret;
}

//分配饼干问题，有点类似于田忌赛马，但是不需要保留下标
//先进行排序，一直找到满足 g[index1]<=s[index2] 的情况，
//如果满足就将 index1 和 index2 都加一，表示这个孩子得到了饼干。
//如果不满足，就将 index2 加一，表示这个饼干被丢弃了。
//最后返回满足条件的孩子数量。
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    int index1=0,index2=0,ret=0;
    while(index1<g.size()&&index2<s.size())
    {
        if(g[index1]<=s[index2])
        {
            ret++;
            index1++;index2++;
        }
        else index2++;
    }
    return ret;
}

//加括号的问题，贪心策略：
//1.如果只有一个数，直接返回这个数。
//2.如果只有两个数，返回 a/b 的形式。
//3.如果有多个数，返回 a/(b/c/d/...) 的形式。
string optimalDivision(vector<int>& nums) {
    if(nums.size()==1) return to_string(nums[0]);
    if(nums.size()==2) return to_string(nums[0])+"/"+to_string(nums[1]);
    string ret;
    for(int i=0;i<nums.size();i++)
    {
        ret+=to_string(nums[i]);
        if(i==0) ret+="/(";
        else if(i==nums.size()-1) ret+=")";
        else ret+="/";
    }
    return ret;
}

//非常特殊的贪心，采用层序遍历的方式来贪心，
//每次都取当前能跳的最远的位置，
//如果能跳的最远的位置大于等于数组的长度，说明可以到达数组的末尾，直接返回当前的步数。
//如果不能到达数组的末尾，就将当前的步数加一，
//并将当前的位置更新为能跳的最远的位置，继续遍历。
int jump(vector<int>& nums)
{
    //采用层序遍历的方式来贪心
    int step=0,left=0,right=0,maxpos=0,n=nums.size();
    while(left<=right)
    {
        if(maxpos>=n-1) return step;//如果能跳到最后一个位置之后，都可以返回
        for(int i=left;i<=right;i++)
        {
            maxpos=max(maxpos,i+nums[i]);
        }

        left=right+1;//下一层的左边界
        right=maxpos;//下一层的右边界
        step++;
    }
    return -1;
}

//跳跃游戏1，原理跟上面一摸一样
bool canJump(vector<int>& nums) {
    int left=0,right=0,maxpos=0,n=nums.size();
    while(left<=right)
    {
        if(maxpos>=n-1) return true;
        for(int i=left;i<=right;i++){
            maxpos=max(maxpos,i+nums[i]);
        }
        left=right+1;right=maxpos;
    }
    return false;
}

//加油站，非常巧妙的优化方法
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n=gas.size();
    for(int i=0;i<n;i++)
    {
        int start=i,free=0,step=0;
        while(free+gas[start]>=cost[start])
        {
            free=free+gas[start]-cost[start];
            start++;step++;
            start%=n;
            if(start==i) return i;
        }
        //记录一下step步数，直接从i+step的下一个开始判断是否可以轮一圈，当走了step步后才不能进行下去
        //则i到i+step都没必要走了，直接从i+step+1开始
        i=i+step;
    }
    return -1;
}

//单调递增的数字：
//常规解法：
//从n开始到0，找到最大的单调递增的数字，
//时间复杂度：O(nlogn)
//贪心解法：
//1.如果当前数字大于下一个数字，就将当前数字减一，
//并将当前数字后面的所有数字都设为9。
//2.如果当前数字小于等于下一个数字，就直接跳过。
int monotoneIncreasingDigits(int n) {
    string s=to_string(n);
    char front=s[0];
    for(int i=1;i<s.size();i++)
    {
        //找到第一次下降的地方
        if(front>s[i])
        {
            int index=i-1;
            while(index-1>=0&&s[index-1]==s[index]) index--;//如果有重复的数就找到第一个减一
            s[index]-=1;
            for(int j=index+1;j<s.size();j++) s[j]='9';
            return stoi(s);
        }
        else front=s[i];
    }
    return stoi(s);
}

//坏掉的计算器
int brokenCalc(int startValue, int target) {
    //采用正难则反的策略
    int step=0,start=target,end=startValue;
    while(start!=end)
    {
        //反过来则采用/2和+1的方式
        if(start<=end) start++;//end比start大只能+1
        else
        {
            if(start%2) start++;
            else start/=2;
        }
        step++;
    }
    return step;
}

//合并区间，区间问题！非常经典！
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    //本质上就是求并集：
    //1.首先按照左端点排序
    //2.以第一个区间的右断点作为judge，如果<=judge说明可以合并，更新右端点的最大值
    //3.如果>judge说明不能合并，单开一个vector
    vector<vector<int>> ret;
    vector<pair<int,int>> tmp;
    for(const auto&e:intervals) tmp.push_back({e[0],e[1]});
    sort(tmp.begin(),tmp.end());//按照左端点排序
    for(int i=0;i<tmp.size();i++)
    {
        int right=tmp[i].second;//初始的右端点
        vector<int> v;
        v.push_back(tmp[i].first);
        //一直合并左端点小于等于right的区间
        while(i+1<tmp.size() && tmp[i+1].first<=right)
        {
            i++;
            right=max(right,tmp[i].second);//更新右端点的最大值
        }
        v.push_back(right);
        ret.push_back(v);
    }
    return ret;
}

//无重叠区间：
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    //区间问题还是需要先排序，按照左端点排序
    int ret=0;
    vector<pair<int,int>> tmp;
    for(const auto&e:intervals) tmp.push_back({e[0],e[1]});
    sort(tmp.begin(),tmp.end());//按照左端点排序
    for(int i=0;i<tmp.size();i++)
    {
        int right=tmp[i].second;
        while(i+1<tmp.size() && tmp[i+1].first<right)
        {
            i++;
            ret++;//删掉较大的那一个区间
            right=min(right,tmp[i].second);//更新右端点的最小值
        }
    }
    return ret;
}

//注意这题是求交集，不是求并集
//[__________]
//       [__________]
//       [___]
//后续如果有交集，只需更新右端点的最小值
int findMinArrowShots(vector<vector<int>>& points) {
    int ret=0;
    sort(points.begin(),points.end());
    for(int i=0;i<points.size();i++)
    {
        //这里是求交集
        int left=points[i][0],right=points[i][1];//选取右端点作为judge
        int count=0;
        while(i+1<points.size()&&points[i+1][0]<=right)
        {
            i++;count++;
            if(count==1)
            {
                //如果是第一次就求出交集
                left=max(left,points[i][0]);
                right=min(right,points[i][1]);
            }
            else
            {
                right=min(right,points[i][1]);
            }
        }
        ret++;
    }
    return ret;
}

//递归比贪心好想的一道题：
int step=INT_MAX;
//先用递归试试看？貌似可以
void dfs(long long n,int count)
{
    if(n==1)
    {
        step=min(step,count);
        return ;
    }
    count++;
    if(n%2)
    {
        dfs(n+1,count);
        dfs(n-1,count);
    }
    else dfs(n/2,count);
}
int integerReplacement(long long n) {
    int count=0;
    dfs(n,count);
    return step;
}
//可以使用记忆化搜索改善！数据量大可以使用哈希表！
int integerReplacement1(int n) {
    //贪心太难想了，不必掌握吧？
    int ret = 0;
    while(n > 1)
    {
        // 分类讨论
        //如果是偶数直接/2
        if(n % 2 == 0)
        {
            ret++;
            n /= 2;
        }
        else
        {
            //如果是奇数就要选择+1还是-1
            //需要对3进行特殊处理
            if(n == 3)
            {
                ret += 2;
                n = 1;
            }
            else if(n % 4 == 1)
            {
                ret += 2;
                n /= 2;
            }
            else
            {
                ret += 2;
                n = n / 2 + 1;
            }
        }
    }
    return ret;
}

//俄罗斯套娃问题：（其实就是最长递增子序列plus版本）
int maxEnvelopes(vector<vector<int>>& envelopes) {
    //如果用动态规划处理，那么就类似于最长递增子序列的翻版
    int n=envelopes.size(),ret=0;
    sort(envelopes.begin(),envelopes.end());
    vector<int> dp(n,1);
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i+1;j<n;j++)
        {
            if(envelopes[i][0]<envelopes[j][0]&&envelopes[i][1]<envelopes[j][1])
            {
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        ret=max(ret,dp[i]);
    }
    return ret;
}
//下面是贪心的具体做法：
class Compar
{
public:
    bool operator()(const vector<int>& v1,const vector<int>& v2)
    {
        // 排序规则是关键：
        // 左端点不同时，按左端点从小到大排：保证处理顺序是 “左端点递增”
        // 左端点相同时，按右端点从大到小排：若左端点相同，保留右端点大的，能为后续构造更长 LIS 提供更多可能性
        // （大右端点更难被后续小元素 “截断”，小右端点会被大右端点覆盖，无需额外处理）。
        return v1[0]!=v2[0] ? v1[0]<v2[0] : v1[1]>v2[1];
    }
};
class solution {
    int bs(const vector<int>& v,int target)
    {
        int left=0,right=v.size()-1;
        while(left<right)
        {
            int mid=left+(right-left)/2;
            if(v[mid]<target) left=mid+1;
            else right=mid;
        }
        return left;
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        vector<int> ret;
        sort(envelopes.begin(),envelopes.end(),Compar());
        //排序后变成只考虑右端点的最长递增子序列问题
        ret.push_back(envelopes[0][1]);
        for(int i=1;i<envelopes.size();i++)
        {
            if(envelopes[i][1]>ret.back()) ret.push_back(envelopes[i][1]);
            else ret[bs(ret,envelopes[i][1])]=envelopes[i][1];
        }
        return ret.size();
    }
};

//取数字，感觉还行
int maxSumDivThree(vector<int>& nums) {
    int ret=0;
    priority_queue<int,vector<int>,greater<int>> one;//存放%1的数字
    priority_queue<int,vector<int>,greater<int>> two;//存放%2的数字
    for(const auto&e:nums)
    {
        ret+=e;
        if(e%3==1) one.push(e);
        if(e%3==2) two.push(e);
    }
    if(ret%3==0) return ret;
    else if(ret%3==1)
    {
        //余1取走one堆中最小与两个two堆元素最小的数字
        int first=INT_MAX,second=INT_MAX,top1=0,top2=0;
        if(one.size())
        {
            second=one.top();
        }
        if(two.size()>=2)
        {
            top1=two.top();two.pop();
            top2=two.top();
            first=top1+top2;
        }
        ret-=min(first,second);
    }
    else
    {
        //余2取走two堆中最小与两个one堆元素最小的数字
        int first=INT_MAX,second=INT_MAX,top1=0,top2=0;
        if(two.size())
        {
            second=two.top();
        }
        if(one.size()>=2)
        {
            top1=one.top();one.pop();
            top2=one.top();
            first=top1+top2;
        }
        ret-=min(first,second);
    }
    return ret;
}

//重新安排条形码，使其中任意两个相邻的元素不相等
vector<int> rearrangeBarcodes(vector<int>& barcodes) {
    unordered_map<int,int> hash;//使用哈希表统计次数
    for(const auto&e:barcodes) hash[e]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>,
            function<bool(const pair<int,int>&, const pair<int,int>&)>> heap
            (hash.begin(), hash.end(),
             [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.second < p2.second;});
    vector<int> ret(barcodes.size(),0);
    //先将出现次数最多的排在偶数位
    int index=0;
    pair<int,int> count=heap.top();heap.pop();
    while(count.second)
    {
        ret[index]=count.first;
        index+=2;
        count.second--;
    }
    index=1;
    //每次取次数最多的进行插空排列
    //尽管剩下的数以循环的方式不受次数限制随便排列也可以，
    //但是我坚持取出堆中次数最多的元素进行插入，这样可以保证交替插入
    while(heap.size())
    {
        count=heap.top();heap.pop();
        if(ret[index]!=0) index++;
        ret[index++]=count.first;
        count.second--;
        if(count.second!=0) heap.push(count);
    }
    return ret;
}

//翻版，需要判断是否可以重排
string reorganizeString(string barcodes) {
    unordered_map<char,int> hash;//使用哈希表统计次数
    for(const auto&e:barcodes) hash[e]++;
    priority_queue<pair<char,int>, vector<pair<char,int>>, function<bool(const pair<char,int>&, const pair<char,int>&)>> heap(
            hash.begin(), hash.end(), [](const pair<char,int>& p1, const pair<char,int>& p2) { return p1.second < p2.second;});
    string ret(barcodes.size(),0);
    //先将出现次数最多的排在偶数位
    int index=0;
    pair<char,int> count=heap.top();heap.pop();
    if(count.second>(barcodes.size()+1)/2) return "";//如果出现最多的次数大于(n+1)/2（2个为一组的组数），根据鸽巢原理，必定会出现重复的数
    while(count.second)                              //如果出现最多的次数小于(n+1)/2，每一组分不够一个，也可以重排
    {
        ret[index]=count.first;
        index+=2;
        count.second--;
    }
    index=1;
    //每次取次数最多的进行插空排列
    //尽管剩下的数以循环的方式不受次数限制随便排列也可以，
    //但是我坚持取出堆中次数最大的元素进行插入
    while(heap.size())
    {
        count=heap.top();heap.pop();
        if(ret[index]!=0) index++;
        ret[index++]=count.first;
        count.second--;
        if(count.second!=0) heap.push(count);
    }
    return ret;
}

//int main()
//{
//    cout<<reorganizeString("aaaabbcccdefffggg");
//    return 0;
//}
