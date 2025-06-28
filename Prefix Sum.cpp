#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//前缀和：
//前缀和是一个数组的前缀和数组，前缀和数组的第i个元素表示原数组中前i个元素的和
//前缀和是用来干嘛的？
//快速求出数组中某一个连续区间的和
//分为两步：第一步：预处理出来一个前缀和数组，（前缀和数组的第i个元素表示原数组中前i个元素的和）
//第二步：根据前缀和数组快速求出某一个连续区间的和

//一般将前缀和数组用dp命名，这里是一个小的动态规划，
//请注意数组的下标是从1开始的，为了防止从0开始计数将dp0=0

//算法1：
//一维 ： 前缀和数组的求法
//arr  0 1 2 3 4 5 6 7 8 9 10
//      /|/|/|/|/|/|/|/|/|/|
//dp   0 1 2 3 4 5 6 7 8 9 10
//使用前缀和：dp[r] - dp[l - 1]
void PrefixSum_singledimension()
{
    int n = 0; int q = 0;
    cin >> n >> q;
    vector<int> arr(n + 1, 0);
    vector<long long int> dp(n + 1, 0);
    //将数据读入到arr中
    for (int i = 1; i <= n; i++) cin >> arr[i];
    //将数据读入到dp中
    for (int i = 0; i <= n; i++) dp[i] = dp[i - 1] + arr[i];
    //直接读取dp数组
    for (int i = 0; i < q; i++)
    {
        int l = 0; int r = 0;
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << endl;
    }
}

//算法2：
//二维 ： 前缀和数组的求法
//                   y1      y2
    //------------------------
    //|              |       |
    //|              |       |
    //|     A        |   B   |
    //|              |       |
  //x1|--------------|-------|
    //|     C        |   D   |
  //x2---------------|-------|
//二维数组:dp如何存储，dp[i][j]表示从(1,1)到(i,j)的和，dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + arr[i][j]
//等价于B+C-A+D
//使用前缀和：dp[r][r] - dp[l-1][r] - dp[r][l-1] + dp[l-1][l-1]
//等价于D+A-B-C
void PrefixSum_twodimension()
{
    int n = 0; int m = 0; int q = 0;
    cin >> n >> m >> q;
    vector<vector<long long int>> arr(n + 1, vector<long long int>(m + 1));//居然还可以这么初始化
    vector<vector<long long int>> dp(n + 1, vector<long long int>(m + 1));//这里初始化的方式要记住
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int tmp = 0; cin >> tmp;
            arr[i][j] = tmp;
        }
    }
    //将数据放入到dp数组
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }
    //使用dp数组
    for (int i = 0; i < q; i++)
    {
        int x1 = 0; int x2 = 0;
        int y1 = 0; int y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1] << endl;
    }
}

//算法三：对前缀和数组dp的运用
int pivotIndex(vector<int>& nums) {
    int size = nums.size();
    vector<int> arr(size + 1, 0);
    for (int i = 1; i <= size; i++) { arr[i] = nums[i - 1]; }
    vector<int> dp(size + 1, 0);
    for (int i = 1; i <= size; i++) { dp[i] = dp[i - 1] + arr[i]; }

    for (int i = 0; i < size; i++)
    {
        int leftSum = 0; int rightSum = 0;
        if (i == 0) leftSum = 0;
        else leftSum = dp[i] - dp[0];
        if (i + 2 > size) rightSum = 0;
        else rightSum = dp[size] - dp[i + 1];

        if (rightSum == leftSum) return i;
    }
    return -1;
}

