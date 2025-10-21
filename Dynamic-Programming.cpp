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

//��̬�滮��Dynamic Programming, DP������Ĳ�����Թ���Ϊ���������
//1. ����״̬��Define the State��
//���ģ���ԭ������Ϊ���ɸ������⣬��һ��������������������� ��״̬������������Ĺؼ�������
//Ŀ�꣺�ҵ�һ��������״̬���壬ʹ��ÿ��״̬��Ӧһ��������Ľ⡣
//ʾ����
//�� ��쳲��������С� �����У�״̬�ɶ���Ϊ dp[i] ��ʾ�� i ��쳲���������
//�� ������������С� �����У�״̬�ɶ���Ϊ dp[i] ��ʾ�Ե� i ��Ԫ�ؽ�β������������г��ȡ�

//2. ȷ��״̬ת�Ʒ��̣�Formulate the Transition��(�Ƶ�״̬ת�ƹ�ʽ�ǳ���Ҫ��)
//���ģ��ҵ���ͬ״̬֮���������ϵ�������ͨ�� ����С��������Ľ⡱ �Ƶ��� ����ǰ����Ľ⡱��
//Ŀ�꣺����һ�����ƹ�ʽ������ dp[i]����ǰ״̬���� dp[j]��ǰ��״̬��j < i���Ĺ�ϵ��
//ʾ����
//쳲��������е�ת�Ʒ���Ϊ dp[i] = dp[i-1] + dp[i-2]��
//��¥�����⣨һ�ο��� 1 �� 2 �ף��У�dp[i] = dp[i-1] + dp[i-2]������� i �׵ķ����� = ����� i-1 �� + ����� i-2 �ף���

//3. ȷ����ʼ������Base Case��
//���ģ�������С������Ľ⣨�޷��ٷֽ�������⣩����Ϊ���Ƶ���㡣
//Ŀ�꣺�������޵ݹ飬ȷ��״̬ת�Ʒ�������ȷ�ļ�����㡣
//ʾ����
//쳲��������еĳ�ʼ����Ϊ dp[0] = 0, dp[1] = 1��
//��¥�������У�dp[0] = 1�����Ҳ�� 1 �ַ�������dp[1] = 1��ֻ�� 1 ����������

//4. ȷ������˳��Order of Computation��
//���ģ�����״̬������ϵ��ȷ������״̬���Ⱥ�˳��ȷ�����㵱ǰ״̬ʱ��������������ǰ��״̬�ѱ���⡣
//Ŀ�꣺������ǰ��״̬δ��������µĴ���
//����˳��
//�Ե����ϣ���С���󣩣��Ƚ����С�����⣬���Ƶ���������⣨��쳲��������д� i=2 ���㵽 i=n����
//�Զ����£��Ӵ�С������ϼ��仯��Memoization�����ݹ���������ʱ����������Ľ⣨��ݹ����쳲�������ʱ�����Ѽ���Ľ������

//5. ȷ�����ս����ʽ��Result Extraction��
//���ģ���ȷԭ����Ľ��Ӧ�ĸ�״̬������Щ״̬����ϣ���
//Ŀ�꣺�Ӽ���õ���״̬����ȡ��ԭ����Ĵ𰸡�
//ʾ����
//쳲����������У�ԭ���� ���� n ��쳲��������� �Ľ���� dp[n]��
//����������������У����ս��� dp �����е����ֵ���������һ��Ԫ�أ���


//1. ״̬��?��
//�������ԡ�������?��Ҫ��ֱ�Ӷ����״̬��?��
//dp[i] ��?���� i ��̩����������ֵ��
//2. ״̬ת��?�̣�
//dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3]
//3. ��ʼ����
//�����ǵĵ��ƹ�ʽ���Կ����� dp[i] �� i = 0 �Լ� i = 1 ��ʱ����û�а취��?�Ƶ��ģ���Ϊ dp[-2] �� dp[-1] ����?����Ч�����ݡ�
//���������Ҫ�����֮ǰ���� 0, 1, 2 λ�õ�ֵ��ʼ������?���Ѿ��������� dp[0] = 0,dp[1] = dp[2] = 1 ��
//4. ���˳��
//��?�����ǡ��������ҡ���
//5. ����ֵ��
//Ӧ�÷��� dp[n] ��ֵ��
int tribonacci(int n) {
    //��̬�滮��
    vector<int> dp(38);
    dp[0]=0;dp[1]=dp[2]=1;
    for(int i=3;i<=n;i++)
    {
        dp[i]=dp[i-3]+dp[i-2]+dp[i-1];
    }
    return dp[n];

    //�ռ��Ż���
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

//��ͬ��ԭ����̨�����⣬ע����Ҫȡģ����a+b+c%1000000007��
//Ҳ����%1e9+7
int waysToStep(int n) {
    //����ֱ��ʹ�ö�̬�滮&�ռ��Ż���
    const int MOD=1e9+7;//1000000007����������ʾ��
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

//�ǳ���������¥�����⣬��������dp�б������ǰ�������ѵ���Сֵ+����һ����Ҫ�Ļ���
//������ڵ�����һ���͵����ڶ���dpԪ�ض����Ե�����Է���������Ԫ�ص���Сֵ����
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
//״̬��ʾҪ�������֣���һ�ǶԵ��أ�

//��˵����¥�ݵı��Σ����Ǻ��Ѱ��������뷽����
int numDecodings(string s) {
    int n=s.size();
    vector<int> dp(n,0);
    if(s[0]=='0') dp[0]=0;
    else dp[0]=1;
    if(n==1) return dp[0];//ע��߽�����Ĵ���

    //��ʼ��dp[0]��dp[1]
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

    //���Զ࿪һ���ռ�����Ż���
    vector<int> dp1(n+1,0);
    dp1[0]=1;//��ע������ڵ�ĸ�ֵ��
    if(s[0]=='0') dp1[1]=0;
    else dp1[1]=1;
    //����ʼ��������ں���һ��
    for(int i=2;i<=n;i++)
    {
        //�±����ڼ�����
        if(s[i-1]!='0') dp1[i]+=dp1[i-1];
        int judge=(s[i-2]-'0')*10+s[i-1]-'0';
        if(judge>=10&&judge<=26) dp1[i]+=dp1[i-2];
    }
    return dp1[n];
}

//��ά����dp��ע���ʼ�������Ǿ����·������
int uniquePaths(int m, int n) {
    //������һ����άdp����
    vector<vector<int>> dp(m+1,vector<int>(n+1,0));
    //���г�ʼ��
    // dp[0][0]=dp[0][1]=dp[1][0]=0;ǰ���ʼ���Ѿ��趨��
    dp[0][1]=1;//ע������ڵ�ĳ�ʼ��
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[m][n];
}

//·������plus��ע��ԭ����Ϊ1�Ļ���˵�����ϰ�������ߣ�dp[i][j]����Ϊ0
//����ǳ�ʼ������Ȼ��dp[0][1]=1��
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

//����·�����⣺ע��״̬ת�Ʒ��̣�dp[i][j]=max(dp[i-1][j],dp[i][j-1])+frame[i-1][j-1];
int jewelleryValue(vector<vector<int>>& frame) {
    int r=frame.size(),c=frame[0].size();
    vector<vector<int>> dp(r+1,vector(c+1,0));
    //dp[0][1]=frame[0][0];ע�����ﲻ��Ҫ��ʼ����ֱ�����������
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            dp[i][j]=max(dp[i-1][j],dp[i][j-1])+frame[i-1][j-1];
        }
    }
    return dp[r][c];
}

