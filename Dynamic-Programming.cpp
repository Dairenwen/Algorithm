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

//动态规划（Dynamic Programming, DP）其核心步骤可以归纳为以下五个：
//1. 定义状态（Define the State）
//核心：将原问题拆解为若干个子问题，用一个或多个变量描述子问题的 “状态”，即子问题的关键特征。
//目标：找到一个清晰的状态定义，使得每个状态对应一个子问题的解。
//示例：
//在 “斐波那契数列” 问题中，状态可定义为 dp[i] 表示第 i 个斐波那契数；
//在 “最长递增子序列” 问题中，状态可定义为 dp[i] 表示以第 i 个元素结尾的最长递增子序列长度。

//2. 确定状态转移方程（Formulate the Transition）(推导状态转移公式非常重要！)
//核心：找到不同状态之间的依赖关系，即如何通过 “更小的子问题的解” 推导出 “当前问题的解”。
//目标：建立一个递推公式，描述 dp[i]（当前状态）与 dp[j]（前置状态，j < i）的关系。
//示例：
//斐波那契数列的转移方程为 dp[i] = dp[i-1] + dp[i-2]；
//爬楼梯问题（一次可爬 1 或 2 阶）中，dp[i] = dp[i-1] + dp[i-2]（到达第 i 阶的方法数 = 到达第 i-1 阶 + 到达第 i-2 阶）。

//3. 确定初始条件（Base Case）
//核心：定义最小子问题的解（无法再分解的子问题），作为递推的起点。
//目标：避免无限递归，确保状态转移方程有明确的计算起点。
//示例：
//斐波那契数列的初始条件为 dp[0] = 0, dp[1] = 1；
//爬楼梯问题中，dp[0] = 1（起点也算 1 种方法），dp[1] = 1（只有 1 种爬法）。

//4. 确定计算顺序（Order of Computation）
//核心：根据状态依赖关系，确定计算状态的先后顺序，确保计算当前状态时，其依赖的所有前置状态已被求解。
//目标：避免因前置状态未计算而导致的错误。
//常见顺序：
//自底向上（从小到大）：先解决最小子问题，逐步推导更大的问题（如斐波那契数列从 i=2 计算到 i=n）。
//自顶向下（从大到小）：结合记忆化（Memoization），递归求解大问题时缓存子问题的解（如递归计算斐波那契数时缓存已计算的结果）。

//5. 确定最终解的形式（Result Extraction）
//核心：明确原问题的解对应哪个状态（或哪些状态的组合）。
//目标：从计算得到的状态中提取出原问题的答案。
//示例：
//斐波那契数列中，原问题 “第 n 个斐波那契数” 的解就是 dp[n]；
//最长递增子序列问题中，最终解是 dp 数组中的最大值（而非最后一个元素）。


//1. 状态表?：
//这道题可以「根据题?的要求」直接定义出状态表?：
//dp[i] 表?：第 i 个泰波那契数的值。
//2. 状态转移?程：
//dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3]
//3. 初始化：
//从我们的递推公式可以看出， dp[i] 在 i = 0 以及 i = 1 的时候是没有办法进?推导的，因为 dp[-2] 或 dp[-1] 不是?个有效的数据。
//因此我们需要在填表之前，将 0, 1, 2 位置的值初始化。题?中已经告诉我们 dp[0] = 0,dp[1] = dp[2] = 1 。
//4. 填表顺序：
//毫?疑问是「从左往右」。
//5. 返回值：
//应该返回 dp[n] 的值。
int tribonacci(int n) {
    //动态规划！
    vector<int> dp(38);
    dp[0]=0;dp[1]=dp[2]=1;
    for(int i=3;i<=n;i++)
    {
        dp[i]=dp[i-3]+dp[i-2]+dp[i-1];
    }
    return dp[n];

    //空间优化：
    int a=0,b=1,c=1;
    if(n==0) return a;
    if(n==1) return b;
    if(n==2) return c;
    for(int i=3;i<=n;i++)
    {
        int tmp=a+b+c;
        a=b;
        b=c;
        c=tmp;
    }
    return c;
}

//相同的原理，上台阶问题，注意需要取模！将a+b+c%1000000007！
//也可以%1e9+7
int waysToStep(int n) {
    //可以直接使用动态规划&空间优化：
    const int MOD=1e9+7;//1000000007可以这样表示！
    int a=1,b=2,c=4;
    if(n==1) return a;
    if(n==2) return b;
    if(n==3) return c;
    for(int i=4;i<=n;i++)
    {
        int tmp=((a+b)%(MOD)+c)%(MOD);
        a=b;b=c;c=tmp;
    }
    return c;
}

//非常类似于爬楼梯问题，但是这里dp中保存的是前两个花费的最小值+走这一步需要的花费
//最后由于倒数第一个和倒数第二个dp元素都可以到达，所以返回这两个元素的最小值即可
int minCostClimbingStairs(vector<int>& cost) {
    int n=cost.size();
    vector<int> dp(n);
    dp[0]=cost[0];dp[1]=cost[1];
    for(int i=2;i<n;i++)
    {
        dp[i]=min(dp[i-2],dp[i-1])+cost[i];
    }
    return min(dp[n-1],dp[n-2]);
}
//状态表示要敢于下手！万一是对的呢？

//虽说是爬楼梯的变形，但是好难啊！（解码方法）
int numDecodings(string s) {
    int n=s.size();
    vector<int> dp(n,0);
    if(s[0]=='0') dp[0]=0;
    else dp[0]=1;
    if(n==1) return dp[0];//注意边界情况的处理

    //初始化dp[0]和dp[1]
    if(s[0]!='0'&&s[1]!='0') dp[1]++;
    int judge=(s[0]-'0')*10+s[1]-'0';
    if(judge>=10&&judge<=26) dp[1]++;

    for(int i=2;i<n;i++)
    {
        if(s[i]!='0') dp[i]+=dp[i-1];
        int judge=(s[i-1]-'0')*10+s[i]-'0';
        if(judge>=10&&judge<=26) dp[i]+=dp[i-2];
    }
    return dp[n-1];

    //可以多开一个空间进行优化：
    vector<int> dp1(n+1,0);
    dp1[0]=1;//！注意虚拟节点的赋值！
    if(s[0]=='0') dp1[1]=0;
    else dp1[1]=1;
    //将初始化和填表融合在一起
    for(int i=2;i<=n;i++)
    {
        //下标代表第几个数
        if(s[i-1]!='0') dp1[i]+=dp1[i-1];
        int judge=(s[i-2]-'0')*10+s[i-1]-'0';
        if(judge>=10&&judge<=26) dp1[i]+=dp1[i-2];
    }
    return dp1[n];
}

//二维数组dp！注意初始化，这是经典的路径问题
int uniquePaths(int m, int n) {
    //来！搞一个二维dp数组
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    //进行初始化
    // dp[0][0]=dp[0][1]=dp[1][0]=0;前面初始化已经设定了
    dp[0][1]=1;//注意虚拟节点的初始化
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[m][n];
}

//路径问题plus，注意原数组为1的话，说明有障碍物，不能走，dp[i][j]处理为0
//其次是初始化，依然是dp[0][1]=1，
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int row=obstacleGrid.size(),col=obstacleGrid[0].size();
    vector<vector<int>> dp(row+1,vector<int>(col+1,0));
    dp[0][1]=1;
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=col;j++)
        {
            if(obstacleGrid[i-1][j-1]) dp[i][j]=0;
            else dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[row][col];
}

//还是路径问题：注意状态转移方程，dp[i][j]=max(dp[i-1][j],dp[i][j-1])+frame[i-1][j-1];
int jewelleryValue(vector<vector<int>>& frame) {
    int r=frame.size(),c=frame[0].size();
    vector<vector<int>> dp(r+1,vector(c+1,0));
    //dp[0][1]=frame[0][0];注意这里不需要初始化！直接融入填表中
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i][j-1])+frame[i-1][j-1];
        }
    }
    return dp[r][c];
}

//二维dp非常特殊的初始化方式，需要多开两列！
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n=matrix.size();
    vector<vector<int>> dp(n+1,vector<int>(n+2,0));
    //需要多开两列，第一行初始化为0，其他两列初始化为INT_MAX
    for(int i=1;i<=n;i++)
    {
        dp[i][0]=dp[i][n+1]=INT_MAX;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            //选择三个方向最小的进行填表
            dp[i][j]=min(min(dp[i-1][j+1],dp[i-1][j]),dp[i-1][j-1])+matrix[i-1][j-1];
        }
    }
    //最后需要找出最后一行的最小值！而不是直接返回dp[n][n]
    int ret=INT_MAX;
    for(int i=1;i<=n;i++) ret=min(ret,dp[n][i]);
    return ret;
}

