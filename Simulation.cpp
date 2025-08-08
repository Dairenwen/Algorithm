#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<map>
#include<set>
#include<list>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//先介绍一下模拟，模拟就是依葫芦画瓢
//模拟算法流程，转换为代码
//如果想要优化，就是找规律，当作数学题做

//算法一：
string modifyString(string s) {
    int size = s.size();
    for (int i = 0; i < size; i++)
    {
        if (s[i] == '?')
        {
            if (i == 0)
            {
                for (int tmp = 97; tmp <= 122; tmp++)
                {
                    if (tmp != s[1])
                    {
                        s[i] = tmp;
                        break;
                    }
                }
            }
            else if (i == size - 1)
            {
                for (int tmp = 97; tmp <= 122; tmp++)
                {
                    if (tmp != s[size - 2])
                    {
                        s[i] = tmp;
                        break;
                    }
                }
            }
            else
            {
                for (int tmp = 97; tmp <= 122; tmp++)
                {
                    if (tmp != s[i - 1] && tmp != s[i + 1])
                    {
                        s[i] = tmp;
                        break;
                    }
                }
            }
        }
    }
    return s;
}

//算法二：模拟题，如果按照第一种方法时间来计数就会超时
//应该按照数组中两个值的差值是否大于等于duration来判断
//这样满足时间要求
int _findPoisonedDuration(vector<int>& timeSeries, int duration) {
    int i = 0; int count = 0; int time = 1; int attack = 0;
    while (i < timeSeries.size())
    {
        if (timeSeries[i] == time)
        {
            attack = duration;
            i++;
        }
        if (attack > 0)
        {
            count++; attack--;
        }
        time++;
    }
    count += attack;
    return count;
}
//这种方法符合要求
int findPoisonedDuration(vector<int>& timeSeries, int duration) {
    int ret = 0;
    for (int i = 1; i < timeSeries.size(); i++)
    {
        int x = timeSeries[i] - timeSeries[i - 1];
        if (x >= duration) ret += duration;
        else ret += x;
    }
    return ret + duration;
}

//算法三：纯找规律题，画图分析
//0     6     12     18
//1   5 7   1113   1719
//2 4   8 10  14 16  20
//3     9     15
//可以看出规律，第一行最后一行每个数字之间的差值是2 * n - 2
//其他行第一个数和第二个数之间的差值是2 * n - 2 - i - i
//可以直接将字符串的每个字符放到返回ret中
string convert(string s, int n) {
    int d = 2 * n - 2;//这里计算的是公差
    if (d == 0) return s;//要注意特殊情况的处理
    int size = s.size();
    string ret;
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || i == n - 1)
        {
            int k = 0;
            while (i + k * d < size)
            {
                ret += s[i + k * d];
                k++;
            }
        }
        else
        {
            int k = 0;
            int sd = d - i - i;
            while (i + k * d < size)
            {
                ret += s[i + k * d];
                if (i + k * d + sd < size) ret += s[i + k * d + sd];
                k++;
            }
        }
    }
    return ret;
}

//算法四：递归模拟，处理字符串easy
string countAndSay(int n) {
    if (n == 1) return string("1");
    else
    {
        string ach = countAndSay(n - 1);
        string ret;
        int size = ach.size();
        for (int i = 0; i < size; i++)
        {
            int count = 1;
            while (i + 1 < size && ach[i + 1] == ach[i])
            {
                i++; count++;
            }
            ret += (count + '0'); ret += ach[i];
        }
        return ret;
    }
}

//算法五：青蛙叫声问题
//解法很难想，原理可以这样理解，使用hash表来存储每个字母的前一个字母和数量
//叫声为"croak",c对应k，r对应c，o对应r，a对应o，k对应a
//对于roak每个字符找前驱字符是否存在，如果存在前驱字符数字--，当前字符数字++
//如果不存在前驱字符，说明叫声不完整，返回-1
//对于c，如果k的数量不为0，说明有k叫声，k--，c++
//如果k的数量为0，说明没有k叫声，c++
//还要注意遍历结束后，除了k，其他字母的数量都要为0，否则不是完整的叫声，返回-1
int minNumberOfFrogs(string s) {
    unordered_map<char, pair<char, int>> hash;
    hash['c'].first = 'k';
    hash['r'].first = 'c';
    hash['o'].first = 'r';
    hash['a'].first = 'o';
    hash['k'].first = 'a';
    for (const auto& e : s)
    {
        if (e == 'c')
        {
            if (hash['k'].second)
            {
                hash['k'].second--; hash['c'].second++;
            }
            else
            {
                hash['c'].second++;
            }
        }
        else
        {
            if (hash[hash[e].first].second)
            {
                hash[hash[e].first].second--;
                hash[e].second++;
            }
            else
            {
                return -1;
            }
        }
    }
    for (const auto& e : hash)
    {
        if (e.first != 'k' && e.second.second) return -1;
    }
    return hash['k'].second;
}