//��άdp�ǳ�����ĳ�ʼ����ʽ����Ҫ�࿪���У�
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n=matrix.size();
    vector<vector<int>> dp(n+1,vector<int>(n+2,0));
    //��Ҫ�࿪���У���һ�г�ʼ��Ϊ0���������г�ʼ��ΪINT_MAX
    for(int i=1;i<=n;i++)
    {
        dp[i][0]=dp[i][n+1]=INT_MAX;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            //ѡ������������С�Ľ������
            dp[i][j]=min(min(dp[i-1][j+1],dp[i-1][j]),dp[i-1][j-1])+matrix[i-1][j-1];
        }
    }
    //�����Ҫ�ҳ����һ�е���Сֵ��������ֱ�ӷ���dp[n][n]
    int ret=INT_MAX;
    for(int i=1;i<=n;i++) ret=min(ret,dp[n][i]);
    return ret;
}

//��С·���ͣ�����һ��ǳ����ƣ�������ע���ʼ���ķ�ʽ��
int minPathSum(vector<vector<int>>& grid) {
    int r=grid.size(),c=grid[0].size();
    vector<vector<int>> dp(r+1,vector<int>(c+1,INT_MAX));
    dp[0][1]=0;//��������ڵ��ֵ�ǳ���Ҫ��
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            dp[i][j]=min(dp[i-1][j],dp[i][j-1])+grid[i-1][j-1];
        }
    }
    return dp[r][c];
}

//��άdp���������
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int r=dungeon.size(),c=dungeon[0].size();
    //ע�����������һ�м����У����һ�м�����
    vector<vector<int>> dp(r+1,vector<int>(c+1,INT_MAX));
    dp[r-1][c]=1;//���г�ʼ��
    //��άdp���з������
    //dp[i][j]��ʾ�ӵ�ǰλ�ó����������յ㣬�������ͳ�ʼ��������
    for(int i=r-1;i>=0;i--)
    {
        for(int j=c-1;j>=0;j--)
        {
            //max��Ϊ�˴�������������Ϊ������������Ϊ1
            dp[i][j]=max(1,min(dp[i+1][j],dp[i][j+1])-dungeon[i][j]);
        }
    }
    return dp[0][0];
}


//�򵥶�״̬dp����////////////////////////////////////////////////////////////
//1. ״̬���壨�����߼���
//f[i]����ʾ����ǰ i ��ԤԼ��0~i�����ҽ��ܵ� i ��ԤԼʱ�������ʱ����
//g[i]����ʾ����ǰ i ��ԤԼ��0~i�����Ҳ����ܵ� i ��ԤԼʱ�������ʱ����
//2. ���ƹ�ϵ����֤��ѡ����Ԫ�أ�
//���� f[i] ���ڲ��ܽ�������ԤԼ���� i-1 ��ԤԼ���벻�����ܣ����ֻ�ܴ� g[i-1]�������� i-1����״̬ת�ƶ���������f[i] = g[i-1] + nums[i]�����ϵ�ǰԤԼ��ʱ������
//���� g[i] ��ʱ�� i-1 ��ԤԼ���Խ���Ҳ���Բ����ܣ�ȡ������������ֵ���ɣ�����g[i] = max(f[i-1], g[i-1])��
//3. ��ʼ����߽紦��
//��û��ԤԼʱ��n=0����ֱ�ӷ��� 0�������߼���
//��ֻ�� 1 ��ԤԼʱ��i=0����f[0] = nums[0]���������ԤԼ����g[0] ����Ϊ 0�����������ԤԼ�������ս��ȡ�������ֵ���� nums[0]����
//4. ���ս��
//���һ��ԤԼ�����ֿ��ܣ����ܻ򲻽��ܡ���˷��� max(f[n-1], g[n-1])
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

