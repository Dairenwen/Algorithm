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

//̰���㷨��һ����ÿһ��ѡ���ж���ȡ�ڵ�ǰ״̬�����ŵ�ѡ�񣬴Ӷ�ϣ������ȫ�����Ž���㷨��
//1. �������⣨Coin Change Problem��
//���⣺������ͬ����Ӳ�Һ�һ���ܽ���������ٵ�Ӳ�Ҵճ������
//�ⷨ��
//̰���㷨�������ڱ�׼��ֵ���� 1��5��10��25 �֣���ÿ��ѡ�������ֵ��Ӳ�ң�ֱ���չ���
//ʱ�临�Ӷȣ�O (n)��n ΪӲ��������
//�����ԣ�����ֵ�Ǳ�׼���� 1��3��4����̰�Ŀ���ʧЧ������Ϊ 6 ʱ��̰��ѡ 4+1+1�����Ž�Ϊ 3+3����
//��̬�滮��ͨ�ýⷨ��������ÿ��������������Ӳ������
//ʱ�临�Ӷȣ�O(amount �� coins)��
//ʾ������� 11��Ӳ�� [1,5,10] �� ̰�Ĳ��ԣ�10+1���� 2 ö��

//2. ��С·���ͣ�Minimum Path Sum��
//���⣺��һ����ά�����У������Ͻǵ����½ǵ�·���У�����֮����С��·���Ƕ��٣�ÿ��ֻ�����»������ƶ���
//�ⷨ��
//��̬�滮��
//״̬���壺dp [i][j] ��ʾ���� (i,j) ����С·���͡�
//״̬ת�ƣ�dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])��
//ʱ�临�Ӷȣ�O (m��n)��m �� n Ϊ�����������������
//ʾ����
//[1,3,1]
//[1,5,1]
//[4,2,1]
//��С·����1��3��1��1��1����Ϊ7��

//3. �������⣨Knapsack Problem��
//���ࣺ
//0-1 ������ÿ����Ʒֻ��ѡһ�Ρ�
//��ȫ������ÿ����Ʒ��ѡ���޴Ρ�
//�ⷨ��
//��̬�滮��ͨ�ýⷨ����
//״̬���壺dp [i][w] ��ʾǰ i ����Ʒ��������Ϊ w �ı���������ֵ��
//
//# ��ȫ������ѡ0�λ��ε�i����Ʒ
//dp[i][w] = max(dp[i-1][w], dp[i][w-weight[i]] + value[i])
//
//ʱ�临�Ӷȣ�O (n��W)��n Ϊ��Ʒ����W Ϊ����������
//̰���㷨���������ڷ���������������λ��ֵ����ѡ����Ʒ���ɲ�֡�
//�����ԣ��������� 0-1 ����������Ʒ��ֵ [6,10,12]������ [1,2,3]���������� 5��̰��ѡ��������Ʒ�����Ž�Ϊѡǰ��������

//4. ��С��������Minimum Spanning Tree, MST��
//���⣺��һ����Ȩ����ͼ�У��ҵ��������нڵ��ұ�Ȩ����С������
//�ⷨ��
//Kruskal �㷨��̰�ģ���
//�����б߰�Ȩֵ��������
//����ѡ����С�ߣ���������γɻ���������
//ʱ�临�Ӷȣ�O (E log E)��E Ϊ������
//Prim �㷨��̰�ģ���
//������ڵ㿪ʼ��ÿ��ѡ��������ѡ�ڵ��δѡ�ڵ����С�ߡ�
//ʱ�临�Ӷȣ�O (E log V)��V Ϊ�ڵ�����
//���ó��������粼�ߡ���·��Ƶȡ�

//5. ���������루Huffman Coding��
//���⣺��������ǰ׺���룬��������ѹ����
//�ⷨ��
//̰���㷨��
//�����ַ�Ƶ�ʹ�������������ÿ�κϲ�Ƶ����͵������ڵ㡣
//��·������Ϊ 0����·������Ϊ 1������ÿ���ַ��ı��롣
//ʱ�临�Ӷȣ�O (n log n)��n Ϊ�ַ�����

