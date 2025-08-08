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

//�Ƚ���һ��ģ�⣬ģ���������«��ư
//ģ���㷨���̣�ת��Ϊ����
//�����Ҫ�Ż��������ҹ��ɣ�������ѧ����

//�㷨һ��
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

//�㷨����ģ���⣬������յ�һ�ַ���ʱ���������ͻᳬʱ
//Ӧ�ð�������������ֵ�Ĳ�ֵ�Ƿ���ڵ���duration���ж�
//��������ʱ��Ҫ��
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
//���ַ�������Ҫ��
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

//�㷨�������ҹ����⣬��ͼ����
//0     6     12     18
//1   5 7   1113   1719
//2 4   8 10  14 16  20
//3     9     15
//���Կ������ɣ���һ�����һ��ÿ������֮��Ĳ�ֵ��2 * n - 2
//�����е�һ�����͵ڶ�����֮��Ĳ�ֵ��2 * n - 2 - i - i
//����ֱ�ӽ��ַ�����ÿ���ַ��ŵ�����ret��
string convert(string s, int n) {
    int d = 2 * n - 2;//���������ǹ���
    if (d == 0) return s;//Ҫע����������Ĵ���
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

//�㷨�ģ��ݹ�ģ�⣬�����ַ���easy
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

//�㷨�壺���ܽ�������
//�ⷨ�����룬ԭ�����������⣬ʹ��hash�����洢ÿ����ĸ��ǰһ����ĸ������
//����Ϊ"croak",c��Ӧk��r��Ӧc��o��Ӧr��a��Ӧo��k��Ӧa
//����roakÿ���ַ���ǰ���ַ��Ƿ���ڣ��������ǰ���ַ�����--����ǰ�ַ�����++
//���������ǰ���ַ���˵������������������-1
//����c�����k��������Ϊ0��˵����k������k--��c++
//���k������Ϊ0��˵��û��k������c++
//��Ҫע����������󣬳���k��������ĸ��������ҪΪ0�������������Ľ���������-1
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