//最小路径和，与上一题非常相似，但是请注意初始化的方式！
int minPathSum(vector<vector<int>>& grid) {
    int r=grid.size(),c=grid[0].size();
    vector<vector<int>> dp(r+1,vector<int>(c+1,INT_MAX));
    dp[0][1]=0;//这里虚拟节点的值非常重要！
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i-1][j-1];
        }
    }
    return dp[r][c];
}

//二维dp的特殊情况
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int r=dungeon.size(),c=dungeon[0].size();
    //注意这题在最后一行加上行，最后一列加上列
    vector<vector<int>> dp(r+1,vector<int>(c+1,INT_MAX));
    dp[r-1][c]=1;//进行初始化
    //二维dp进行反向填表
    //dp[i][j]表示从当前位置出发，到达终点，所需的最低初始健康点数
    for(int i=r-1;i>=0;i--)
    {
        for(int j=c-1;j>=0;j--)
        {
            //max是为了处理健康点数可能为负数，将其设为1
            dp[i][j]=max(1,min(dp[i+1][j],dp[i][j+1])-dungeon[i][j]);
        }
    }
    return dp[0][0];
}


//简单多状态dp问题////////////////////////////////////////////////////////////
//1. 状态定义（核心逻辑）
//f[i]：表示考虑前 i 个预约（0~i），且接受第 i 个预约时的最大总时长。
//g[i]：表示考虑前 i 个预约（0~i），且不接受第 i 个预约时的最大总时长。
//2. 递推关系（保证不选相邻元素）
//对于 f[i] 由于不能接受相邻预约，第 i-1 个预约必须不被接受，因此只能从 g[i-1]（不接受 i-1）的状态转移而来，即：f[i] = g[i-1] + nums[i]（加上当前预约的时长）。
//对于 g[i] 此时第 i-1 个预约可以接受也可以不接受，取两种情况的最大值即可，即：g[i] = max(f[i-1], g[i-1])。
//3. 初始化与边界处理
//当没有预约时（n=0），直接返回 0，符合逻辑。
//当只有 1 个预约时（i=0）：f[0] = nums[0]（接受这个预约），g[0] 隐含为 0（不接受这个预约），最终结果取两者最大值（即 nums[0]）。
//4. 最终结果
//最后一个预约有两种可能：接受或不接受。因此返回 max(f[n-1], g[n-1])
int massage(vector<int>& nums) {
    int n=nums.size();
    if(n==0) return 0;
    vector<int> fx(n);
    vector<int> gx(n);
    fx[0]=nums[0];
    gx[0]=0;
    for(int i=1;i<n;i++)
    {
        fx[i]=gx[i-1]+nums[i];
        gx[i]=max(gx[i-1],fx[i-1]);
    }
    return max(fx[n-1],gx[n-1]);
}

//打家劫舍1：
//与简单dp非常相似的一道题目，就当复习了
//还是设置两张dp表
int rob1(vector<int>& nums) {
    //与简单dp非常相似的一道题目，就当复习了
    //还是设置两张dp表
    int n=nums.size();
    vector<int> f(n,0),g(n,0);
    f[0]=nums[0];g[0]=0;
    for(int i=1;i<n;i++)
    {
        f[i]=g[i-1]+nums[i];
        g[i]=max(f[i-1],g[i-1]);
    }
    return max(f[n-1],g[n-1]);
}

//打家劫舍2：.
//偷第?个房屋时的最??额 x ，此时不能偷最后?个房?，因此就是偷 [0, n - 2] 区间的房?；
//不偷第?个房屋时的最??额 y ，此时可以偷最后?个房?，因此就是偷 [1, n - 1] 区间的房?；
//两种情况下的「最?值」，就是最终的结果
int rob2(vector<int>& nums) {
    int n=nums.size();
    if(nums.size()==1) return nums[0];
    vector<int> f(n,0),g(n,0);
    f[0]=nums[0];g[0]=0;
    for(int i=1;i<n-1;i++)
    {
        f[i]=g[i-1]+nums[i];
        g[i]=max(f[i-1],g[i-1]);
    }
    int tmp=max(f[n-2],g[n-2]);
    f.clear();g.clear();
    f[0]=nums[1];g[0]=0;
    for(int i=1;i<n-1;i++)
    {
        f[i]=g[i-1]+nums[i+1];
        g[i]=max(f[i-1],g[i-1]);
    }
    return max(tmp,max(f[n-2],g[n-2]));
}

//删除并获得点数
int deleteAndEarn(vector<int>& nums) {
    //想办法将问题转换为打家劫舍模型，统计每一个数字出现的总和，放进数组中，下标代表这个数
    //相邻之间的数不能获得点数
    sort(nums.begin(),nums.end());//先排序，方便统计
    vector<int> rev(nums.back()+1,0),f(nums.back()+1,0),g(nums.back()+1,0);
    for(const auto&e:nums) rev[e]+=e;
    int n=rev.size();
    f[0]=rev[0];g[0]=0;
    for(int i=1;i<n;i++)
    {
        f[i]=g[i-1]+rev[i];
        g[i]=max(f[i-1],g[i-1]);
    }
    return max(f[n-1],g[n-1]);
}

//还是打家劫舍的问题，没有转换过来，时间太久了，这次是i-2 i-1 i+1 i+2都不能连续访问，其实更改几处就可以了，存在超时的问题，未优化
long long maximumTotalDamage(vector<int>& power) {
    sort(power.begin(),power.end());
    int n=power.back();
    vector<int> sum(n+2,0),c(n+2,0),nc(n+2,0);
    for(const auto&e:power) sum[e]+=e;//下标就代表咒语
    c[0]=sum[0];c[1]=sum[1];
    nc[0]=0;nc[1]=max(nc[0],c[0]);
    for(int i=2;i<=n+1;i++)
    {
        c[i]=nc[i-2]+sum[i];
        nc[i]=max(max(c[i-1],nc[i-1]),max(c[i-2],nc[i-2]));
    }
    return max(c[n+1],nc[n+1]);
}


//小小粉刷竟敢班门弄斧？拿下！
//动态规划状态定义：
//定义了 3 个状态数组：
//dp1[i]：第 i 栋房子刷颜色 0（第一列）时的最小总花费
//dp2[i]：第 i 栋房子刷颜色 1（第二列）时的最小总花费
//dp3[i]：第 i 栋房子刷颜色 2（第三列）时的最小总花费
//状态转移方程：
//对于第 i 栋房子，选择某种颜色的花费 = 该颜色的成本 + 上一栋房子刷不同颜色的最小花费：
//dp1[i] = min(dp2[i-1], dp3[i-1]) + costs[i][0]（当前刷颜色 0，上一栋只能刷 1 或 2）
//同理推导 dp2[i] 和 dp3[i]
//初始化：
//第一栋房子（i=0）的花费就是其本身的成本，即 dp1[0] = costs[0][0] 等。
//结果：
//最后一栋房子（i=n-1）的 3 种颜色花费中的最小值，就是全局最小总花费。
int minCost(vector<vector<int>>& costs) {
    int n=costs.size();
    vector<int> dp1(n),dp2(n),dp3(n);
    dp1[0]=costs[0][0];
    dp2[0]=costs[0][1];
    dp3[0]=costs[0][2];
    for(int i=1;i<n;i++)
    {
        dp1[i]=min(dp2[i-1],dp3[i-1])+costs[i][0];
        dp2[i]=min(dp1[i-1],dp3[i-1])+costs[i][1];
        dp3[i]=min(dp1[i-1],dp2[i-1])+costs[i][2];
    }
    return min(dp1[n-1],min(dp2[n-1],dp3[n-1]));
}