//�������⣡̰�ĵĲ����Ǿ���ʹ���������Ӳ�������㡣
//�������С��Ӳ�������������ʹ�þ���ʹ�á�
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

//ѡ��һ���ѣ�ÿ�ζ�����Ԫ�ؽ��м��������ֱ������ĺ�С�ڵ���ԭ����͵�һ�롣
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

//�ҳ�������֣�����̰�ĸ��ıȽϷ������У���סҪ��ab��ba��ƴ�ӽ��бȽϡ�
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

//��left��¼��һ����ֵ��right��¼��ǰ��ֵ��
//�������飬��������Ԫ�صĲ�ֵright��
//���right==0����������Ȳ���ڶ�����
//���left*right<=0��˵�������˰ڶ��������ŷ����仯���ʼ����������ret++��
//����left=right�������ж���һ����ֵ��
//��󷵻�ret+1����Ϊ�����г��ȱȰڶ�������1��
int wiggleMaxLength(vector<int>& nums) {
    int ret=0,left=0,right=0;
    for(int i=0;i<nums.size();i++)
    {
        if(i+1<nums.size()) right=nums[i+1]-nums[i];
        if(right==0) continue;//˵���ҵ���˵���ͬ
        if(left*right<=0) ret++;
        left=right;//������ߵ��������
    }
    return ret+1;//
}

//������ǡ�����������С���LIS������̰��+�����Ż���
//
//Ϊʲô������̰�ģ�
//ÿ�α�����һ����Ԫ��ʱ��
//
//����ȵ�ǰ�����С�ĩβ��ֱ�Ӽӵ�ĩβ��̰��ѡ����ģ���֤��������
//�����ĩβС���ö����ҵ���һ����С������λ�ã��滻����̰���á���β������С��Ϊ���������������ռ䣩��
//����������Ӱ�����ճ��ȣ���Ϊ����ֻ��������ɶ೤�ĵ������У���βԽСԽ���׽��Ϻ���ĸ�������
//������ά��һ�������ܵĵ������н�β����ÿ�ζ��������ţ���С�������Կ�����̰�ġ�
//
//���ֲ�����Ϊ�˼����ҵ��滻λ�ã�����ʱ�临�Ӷ� O(n log n)��
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

//��������������У�LCIS�����⣺ע���������������У�Ҳ�������Ϊ�ִ�
//��ô��̬�滮�汾�Ͳ���Ҫһֱά��һ�������ˣ�����ά��һ��dp���飬��ʾ�Ե�ǰԪ�ؽ�β����������������г��ȡ�
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
//���ѣ������ñȵ�ǰ�����С�ĩβ��ֱ�Ӽӵ�ĩβ��̰��ѡ����ģ���֤��������ĩβС���ö����ҵ���һ����С������λ�ã�

//������Ŀ��������Ʊ�����ʱ��
//frontmin ��¼ĿǰΪֹ��������С�۸��������͵㣩��
//����ÿһ��ļ۸񣬼�����������������ܻ�õ�������� prices[i] - frontmin��
//�� ret ��¼ȫ���е��������
//����������͵ļ۸񣬾͸��� frontmin��Ϊ�������ܵĸ���������׼����
int maxProfit(vector<int>& prices) {
    int frontmin=prices[0],ret=0;
    for(int i=1;i<prices.size();i++)
    {
        ret=max(ret,prices[i]-frontmin);
        if(prices[i]<frontmin) frontmin=prices[i];
    }
    return ret;
}