//��ҽ���1��
//���dp�ǳ����Ƶ�һ����Ŀ���͵���ϰ��
//������������dp��
int rob1(vector<int>& nums) {
    //���dp�ǳ����Ƶ�һ����Ŀ���͵���ϰ��
    //������������dp��
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

//��ҽ���2��.
//͵��?������ʱ����??�� x ����ʱ����͵���?����?����˾���͵ [0, n - 2] ����ķ�?��
//��͵��?������ʱ����??�� y ����ʱ����͵���?����?����˾���͵ [1, n - 1] ����ķ�?��
//��������µġ���?ֵ�����������յĽ��
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

//ɾ������õ���
int deleteAndEarn(vector<int>& nums) {
    //��취������ת��Ϊ��ҽ���ģ�ͣ�ͳ��ÿһ�����ֳ��ֵ��ܺͣ��Ž������У��±���������
    //����֮��������ܻ�õ���
    sort(nums.begin(),nums.end());//�����򣬷���ͳ��
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

//���Ǵ�ҽ�������⣬û��ת��������ʱ��̫���ˣ������i-2 i-1 i+1 i+2�������������ʣ���ʵ���ļ����Ϳ����ˣ����ڳ�ʱ�����⣬δ�Ż�
long long maximumTotalDamage(vector<int>& power) {
    sort(power.begin(),power.end());
    int n=power.back();
    vector<int> sum(n+2,0),c(n+2,0),nc(n+2,0);
    for(const auto&e:power) sum[e]+=e;//�±�ʹ�������
    c[0]=sum[0];c[1]=sum[1];
    nc[0]=0;nc[1]=max(nc[0],c[0]);
    for(int i=2;i<=n+1;i++)
    {
        c[i]=nc[i-2]+sum[i];
        nc[i]=max(max(c[i-1],nc[i-1]),max(c[i-2],nc[i-2]));
    }
    return max(c[n+1],nc[n+1]);
}


//СС��ˢ���Ұ���Ū�������£�
//��̬�滮״̬���壺
//������ 3 ��״̬���飺
//dp1[i]���� i ������ˢ��ɫ 0����һ�У�ʱ����С�ܻ���
//dp2[i]���� i ������ˢ��ɫ 1���ڶ��У�ʱ����С�ܻ���
//dp3[i]���� i ������ˢ��ɫ 2�������У�ʱ����С�ܻ���
//״̬ת�Ʒ��̣�
//���ڵ� i �����ӣ�ѡ��ĳ����ɫ�Ļ��� = ����ɫ�ĳɱ� + ��һ������ˢ��ͬ��ɫ����С���ѣ�
//dp1[i] = min(dp2[i-1], dp3[i-1]) + costs[i][0]����ǰˢ��ɫ 0����һ��ֻ��ˢ 1 �� 2��
//ͬ���Ƶ� dp2[i] �� dp3[i]
//��ʼ����
//��һ�����ӣ�i=0���Ļ��Ѿ����䱾��ĳɱ����� dp1[0] = costs[0][0] �ȡ�
//�����
//���һ�����ӣ�i=n-1���� 3 ����ɫ�����е���Сֵ������ȫ����С�ܻ��ѡ�
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

//��Ʊ����//////////////////////////////////////////////
//1. ״̬����
//dp1[i]���� i �����ʱ���ڡ����й�Ʊ��״̬��������󣨿����ǵ������룬��֮ǰ�����һֱ���У���
//dp2[i]���� i �����ʱ���ڡ��ɽ��ס�״̬��������󣨲����й�Ʊ���ҵ��첻���䶳�ڣ�������ʱ���룩��
//dp3[i]���� i �����ʱ���ڡ��䶳�ڡ�״̬��������󣨵��������˹�Ʊ�����ղ������룩��
//2. ״̬ת���߼�
//dp1[i]�����й�Ʊ����
//�����ֿ�����Դ��
//�� ǰһ���Ѿ����й�Ʊ��dp1[i-1]��������������У����󲻱䣻
//�� ǰһ�촦�ڿɽ���״̬��dp2[i-1]�������������Ʊ��������ٵ�ǰ�ɼۣ�-prices[i]����
//ȡ�������ֵ��dp1[i] = max(dp1[i-1], dp2[i-1] - prices[i])��
//dp2[i]���ɽ���״̬����
//�����ֿ�����Դ��
//�� ǰһ���Ѿ����ڿɽ���״̬��dp2[i-1]��������������֣����󲻱䣻
//�� ǰһ�촦���䶳�ڣ�dp3[i-1]���������䶳�ڽ������ָ��ɽ���״̬�����󲻱䡣
//ȡ�������ֵ��dp2[i] = max(dp2[i-1], dp3[i-1])��
//dp3[i]���䶳�ڣ���
//ֻ��һ�ֿ��ܣ�ǰһ����й�Ʊ��dp1[i-1]��������������Ʊ���������ӵ�ǰ�ɼۣ�+prices[i]����
//��ˣ�dp3[i] = dp1[i-1] + prices[i]��
//3. ��ʼ��
//�� 0 �죨i=0���������й�Ʊ��dp1[0]����ֻ���ǵ������룬����Ϊ -prices[0]��
//�ɽ���״̬��dp2[0]����δ�����κβ���������Ϊ 0��
//�䶳�ڣ�dp3[0]���������޷��������������δ������������Ϊ 0��
int maxProfit(vector<int>& prices) {
    int n=prices.size();
    vector<int> dp1(n),dp2(n),dp3(n);
    dp1[0]=-prices[0];//����״̬
    dp2[0]=0;//�ɽ���״̬
    dp3[0]=0;//���ɽ���״̬���䶳�ڣ�
    for(int i=1;i<n;i++)
    {
        //�����롹����������˲ʱ��������ĳһʱ����ɣ�������̬�滮��Ҫ���ٵ��ǡ��������ʱ���ȶ�״̬����
        // ���ֻ���ǳ��й�Ʊ��״̬���ɽ��׵�״̬���䶳״̬
        dp1[i]=max(dp1[i-1],dp2[i-1]-prices[i]);
        dp2[i]=max(dp2[i-1],dp3[i-1]);
        dp3[i]=dp1[i-1]+prices[i];
    }
    return max(dp1[n-1],max(dp2[n-1],dp3[n-1]));
}

//��һ��û���䶳�ڣ�ֻ�г���״̬������״̬
//1. ״̬����
//dp1[i]���� i �����ʱ���ڡ����й�Ʊ��״̬��������󣨿����ǵ������룬��֮ǰ�����һֱ���У���
//dp2[i]���� i �����ʱ���ڡ��ɽ��ס�״̬��������󣨲����й�Ʊ���ҵ��첻���䶳�ڣ�������ʱ���룩��
//2. ״̬ת���߼�
//dp1[i]�����й�Ʊ����
//�����ֿ�����Դ��
//�� ǰһ���Ѿ����й�Ʊ��dp1[i-1]��������������У����󲻱䣻
//�� ǰһ�촦�ڿɽ���״̬��dp2[i-1]�������������Ʊ��������ٵ�ǰ�ɼۣ�-prices[i]����
//ȡ�������ֵ��dp1[i] = max(dp1[i-1], dp2[i-1] - prices[i])��
//dp2[i]���ɽ���״̬����
//�����ֿ�����Դ��
//�� ǰһ���Ѿ����ڿɽ���״̬��dp2[i-1]��������������֣����󲻱䣻
//�� ǰһ�촦�ڳ����ڣ�����������Ʊ���������ӵ�ǰ�ɼۣ�+prices[i]��������ȥ�����ѡ�
//ȡ�������ֵ��dp2[i] = max(dp2[i-1], dp1[i-1] + prices[i] - fee)��
//3. ��ʼ��
//�� 0 �죨i=0���������й�Ʊ��dp1[0]����ֻ���ǵ������룬����Ϊ -prices[0]��
//�ɽ���״̬��dp2[0]����δ�����κβ���������Ϊ 0��
int maxProfit1(vector<int>& prices, int fee) {
        int n=prices.size();
        vector<int> dp1(n),dp2(n);
        dp1[0]=-prices[0];//����״̬
        dp2[0]=0;//�ɽ���״̬
        for(int i=1;i<n;i++)
        {
            dp1[i]=max(dp1[i-1],dp2[i-1]-prices[i]);
            dp2[i]=max(dp2[i-1],dp1[i-1]+prices[i]-fee);
        }
        return max(dp1[n-1],dp2[n-1]);
}

//1. ���ⱳ��
//Ŀ�����ڹ�Ʊ�۸����� prices �У�ͨ������������������������������󡣣���������0/1/2�Σ�
//2. ״̬����
//����������ά DP ���飬׷�����ֺ���״̬��
//f[i][j]���� i �����ʱ�����й�Ʊ��������� j �ν��׵��������
//g[i][j]���� i �����ʱ�������й�Ʊ��������� j �ν��׵��������
//���У�
//i ��ʾ������0 �� n-1����
//j ��ʾ����ɵĽ��״�����0��1��2����Ϊ������� 2 �ν��ף���
//3. ��ʼ��
//�� 0 �죨i=0����
//f[0][0] = -prices[0]���� 0 �������Ʊ��0 �ν�����ɣ����й�Ʊ��
//g[0][0] = 0���� 0 �첻���Ʊ��0 �ν�����ɣ������й�Ʊ��������Ϊ 0
//��������dp�� ��һ��Ԫ�أ��� f[0][1]��g[0][2] �ȣ���ʼ��Ϊ��Сֵ MIN����ʾ��Щ״̬�ڵ� 0 �첻���ܴ��ڡ�
//4. ״̬ת��
//�ӵ� 1 �죨i=1����ʼ������ǰһ���״̬���µ�ǰ״̬��
//���ڳ��й�Ʊ��״̬ f[i][j]��j���ı䣬��Ϊ��û����ɽ��ף�
//������й�Ʊ�����ֿ��ܣ�
//ǰһ���ѳ��й�Ʊ������δ������f[i-1][j]��
//ǰһ�첻���й�Ʊ���������룺g[i-1][j] - prices[i]����ǰһ�첻���й�Ʊ�������ȥ��ǰ����ɱ�����
//ȡ������������ֵ��
//f[i][j] = max(f[i-1][j], g[i-1][j] - prices[i])

//���ڲ����й�Ʊ��״̬ g[i][j]
//���첻���й�Ʊ�����������
//�� j=0��0 �ν�����ɣ���ֻ����ǰһ��Ҳ�����й�Ʊ�� 0 �ν��ף��� g[i][0] = g[i-1][0]������Ҫ��Ϊ�˴���Խ�������
//�� j>0��1 �� 2 �ν�����ɣ��������ֿ��ܣ�
//ǰһ���Ѳ����й�Ʊ������δ������g[i-1][j]��
//ǰһ����й�Ʊ��������������ɵ� j �ν��ף���f[i-1][j-1] + prices[i]����ǰһ����й�Ʊ��������ϵ�ǰ�������棩��
//ȡ������������ֵ��
//g[i][j] = max(g[i-1][j], f[i-1][j-1] + prices[i])���� j>0 ʱ��
//5. �������
//ȡ��Щ״̬�����ֵ��Ϊ�����
//ret = max(f[n-1][0..2], g[n-1][0..2])
int maxProfit2(vector<int>& prices) {
    const int MIN=-0x3f3f3f3f;//0x3f3f3f3f��һ���ܴ������������ʾ����������������Ҳ�������
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
//k�ν��ף��޷Ǿ��ǽ�3��Ϊk+1��û�䣡
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

//����������//////////////////////////////////////////////////////////////////
//����������
//ѡ�� 1��������ǰ�ߵ������飬������ nums[i] ��Ϊ�����飨��Ӧ nums[i]����
//ѡ�� 2������ǰ���� i-1 ��β����������飨��Ӧ dp[i-1] + nums[i]����
//ȡ���ߵ����ֵ�������� i ��β�����Ž⡣
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

//�������������͡��ӵ�һ��Ԫ�ؿ�ʼ����n�����ȵ�vector��������һ���˼·������ֵ��
//��������ʱ�临�Ӷ�ΪO(n^2)���ᳬʱ��
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
//�Ż���
//��󷵻ص���ret1��total-ret2�����ֵ����Ϊret2����С��������ͣ�����total-ret2������������͡�
//ע�����ret1<0��˵������������Ԫ�ض��Ǹ�������ô���������;���ret1��
//�������������;���ret1��total-ret2�����ֵ��
//ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
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
    return ret1<0 ? ret1 : max(ret1,total-ret2);//��Ҫע��ȫ�Ǹ��������
}

//���������˻���
//�����˻������项Ҫ���������������ҵ��˻��������������顣�����������Ͳ�ͬ���˷������������ڣ�
//���� �� ���� = ������������С�˻����
//���� �� ���� = �����������ô�˻���С��
//��ˣ���ά������ǰ���˻����ǲ����ģ�����Ҫ׷�١���ǰ��С�˻�������Ϊ������С�˻����Ը������ܱ�����˻�����
//2. ��̬�滮״̬����
//���������� DP ���飺
//dp1[i]���Ե� i ��Ԫ��Ϊ��β�����˻�������ĳ˻���
//dp2[i]���Ե� i ��Ԫ��Ϊ��β����С�˻�������ĳ˻�������Ӧ�Ը����������
//3. ״̬ת���߼�������˼·��
//���ݵ�ǰԪ�� nums[i] �������ԣ��������������״̬��
//�� nums[i] < 0 ʱ��
//���˻� = max(nums[i], ǰһ����С�˻� �� nums[i])����Ϊ����������ǰһ����С�˻������Ǹ�������˺���ܱ�󣩡�
//��С�˻� = min(nums[i], ǰһ�����˻� �� nums[i])������ �� �������С��ǰһ�����˻���������������˺���ܱ���С����
//�� nums[i] �� 0 ʱ��
//���˻� = max(nums[i], ǰһ�����˻� �� nums[i])������ �� ��������󣩡�
//��С�˻� = min(nums[i], ǰһ����С�˻� �� nums[i])������ �� ���� / С�����С����
//ÿ�θ��º��� dp1[i] ˢ��ȫ�����ֵ ret��
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

//��ĳ˻�Ϊ���������鳤��
//��1����ǰԪ��Ϊ������nums[i-1] < 0��
//���� �� ���� = ��������ǰһ��λ���и��˻������飨g[i-1] > 0������ǰ���˻����� = ǰ�򸺳˻����� + 1�������޷��γ����˻���f[i] = 0��
//���� �� ���� = ��������ǰ���˻����� = ǰ�����˻����� + 1����ʹǰ�����˻�����Ϊ 0����ǰԪ������Ҳ��һ�����˻������飩
//��2����ǰԪ��Ϊ������nums[i-1] > 0��
//���� �� ���� = ��������ǰ���˻����� = ǰ�����˻����� + 1����ʹǰ��Ϊ 0����ǰԪ������Ҳ�����˻���
//���� �� ���� = ��������ǰһ��λ���и��˻������飨g[i-1] > 0������ǰ���˻����� = ǰ�򸺳˻����� + 1�������޷��γɸ��˻���g[i] = 0��
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

//�Ȳ����л���
int numberOfArithmeticSlices(vector<int>& nums) {
    int n=nums.size(),ret=0;
    if(n<3) return 0;
    vector<int> dp(n,0);
    for(int i=2;i<n;i++)
    {
        if(nums[i-1]*2-nums[i-2]==nums[i]) dp[i]=dp[i-1]+1;
        else dp[i]=0;
        ret+=dp[i];//ע��dp[i]��ʾ������iΪ��β�ĵȲ����еĸ������޷���ʾΪһ���ж��ٵȲ�����
        //�����Ҫ�ۼ�
    }
    return ret;
}

//����������飬����������ĺ���������Ԫ�صĴ�С��ϵ����仯���� �����С���� �� ��С�����С���������ֽ�����������������ڲ���λ�ã�����ԭ�����ȫ��������
//����ͨ������ż�����жϱ仯��ע���ʼ��ȫ����Ϊ1��
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

//�ǳ������dp���⣬
//���� dp[i] ��ʾ�ַ��� s ��ǰ i ���ַ��ܷ񱻲�ֳ��ֵ��еĵ������
//dp[0] ��ʼ��Ϊ true����ʾ���ַ������Ա����!!!
//�ַ���Ԥ����
//��ԭ�ַ��� s ǰ���һ���ո�Ŀ���Ǳ�������ӳ�䣬ʹ�ַ����±�� 1 ��ʼ���� dp �����������Ӧ

//״̬ת�ƹ��̣�
//���ѭ�������ַ�����ÿ��λ�� i���� 1 �� n��
//�ڲ�ѭ���������п��ܵĲ�ֵ� j���� 1 �� i��
//����ÿ�� i������Ƿ����һ�� j ʹ�ã�
//dp[j-1] Ϊ true����ǰ j-1 ���ַ����Ա���֣�
//�� j �� i ���Ӵ� s.substr(j, i-j+1) �������ֵ���
//����ҵ������� j�������� dp[i] Ϊ true �������ڲ�ѭ��
bool wordBreak(string s, vector<string>& wordDict) {
    //���ù�ϣ���ʼ�������ڲ���
    unordered_map<string,int> hash;
    for(const auto&e:wordDict) hash[e]++;
    int n=s.size();
    vector<bool> dp(n+1,false);
    dp[0]=true;
    s=" "+s;//�����±�ӳ��
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)//����˳������ν�������ң����ߴ��ҵ���
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

//dp[i] ��ʾ���� i λ�õ�Ԫ��Ϊ��β�������Ӵ����������ж��ٸ��� base �г��ֹ�
//�����������Ҫ��dp�����ۼ���������Ϊdp[i]�޷���ʾȫ�����
int findSubstringInWraproundString(string s) {
    int n=s.size(),ret=0;
    vector<int> dp(n+1,1);//dp[i]ֻ�ܱ�ʾ��s[i]Ϊ��β���Ӵ���������������Ҫͳ��֮��
    //��ȫ����ʼ��Ϊ1
    for(int i=1;i<=n;i++)
    {
        if(s[i-1]+1==s[i]||s[i-1]=='z'&&s[i]=='a') dp[i]=dp[i-1]+1;//���������������s[i]����+1��
        //�������1
    }

    int hash[26]={0};//����ͬ�ַ���β�ģ�ѡ����������Ϊ�ִ�������ȥ�أ�
    for(int i=0;i<n;i++)
    {
        hash[s[i]-'a']=max(hash[s[i]-'a'],dp[i+1]);
    }

    for(const auto&e:hash) ret+=e;
    return ret;
}

//ȫ��0�������飬����һ��ǳ����ƣ�ֻ��������Ҫȥ��
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

//�ҳ����е������Σ����Ƕ�άdp����ע��״̬ת�Ʒ��̣�������������Ҫѡ������б�Խǵ���Сdpֵ
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


//����������У�dp[i]��ʾ��iλ�õ�Ԫ��Ϊ��β������������еĳ��ȣ���̰���еİ汾����dp[i]Ϊ���ģ�
int lengthOfLIS(vector<int>& nums) {
    int ret=1,n=nums.size();
    vector<int> dp(n,1);//dp[i]��ʾ��iλ�õ�Ԫ��Ϊ��β������������еĳ���
    for(int i=1;i<n;i++)
    {
        //���������ⲻ�����������飬��Ҫ��0��i�������ҳ�����dp[j]+1��
        for(int j=0;j<=i;j++)
        {
            if(nums[j]<nums[i]) dp[i]=max(dp[i],dp[j]+1);
        }
        ret=max(ret,dp[i]);
    }
    return ret;
}

//�ڶ����У��Ѿ�����������󲿷��ˣ�
int wiggleMaxLength(vector<int>& nums) {
    int n=nums.size(),ret=1;
    vector<int> dp1(n,1),dp2(n,1);//dp1��β�½�,dp2�������
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

//����������е��������о��ǳ����룡
//�����������飺
//dp ���飺dp[i] ��ʾ�� nums[i] ��β������������еĳ��ȡ�
//count ���飺count[i] ��ʾ�� nums[i] ��β�ҳ���Ϊ dp[i] ������������еĸ�����

//��ʼ��������ÿ��Ԫ�� nums[i]����ʼʱ dp[i] = 1��������һ������Ϊ 1 �������� ����count[i] = 1��ֻ��������һ����� ����

//״̬ת�ƣ��������飬����ÿ�� i���ٱ��� j �� 0 �� i - 1��
//��� nums[i] > nums[j]��˵�����Խ����� nums[j] ��β�ĵ��������к����γɸ����������С���ʱ�Ƚ� dp[j] + 1 �� dp[i]��
//��� dp[j] + 1 > dp[i]����ô���� dp[i] = dp[j] + 1��ͬʱ count[i] = count[j]����Ϊ�µ�����ȶ�Ӧ�������и��������� j ��β�Ķ�Ӧ���� ����
//��� dp[j] + 1 == dp[i]����ô count[i] += count[j]��˵���ҵ����µĹ�����ͬ����������е����������Ӧ�����ۼ� ����

//�����������ҵ�����������еĳ��� max_len������ dp ����õ� ����Ȼ����� dp ���飬������ dp[i] == max_len ��Ӧ�� count[i] �ۼӣ��õ���������������еĸ�����
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

//���԰�����ת��������ѧ����һ��ģ�ͣ� 300. ����������С�������ǽ������ķ���Ӧ���ڡ�����������С����ģ���ϡ�
//���ö�̬�滮�������֮ǰ��Ӧ���Ȱ������Ÿ�����Ϊ�����ڼ��� dp[i] ��ʱ��Ҫ֪������������� pairs[i] ��������С�����ԡ�������֮��ֻ�á���ǰ����һ�项���ɡ�
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

//��ɾ��һ��Ԫ���Ժ�ȫΪ 1 ��������顱
//����������̬�滮���飺
//dp0[i]����ʾ�Ե� i ��Ԫ�ؽ�β��δɾ��Ԫ��ʱ���ȫΪ 1 �������鳤�ȡ�
//dp1[i]����ʾ�Ե� i ��Ԫ�ؽ�β���Ѿ�ɾ��һ��Ԫ�أ������ǵ�ǰԪ��ǰ���ĳ�� 0 ��Ҳ�����ǵ�ǰԪ�ر���ʱ���ȫΪ 1 �������鳤�ȡ�
//״̬ת�Ʒ��̣�
//�� nums[i] == 1 ʱ��
//dp0[i] = dp0[i - 1] + 1 ����Ϊ��ǰԪ���� 1 ��δɾ��Ԫ�ص�����Ⱦ���ǰһ��λ��δɾ��ʱ�ĳ��ȼ� 1 ��
//dp1[i] = dp1[i - 1] + 1 ���Ѿ�ɾ����Ԫ�ص�����£���ǰԪ���� 1 ��������֮ǰ��ɾ���Ļ����ϼ� 1 ��
//�� nums[i] == 0 ʱ��
//dp0[i] = 0 ����Ϊ��ǰԪ���� 0 ��δɾ��Ԫ��ʱ�޷��γ�ȫ 1 �����飬��������Ϊ 0 ��
//dp1[i] = dp0[i - 1] ����ʱɾ����ǰ��� 0 ����ô���Ⱦ͵���ǰһ��λ��δɾ��Ԫ��ʱ���ȫ 1 �����鳤�ȡ�
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

//����������С� ���⣬Ѱ����������������У�ʹ��������������Ԫ�صĲ���ڸ����� difference
//����ת����
//���������е�ÿ��Ԫ�� arr[i]���������һ��Ԫ�� arr[j] = arr[i] - difference��j < i����
//��ô�� arr[i] ��β������������г��ȣ��͵����� arr[j] ��β������������г��ȼ� 1������ arr[i] ���� arr[j] ���棩��
//��������������� arr[j]������ arr[i] ��β������������г��Ⱦ��� 1��������������
//��̬�滮 + ��ϣ��
//�ù�ϣ�� hash ��¼��ĳ��ֵΪ��β������������г��ȣ���ΪԪ��ֵ��ֵΪ��Ӧ������ȡ�
//��������ʱ������ÿ��Ԫ�� arr[i]��ͨ�� hash[arr[i] - difference] �����ҵ�ǰһ������������Ԫ�ص�����ȣ��Ӷ����㵱ǰԪ�ص�����ȡ�
//���ϸ��¹�ϣ���ȫ�����ֵ�����յõ������
int longestSubsequence(vector<int>& arr, int difference) {
    int n=arr.size(),ret=0;
    unordered_map<int,int> hash;//{Ԫ��ֵ������������г���}
    hash[arr[0]]=1;
    for(int i=1;i<n;i++)
    {
        hash[arr[i]]=hash[arr[i]-difference]+1;
        ret=max(ret,hash[arr[i]]);
    }
    return ret;
}

//�쳲����������еĳ���
//dp[i][j] ��ʾ���� i λ���Լ� j λ�õ�Ԫ��Ϊ��β�����е��������У����쳲�������
//���еĳ��ȡ��涨һ�� i < j ��
//2. ״̬ת�Ʒ��̣�
//�� nums[i] = b, nums[j] = c ����ô������е�ǰһ��Ԫ�ؾ��� a = c - b �����Ǹ�
//�� a ��������ۣ�
//i. a ���ڣ��±�Ϊ k ������ a < b ����ʱ������Ҫ�� k λ���Լ� i λ��Ԫ��Ϊ��β��
//�쳲����������еĳ��ȣ�Ȼ���ټ��� j λ�õ�Ԫ�ؼ��ɡ����� dp[i][j] =
//dp[k][i] + 1 ��
//ii. a ���ڣ����� b < a < c ����ʱֻ������Ԫ���Լ����ˣ� dp[i][j] = 2 ��
//iii. a �����ڣ���ʱ����ֻ������Ԫ���Լ����ˣ� dp[i][j] = 2 ��
//�Ż��㣺���Ƿ��֣���״̬ת�Ʒ����У�������Ҫȷ�� a Ԫ�ص��±ꡣ������ǿ����� dp ֮ǰ�������еġ�Ԫ�� + �±꡹����һ�𣬷ŵ���ϣ���С�
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
    return ret<3 ? 0 : ret;//���еĳ��ȱ������3
}

//��Ȳ����еĳ��ȣ�������һ��ǳ����ƣ����ǲ�ͬ���ǣ���һ��Ļ���ͬһ������Ӧ��ͬ�±�
//a. �� dp ֮ǰ�������ϣ���С����ǿ��Եģ�������Ҫ���±��γ�һ������Ž���ϣ���С�����
//ʱ�临�ӶȽϸߣ��Ұ����Թ��ˣ���ʱ��
//b. һ�� dp ��һ�߱��档���ַ�ʽ�����ǽ��豣�������Ԫ�ص��±꣬���ñ����±����顣����
//�����ַ����Ļ��������ڱ���˳������ȹ̶������ڶ��������ٱ���������һ������������
//������ i ʹ����ʱ�򣬽� nums[i] �ӵ���ϣ����
int longestArithSeqLength(vector<int>& nums) {
    int n=nums.size(),ret=0;
    vector<vector<int>> dp(n,vector<int>(n,1));
    unordered_map<int,int> hash;
    hash[nums[0]]=0;
    for(int i=0;i<n;i++)
    {
        //������ͬ��������ѡ���±꿿��ģ�������֤�������
        //���������ڱ���˳������ȹ̶������ڶ��������ٱ���������һ��������ô����ԭ�����������ǰ��Ļ�����ϣ���ֵһֱ�ڱ䣬�𲻵�Ч��
        //�����ڱ����� i λ��ʱ�򣬹�ϣ���б������ i λ��֮ǰ��Ԫ�ص��±꣬�������ǿ���
        //ֱ��ʹ�ù�ϣ���б�����±꣬������ dp[i][j] ��
        for(int j=i+1;j<n;j++)
        {
            if(hash.count(nums[i]*2-nums[j])) dp[i][j]=dp[hash[nums[i]*2-nums[j]]][i]+1;
            else dp[i][j]=2;

            ret=max(ret,dp[i][j]);
        }
        hash[nums[i]]=i;//�����ˣ��Ϳ����ӵ���ϣ������
    }
    return ret;
}

//�Ȳ����л��֣���ǰ�����������ƣ������Ƚ���ֵ���±�������ж�Ӧ��Ȼ��̶�������һ����
//���������ڶ���������Ҫע��long long��ֹ��������ڿ���һ�������ֶ�Σ�����dp[j][i]+=dp[e][j]+1;
//һ��dp[e][j]��Ҫ+1������±���Ҫ�����еļ�����������
int numberOfArithmeticSlices1(vector<int>& nums) {
    int n=nums.size(),ret=0;
    vector<vector<int>> dp(n,vector<int>(n,0));
    unordered_map<long long,vector<int>> hash;
    for(int i=0;i<n;i++) hash[nums[i]].push_back(i);//�ù�ϣ����ֵ���±�����󶨣����ڲ���
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)//���ﲻ����j=i����Ϊi�ǵ�����һ������j�ǵ����ڶ��������������
        {
            long long tmp=(long long)nums[j]*(long long)2-nums[i];
            if(hash.count(tmp))
            {
                for(const auto&e:hash[tmp])
                {
                    if(e<j) dp[j][i]+=dp[e][j]+1;//ע����һ��
                }
                ret+=dp[j][i];
            }
        }
    }
    return ret;
}

