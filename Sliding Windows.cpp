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

//算法1:寻找数组合适的区间
//采用滑动窗口的方法
//时间复杂度O(n)，这是因为两个指针i和j各自最多各移动n次
//并且数组的长度已经被记录过了，只需要更新即可，所以时间复杂度为O(n)
//下面讲解方法：
//1.初始化两个指针left,right，分别指向数组的第一个元素
//2.移动right指针，直到区间[left,right]的和大于等于target
//3.更新最小长度，然后移动left指针，直到区间[left,right]的和小于target
//4.重复2-3步骤，直到right指针到达数组的末尾
//5.返回最小长度,如果没有找到则返回0,这是因为len初始化为INT_MAX,这也是技巧之一！
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size(); int len = INT_MAX; int sum = 0;
    for (int left = 0, right = 0; right < n; right++)
    {
        sum += nums[right];
        while (sum >= target)
        {
            len = min(len, right - left + 1);
            sum -= nums[left++];
        }
    }
    return len == INT_MAX ? 0 : len;
}

//算法2：还是sliding windows
//寻找字符的最小子串
int lengthOfLongestSubstring(string s) {
    set<char> tool;
    int len = 0;
    bool judge = false;
    int left = 0, right = 0;//老师使用了哈希表，不会哈哈，用set麻烦一点做出来
    for (left = 0, right = 0; right < s.size(); right++)
    {
        //tool.insert(s[right]);
        while (tool.find(s[right]) != tool.end())
        {
            judge = true;
            len = max(len, right - left);
            tool.erase(s[left++]);
        }
        tool.insert(s[right]);
    }
    if (judge == false)
    {
        return s.length();
    }
    else
    {
        len = max(len, right - left);
        return len;
    }
}

//算法3：最长连续子数组
//超时了
int longestOness(vector<int>& nums, int k) {
    //int tmp=0;
    int j = 0;
    vector<int> v;
    for (int i = 0; i < nums.size(); i++)
    {
        int count = 0;
        int tmp = 0;
        j = i;
        while (j < nums.size())
        {
            if (nums[j] == 1)
            {
                count++;
                j++;
            }
            else
            {
                tmp++;
                if (tmp > k)
                {
                    break;
                }
                count++;
                j++;
            }
        }
        v.push_back(count);
    }
    sort(v.begin(), v.end(), greater<int>());
    return v[0];
}
//sliding windows如果right遇到0，那么count++，如果count>k，那么left++，直到count<=k
//满足条件的时候，更新len=max(len,right-left+1)
int longestOnes(vector<int>& nums, int k) {
    int len = 0;
    int count = 0;
    for (int right = 0, left = 0; right < nums.size(); right++)
    {
        if (nums[right] == 0) count++;
        while (count > k)
        {
            if (nums[left] == 0)
            {
                count--;
                left++;
            }
            else
            {
                left++;
            }
        }
        len = max(len, right - left + 1);
    }
    return len;
}

//算法4：转换思路求和
int minOperations(vector<int>& nums, int x) {
    //转换思路，要求左边右边的和以及长度，可以转换为求中间长度片段的和=sum-x，
    // 返回len-中间片段的和即可解决
    int SUM = 0;
    for (const auto& e : nums)
    {
        SUM += e;
    }
    int target = SUM - x;
    int len = 0;
    bool judge = false;
    int sum = 0;
    int left = 0, right = 0;
    for (left = 0, right = 0; left < nums.size() && right < nums.size(); right++)
    {
        sum += nums[right];
        while (left < nums.size() && sum >= target)
        {
            if (sum == target)
            {
                judge = true;
                len = max(len, right - left + 1);
            }
            sum -= nums[left++];
        }
    }
    if (sum == target && nums.size() == 1)
    {
        return 1;
    }
    if (judge)
    {
        return nums.size() - len;
    }
    else
    {
        return -1;
    }
}

class Solution
{
public:
    int minOperations(vector<int>& nums, int x)
    {
        int sum = 0;
        for (int a : nums) sum += a;
        int target = sum - x;
        // 细节问题
		if (target < 0) return -1;//因为数组中胡元素都是正数，这很坑，题目并没有直接说明！
        int ret = -1;
        for (int left = 0, right = 0, tmp = 0; right < nums.size(); right++)
        {
            tmp += nums[right]; // 进窗⼝
            while (tmp > target) // 判断
                tmp -= nums[left++]; // 出窗⼝
            if (tmp == target) // 更新结果
                ret = max(ret, right - left + 1);
        }
        if (ret == -1) return ret;
        else return nums.size() - ret;
    }
};