//���ǹ��ڹ�Ʊ�����⣬��������ǿ��Զ�������ġ�
int maxProfitII(vector<int>& prices) {
    //����̰�Ĳ��ԣ�ֻҪ���������ƣ�����������
    //1.˫ָ�����
    // int ret=0;
    // for(int i=0;i<prices.size();i++)
    // {
    //     int left=i;
    //     while(i+1<prices.size()&&prices[i+1]>=prices[i]) i++;
    //     ret+=prices[i]-prices[left];
    // }
    // return ret;
    //2.������������Ϊһ�����ڣ��ж��Ƿ�ӵ�ret
    int ret=0;
    for(int i=0;i<prices.size();i++)
    {
        if(i+1<prices.size()&&prices[i+1]>=prices[i]) ret+=prices[i+1]-prices[i];
    }
    return ret;
}

//K��ȡ������󻯵������
//̰�ķ�����
//a. m > k ����ǰ k ?������ȫ�����������
//b. m == k �������еĸ���ȫ��ת����������
//c. m < k ��
//i. �Ȱ����еĸ������������
//ii. Ȼ����� k - m ����ż��������ۣ�
//1. �����ż����ֱ�Ӻ��ԣ�
//2. �������������ѡ��ǰ��������?��������ɸ���
int largestSumAfterKNegations(vector<int>& nums, int k) {
    int m = 0, minElem = INT_MAX, n = nums.size();
    for(auto x : nums)
    {
        if(x < 0) m++;
        minElem = min(minElem, abs(x)); // �����ֵ��?���Ǹ���
    }
    // ��������
    int ret = 0;
    if(m > k)
    {
        sort(nums.begin(), nums.end());
        for(int i = 0; i < k; i++) // ǰ k ?���������������
        {
            ret += -nums[i];
        }
        for(int i = k; i < n; i++) // ��?��������
        {
            ret += nums[i];
        }
    }
    else
    {
        // �����еĸ����������
        for(auto x : nums) ret += abs(x);

        if((k - m) % 2) // �ж��Ƿ�����?������
        {
            ret -= minElem * 2;
        }
    }
    return ret;
    // //ʹ�öѵķ�ʽ�����������뵽��
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

//����������򣬲�֪����һ����������̰����ʲô��ϵ������
//����ֱ�Ӱ���map�ķ�ʽ�������򣬰�����ߴӴ�С����Ȼ�����ַ���vector�з��ؼ��ɡ�
vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
    //��������ǳ���Ҫ�����±��������Ȼ������±귵�ض�Ӧ�����֣�
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

    //���Ƕ���߽�������Ȼ������ߴӴ�С��˳�򷵻����֡�
//    map<int,string> hash;
//    for(int i=0;i<names.size();i++) hash[heights[i]]=names[i];
//    vector<string> ret;
//    for(const auto&e:hash)
//    {
//        ret.push_back(e.second);
//    }
//    return vector<string>(ret.rbegin(),ret.rend());

    //Ҳ���Խ���ߺ����ַ���һ��pair�У�Ȼ������߽�������
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

//����Ĵ�
//̰�Ĳ��ԣ�
//1.ͳ��ÿ���ַ��ĳ��ִ���
//2.ͳ�Ƴ��ִ���Ϊż�����ַ����ܳ���
//3.����г��ִ���Ϊ�������ַ���ȡ���е����ż������
//4.����г��ִ���Ϊ�������ַ������м������һ���ַ�
int longestPalindrome(string s) {
    unordered_map<char,int> hash;
    for(const auto&e:s) hash[e]++;
    int mid=-1,len=0;
    bool hasOdd=false;
    for (const auto& e : hash) {
        if (e.second % 2 == 0) {
            // ż���������ַ�����ȫ��ʹ��
            len += e.second;
        } else {
            // �����ַ�����ʹ����ż�����֣�����-1��
            len += e.second - 1;
            hasOdd = true;  // ���������ַ�
        }
    }

    // ����������ַ����������м������һ���ַ�
    if (hasOdd) {
        len += 1;
    }
    return len;
}

//���������������⣬ʹ��̰���㷨��������ơ�
//˼·��
//1.�ȶ� nums1 �� nums2 ��������
//2.ʹ��˫ָ����� nums1 �� nums2���Ƚϵ�ǰ nums1 ��Ԫ�غ� nums2 ��Ԫ�ء�
//3.��� nums1[i] > nums2[left]��˵�� nums1[i] ����սʤ nums2[left]���� nums1[i] ���������飬���� left ָ�������ƶ���
//4.��� nums1[i] <= nums2[left]��˵�� nums1[i] �޷�սʤ nums2[left]���� nums1[i] ���������飬���� right ָ�������ƶ���
vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    //�������ķ��棬��Ҫ���������Ӯ�ñ�����
    //1.������ 2.��˫ָ��һһ���бȽϣ����������nums1[i] > nums2[i]�������������num2��������
    //�������nums1[i] > nums2[i]ֱ�Ӽ��뼴��
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

//�����ַ���ƥ�����⣬����һ���ַ��� s������ 'I' �� 'D'����ʾ������ϵ��
//'I' ��ʾ��ǰ���ֱ�ǰһ�����ִ�'D' ��ʾ��ǰ���ֱ�ǰһ������С��
//̰�Ĳ��ԣ�I�������ӣ�D������٣�ÿ�ζ�ѡ��ǰ��С�����������֡�
vector<int> diStringMatch(string s) {
    //���һ������������&��С��������
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

//����������⣬�е�����������������ǲ���Ҫ�����±�
//�Ƚ�������һֱ�ҵ����� g[index1]<=s[index2] �������
//�������ͽ� index1 �� index2 ����һ����ʾ������ӵõ��˱��ɡ�
//��������㣬�ͽ� index2 ��һ����ʾ������ɱ������ˡ�
//��󷵻����������ĺ���������
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

//�����ŵ����⣬̰�Ĳ��ԣ�
//1.���ֻ��һ������ֱ�ӷ����������
//2.���ֻ�������������� a/b ����ʽ��
//3.����ж���������� a/(b/c/d/...) ����ʽ��
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

//�ǳ������̰�ģ����ò�������ķ�ʽ��̰�ģ�
//ÿ�ζ�ȡ��ǰ��������Զ��λ�ã�
//�����������Զ��λ�ô��ڵ�������ĳ��ȣ�˵�����Ե��������ĩβ��ֱ�ӷ��ص�ǰ�Ĳ�����
//������ܵ��������ĩβ���ͽ���ǰ�Ĳ�����һ��
//������ǰ��λ�ø���Ϊ��������Զ��λ�ã�����������
int jump(vector<int>& nums)
{
    //���ò�������ķ�ʽ��̰��
    int step=0,left=0,right=0,maxpos=0,n=nums.size();
    while(left<=right)
    {
        if(maxpos>=n-1) return step;//������������һ��λ��֮�󣬶����Է���
        for(int i=left;i<=right;i++)
        {
            maxpos=max(maxpos,i+nums[i]);
        }

        left=right+1;//��һ�����߽�
        right=maxpos;//��һ����ұ߽�
        step++;
    }
    return -1;
}

//��Ծ��Ϸ1��ԭ�������һ��һ��
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

//����վ���ǳ�������Ż�����
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
        //��¼һ��step������ֱ�Ӵ�i+step����һ����ʼ�ж��Ƿ������һȦ��������step����Ų��ܽ�����ȥ
        //��i��i+step��û��Ҫ���ˣ�ֱ�Ӵ�i+step+1��ʼ
        i=i+step;
    }
    return -1;
}