//���Ĵ�����////////////////////////////////////////////////
//��ע����һ���˼·�ǳ��ؼ�������ʹ��һ����ά����dp[i][j]��ʾi��j�Ƿ�Ϊ���Ĵ�
//���s[i]==s[j]�����������ͬһ���ַ����������ַ�Ϊtrue������ȡ����dp[i+1][j-1]
//���s[i]!=s[j]����ôdp[i][j]Ϊfalse
int countSubstrings(string s) {
    int n=s.size(),ret=0;
    vector<vector<bool>> dp(n,vector<bool>(n,0));
    for(int i=n-1;i>=0;i--)
    {
        for(int j=i;j<n;j++)//��ע�����˳��iҪȡ���jҪ���ڵ���i
        {
            if(s[i]==s[j]) dp[i][j]= j-i>1 ? dp[i+1][j-1] : true;
            else dp[i][j]=false;

            if(dp[i][j]) ret++;
        }
    }
    return ret;
}

//������ִ����⣬ǰ�����������չ�㷨��������ö�̬�滮
//ʵ�������������Ŀ�ǳ����ƣ������ö�ά������i��j���ִ��Ƿ�Ϊ���Ĵ�������Ҫ����Ļ��Ĵ�����ô����ret����
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

//Ѱ�����������Ӵ����������ѣ�ʵ����dp��Ǿ���Ļ��Ĵ�֮��ֻ��Ҫ�ҵ�����
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

