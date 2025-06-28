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

//ǰ׺�ͣ�
//ǰ׺����һ�������ǰ׺�����飬ǰ׺������ĵ�i��Ԫ�ر�ʾԭ������ǰi��Ԫ�صĺ�
//ǰ׺������������ģ�
//�������������ĳһ����������ĺ�
//��Ϊ��������һ����Ԥ�������һ��ǰ׺�����飬��ǰ׺������ĵ�i��Ԫ�ر�ʾԭ������ǰi��Ԫ�صĺͣ�
//�ڶ���������ǰ׺������������ĳһ����������ĺ�

//һ�㽫ǰ׺��������dp������������һ��С�Ķ�̬�滮��
//��ע��������±��Ǵ�1��ʼ�ģ�Ϊ�˷�ֹ��0��ʼ������dp0=0

//�㷨1��
//һά �� ǰ׺���������
//arr  0 1 2 3 4 5 6 7 8 9 10
//      /|/|/|/|/|/|/|/|/|/|
//dp   0 1 2 3 4 5 6 7 8 9 10
//ʹ��ǰ׺�ͣ�dp[r] - dp[l - 1]
void PrefixSum_singledimension()
{
    int n = 0; int q = 0;
    cin >> n >> q;
    vector<int> arr(n + 1, 0);
    vector<long long int> dp(n + 1, 0);
    //�����ݶ��뵽arr��
    for (int i = 1; i <= n; i++) cin >> arr[i];
    //�����ݶ��뵽dp��
    for (int i = 0; i <= n; i++) dp[i] = dp[i - 1] + arr[i];
    //ֱ�Ӷ�ȡdp����
    for (int i = 0; i < q; i++)
    {
        int l = 0; int r = 0;
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << endl;
    }
}

//�㷨2��
//��ά �� ǰ׺���������
//                   y1      y2
    //------------------------
    //|              |       |
    //|              |       |
    //|     A        |   B   |
    //|              |       |
  //x1|--------------|-------|
    //|     C        |   D   |
  //x2---------------|-------|
//��ά����:dp��δ洢��dp[i][j]��ʾ��(1,1)��(i,j)�ĺͣ�dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + arr[i][j]
//�ȼ���B+C-A+D
//ʹ��ǰ׺�ͣ�dp[r][r] - dp[l-1][r] - dp[r][l-1] + dp[l-1][l-1]
//�ȼ���D+A-B-C
void PrefixSum_twodimension()
{
    int n = 0; int m = 0; int q = 0;
    cin >> n >> m >> q;
    vector<vector<long long int>> arr(n + 1, vector<long long int>(m + 1));//��Ȼ��������ô��ʼ��
    vector<vector<long long int>> dp(n + 1, vector<long long int>(m + 1));//�����ʼ���ķ�ʽҪ��ס
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int tmp = 0; cin >> tmp;
            arr[i][j] = tmp;
        }
    }
    //�����ݷ��뵽dp����
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }
    //ʹ��dp����
    for (int i = 0; i < q; i++)
    {
        int x1 = 0; int x2 = 0;
        int y1 = 0; int y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1] << endl;
    }
}

//�㷨������ǰ׺������dp������
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

//�㷨�ģ�ǰ׺�͵ı��Σ�ǰ׺����
//��Ϊ��Ŀ�涨������ʹ�ó�������ô�Ͳ�����ǰ׺��������-�滻Ϊ/
//�������Ҫ����vector��һ����ǰ׺����һ���Ǻ�׺��
//���÷ǳ�������ǲ�Ҫ����ǰ׺��Ҫ��nums[i]���д���
//����׺������Ҫ��nums[i]���д���
//ǰ׺����dp[i] = dp[i-1] * arr[i]
//��׺����dp[i] = dp[i+1] * nums[i]
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


//�㷨�壺��Ϊk��������
//ע�⣺���ﲻ��ʹ�û������ڣ���Ϊ��������������ģ��������������
//���������п����и��������ע��!
//ʹ��ǰ׺��+��ϣ��
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> hash;
    int sum = 0; int ret = 0;
    hash[0] = 1;//��ֹȫ����Ϊk���Ҳ������䣬hash0=1��
    for (const auto& e : nums)
    {
        //����������0-i��������ϣ�Ѱ��ǰ׺��Ϊsumi-k������
        //�������ΪkҲ��һ������ĺͣ�Ϊʲôret+=ֵ
        //��Ϊ���ڸ�����0�������ж������ĺ���ͬ
        sum += e;
        if (hash[sum - k]) ret += hash[sum - k];
        hash[sum]++;
    }
    return ret;
}

//�㷨�����ı����㷨��
//����ͬ�ඨ����a-b��%c = 0����ôa%c = b%c
//���为��ȡģ����a%c+c)%c
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> hash;
    hash[0] = 1; int sum = 0; int ret = 0;
    for (const auto& e : nums)
    {
        sum += e;
        if (hash[(sum % k + k) % k]) ret += hash[(sum % k + k) % k];
        hash[(sum % k + k) % k]++;
        //ע����������һ�ⲻͬ�ĵط����ڣ�hash�д洢����ǰ׺�͵�����
    }
    return ret;
}

//�㷨�ߣ��ı����㷨��
//�����0�滻Ϊ-1����ô�Ϳ��Խ�����ת��Ϊ��Ϊ0�������飬�ǳ�����
//�������ù�ϣ��ڶ���pair���洢len�Լ�����
//����һ�η���������ʱ������len���ɣ������Ϳ���ȷ���������ret������
//ע�⣺�����len�Ǵ�1��ʼ�ģ�����hash[0].first = 0; hash[0].second = 1;
//��ʦ����ʱ�ڶ����洢int�������꣬��Ҫ��������ϸ�����⣬�����ο�
//������ؼ���һ�����ǽ�0�滻Ϊ-1�������Ϳ���ʹ��ǰ׺�͵�˼��������Ŀ���������Ϊ0������
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

//�㷨�ˣ���άǰ׺�͵ı���
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
    //�����ݷ��뵽dp����
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }
	//����dp����û�б�Ҫ�࿪2*k�Ŀռ䣬��ʹ�ڼ���ʱ�����˼������������Ĵ������鷳
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {   //ע��߽������Ĵ����ǳ���Ҫ
			ret[i - 1][j - 1] = dp[min(i + k, m)][min(j + k, n)] - 
                dp[min(i + k, m)][max(j - k - 1, 0)] - 
                dp[max(i - k - 1, 0)][min(j + k, n)] + 
                dp[max(i - k - 1, 0)][max(j - k - 1, 0)];
        }
    }
    return ret;
}