//�������������֣�
//����ⷨ��
//��n��ʼ��0���ҵ����ĵ������������֣�
//ʱ�临�Ӷȣ�O(nlogn)
//̰�Ľⷨ��
//1.�����ǰ���ִ�����һ�����֣��ͽ���ǰ���ּ�һ��
//������ǰ���ֺ�����������ֶ���Ϊ9��
//2.�����ǰ����С�ڵ�����һ�����֣���ֱ��������
int monotoneIncreasingDigits(int n) {
    string s=to_string(n);
    char front=s[0];
    for(int i=1;i<s.size();i++)
    {
        //�ҵ���һ���½��ĵط�
        if(front>s[i])
        {
            int index=i-1;
            while(index-1>=0&&s[index-1]==s[index]) index--;//������ظ��������ҵ���һ����һ
            s[index]-=1;
            for(int j=index+1;j<s.size();j++) s[j]='9';
            return stoi(s);
        }
        else front=s[i];
    }
    return stoi(s);
}

//�����ļ�����
int brokenCalc(int startValue, int target) {
    //���������򷴵Ĳ���
    int step=0,start=target,end=startValue;
    while(start!=end)
    {
        //�����������/2��+1�ķ�ʽ
        if(start<=end) start++;//end��start��ֻ��+1
        else
        {
            if(start%2) start++;
            else start/=2;
        }
        step++;
    }
    return step;
}