//算法四：前缀和的变形，前缀积，
//因为题目规定，不能使用除法，那么就不能像前缀和那样将-替换为/
//这里就需要两个vector，一个是前缀积，一个是后缀积
//运用非常巧妙，但是不要忘记前缀积要对nums[i]进行处理
//而后缀积不需要对nums[i]进行处理
//前缀积：dp[i] = dp[i-1] * arr[i]
//后缀积：dp[i] = dp[i+1] * nums[i]
vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> ret;
    int size = nums.size();
    ret.reserve(size);
    vector<int> arr(size + 1, 0);
    for (int i = 0; i < size; i++) arr[i + 1] = nums[i];
    vector<int> left(size + 1, 1);
    vector<int> right(size + 1, 1);
    for (int i = 1; i <= size; i++)
    {
        left[i] = left[i - 1] * arr[i];
    }
    for (int i = size-1; i >= 0; i--)
    {
        right[i] = right[i + 1] * nums[i];
    }
    for (int i = 1; i <= size; i++)
    {
        ret.push_back(left[i-1] * right[i]);
    }
    return ret;
}


//算法五：和为k的子数组
//注意：这里不能使用滑动窗口，因为滑动窗口是有序的，而这里是无序的
//并且数组中可能有负数，多加注意!
//使用前缀和+哈希表
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> hash;
    int sum = 0; int ret = 0;
    hash[0] = 1;//防止全部和为k而找不到区间，hash0=1；
    for (const auto& e : nums)
    {
        //本质上是在0-i这个区间上，寻找前缀和为sumi-k的区间
        //可以理解为k也是一段区间的和，为什么ret+=值
        //因为存在负数和0，可能有多个区间的和相同
        sum += e;
        if (hash[sum - k]) ret += hash[sum - k];
        hash[sum]++;
    }
    return ret;
}

//算法六：改编自算法五
//补充同余定理：（a-b）%c = 0，那么a%c = b%c
//补充负数取模：（a%c+c)%c
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> hash;
    hash[0] = 1; int sum = 0; int ret = 0;
    for (const auto& e : nums)
    {
        sum += e;
        if (hash[(sum % k + k) % k]) ret += hash[(sum % k + k) % k];
        hash[(sum % k + k) % k]++;
        //注意这里与上一题不同的地方在于，hash中存储的是前缀和的余数
    }
    return ret;
}

//算法七：改编自算法五
//如果把0替换为-1，那么就可以将问题转化为和为0的子数组，非常巧妙
//这里我用哈希表第二个pair来存储len以及个数
//当第一次符合条件的时候设置len即可，这样就可以确保求出来的ret是最大的
//注意：这里的len是从1开始的，所以hash[0].first = 0; hash[0].second = 1;
//老师讲解时第二个存储int代表坐标，需要处理更多的细节问题，仅供参考
//这题最关键的一步便是将0替换为-1，这样就可以使用前缀和的思想来处理目标子数组和为0的问题
int findMaxLength(vector<int>& nums) {
    int sum = 0; int len = 0; int ret = 0;
    unordered_map<int, pair<int, int>> hash;
    hash[0].first = 0; hash[0].second = 1;
    for (auto& e : nums)
    {
        len++;
        if (e == 0) sum += -1;
        else sum += 1;
        if (hash[sum - 0].second)
        {
            if (len - (hash[sum - 0].first) > ret) ret = len - (hash[sum - 0].first);
        }
        if (!hash[sum].second) hash[sum].first = len;
        (hash[sum].second)++;
    }
    return ret;
}

//算法八：二维前缀和的变形
vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    int m = mat.size(); int n = mat[0].size();
    vector<vector<int>> arr(m +1, vector<int>(n +1, 0));
    vector<vector<int>> dp(m +1, vector<int>(n +1, 0));
    vector<vector<int>> ret(m, vector<int>(n, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
			arr[i][j] = mat[i - 1][j - 1];
        }
    }
    //将数据放入到dp数组
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }
	//这里dp数组没有必要多开2*k的空间，即使在计算时候便于思考，但是坐标的处理会很麻烦
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {   //注意边界条件的处理！非常重要
			ret[i - 1][j - 1] = dp[min(i + k, m)][min(j + k, n)] - 
                dp[min(i + k, m)][max(j - k - 1, 0)] - 
                dp[max(i - k - 1, 0)][min(j + k, n)] + 
                dp[max(i - k - 1, 0)][max(j - k - 1, 0)];
        }
    }
    return ret;
}