//���Ĵ��Ļ��֣�ע�����ⲻ����һ��򵥵Ļ����ˣ�����Ҫ�õ���̬�滮��������ٵĻ��ִ���
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
    vector<int> Dp(n,0x3f3f3f3f);//���Dp�������i��β������Ĵ������ٷָ����
    //ע���ʼ������ȫ��Ϊ0����Ӱ���ж�
    for(int i=0;i<n;i++)
    {
        if(dp[0][i]) Dp[i]=0;
        else
        {
            for(int j=0;j<=i;j++)
            {
                if(dp[j][i]) Dp[i]=min(Dp[i],Dp[j-1]+1);
                //������ǰ��ĵ��ʻ��ַǳ����ƣ������ǽ����ʱ����ڹ�ϣ���У������ö�άdp�����Ƿ���Ķ���
                //���j��i���ģ���ô���ִ���Ϊj-1��Ӧ��ֵ+1������dp[i]Ҫȡ��Сֵ
            }
        }
    }
    return Dp[n-1];
}

//��һ�ⷢ��ǰ���ö�ά����dp[i][j]��ʾi��j������������и����ò��ϣ��������뵽��������������������ƣ�
//����˵dp[i][j]��ʾi��j������������еĳ��ȣ�����״̬ת�Ʒ������漰dp[i+1][j-1]�����Ծ��������˳��
//��ǰ�����ƣ����s[i]==s[j]�������������i==j,i+1==j,i+1<j�����ȷֱ�Ϊ1,2,dp[i+1][j-1]+2;
//���������أ���Ҫȥdp[i+1][j],dp[i][j-1]�ҵ����ģ�Ϊʲô�����������м��������أ���Ϊ�Ѿ�������ȥ�ˡ�
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