//�ϲ����䣬�������⣡�ǳ����䣡
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    //�����Ͼ����󲢼���
    //1.���Ȱ�����˵�����
    //2.�Ե�һ��������Ҷϵ���Ϊjudge�����<=judge˵�����Ժϲ��������Ҷ˵�����ֵ
    //3.���>judge˵�����ܺϲ�������һ��vector
    vector<vector<int>> ret;
    vector<pair<int,int>> tmp;
    for(const auto&e:intervals) tmp.push_back({e[0],e[1]});
    sort(tmp.begin(),tmp.end());//������˵�����
    for(int i=0;i<tmp.size();i++)
    {
        int right=tmp[i].second;//��ʼ���Ҷ˵�
        vector<int> v;
        v.push_back(tmp[i].first);
        //һֱ�ϲ���˵�С�ڵ���right������
        while(i+1<tmp.size() && tmp[i+1].first<=right)
        {
            i++;
            right=max(right,tmp[i].second);//�����Ҷ˵�����ֵ
        }
        v.push_back(right);
        ret.push_back(v);
    }
    return ret;
}

//���ص����䣺
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    //�������⻹����Ҫ�����򣬰�����˵�����
    int ret=0;
    vector<pair<int,int>> tmp;
    for(const auto&e:intervals) tmp.push_back({e[0],e[1]});
    sort(tmp.begin(),tmp.end());//������˵�����
    for(int i=0;i<tmp.size();i++)
    {
        int right=tmp[i].second;
        while(i+1<tmp.size() && tmp[i+1].first<right)
        {
            i++;
            ret++;//ɾ���ϴ����һ������
            right=min(right,tmp[i].second);//�����Ҷ˵����Сֵ
        }
    }
    return ret;
}