//算法5：水果成篮
//这个题目是求最多的水果数，也就是求最长的连续子数组
//这个题目和算法2有点类似，但是这个题目是求最多的水果数，而算法2是求最长的连续子数组
//sliding windows
//注意要使用map，因为map可以存储键值对，而set只能存储键
//因为还不清楚unordered_map的使用，所以使用map
//学习完哈希表之后，再来解决这个问题
int totalFruit(vector<int>& fruits) {
    map<int, int> m;
    int len = 0;
    for (int left = 0, right = 0; right < fruits.size(); right++)
    {
        m[fruits[right]]++;
        while (m.size() >= 3)
        {
            m[fruits[left]]--;
            if (m[fruits[left]] == 0) m.erase(fruits[left]);
            left++;
        }
        len = max(len, right - left + 1);
    }
    return len;
}

//算法6：找到字符串中所有字母异位词
//终于过了，不适用哈希表，而是使用map
bool jug(const map<char, int>& m, map<char, int>& c)
{
    if (m.size() > c.size()) return true;
    if (m.size() == 0) return false;
    for (const auto& e : m)
    {
        //去c中寻找
        if (c.find(e.first) != c.end())
        {
            if (e.second > c[e.first])
                return true;
        }
        else
        {
            return true;
        }
    }
    return false;
}
    vector<int> findAnagrams(string s, string p) {
        map<char, int> m, cmp;
        vector<int> search;
        for (const auto& e : p) { cmp[e]++; }
        int left = 0;
        for (int right = 0; right < s.size(); right++)
        {
            m[s[right]]++;
            while (jug(m, cmp))
            {
                m[s[left]]--;
                if (m[s[left]] == 0) m.erase(s[left]);
                left++;
            }
            if (m == cmp)
                search.push_back(left);
        }
        return search;
    }
	//算法7：找到字符串中所有字符串异位词
	//这个题目和算法6有点类似，但是这个题目是找到字符串中所有字符串异位词
	//将字符串看作算法6中的字符，然后使用map来解决这个问题
    bool judge(map<string, int>& m, map<string, int>& c)
    {
        if (m.size() > c.size()) return true;
        if (m.size() == 0) return false;
        for (const auto& e : m)
        {
            //去c中寻找
            if (c.find(e.first) != c.end())
            {
                if (e.second > c[e.first])
                    return true;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        map<string, int> m, cmp;
        for (const auto& e : words) { cmp[e]++; }
        int ref = words[0].size();
        auto begin = s.begin();
        for (int i = 0; i < ref; i++)
        {
            m.clear();
            for (int left = i, right = i; right + ref <= s.size(); right += ref)
            {
                string s(begin + right, begin + right + ref);
                m[s]++;
                while (judge(m, cmp))
                {
                    string tmp(begin + left, begin + left + ref);
                    m[tmp]--;
                    if (m[tmp] == 0) m.erase(tmp);
                    left += ref;
                }
                if (m == cmp)
                {
                    ret.push_back(left);
                }
            }
        }
        return ret;
    }
    //滑动窗口绝唱，因为字符只有128个，所以使用128数组，妙！记录有效字符的个数来评判，
    //在满足条件的时候缩小窗口，使用intmax来判断是否存在满足条件的字符串，我只能说牛b！
    string minWindow(string s, string t) 
    {
        int hash1[128] = { 0 }; int hash2[128] = { 0 };
        int kind = 0;
        for (const auto& e : t)
        {
            if (hash1[e] == 0) kind++;
            hash1[e]++; 
        }
        int minlen = INT_MAX; int begin = 0; int count = 0;//记录有效字符个数
        for (int left = 0, right = 0; right < s.size(); right++)
        {
            char in = s[right];
            if (++hash2[in] == hash1[in]) count++;
            while (count == kind)
            {
                //更新结果
                if (minlen > right - left + 1)
                {
                    minlen = right - left + 1;
                    begin = left;
                }
                char out = s[left++];
                if (hash2[out]-- == hash1[out]) count--;
            }
        }
        return minlen == INT_MAX ? string() : string(s, begin, minlen);
    }
    