//�¸ҳ�����һ�£���Ȼ���ˣ�ԭ��������һ��ǳ����ƣ�����Ҫ��s���������Ĳ��룬�����dp[i][j]��ʾi��j�����ٲ������
//���s[i]==s[j]����ôdp[i][j]=dp[i+1][j-1]������dp[i][j]=min(dp[i+1][j-1]+2,min(dp[i+1][j]+1,dp[i][j-1]+1))
//Ĭ��dp[i+1][j]��dp[i][j-1]�����Ѿ����ĵ��ַ��������ұ�ʾ���ٲ��������ȡ��Сֵ���ɣ�
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

//��������� dp �����ַ������飩//////////////////////////////////////////////////////////
//����Ϊģ���⣬���������ַ�����dp��Ҫ����һ����ά���飬�࿪��һ��һ������ʼ��
//ѡȡ��һ������ [0, i] �����Լ��ڶ������� [0, j] ������Ϊ�о�����dp[i][j] ��ʾ�� s1 �� [0, i] �����Լ� s2 �� [0, j] �����ڵ����е��������У�����������еĳ��ȡ�
int longestCommonSubsequence(string test1, string test2) {
    int n=test1.size(),m=test2.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));//��ʼ��Ϊ0��ֹԽ����ʣ��͵����ǿմ�������Ϊ0
    //dp[i][j]��ʾ0-i��0-j��ij��β���ַ��������й��������е����ֵ
    test1=" "+test1;test2=" "+test2;//��ô����Ϊ�˷����±�ʱ����-1
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(test1[i]==test2[j]) dp[i][j]=dp[i-1][j-1]+1;//�����β�ַ���ͬ��i-1 j-1�ĳ���+1
            else
            {
                //�������Ⱦ�ȥ0~i 0~j-1/0~i-1 0~j/0~i-1 0~j-1��Ѱ�����ֵ�������������Ļ������ܻᵼ���ظ����������������ֵ�Ļ����������
                dp[i][j]=max(dp[i][j-1],max(dp[i-1][j],dp[i-1][j-1]));
            }
        }
    }
    return dp[n][m];
}

//����������е�Ӧ�ã�����ཻ�ߣ���Ҫ�Խת��һ��
int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int n=nums1.size(),m=nums2.size();
    //ת��ΪѰ������������е����⣬������������Ѱ���������ĳ���
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