//股票问题//////////////////////////////////////////////
//1. 状态定义
//dp1[i]：第 i 天结束时处于「持有股票」状态的最大利润（可能是当天买入，或之前买入后一直持有）。
//dp2[i]：第 i 天结束时处于「可交易」状态的最大利润（不持有股票，且当天不是冷冻期，可以随时买入）。
//dp3[i]：第 i 天结束时处于「冷冻期」状态的最大利润（当天卖出了股票，次日不能买入）。
//2. 状态转移逻辑
//dp1[i]（持有股票）：
//有两种可能来源：
//① 前一天已经持有股票（dp1[i-1]），今天继续持有，利润不变；
//② 前一天处于可交易状态（dp2[i-1]），今天买入股票，利润减少当前股价（-prices[i]）。
//取两者最大值：dp1[i] = max(dp1[i-1], dp2[i-1] - prices[i])。
//dp2[i]（可交易状态）：
//有两种可能来源：
//① 前一天已经处于可交易状态（dp2[i-1]），今天继续保持，利润不变；
//② 前一天处于冷冻期（dp3[i-1]），今天冷冻期结束，恢复可交易状态，利润不变。
//取两者最大值：dp2[i] = max(dp2[i-1], dp3[i-1])。
//dp3[i]（冷冻期）：
//只有一种可能：前一天持有股票（dp1[i-1]），今天卖出股票，利润增加当前股价（+prices[i]）。
//因此：dp3[i] = dp1[i-1] + prices[i]。
//3. 初始化
//第 0 天（i=0）：若持有股票（dp1[0]），只能是当天买入，利润为 -prices[0]；
//可交易状态（dp2[0]）：未进行任何操作，利润为 0；
//冷冻期（dp3[0]）：当天无法卖出（刚买入或未操作），利润为 0。
int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<int> dp1(n),dp2(n),dp3(n);
    dp1[0]=-prices[0];//买入状态
    dp2[0]=0;//可交易状态
    dp3[0]=0;//不可交易状态（冷冻期）
    for(int i=1;i<n;i++)
    {
        //「买入」「卖出」是瞬时动作（在某一时刻完成），而动态规划需要跟踪的是「当天结束时的稳定状态」。
        // 因此只能是持有股票的状态，可交易的状态，冷冻状态
        dp1[i]=max(dp1[i-1],dp2[i-1]-prices[i]);
        dp2[i]=max(dp2[i-1],dp3[i-1]);
        dp3[i]=dp1[i-1]+prices[i];
    }
    return max(dp1[n-1],max(dp2[n-1],dp3[n-1]));
}

//这一题没有冷冻期，只有持有状态和卖出状态
//1. 状态定义
//dp1[i]：第 i 天结束时处于「持有股票」状态的最大利润（可能是当天买入，或之前买入后一直持有）。
//dp2[i]：第 i 天结束时处于「可交易」状态的最大利润（不持有股票，且当天不是冷冻期，可以随时买入）。
//2. 状态转移逻辑
//dp1[i]（持有股票）：
//有两种可能来源：
//① 前一天已经持有股票（dp1[i-1]），今天继续持有，利润不变；
//② 前一天处于可交易状态（dp2[i-1]），今天买入股票，利润减少当前股价（-prices[i]）。
//取两者最大值：dp1[i] = max(dp1[i-1], dp2[i-1] - prices[i])。
//dp2[i]（可交易状态）：
//有两种可能来源：
//① 前一天已经处于可交易状态（dp2[i-1]），今天继续保持，利润不变；
//② 前一天处于持有期，今天卖出股票，利润增加当前股价（+prices[i]），并减去手续费。
//取两者最大值：dp2[i] = max(dp2[i-1], dp1[i-1] + prices[i] - fee)。
//3. 初始化
//第 0 天（i=0）：若持有股票（dp1[0]），只能是当天买入，利润为 -prices[0]；
//可交易状态（dp2[0]）：未进行任何操作，利润为 0。
int maxProfit1(vector<int>& prices, int fee) {
        int n=prices.size();
        vector<int> dp1(n),dp2(n);
        dp1[0]=-prices[0];//买入状态
        dp2[0]=0;//可交易状态
        for(int i=1;i<n;i++)
        {
            dp1[i]=max(dp1[i-1],dp2[i-1]-prices[i]);
            dp2[i]=max(dp2[i-1],dp1[i-1]+prices[i]-fee);
        }
        return max(dp1[n-1],dp2[n-1]);
}

//1. 问题背景
//目标是在股票价格数组 prices 中，通过最多两次买入卖出操作获得最大利润。（可以买卖0/1/2次）
//2. 状态定义
//定义两个二维 DP 数组，追踪两种核心状态：
//f[i][j]：第 i 天结束时，持有股票，且已完成 j 次交易的最大利润。
//g[i][j]：第 i 天结束时，不持有股票，且已完成 j 次交易的最大利润。
//其中：
//i 表示天数（0 到 n-1）。
//j 表示已完成的交易次数（0、1、2，因为最多允许 2 次交易）。
//3. 初始化
//第 0 天（i=0）：
//f[0][0] = -prices[0]：第 0 天买入股票（0 次交易完成，持有股票）
//g[0][0] = 0：第 0 天不买股票（0 次交易完成，不持有股票），利润为 0
//其他两张dp表 第一行元素（如 f[0][1]、g[0][2] 等）初始化为极小值 MIN，表示这些状态在第 0 天不可能存在。
//4. 状态转移
//从第 1 天（i=1）开始，根据前一天的状态更新当前状态：
//对于持有股票的状态 f[i][j]（j不改变，因为还没有完成交易）
//当天持有股票有两种可能：
//前一天已持有股票，当天未操作：f[i-1][j]。
//前一天不持有股票，当天买入：g[i-1][j] - prices[i]（用前一天不持有股票的利润减去当前买入成本）。
//取两种情况的最大值：
//f[i][j] = max(f[i-1][j], g[i-1][j] - prices[i])

//对于不持有股票的状态 g[i][j]
//当天不持有股票分两种情况：
//若 j=0（0 次交易完成）：只能是前一天也不持有股票且 0 次交易，即 g[i][0] = g[i-1][0]。（主要是为了处理越界情况）
//若 j>0（1 或 2 次交易完成）：有两种可能：
//前一天已不持有股票，当天未操作：g[i-1][j]。
//前一天持有股票，当天卖出（完成第 j 次交易）：f[i-1][j-1] + prices[i]（用前一天持有股票的利润加上当前卖出收益）。
//取两种情况的最大值：
//g[i][j] = max(g[i-1][j], f[i-1][j-1] + prices[i])（当 j>0 时）
//5. 结果计算
//取这些状态的最大值作为结果：
//ret = max(f[n-1][0..2], g[n-1][0..2])
int maxProfit2(vector<int>& prices) {
    const int MIN=-0x3f3f3f3f;//0x3f3f3f3f是一个很大的数，用来表示负无穷，加上任意的数也不会溢出
    int n=prices.size();
    vector<vector<int>> f(n,vector<int>(3,MIN)),g(n,vector<int>(3,MIN));
    f[0][0]=-prices[0];g[0][0]=0;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            f[i][j]=max(f[i-1][j],g[i-1][j]-prices[i]);
            if(j>0) g[i][j]=max(g[i-1][j],f[i-1][j-1]+prices[i]);
            else g[i][j]=g[i-1][j];
        }
    }
    int ret=f[n-1][0];
    for(int i=0;i<3;i++)
    {
        if(f[n-1][i]>ret) ret=f[n-1][i];
        if(g[n-1][i]>ret) ret=g[n-1][i];
    }
    return ret;
}
//k次交易，无非就是将3改为k+1，没变！
int maxProfitk(int k, vector<int>& prices) {
    const int MIN=-0x3f3f3f3f;
    int n=prices.size();
    vector<vector<int>> f(n,vector<int>(k+1,MIN)),g(n,vector<int>(k+1,MIN));
    f[0][0]=-prices[0];g[0][0]=0;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<k+1;j++)
        {
            f[i][j]=max(f[i-1][j],g[i-1][j]-prices[i]);
            if(j>0) g[i][j]=max(g[i-1][j],f[i-1][j-1]+prices[i]);
            else g[i][j]=g[i-1][j];
        }
    }
    int ret=f[n-1][0];
    for(int i=0;i<k+1;i++)
    {
        if(f[n-1][i]>ret) ret=f[n-1][i];
        if(g[n-1][i]>ret) ret=g[n-1][i];
    }
    return ret;
}

//子数组问题//////////////////////////////////////////////////////////////////
//最大子数组和
//选择 1：不接上前边的子数组，单独以 nums[i] 作为子数组（对应 nums[i]）。
//选择 2：接上前边以 i-1 结尾的最大子数组（对应 dp[i-1] + nums[i]）。
//取两者的最大值，就是以 i 结尾的最优解。
int maxSubArray(vector<int>& nums) {
    int n=nums.size(),ret=nums[0];
    vector<int> dp(n);
    dp[0]=nums[0];
    for(int i=1;i<n;i++)
    {
        dp[i]=max(nums[i],dp[i-1]+nums[i]);
        ret=max(ret,dp[i]);
    }
    return ret;
}