//ע���������󽻼��������󲢼�
//[__________]
//       [__________]
//       [___]
//��������н�����ֻ������Ҷ˵����Сֵ
int findMinArrowShots(vector<vector<int>>& points) {
    int ret=0;
    sort(points.begin(),points.end());
    for(int i=0;i<points.size();i++)
    {
        //�������󽻼�
        int left=points[i][0],right=points[i][1];//ѡȡ�Ҷ˵���Ϊjudge
        int count=0;
        while(i+1<points.size()&&points[i+1][0]<=right)
        {
            i++;count++;
            if(count==1)
            {
                //����ǵ�һ�ξ��������
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

//�ݹ��̰�ĺ����һ���⣺
int step=INT_MAX;
//���õݹ����Կ���ò�ƿ���
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
//����ʹ�ü��仯�������ƣ������������ʹ�ù�ϣ��
int integerReplacement1(int n) {
    //̰��̫�����ˣ��������հɣ�
    int ret = 0;
    while(n > 1)
    {
        // ��������
        //�����ż��ֱ��/2
        if(n % 2 == 0)
        {
            ret++;
            n /= 2;
        }
        else
        {
            //�����������Ҫѡ��+1����-1
            //��Ҫ��3�������⴦��
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

//����˹�������⣺����ʵ���������������plus�汾��
int maxEnvelopes(vector<vector<int>>& envelopes) {
    //����ö�̬�滮������ô������������������еķ���
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
//������̰�ĵľ���������
class Compar
{
public:
    bool operator()(const vector<int>& v1,const vector<int>& v2)
    {
        // ��������ǹؼ���
        // ��˵㲻ͬʱ������˵��С�����ţ���֤����˳���� ����˵������
        // ��˵���ͬʱ�����Ҷ˵�Ӵ�С�ţ�����˵���ͬ�������Ҷ˵��ģ���Ϊ����������� LIS �ṩ���������
        // �����Ҷ˵���ѱ�����СԪ�� ���ضϡ���С�Ҷ˵�ᱻ���Ҷ˵㸲�ǣ�������⴦����
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
        //�������ֻ�����Ҷ˵�����������������
        ret.push_back(envelopes[0][1]);
        for(int i=1;i<envelopes.size();i++)
        {
            if(envelopes[i][1]>ret.back()) ret.push_back(envelopes[i][1]);
            else ret[bs(ret,envelopes[i][1])]=envelopes[i][1];
        }
        return ret.size();
    }
};

//ȡ���֣��о�����
int maxSumDivThree(vector<int>& nums) {
    int ret=0;
    priority_queue<int,vector<int>,greater<int>> one;//���%1������
    priority_queue<int,vector<int>,greater<int>> two;//���%2������
    for(const auto&e:nums)
    {
        ret+=e;
        if(e%3==1) one.push(e);
        if(e%3==2) two.push(e);
    }
    if(ret%3==0) return ret;
    else if(ret%3==1)
    {
        //��1ȡ��one������С������two��Ԫ����С������
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
        //��2ȡ��two������С������one��Ԫ����С������
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

//���°��������룬ʹ���������������ڵ�Ԫ�ز����
vector<int> rearrangeBarcodes(vector<int>& barcodes) {
    unordered_map<int,int> hash;//ʹ�ù�ϣ��ͳ�ƴ���
    for(const auto&e:barcodes) hash[e]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>,
            function<bool(const pair<int,int>&, const pair<int,int>&)>> heap
            (hash.begin(), hash.end(),
             [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.second < p2.second;});
    vector<int> ret(barcodes.size(),0);
    //�Ƚ����ִ�����������ż��λ
    int index=0;
    pair<int,int> count=heap.top();heap.pop();
    while(count.second)
    {
        ret[index]=count.first;
        index+=2;
        count.second--;
    }
    index=1;
    //ÿ��ȡ�������Ľ��в������
    //����ʣ�µ�����ѭ���ķ�ʽ���ܴ��������������Ҳ���ԣ�
    //�����Ҽ��ȡ�����д�������Ԫ�ؽ��в��룬�������Ա�֤�������
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

//���棬��Ҫ�ж��Ƿ��������
string reorganizeString(string barcodes) {
    unordered_map<char,int> hash;//ʹ�ù�ϣ��ͳ�ƴ���
    for(const auto&e:barcodes) hash[e]++;
    priority_queue<pair<char,int>, vector<pair<char,int>>, function<bool(const pair<char,int>&, const pair<char,int>&)>> heap(
            hash.begin(), hash.end(), [](const pair<char,int>& p1, const pair<char,int>& p2) { return p1.second < p2.second;});
    string ret(barcodes.size(),0);
    //�Ƚ����ִ�����������ż��λ
    int index=0;
    pair<char,int> count=heap.top();heap.pop();
    if(count.second>(barcodes.size()+1)/2) return "";//����������Ĵ�������(n+1)/2��2��Ϊһ��������������ݸ볲ԭ���ض�������ظ�����
    while(count.second)                              //����������Ĵ���С��(n+1)/2��ÿһ��ֲ���һ����Ҳ��������
    {
        ret[index]=count.first;
        index+=2;
        count.second--;
    }
    index=1;
    //ÿ��ȡ�������Ľ��в������
    //����ʣ�µ�����ѭ���ķ�ʽ���ܴ��������������Ҳ���ԣ�
    //�����Ҽ��ȡ�����д�������Ԫ�ؽ��в���
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