//����������е�Ӧ�ã���ͬ��������
int numDistinct(string s, string t) {
    //dp[i][j] ��ʾ�����ַ��� s ��[0, j] �����ڵ������������У��ж��ٸ� t �ַ���[0,i] �����ڵ��Ӵ���
    s=" "+s;t=" "+t;//���ڷ����±�
    int m = t.size(), n = s.size();
    vector<vector<double>> dp(m + 1, vector<double>(n + 1));
    for(int j = 0; j <= n; j++) dp[0][j] = 1; // ��ʼ��
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
        {
            dp[i][j] += dp[i][j - 1];//����ͷ������һ���ַ���ȥ0~i 0~j-1����
            if(t[i] == s[j]) dp[i][j] += dp[i - 1][j - 1];//���һ���ַ���ͬ������0~i-1 0~j-1�Ľ��
        }
    return dp[m][n];
}

//����һ�������������⣬Ҫ��������
//�� s[i] == p[j] �� p[j] == '?' ��ʱ�򣬴�ʱ�����ַ���ƥ�����˵�ǰ��һ����
//����ֻ�ܴ� dp[i - 1][j - 1] �п���ǰ�ַ�ǰ��������Ӵ��Ƿ�ƥ�䡣ֻ�ܼ̳��ϸ�
//״̬�е�ƥ������ dp[i][j] = dp[i][j - 1] ��

//�� p[j] == '*' ��ʱ�򣬴�ʱƥ�����������ѡ��
//һ��ѡ���ǣ� * ƥ����ַ�������ʱ�൱����ƥ����һ����į��ֱ�Ӽ̳�״̬ dp[i]
//[j - 1] ����ʱ dp[i][j] = dp[i][j - 1] ��
//��һ��ѡ���ǣ� * ��ǰƥ�� 1 ~ n ���ַ���ֱ��ƥ�������� s1 ������ʱ�൱��
//�� dp[k][j - 1] (0 <= k <= i) ������ƥ������У�ѡ���Լ̳п��Գɹ���
//�������ʱ dp[i][j] = dp[k][j - 1] (0 <= k <= i) ��
//�� p[j] ���������ַ����Ҳ��� s[i] ���ʱ���޷�ƥ��
bool isMatch(string s, string p) {
    //��������û���κ��Ż���dp
    int n=s.size(),m=p.size();
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    dp[0][0]=true;
    s=" "+s;p=" "+p;
    for (int j = 1; j <= m; j++)
    {
        // ���p[j]��*�����sƥ��p[1..j] �ȼ��� ��sƥ��p[1..j-1]��*ƥ��0���ַ���
        if (p[j] == '*') dp[0][j] = dp[0][j - 1];
    }
    //dp[i][j]��Ҫ��ʾ����0~j��0~i�Ƿ�ƥ��
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s[i]==p[j]||p[j]=='?') dp[i][j]=dp[i-1][j-1];
            else if(p[j]=='*')
            {
                dp[i][j]=dp[i-1][j]||dp[i][j-1];
                //�Ż�״̬ת�Ʒ��̣�
                // dp[i][j] = dp[i][j - 1] || dp[i - 1][j - 1] || dp[i - 2][j - 1]......
                //���Ƿ��� i ���й��ɵļ�С�ģ��������ȥ���� dp[i - 1][j] ��
                //             dp[i - 1][j] = dp[i - 1][j - 1] || dp[i - 2][j - 1] || dp[i - 3][j - 1] ......
                //��ôdp[i][j]=dp[i-1][j]||dp[i][j-1];
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

//������һ��ǳ����ƣ�ֻ��������һ���Ǻſ���ƥ��ǰ����ַ�0�λ��߶��
bool isMatch1(string s, string p) {
    int n=s.size(),m=p.size();
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    s=" "+s;p=" "+p;
    dp[0][0]=true;
    //0~i 0~j���о�����ǰ��һ��
    //���ĵĳ�ʼ��
    for(int j=1;j<=m;j++) if(p[j]=='*') dp[0][j]=dp[0][j-2];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s[i]==p[j]||p[j]=='.') dp[i][j]=dp[i-1][j-1];
            else if(p[j]=='*')
            {
                //���ﲻ��д��dp[i][j] = dp[i-1][j] || dp[i][j-2];��Ϊs[i]��p[j - 1]���ܲ�ƥ�䣬������
                dp[i][j] = dp[i][j - 2];

                //��ǰ����ַ���s[i]ƥ�䣬�ٿ���ƥ���Σ�������ʹ�� || dp[i-1][j]
                if(s[i] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    return dp[n][m];
}

//�����ַ������Ѿ���ܼ򵥵�dp�ˣ�ע���ʼ����
bool isInterleave(string s1, string s2, string s3) {
    int n=s1.size(),m=s2.size(),k=s3.size();
    if(n+m!=k) return false;
    s1=" "+s1;s2=" "+s2;s3=" "+s3;//���ڷ����±�
    //dp[i][j] ��ʾ�ַ��� s1 �� [1, i] �����ڵ��ַ����Լ� s2 �� [1, j] �����ڵ��ַ������ܷ�ƴ�ӳ� s3 �� [1, i + j] �����ڵ��ַ�����
    vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
    dp[0][0]=true;
    for(int i=1;i<=n;i++)
    {
        //��ʼ�������s3��ǰi���ַ���s1��ǰi���ַ���ͬ����ôdp[i][0]Ϊtrue��������涼Ϊfalse
        if(s3[i]==s1[i]) dp[i][0]=true;
        else break;
    }
    for(int i=1;i<=m;i++)
    {
        //��ʼ�������s3��ǰi���ַ���s2��ǰi���ַ���ͬ����ôdp[0][i]Ϊtrue��������涼Ϊfalse
        if(s3[i]==s2[i]) dp[0][i]=true;
        else break;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            //������||��ֹ�ظ�����
            //���s3�����һ���ַ���s1�����һ���ַ���ͬ����ô��ȥ��s1�����һ���ַ�������ǰ����Ƿ�ƥ��
            //���s3�����һ���ַ���s2�����һ���ַ���ͬ����ô��ȥ��s2�����һ���ַ�������ǰ����Ƿ�ƥ��
            //���������ͬ����ô�϶���ƥ��
            //ע�������i,j�Ǵ�1��ʼ�ģ�����Ҫ��i+j������s3
            dp[i][j]=(s3[i+j]==s1[i]&&dp[i-1][j])||(s3[i+j]==s2[j]&&dp[i][j-1]);
        }
    }
    return dp[n][m];
}

//�����ַ�����ɾ���������о��ǳ�����
//�����򷴣��������ַ�������С ASCII ɾ���ͣ���ʵ�����ҵ������ַ��������еĹ������������棬 ASCII ���͡�
//��ˣ����ǵ�˼·���ǰ��ա�����������С��ķ�����ʽ������
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

//��ظ������飬ע�������������е������������������ģ�������Ҫret��ʵʱ����
//״̬ת�Ʒ��̱Ƚ����ױ�ʾ��
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

//�������⣡����//////////////////////////////////////////////////////
//һ��0-1 �������������
//�� n ����Ʒ��ÿ����Ʒ���������ԣ����� w[i] �ͼ�ֵ v[i]��ÿ����Ʒֻ��ѡһ�Σ�Ҫôѡ��Ҫô��ѡ��������������Ϊ C���󱳰���װ�������ֵ��
//�ⷨ˼·����̬�滮����
//״̬���壺�� dp[i][j] ��ʾ ����ǰ i ����Ʒ��ѡ�������������� j ʱ������ֵ����
//״̬ת�ƣ��Ե� i ����Ʒ��������ѡ��
//��ѡ��dp[i][j] = dp[i-1][j]����ֵ��ǰ i-1 ����Ʒ��ͬ����
//ѡ��ǰ���� j >= w[i]����dp[i][j] = dp[i-1][j - w[i]] + v[i]����ֵ = ǰ i-1 ����Ʒ������ j-w[i] �µ�����ֵ + ��ǰ��Ʒ��ֵ����
//��ˣ�ת�Ʒ���Ϊ��
//             dp[i][j] = max(dp[i-1][j], (j >= w[i] ? dp[i-1][j - w[i]] + v[i] : 0))
//�ռ��Ż����۲췢�֣�dp[i][j] ֻ������ dp[i-1][...]����һ�У�����˿ɽ���ά�����Ż�Ϊһά���� dp[j]�����Ӻ���ǰ���������⸲����һ��δʹ�õ����ݣ���
//��������� dp[C] ��Ϊ����ֵ����Ϊ dp[j] ����Ϊ ������������ j ������ֵ������Ȼ���������Ž⣩��

//������ȫ��������Ʒ������ѡ��
//���ⶨ�壺
//�� 0-1 �������ƣ���ÿ����Ʒ����ѡ���޴Σ�ֻҪ������������������
//�ⷨ˼·��
//״̬���壺���� dp[j] ��ʾ ������������ j ʱ������ֵ������������չΪ �����ظ�ѡ��Ʒ����
//״̬ת�ƣ�������Ʒ���ظ�ѡ��ѡ�� i �����Կ���ѡ����˴�ǰ��������������ظ�ʹ�õ�ǰ��Ʒ��״̬����
//���������� 0-1 ������Ψһ�����Ǳ���˳�� ���� ��ȫ������������������ظ�ѡ����0-1 ���������������ֹ�ظ�ѡ����

//�������ر�������Ʒ���޴�ѡ��
//���ⶨ�壺
//ÿ����Ʒ�й̶��������ƣ���� i �����ѡ k[i] �Σ������� 0-1 ������k=1������ȫ������k=�ޣ�֮�䡣
//�ⷨ˼·��
//����˼·���� ����� k ���� ��� k ��������Ʒ��ת��Ϊ 0-1 ���������� k �ܴ�ʱ���� 1e5����Ч�ʼ��͡�
//�Ż��������Ʋ�֣��� k ���Ϊ 2^0, 2^1, ..., 2^m, r��r = k - (2^{m+1}-1)��������Щ ����������ϡ� ��ʾ 0~k �����п��ܴ��������� k=5 �ɲ�Ϊ 1,2,2��1+2+2=5����ͨ��ѡ��ѡ��Щ��ϣ��ܸ��� 0~5 �����д�������ֺ���Ʒ������ k ���� log2(k)������ 0-1 �����ⷨ���ɡ�

//���ӣ�
void package_01()
{
    int n=0,val=0;
    cin>>n>>val;
    //��һ��װ�������������
    //״̬��ʾ��
    //dp[i][j] ��ʾ����ǰ i ����Ʒ����ѡ����������������� j �����е�ѡ���У�����ѡ����������ֵ��
    //i. ��ѡ�� i ����Ʒ���൱�ھ���ȥǰ i - 1 ����Ʒ����ѡ����������������� j ����
    //ʱ dp[i][j] = dp[i - 1][j] ��
    //ii. ѡ��� i ����Ʒ����ô�Ҿ�ֻ��ȥǰ i - 1 ����Ʒ�У���ѡ����������� j - v[i]
    //����Ʒ����ʱ dp[i][j] = dp[i - 1][j - v[i]] + w[i] ����������״̬��һ�����ڣ������Ҫ����һ�¡�
    //���ϣ�״̬ת�Ʒ���Ϊ�� dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] +
    //w[i]) ��
    vector<vector<int>> items(n+1,vector<int>(val+1,0));
    vector<int> w(n+1,0),v(n+1,0);
    for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=val;j++)
        {
            //0-1����
            if(j-v[i]>=0) items[i][j]=max(items[i-1][j],items[i-1][j-v[i]]+w[i]);//ѡ��ǰ��Ʒ
            else items[i][j]=items[i-1][j];//��ѡ��ǰ��Ʒ
        }
    }
    cout<<items[n][val]<<endl;
    items.resize(n+1,vector<int>(val+1,0));
    //ǡ��װ����������������ʹ����װ����״̬���-1
    for(int j=1;j<=val;j++) items[0][j]=-1;//���ǡ��Ϊj������ѡ��Ʒ��״̬�ǲ����ڵ�
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=val;j++)
        {
            items[i][j]=items[i-1][j];//��ѡ��ǰ��Ʒ��ȥǰi-1����Ʒ��������ǡ��Ϊj��״̬
            if(j-v[i]>=0&&items[i-1][j-v[i]]!=-1) items[i][j]=max(items[i-1][j],items[i-1][j-v[i]]+w[i]);
            //j-v[i]ȷ����Խ�磬���һ���ʣ��������items[i-1][j-v[i]]!=-1ȷ��״̬����
        }
    }
    cout<< (items[n][val]==-1 ? 0 : items[n][val])<<endl;

}