//环形最大子数组和。从第一个元素开始创建n个长度的vector，再用上一题的思路求出最大值，
//这样做的时间复杂度为O(n^2)，会超时。
class Solution {
    int findsiglemax(vector<int>& nums)
    {
        int n=nums.size(),ret=nums[0];
        vector<int> dp(n);dp[0]=nums[0];
        for(int i=1;i<n;i++)
        {
            dp[i]=max(nums[i],dp[i-1]+nums[i]);
            ret=max(ret,dp[i]);
        }
        return ret;
    }
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n=nums.size(),ret=-0x3f3f3f3f;
        for(int i=0;i<n;i++)
        {
            vector<int> tmp;
            for(int j=0;j<n;j++)
            {
                tmp.push_back(nums[(i+j)%n]);
            }
            ret=max(ret,findsiglemax(tmp));
        }
        return ret;
    }
};
//优化：
//最后返回的是ret1和total-ret2的最大值，因为ret2是最小的子数组和，所以total-ret2是最大的子数组和。
//注意如果ret1<0，说明数组中所有元素都是负数，那么最大子数组和就是ret1，
//否则最大子数组和就是ret1和total-ret2的最大值。
//时间复杂度为O(n)，空间复杂度为O(n)。
int maxSubarraySumCircular(vector<int>& nums) {
    int n=nums.size(),ret1=nums[0],ret2=nums[0],total=0;
    for(const auto&e:nums) total+=e;
    vector<int> dp1(n);dp1[0]=nums[0];
    vector<int> dp2(n);dp2[0]=nums[0];
    for(int i=1;i<n;i++)
    {
        dp1[i]=max(nums[i],dp1[i-1]+nums[i]);
        dp2[i]=min(nums[i],dp2[i-1]+nums[i]);
        ret1=max(ret1,dp1[i]);
        ret2=min(ret2,dp2[i]);
    }
    return ret1<0 ? ret1 : max(ret1,total-ret2);//还要注意全是负数的情况
}

//最大子数组乘积，
//「最大乘积子数组」要求在整数数组中找到乘积最大的连续子数组。与最大子数组和不同，乘法的特殊性在于：
//负数 × 负数 = 正数（可能让小乘积变大）
//正数 × 负数 = 负数（可能让大乘积变小）
//因此，仅维护「当前最大乘积」是不够的，还需要追踪「当前最小乘积」（因为负的最小乘积乘以负数可能变成最大乘积）。
//2. 动态规划状态定义
//定义了两个 DP 数组：
//dp1[i]：以第 i 个元素为结尾的最大乘积子数组的乘积。
//dp2[i]：以第 i 个元素为结尾的最小乘积子数组的乘积（用于应对负数情况）。
//3. 状态转移逻辑（核心思路）
//根据当前元素 nums[i] 的正负性，分两种情况更新状态：
//当 nums[i] < 0 时：
//最大乘积 = max(nums[i], 前一个最小乘积 × nums[i])（因为负负得正，前一个最小乘积可能是负数，相乘后可能变大）。
//最小乘积 = min(nums[i], 前一个最大乘积 × nums[i])（正数 × 负数会变小，前一个最大乘积可能是正数，相乘后可能变最小）。
//当 nums[i] ≥ 0 时：
//最大乘积 = max(nums[i], 前一个最大乘积 × nums[i])（正数 × 正数会更大）。
//最小乘积 = min(nums[i], 前一个最小乘积 × nums[i])（正数 × 负数 / 小数会更小）。
//每次更新后，用 dp1[i] 刷新全局最大值 ret。
int maxProduct(vector<int>& nums) {
    int n=nums.size(),ret=nums[0];
    vector<int> dp1(n);dp1[0]=nums[0];
    vector<int> dp2(n);dp2[0]=nums[0];
    for(int i=1;i<n;i++)
    {
        if(nums[i]<0)
        {
            dp1[i]=max(nums[i],dp2[i-1]*nums[i]);
            dp2[i]=min(nums[i],dp1[i-1]*nums[i]);
        }
        else
        {
            dp1[i]=max(nums[i],dp1[i-1]*nums[i]);
            dp2[i]=min(nums[i],dp2[i-1]*nums[i]);
        }
        ret=max(ret,dp1[i]);
    }
    return ret;
}

//最长的乘积为正的子数组长度
//（1）当前元素为负数（nums[i-1] < 0）
//负数 × 负数 = 正数：若前一个位置有负乘积子数组（g[i-1] > 0），则当前正乘积长度 = 前序负乘积长度 + 1；否则无法形成正乘积（f[i] = 0）
//正数 × 负数 = 负数：当前负乘积长度 = 前序正乘积长度 + 1（即使前序正乘积长度为 0，当前元素自身也是一个负乘积子数组）
//（2）当前元素为正数（nums[i-1] > 0）
//正数 × 正数 = 正数：当前正乘积长度 = 前序正乘积长度 + 1（即使前序为 0，当前元素自身也是正乘积）
//负数 × 正数 = 负数：若前一个位置有负乘积子数组（g[i-1] > 0），则当前负乘积长度 = 前序负乘积长度 + 1；否则无法形成负乘积（g[i] = 0）
int getMaxLen(vector<int>& nums) {
    int n=nums.size(),ret=0;
    vector<int> f(n+1),g(n+1);
    for(int i=1;i<=n;i++)
    {
        if(nums[i-1]<0)
        {
            f[i]=g[i-1]>0 ? g[i-1]+1 : 0;
            g[i]=f[i-1]+1;
        }
        else if(nums[i-1]>0)
        {
            f[i]=f[i-1]+1;
            g[i]=g[i-1]>0 ? g[i-1]+1 : 0;
        }
        else
        {
            f[i]=0;
            g[i]=0;
        }
        ret=max(ret,f[i]);
    }
    return ret;
}

//等差数列划分
int numberOfArithmeticSlices(vector<int>& nums) {
    int n=nums.size(),ret=0;
    if(n<3) return 0;
    vector<int> dp(n,0);
    for(int i=2;i<n;i++)
    {
        if(nums[i-1]*2-nums[i-2]==nums[i]) dp[i]=dp[i-1]+1;
        else dp[i]=0;
        ret+=dp[i];//注意dp[i]表示的是以i为结尾的等差数列的个数，无法表示为一共有多少等差数列
        //结果需要累加
    }
    return ret;
}

//最长湍流子数组，湍流子数组的核心是相邻元素的大小关系交替变化（如 “大→小→大” 或 “小→大→小”），这种交替是相对于子数组内部的位置，而非原数组的全局索引。
//不能通过奇数偶数来判断变化，注意初始化全部设为1！
int maxTurbulenceSize(vector<int>& arr) {
    int n=arr.size(),ret=0;
    if(n<=1) return n;
    vector<int> f(n+1,1),g(n+1,1);
    for(int i=1;i<n;i++)
    {
        if(arr[i-1]>arr[i]) g[i]=f[i-1]+1;
        else if(arr[i-1]<arr[i]) f[i]=g[i-1]+1;
        else f[i]=g[i]=1;
        ret=max(ret,max(f[i],g[i]));
    }
    return ret;
}

//非常难想的dp问题，
//定义 dp[i] 表示字符串 s 的前 i 个字符能否被拆分成字典中的单词组合
//dp[0] 初始化为 true，表示空字符串可以被拆分!!!
//字符串预处理：
//在原字符串 s 前添加一个空格，目的是便于索引映射，使字符串下标从 1 开始，与 dp 数组的索引对应

//状态转移过程：
//外层循环遍历字符串的每个位置 i（从 1 到 n）
//内层循环遍历所有可能的拆分点 j（从 1 到 i）
//对于每个 i，检查是否存在一个 j 使得：
//dp[j-1] 为 true（即前 j-1 个字符可以被拆分）
//从 j 到 i 的子串 s.substr(j, i-j+1) 存在于字典中
//如果找到这样的 j，则设置 dp[i] 为 true 并跳出内层循环
bool wordBreak(string s, vector<string>& wordDict) {
    //先用哈希表初始化，便于查找
    unordered_map<string,int> hash;
    for(const auto&e:wordDict) hash[e]++;
    int n=s.size();
    vector<bool> dp(n+1,false);
    dp[0]=true;
    s=" "+s;//便于下表映射
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)//遍历顺序无所谓，从左到右，或者从右到左
        {
            if(dp[j-1]==true&&hash.count(s.substr(j,i-j+1)))
            {
                dp[i]=true;
                break;
            }
        }
    }
    return dp[n];
}

//dp[i] 表示：以 i 位置的元素为结尾的所有子串的数量，有多少个在 base 中出现过
//这种题最后需要将dp数组累加起来，因为dp[i]无法表示全部情况
int findSubstringInWraproundString(string s) {
    int n=s.size(),ret=0;
    vector<int> dp(n+1,1);//dp[i]只能表示以s[i]为结尾的子串数量，后续还需要统计之和
    //先全部初始化为1
    for(int i=1;i<=n;i++)
    {
        if(s[i-1]+1==s[i]||s[i-1]=='z'&&s[i]=='a') dp[i]=dp[i-1]+1;//如果连续，就算上s[i]本身（+1）
        //否则就是1
    }

    int hash[26]={0};//以相同字符结尾的，选择最大的数作为字串数量（去重）
    for(int i=0;i<n;i++)
    {
        hash[s[i]-'a']=max(hash[s[i]-'a'],dp[i+1]);
    }

    for(const auto&e:hash) ret+=e;
    return ret;
}

//全是0的子数组，与上一题非常类似，只不过不需要去重
long long zeroFilledSubarray(vector<int>& nums) {
    int n= nums.size();
    vector<int> dp(n+1,0);
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        if(nums[i-1]==0) dp[i]=dp[i-1]+1;
    }
    long long ret=0;
    for(const auto&e:dp) ret+=e;
    return ret;
}

//找出所有的正方形，这是二维dp，请注意状态转移方程，构成正方形需要选择上左斜对角的最小dp值
int countSquares(vector<vector<int>>& matrix) {
    int row=matrix.size(),col=matrix[0].size(),ret=0;
    vector<vector<int>> dp(row+1,vector<int>(col+1,0));
    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=col;j++)
        {
            if(matrix[i-1][j-1]) dp[i][j]=min(dp[i-1][j],min(dp[i][j-1],dp[i-1][j-1]))+1;
        }
    }
    for(const auto&e:dp)
        for(const auto&s:e) ret+=s;
    return ret;
}


//最长上升子序列，dp[i]表示以i位置的元素为结尾的最长上升子序列的长度，在贪心中的版本是以dp[i]为起点的！
int lengthOfLIS(vector<int>& nums) {
    int ret=1,n=nums.size();
    vector<int> dp(n,1);//dp[i]表示以i位置的元素为结尾的最长上升子序列的长度
    for(int i=1;i<n;i++)
    {
        //子序列问题不是连续子数组，需要从0到i遍历，找出最大的dp[j]+1！
        for(int j=0;j<=i;j++)
        {
            if(nums[j]<nums[i]) dp[i]=max(dp[i],dp[j]+1);
        }
        ret=max(ret,dp[i]);
    }
    return ret;
}

//摆动序列，已经可以想出来大部分了！
int wiggleMaxLength(vector<int>& nums) {
    int n=nums.size(),ret=1;
    vector<int> dp1(n,1),dp2(n,1);//dp1结尾下降,dp2结果上升
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(nums[j]<nums[i]) dp2[i]=max(dp2[i],dp1[j]+1);
            else if(nums[j]>nums[i]) dp1[i]=max(dp1[i],dp2[j]+1);
        }
        ret=max(ret,max(dp1[i],dp2[i]));
    }
    return ret;
}

//最长上升子序列的数量，感觉非常难想！
//定义两个数组：
//dp 数组：dp[i] 表示以 nums[i] 结尾的最长递增子序列的长度。
//count 数组：count[i] 表示以 nums[i] 结尾且长度为 dp[i] 的最长递增子序列的个数。

//初始化：对于每个元素 nums[i]，初始时 dp[i] = 1（自身构成一个长度为 1 的子序列 ），count[i] = 1（只有自身这一种情况 ）。

//状态转移：遍历数组，对于每个 i，再遍历 j 从 0 到 i - 1：
//如果 nums[i] > nums[j]，说明可以接在以 nums[j] 结尾的递增子序列后面形成更长的子序列。此时比较 dp[j] + 1 和 dp[i]：
//如果 dp[j] + 1 > dp[i]，那么更新 dp[i] = dp[j] + 1，同时 count[i] = count[j]（因为新的最长长度对应的子序列个数就是以 j 结尾的对应个数 ）。
//如果 dp[j] + 1 == dp[i]，那么 count[i] += count[j]（说明找到了新的构成相同长度最长子序列的情况，将对应个数累加 ）。

//计算结果：先找到最长递增子序列的长度 max_len（遍历 dp 数组得到 ），然后遍历 dp 数组，将所有 dp[i] == max_len 对应的 count[i] 累加，得到最终最长递增子序列的个数。
int findNumberOfLIS(vector<int>& nums) {
    int n=nums.size(),maxlen=1,maxcount=1;
    vector<int> dp(n,1),count(n,1);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(nums[j]<nums[i])
            {
                if(dp[i]==dp[j]+1) count[i]+=count[j];
                else if(dp[i]<dp[j]+1) dp[i]=dp[j]+1,count[i]=count[j];
            }
        }
        if(maxlen==dp[i]) maxcount+=count[i];
        else if(maxlen<dp[i]) maxlen=dp[i],maxcount=count[i];
    }
    return maxcount;
}

//可以把问题转化成我们学过的一个模型： 300. 最长递增子序列。因此我们解决问题的方向，应该在「最长递增子序列」这个模型上。
//在用动态规划结局问题之前，应该先把数组排个序。因为我们在计算 dp[i] 的时候，要知道所有左区间比 pairs[i] 的左区间小的链对。排完序之后，只用「往前遍历一遍」即可。
int findLongestChain(vector<vector<int>>& pairs) {
    sort(pairs.begin(),pairs.end(),[](const vector<int>& v1,const vector<int>& v2){return v1[0]<v2[0];});
    int n=pairs.size(),ret=1;
    vector<int> dp(n,1);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(pairs[j][1]<pairs[i][0]) dp[i]=max(dp[i],dp[j]+1);
        }
        ret=max(ret,dp[i]);
    }
    return ret;
}

//“删掉一个元素以后全为 1 的最长子数组”
//定义两个动态规划数组：
//dp0[i]：表示以第 i 个元素结尾，未删除元素时，最长全为 1 的子数组长度。
//dp1[i]：表示以第 i 个元素结尾，已经删除一个元素（可以是当前元素前面的某个 0 ，也可以是当前元素本身）时，最长全为 1 的子数组长度。
//状态转移方程：
//当 nums[i] == 1 时：
//dp0[i] = dp0[i - 1] + 1 ，因为当前元素是 1 ，未删除元素的最长长度就是前一个位置未删除时的长度加 1 。
//dp1[i] = dp1[i - 1] + 1 ，已经删除过元素的情况下，当前元素是 1 ，长度在之前已删除的基础上加 1 。
//当 nums[i] == 0 时：
//dp0[i] = 0 ，因为当前元素是 0 ，未删除元素时无法形成全 1 子数组，长度重置为 0 。
//dp1[i] = dp0[i - 1] ，此时删除当前这个 0 ，那么长度就等于前一个位置未删除元素时的最长全 1 子数组长度。
int longestSubarray(vector<int>& nums)
{
        int n=nums.size(),ret=0;bool judge=false;
        vector<int> f(n+1,0),g(n+1,0);
        for(int i=1;i<=n;i++)
        {
            if(nums[i-1]) f[i]=f[i-1]+1,g[i]=g[i-1]+1;
            else g[i]=f[i-1],judge=true;
            ret=max(ret,g[i]);
        }
        if(!judge) return n-1;
        else return ret;
}

//最长定差子序列” 问题，寻找数组中最长的子序列，使得子序列中相邻元素的差等于给定的 difference
//问题转化：
//对于数组中的每个元素 arr[i]，如果存在一个元素 arr[j] = arr[i] - difference（j < i），
//那么以 arr[i] 结尾的最长定差子序列长度，就等于以 arr[j] 结尾的最长定差子序列长度加 1（即把 arr[i] 接在 arr[j] 后面）。
//如果不存在这样的 arr[j]，则以 arr[i] 结尾的最长定差子序列长度就是 1（仅包含自身）。
//动态规划 + 哈希表：
//用哈希表 hash 记录以某个值为结尾的最长定差子序列长度，键为元素值，值为对应的最长长度。
//遍历数组时，对于每个元素 arr[i]，通过 hash[arr[i] - difference] 快速找到前一个符合条件的元素的最长长度，从而计算当前元素的最长长度。
//不断更新哈希表和全局最大值，最终得到结果。
int longestSubsequence(vector<int>& arr, int difference) {
    int n=arr.size(),ret=0;
    unordered_map<int,int> hash;//{元素值，最长定差子序列长度}
    hash[arr[0]]=1;
    for(int i=1;i<n;i++)
    {
        hash[arr[i]]=hash[arr[i]-difference]+1;
        ret=max(ret,hash[arr[i]]);
    }
    return ret;
}