//����ѡ�ù������������пռ��Ż���ע�⵽�����״̬ת�Ʒ����У�dp[i][j]ֻ������ dp[i-1][...]����һ�У���
//��˿ɽ���ά�����Ż�Ϊһά���� dp[j]�����Ӻ���ǰ���������⸲����һ��δʹ�õ����ݣ�
void package_01_Pro()
{
    int n=0,val=0;
    cin>>n>>val;
    vector<int> w(n+1,0),v(n+1,0);
    for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
    vector<int> items(val+1,0);
    for(int i=1;i<=n;i++)
    {
        for(int j=val;j>=1;j--)//ע�������ǴӺ���ǰ���������⸲����һ��δʹ�õ�����
        {
            //�������������飬�������ﲻѡ��ǰ��Ʒ��״̬����items[j]�����ø�����
            if(j-v[i]>=0) items[j]=max(items[j],items[j-v[i]]+w[i]);
        }
    }
    cout<<items[val]<<endl;
    items.resize(val+1,0);
    //ǡ��װ������
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

//�ָ�Ⱥ��Ӽ���0-1�����ı��Σ�����ת��ΪѰ�ұ���ǡ��װ��������Ϊsum/2��������ֵ
//�������Ʒ��ֵ��������
bool canPartition(vector<int>& nums) {
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if(sum%2) return false;
    int t=sum/2;//��������
    vector<int> dp(t+1,-1);dp[0]=0;//��ʼ��������Ϊ0ʱ����ֵΪ0
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=1;j--)//�Ӻ���ǰ����
        {
            if(j-nums[i]>=0&&dp[j-nums[i]]!=-1) dp[j]=max(dp[j],dp[j-nums[i]]+nums[i]);
        }
    }
    return dp[t]==t;
}
//�߼��ǶԵģ�����״̬��ʾ����ѡ���i��Ԫ�غ��ܷ���ӽӽ�Ŀ�꣬�����Ǹ�׼ȷ��״̬��ʾ��
bool canPartition1(vector<int>& nums) {
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if(sum%2) return false;
    int t=sum/2;//��������
    vector<bool> dp(t+1,false);dp[0]=true;//dp[i]��ʾ�ܷ�õ���Ϊi���Ӽ�
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=1;j--)//�Ӻ���ǰ����
        {
            if(j-nums[i]>=0) dp[j]=dp[j]||dp[j-nums[i]];
        }
    }
    return dp[t];
}

//Ŀ��ͣ�����ѡ��dfs�������ṩdp�ķ�����
int findTargetSumWays(vector<int>& nums, int target) {
    //��ѡ��+������֮��Ϊa��ѡ��-������֮��Ϊb����a+b=sum��a-b=target
    //��t=(sum+target)/2;ѡ������ʹ��Ϊt
    int sum=0,n=nums.size();
    for(const auto&e:nums) sum+=e;
    if((sum+target)%2||sum+target<0) return 0;
    int t=(sum+target)/2;//����
    //����dp[i]��ʾǰi���ĺ�Ϊi��ѡ�񷽷�
    vector<int> dp(t+1,0);dp[0]=1;//��ʼ��
    for(int i=0;i<n;i++)
    {
        for(int j=t;j>=nums[i];j--)//����ֱ�ӽ�����������ںϣ���ֹ���ֺͿ���Ϊ0��©������
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