//最长斐波那契子序列的长度
//dp[i][j] 表示：以 i 位置以及 j 位置的元素为结尾的所有的子序列中，最长的斐波那契子
//序列的长度。规定一下 i < j 。
//2. 状态转移方程：
//设 nums[i] = b, nums[j] = c ，那么这个序列的前一个元素就是 a = c - b 。我们根
//据 a 的情况讨论：
//i. a 存在，下标为 k ，并且 a < b ：此时我们需要以 k 位置以及 i 位置元素为结尾的
//最长斐波那契子序列的长度，然后再加上 j 位置的元素即可。于是 dp[i][j] =
//dp[k][i] + 1 ；
//ii. a 存在，但是 b < a < c ：此时只能两个元素自己玩了， dp[i][j] = 2 ；
//iii. a 不存在：此时依旧只能两个元素自己玩了， dp[i][j] = 2 。
//优化点：我们发现，在状态转移方程中，我们需要确定 a 元素的下标。因此我们可以在 dp 之前，将所有的「元素 + 下标」绑定在一起，放到哈希表中。
int lenLongestFibSubseq(vector<int>& arr) {
    int n=arr.size(),ret=0;
    vector<vector<int>> dp(n,vector<int>(n,1));
    unordered_map<int,int> hash;
    for(int i=0;i<n;i++) hash[arr[i]]=i;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(hash.count(arr[i]-arr[j])&&hash[arr[i]-arr[j]]<j) dp[j][i]=dp[hash[arr[i]-arr[j]]][j]+1;
            else dp[j][i]=2;

            ret=max(ret,dp[j][i]);
        }

    }
    return ret<3 ? 0 : ret;//数列的长度必须大于3
}

//最长等差数列的长度，与上面一题非常相似，但是不同的是，这一题的会有同一个数对应不同下标
//a. 在 dp 之前，放入哈希表中。这是可以的，但是需要将下标形成一个数组放进哈希表中。这样
//时间复杂度较高，我帮大家试过了，超时。
//b. 一边 dp ，一边保存。这种方式，我们仅需保存最近的元素的下标，不用保存下标数组。但是
//用这种方法的话，我们在遍历顺序那里，先固定倒数第二个数，再遍历倒数第一个数。这样就
//可以在 i 使用完时候，将 nums[i] 扔到哈希表中
int longestArithSeqLength(vector<int>& nums) {
    int n=nums.size(),ret=0;
    vector<vector<int>> dp(n,vector<int>(n,1));
    unordered_map<int,int> hash;
    hash[nums[0]]=0;
    for(int i=0;i<n;i++)
    {
        //由于相同的数建议选择下标靠后的，这样保证长度最大，
        //所以我们在遍历顺序那里，先固定倒数第二个数，再遍历倒数第一个数，这么做的原因是如果遍历前面的话，哈希表的值一直在变，起不到效果
        //我们在遍历到 i 位置时候，哈希表中保存的是 i 位置之前的元素的下标，所以我们可以
        //直接使用哈希表中保存的下标，来更新 dp[i][j] 。
        for(int j=i+1;j<n;j++)
        {
            if(hash.count(nums[i]*2-nums[j])) dp[i][j]=dp[hash[nums[i]*2-nums[j]]][i]+1;
            else dp[i][j]=2;

            ret=max(ret,dp[i][j]);
        }
        hash[nums[i]]=i;//用完了，就可以扔到哈希表中了
    }
    return ret;
}

//等差数列划分，与前面两题有相似，还是先将数值与下标数组进行对应，然后固定倒数第一个数
//遍历倒数第二个数，需要注意long long防止溢出，由于可能一个数出现多次，所以dp[j][i]+=dp[e][j]+1;
//一个dp[e][j]需要+1，多个下标需要将所有的加起来！！！
int numberOfArithmeticSlices1(vector<int>& nums) {
    int n=nums.size(),ret=0;
    vector<vector<int>> dp(n,vector<int>(n,0));
    unordered_map<long long,vector<int>> hash;
    for(int i=0;i<n;i++) hash[nums[i]].push_back(i);//用哈希表将数值与下标数组绑定，便于查找
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)//这里不能让j=i，因为i是倒数第一个数，j是倒数第二个数，不能相等
        {
            long long tmp=(long long)nums[j]*(long long)2-nums[i];
            if(hash.count(tmp))
            {
                for(const auto&e:hash[tmp])
                {
                    if(e<j) dp[j][i]+=dp[e][j]+1;//注意这一步
                }
                ret+=dp[j][i];
            }
        }
    }
    return ret;
}

//回文串问题////////////////////////////////////////////////
//请注意这一题的思路非常关键！可以使用一个二维数组dp[i][j]表示i到j是否为回文串
//如果s[i]==s[j]分两种情况，同一个字符或者相邻字符为true，其他取决于dp[i+1][j-1]
//如果s[i]!=s[j]，那么dp[i][j]为false
int countSubstrings(string s) {
    int n=s.size(),ret=0;
    vector<vector<bool>> dp(n,vector<bool>(n,0));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)//请注意填表顺序，i要取最大，j要大于等于i
        {
            if(s[i]==s[j]) dp[i][j]= j-i>1 ? dp[i+1][j-1] : true;
            else dp[i][j]=false;

            if(dp[i][j]) ret++;
        }
    }
    return ret;
}

//最长回文字串问题，前面采用中心扩展算法，这里采用动态规划
//实际上与上面的题目非常相似，都是用二维数组标记i到j的字串是否为回文串，这里要求最长的回文串，那么更新ret即可
string longestPalindrome(string s) {
    string ret;
    int length=1,n=s.size();
    vector<vector<bool>> dp(n,vector<bool>(n,false));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)
        {
            if(s[i]==s[j]) dp[i][j]=i+1<j?dp[i+1][j-1]:true;
            if(dp[i][j]&&j-i+1>ret.size()) ret=s.substr(i,j-i+1);
        }
    }
    return ret;
}

//寻找三个回文子串，看似困难，实则用dp标记具体的回文串之后只需要找到即可
bool checkPartitioning(string s) {
    int n=s.size();
    vector<vector<bool>> dp(n,vector<bool>(n,false));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)
        {
            if(s[i]==s[j]) dp[i][j]=i+1<j?dp[i+1][j-1]:true;
        }
    }
    for(int i=0;i<n-2;i++)
    {
        if(dp[0][i])
        {
            for(int j=i+1;j<n-1;j++)
            {
                if(dp[i+1][j]&&dp[j+1][n-1]) return true;
            }
        }
    }
    return false;
}

//回文串的划分，注意这题不是上一题简单的划分了，而是要用到动态规划，求得最少的划分次数
int minCut(string s) {
    int n=s.size(),ret1=-1,ret2=-1;
    vector<vector<bool>> dp(n,vector<bool>(n,false));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)
        {
            if(s[i]==s[j]) dp[i][j]=i+1<j?dp[i+1][j-1]:true;
        }
    }
    vector<int> Dp(n,0x3f3f3f3f);//这个Dp表代表以i结尾，最长回文串的最少分割次数
    //注意初始化不能全部为0，会影响判断
    for(int i=0;i<n;i++)
    {
        if(dp[0][i]) Dp[i]=0;
        else
        {
            for(int j=0;j<=i;j++)
            {
                if(dp[j][i]) Dp[i]=min(Dp[i],Dp[j-1]+1);
                //这里与前面的单词划分非常类似，不过是将单词保存在哈希表中，这里用二维dp保存是否回文而已
                //如果j到i回文，那么划分次数为j-1对应的值+1，这里dp[i]要取最小值
            }
        }
    }
    return Dp[n-1];
}

//这一题发现前面用二维数组dp[i][j]表示i到j的最长回文子序列根本用不上，但是又想到可能与最长递增子序列相似，
//可以说dp[i][j]表示i到j的最长回文子序列的长度，由于状态转移方程中涉及dp[i+1][j-1]，所以决定了填表顺序
//与前面相似，如果s[i]==s[j]，分三种情况，i==j,i+1==j,i+1<j，长度分别为1,2,dp[i+1][j-1]+2;
//如果不相等呢，就要去dp[i+1][j],dp[i][j-1]找到最大的，为什么不继续找找中间别的区间呢？因为已经包括进去了。
int longestPalindromeSubseq(string s) {
    int n=s.size(),ret=1;
    vector<vector<int>> dp(n,vector<int>(n,1));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)
        {
            if(s[i]==s[j]) dp[i][j]=i+1<j ? dp[i+1][j-1]+2 : (i+1==j ? 2 : 1);
            else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);

            ret=max(ret,dp[i][j]);
        }
    }
    return ret;

}

//勇敢尝试了一下，居然过了！原理与上面一题非常相似，不需要对s做出真正的插入，这里的dp[i][j]表示i到j的最少插入次数
//如果s[i]==s[j]，那么dp[i][j]=dp[i+1][j-1]，否则dp[i][j]=min(dp[i+1][j-1]+2,min(dp[i+1][j]+1,dp[i][j-1]+1))
//默认dp[i+1][j]和dp[i][j-1]都是已经回文的字符串，并且表示最少插入次数，取最小值即可！
int minInsertions(string s) {
    int n=s.size(),step=0;
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)
        {
            if(s[i]==s[j]) dp[i][j]=i+1<j ? dp[i+1][j-1] : 0;
            else
            {
                dp[i][j]=min(dp[i+1][j-1]+2,min(dp[i+1][j]+1,dp[i][j-1]+1));
            }
        }
    }
    return dp[0][n-1];
}

//两个数组的 dp （含字符串数组）//////////////////////////////////////////////////////////
//此题为模板题，对于两个字符串的dp需要创建一个二维数组，多开辟一行一列来初始化
//选取第一个数组 [0, i] 区间以及第二个数组 [0, j] 区间作为研究对象；dp[i][j] 表示： s1 的 [0, i] 区间以及 s2 的 [0, j] 区间内的所有的子序列中，最长公共子序列的长度。
int longestCommonSubsequence(string test1, string test2) {
    int n=test1.size(),m=test2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));//初始化为0防止越界访问，就当作是空串，长度为0
    //dp[i][j]表示0-i和0-j以ij结尾的字符串的所有公共子序列的最大值
    test1=" "+test1;test2=" "+test2;//这么做是为了访问下标时不用-1
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(test1[i]==test2[j]) dp[i][j]=dp[i-1][j-1]+1;//如果结尾字符相同，i-1 j-1的长度+1
            else
            {
                //如果不相等就去0~i 0~j-1/0~i-1 0~j/0~i-1 0~j-1中寻找最大值，如果是求个数的话，可能会导致重复计数，但是求最大值的话就无需关心
                dp[i][j]=max(dp[i][j-1],max(dp[i-1][j],dp[i-1][j-1]));
            }
        }
    }
    return dp[n][m];
}

//最长公共子序列的应用：最大不相交线，需要脑筋急转弯一下
int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int n=nums1.size(),m=nums2.size();
    //转换为寻找最长公共子序列的问题，在两个数组中寻找最长子数组的长度
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(nums1[i-1]==nums2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else
            {
                dp[i][j]=max(dp[i-1][j-1],max(dp[i][j-1],dp[i-1][j]));
            }
        }
    }
    return dp[n][m];
}

//最长公共子序列的应用：不同的子序列
int numDistinct(string s, string t) {
    //dp[i][j] 表示：在字符串 s 的[0, j] 区间内的所有子序列中，有多少个 t 字符串[0,i] 区间内的子串。
    s=" "+s;t=" "+t;//便于访问下标
    int m = t.size(), n = s.size();
    vector<vector<double>> dp(m + 1, vector<double>(n + 1));
    for(int j = 0; j <= n; j++) dp[0][j] = 1; // 初始化
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
        {
            dp[i][j] += dp[i][j - 1];//否则就放弃最后一个字符，去0~i 0~j-1找找
            if(t[i] == s[j]) dp[i][j] += dp[i - 1][j - 1];//最后一个字符相同，等于0~i-1 0~j-1的结果
        }
    return dp[m][n];
}

//这是一道真正的困难题，要用心做！
//当 s[i] == p[j] 或 p[j] == '?' 的时候，此时两个字符串匹配上了当前的一个字
//符，只能从 dp[i - 1][j - 1] 中看当前字符前面的两个子串是否匹配。只能继承上个
//状态中的匹配结果， dp[i][j] = dp[i][j - 1] ；

//当 p[j] == '*' 的时候，此时匹配策略有两种选择：
//一种选择是： * 匹配空字符串，此时相当于它匹配了一个寂寞，直接继承状态 dp[i]
//[j - 1] ，此时 dp[i][j] = dp[i][j - 1] ；
//另一种选择是： * 向前匹配 1 ~ n 个字符，直至匹配上整个 s1 串。此时相当于
//从 dp[k][j - 1] (0 <= k <= i) 中所有匹配情况中，选择性继承可以成功的
//情况。此时 dp[i][j] = dp[k][j - 1] (0 <= k <= i) ；
//当 p[j] 不是特殊字符，且不与 s[i] 相等时，无法匹配
bool isMatch(string s, string p) {
    //先来尝试没有任何优化的dp
    int n=s.size(),m=p.size();
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    dp[0][0]=true;
    s=" "+s;p=" "+p;
    for (int j = 1; j <= m; j++)
    {
        // 如果p[j]是*，则空s匹配p[1..j] 等价于 空s匹配p[1..j-1]（*匹配0个字符）
        if (p[j] == '*') dp[0][j] = dp[0][j - 1];
    }
    //dp[i][j]将要表示的是0~j与0~i是否匹配
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s[i]==p[j]||p[j]=='?') dp[i][j]=dp[i-1][j-1];
            else if(p[j]=='*')
            {
                dp[i][j]=dp[i-1][j]||dp[i][j-1];
                //优化状态转移方程，
                // dp[i][j] = dp[i][j - 1] || dp[i - 1][j - 1] || dp[i - 2][j - 1]......
                //我们发现 i 是有规律的减小的，因此我们去看看 dp[i - 1][j] ：
                //             dp[i - 1][j] = dp[i - 1][j - 1] || dp[i - 2][j - 1] || dp[i - 3][j - 1] ......
                //那么dp[i][j]=dp[i-1][j]||dp[i][j-1];
                // for(int tmp=0;tmp<=i;tmp++)
                // {
                //     if(dp[tmp][j-1])
                //     {
                //         dp[i][j]=true;
                //         break;
                //     }
                // }
            }
        }
    }
    return dp[n][m];
}

//与上面一题非常类似，只不过多了一个星号可以匹配前面的字符0次或者多次
bool isMatch1(string s, string p) {
    int n=s.size(),m=p.size();
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    s=" "+s;p=" "+p;
    dp[0][0]=true;
    //0~i 0~j上研究，和前面一样
    //恶心的初始化
    for(int j=1;j<=m;j++) if(p[j]=='*') dp[0][j]=dp[0][j-2];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s[i]==p[j]||p[j]=='.') dp[i][j]=dp[i-1][j-1];
            else if(p[j]=='*')
            {
                //这里不能写成dp[i][j] = dp[i-1][j] || dp[i][j-2];因为s[i]与p[j - 1]可能不匹配，闹麻了
                dp[i][j] = dp[i][j - 2];

                //若前面的字符与s[i]匹配，再考虑匹配多次，否则不能使用 || dp[i-1][j]
                if(s[i] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    return dp[n][m];
}

//交错字符串，已经算很简单的dp了，注意初始化！
bool isInterleave(string s1, string s2, string s3) {
    int n=s1.size(),m=s2.size(),k=s3.size();
    if(n+m!=k) return false;
    s1=" "+s1;s2=" "+s2;s3=" "+s3;//便于访问下标
    //dp[i][j] 表示字符串 s1 中 [1, i] 区间内的字符串以及 s2 中 [1, j] 区间内的字符串，能否拼接成 s3 中 [1, i + j] 区间内的字符串。
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    dp[0][0]=true;
    for(int i=1;i<=n;i++)
    {
        //初始化，如果s3的前i个字符与s1的前i个字符相同，那么dp[i][0]为true，否则后面都为false
        if(s3[i]==s1[i]) dp[i][0]=true;
        else break;
    }
    for(int i=1;i<=m;i++)
    {
        //初始化，如果s3的前i个字符与s2的前i个字符相同，那么dp[0][i]为true，否则后面都为false
        if(s3[i]==s2[i]) dp[0][i]=true;
        else break;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            //这里用||防止重复计算
            //如果s3的最后一个字符与s1的最后一个字符相同，那么就去掉s1的最后一个字符，看看前面的是否匹配
            //如果s3的最后一个字符与s2的最后一个字符相同，那么就去掉s2的最后一个字符，看看前面的是否匹配
            //如果都不相同，那么肯定不匹配
            //注意这里的i,j是从1开始的，所以要用i+j来访问s3
            dp[i][j]=(s3[i+j]==s1[i]&&dp[i-1][j])||(s3[i+j]==s2[j]&&dp[i][j-1]);
        }
    }
    return dp[n][m];
}

//两个字符串的删除操作，感觉非常难想
//正难则反：求两个字符串的最小 ASCII 删除和，其实就是找到两个字符串中所有的公共子序列里面， ASCII 最大和。
//因此，我们的思路就是按照「最长公共子序列」的分析方式来分析
int minimumDeleteSum(string s1, string s2) {
    int n=s1.size(),m=s2.size(),sum1=0,sum2=0;
    s1=" "+s1;s2=" "+s2;
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++) sum1+=s1[i];
    for(int j=1;j<=m;j++) sum2+=s2[j];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s1[i]==s2[j]) dp[i][j]=dp[i-1][j-1]+s1[i];
            else dp[i][j]=max(dp[i-1][j],max(dp[i][j-1],dp[i-1][j-1]));
        }
    }
    return sum1+sum2-2*dp[n][m];
}

//最长重复子数组，注意和最长公共子序列的区别，子数组是连续的，这里需要ret来实时更新
//状态转移方程比较容易表示出
int findLength(vector<int>& nums1, vector<int>& nums2) {
    int n=nums1.size(),m=nums2.size(),ret=0;
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(nums1[i-1]==nums2[j-1]) dp[i][j]=max(dp[i-1][j-1]+1,1);
            ret=max(ret,dp[i][j]);
        }
    }
    return ret;
}

//背包问题！！！//////////////////////////////////////////////////////
//一、0-1 背包（最基础）
//有 n 件物品，每件物品有两个属性：重量 w[i] 和价值 v[i]。每件物品只能选一次（要么选，要么不选），背包最大承重为 C。求背包能装入的最大价值。
//解法思路（动态规划）：
//状态定义：设 dp[i][j] 表示 “从前 i 件物品中选择，总重量不超过 j 时的最大价值”。
//状态转移：对第 i 件物品，有两种选择：
//不选：dp[i][j] = dp[i-1][j]（价值和前 i-1 件物品相同）。
//选（前提是 j >= w[i]）：dp[i][j] = dp[i-1][j - w[i]] + v[i]（价值 = 前 i-1 件物品在重量 j-w[i] 下的最大价值 + 当前物品价值）。
//因此，转移方程为：
//             dp[i][j] = max(dp[i-1][j], (j >= w[i] ? dp[i-1][j - w[i]] + v[i] : 0))
//空间优化：观察发现，dp[i][j] 只依赖于 dp[i-1][...]（上一行），因此可将二维数组优化为一维数组 dp[j]，并从后往前遍历（避免覆盖上一行未使用的数据）：
//结果：最终 dp[C] 即为最大价值（因为 dp[j] 定义为 “重量不超过 j 的最大价值”，自然包含了最优解）。

//二、完全背包（物品可无限选）
//问题定义：
//与 0-1 背包类似，但每件物品可以选无限次（只要不超过背包容量）。
//解法思路：
//状态定义：仍用 dp[j] 表示 “重量不超过 j 时的最大价值”，但含义扩展为 “可重复选物品”。
//状态转移：由于物品可重复选，选第 i 件后仍可再选，因此从前往后遍历（允许重复使用当前物品的状态）：
//核心区别：与 0-1 背包的唯一差异是遍历顺序 —— 完全背包正向遍历（允许重复选），0-1 背包反向遍历（禁止重复选）。

//三、多重背包（物品有限次选）
//问题定义：
//每件物品有固定数量限制（如第 i 件最多选 k[i] 次），介于 0-1 背包（k=1）和完全背包（k=∞）之间。
//解法思路：
//基础思路：把 “最多 k 件” 拆成 k 个独立物品，转化为 0-1 背包。但当 k 很大时（如 1e5），效率极低。
//优化：二进制拆分：将 k 拆分为 2^0, 2^1, ..., 2^m, r（r = k - (2^{m+1}-1)），用这些 “二进制组合” 表示 0~k 的所有可能次数。例如 k=5 可拆为 1,2,2（1+2+2=5），通过选或不选这些组合，能覆盖 0~5 的所有次数。拆分后物品数量从 k 降至 log2(k)，再用 0-1 背包解法即可。

//板子：
void package_01()
{
    int n=0,val=0;
    cin>>n>>val;
    //不一定装满背包的情况：
    //状态表示：
    //dp[i][j] 表示：从前 i 个物品中挑选，总体积「不超过」 j ，所有的选法中，能挑选出来的最大价值。
    //i. 不选第 i 个物品：相当于就是去前 i - 1 个物品中挑选，并且总体积不超过 j 。此
    //时 dp[i][j] = dp[i - 1][j] ；
    //ii. 选择第 i 个物品：那么我就只能去前 i - 1 个物品中，挑选总体积不超过 j - v[i]
    //的物品。此时 dp[i][j] = dp[i - 1][j - v[i]] + w[i] 。但是这种状态不一定存在，因此需要特判一下。
    //综上，状态转移方程为： dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] +
    //w[i]) 。
    vector<vector<int>> items(n+1,vector<int>(val+1,0));
    vector<int> w(n+1,0),v(n+1,0);
    for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=val;j++)
        {
            //0-1背包
            if(j-v[i]>=0) items[i][j]=max(items[i-1][j],items[i-1][j-v[i]]+w[i]);//选择当前物品
            else items[i][j]=items[i-1][j];//不选当前物品
        }
    }
    cout<<items[n][val]<<endl;
    items.resize(n+1,vector<int>(val+1,0));
    //恰好装满背包：将不存在使背包装满的状态填充-1
    for(int j=1;j<=val;j++) items[0][j]=-1;//体积恰好为j而不挑选物品的状态是不存在的
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=val;j++)
        {
            items[i][j]=items[i-1][j];//不选当前物品，去前i-1个物品中找容量恰好为j的状态
            if(j-v[i]>=0&&items[i-1][j-v[i]]!=-1) items[i][j]=max(items[i-1][j],items[i-1][j-v[i]]+w[i]);
            //j-v[i]确保不越界，并且还有剩余容量，items[i-1][j-v[i]]!=-1确保状态存在
        }
    }
    cout<< (items[n][val]==-1 ? 0 : items[n][val])<<endl;

}

//这里选用滚动数组来进行空间优化，注意到这里的状态转移方程中，dp[i][j]只依赖于 dp[i-1][...]（上一行），
//因此可将二维数组优化为一维数组 dp[j]，并从后往前遍历（避免覆盖上一行未使用的数据）
void package_01_Pro()
{
    int n=0,val=0;
    cin>>n>>val;
    vector<int> w(n+1,0),v(n+1,0);
    for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
    vector<int> items(val+1,0);
    for(int i=1;i<=n;i++)
    {
        for(int j=val;j>=1;j--)//注意这里是从后往前遍历，避免覆盖上一行未使用的数据
        {
            //由于是线性数组，所以这里不选择当前物品的状态就是items[j]，不用更新了
            if(j-v[i]>=0) items[j]=max(items[j],items[j-v[i]]+w[i]);
        }
    }
    cout<<items[val]<<endl;
    items.resize(val+1,0);
    //恰好装满背包
    for(int j=1;j<=val;j++) items[j]=-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=val;j>=1;j--)
        {
            if(j-v[i]>=0&&items[j-v[i]]!=-1) items[j]=max(items[j],items[j-v[i]]+w[i]);
        }
    }
    cout<<(items[val]==-1 ? 0 : items[val])<<endl;
}

//分割等和子集，0-1背包的变形，这里转换为寻找背包恰好装满（容量为sum/2）的最大价值
//这里的物品价值与体积相等
bool canPartition(vector<int>& nums) {
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if(sum%2) return false;
    int t=sum/2;//背包容量
    vector<int> dp(t+1,-1);dp[0]=0;//初始化，容量为0时，价值为0
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=1;j--)//从后往前遍历
        {
            if(j-nums[i]>=0&&dp[j-nums[i]]!=-1) dp[j]=max(dp[j],dp[j-nums[i]]+nums[i]);
        }
    }
    return dp[t]==t;
}
//逻辑是对的，但是状态表示尝试选择第i个元素后，能否更加接近目标，下面是更准确的状态表示：
bool canPartition1(vector<int>& nums) {
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if(sum%2) return false;
    int t=sum/2;//背包容量
    vector<bool> dp(t+1,false);dp[0]=true;//dp[i]表示能否得到和为i的子集
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=1;j--)//从后往前遍历
        {
            if(j-nums[i]>=0) dp[j]=dp[j]||dp[j-nums[i]];
        }
    }
    return dp[t];
}

//目标和，可以选择dfs，这里提供dp的方法：
int findTargetSumWays(vector<int>& nums, int target) {
    //设选择+的数字之和为a，选择-的数字之和为b，则a+b=sum，a-b=target
    //得t=(sum+target)/2;选择数字使和为t
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if((sum+target)%2||sum+target<0) return 0;
    int t=(sum+target)/2;//容量
    //这里dp[i]表示前i个的和为i的选择方法
    vector<int> dp(t+1,0);dp[0]=1;//初始化
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=nums[i];j--)//这里直接将下面的条件融合，防止出现和可能为0而漏解的情况
        {
            dp[j]+=dp[j-nums[i]];
        }
    }
    return dp[t];
}


int main()
{

    return 0;
}