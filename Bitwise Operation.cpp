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
//Ҳ���Ǹ�ϰһ��bitset�ɣ�
//λ���㣺
//1.������Ϥ������λ��������
//&����λ�룬��0����0
//|����λ����1����1
//^����λ�����ͬΪ0����ͬΪ1
//2.��һ������ȷ�����������ĵ�xλ��0/1
//����xλ��&1
//3.��һ���������Ƶ�xλ�޸ĳ�1
//��1����xλ��|(1<<x)
//4.��һ�����Ķ����Ƶ�xλ�޸ĳ�0
// ��1����xλ��&(~1<<x)
//5.��ȡһ���������Ʊ�ʾ�����Ҳ��1��lowbit��
// n & (-n) -n���൱�ڽ����Ҳ��1���������ȫ����λȡ��
// -�൱����~��+1��0110101000
//			ȡ��   1001010111
//			+1     1001011000
//			&      0000001000
//6.�ɵ�һ���������Ʊ�ʾ�����Ҳ��1
// n & (n - 1) n-1���൱�ڽ����Ҳ��1���ұ�����ȫ����λȡ��
//  n  011010100
// n-1 011010011 -1��Ҫ��λ�������Ҳ��1��Ϊ0
// &   011010100
//     011010000
// 
//���������ʣ�
// 0^x = x
// x^x = 0
// x^y^x = y
// x^y^z = x^(y^z) = y^(x^z) = z^(x^y)
// 
//����������ȼ���
//�ܼ����žͼ����ţ����ÿ���������ȼ�˳��

//�㷨1:�ж��ַ������Ƿ����ظ��ַ�
//��������ϣ��ͳ�ƴ���
//�Ż���ʹ��int [128]��������ϣ��
// ͬʱ���ڶ���Сд�ַ�����������Ϊ26
// ��һ���Ż�������ʹ��λͼ
//����һ���Ż������ݸ볲ԭ�����ַ������ȴ���26ʱ����Ȼ���ظ��ַ�������ֱ�ӷ���false 

//ASCII�븴ϰ��A65 a97
bool isUnique1(string astr) {
    int arr[128] = { 0 };
    for (const auto& e : astr)
    {
        arr[e]++;
        if (arr[e] > 1) return false;
    }
    return true;
}

bool isUnique2(string astr) {
    int arr[28] = { 0 };
    for (const auto& e : astr)
    {
        arr[e - 97]++;
        if (arr[e - 97] > 1) return false;
    }
    return true;
}

bool isUnique3(string astr) {
    if (astr.length() > 26) return false;
    int bitset = 0;
    for (const auto& e : astr)
    {
        if (bitset & (1 << (e - 97))) return false;
		else bitset |= (1 << (e - 97));//ע����|=������|
    }
    return true;
}

//�㷨2:�ж�һ�����Ƿ����
//������ʹ��λͼ
int missingNumber1(vector<int>& nums) {
    int size = nums.size();
    bitset<10000> bt;
    for (const auto& e : nums) bt.set(e);
    for (int i = 0; i <= size; i++)
    {
        if (!bt.test(i)) return i;
    }
    return 114514;
}

//��������ʹ������+���ֲ���
int missingNumber2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int left = 0; int right = nums.size() - 1;
    if (nums[right] == right) return right + 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == mid) left = mid + 1;
        else right = mid;
    }
    return right;
}

//���������Ȳ��������
int missingNumber3(vector<int>& nums) {
    int size = nums.size();
    int sum = (0 + size) * (size + 1) / 2;
    int fixsum = 0;
    for (const auto& e : nums)
    {
        fixsum += e;
    }
    return sum - fixsum;
}

//�����ģ���򣬷ǳ������0-n��nums�е����������
int missingNumber4(vector<int>& nums) {
    int num = 0;
    for (const auto& e : nums)
    {
        num ^= e;
    }
    for (int i = 0; i <= nums.size(); i++)
    {
        num ^= i;
    }
    return num;
}

//�㷨�������
//˼·���������޽�λ���ʹ��������λʹ�ð�λ��
//��ע���λ����Ҫ����һλ����λ����һ����
//ֱ����λΪ0�������޽�λ��ӵĽ����������֮��
int getSum(int a, int b) {
    int unsignedp = a ^ b; int overp = (a & b) << 1;
    while (overp)
    {
        int tmpup = unsignedp; int tmpop = overp;
        unsignedp = tmpup ^ tmpop;
        overp = (tmpup & tmpop) << 1;
    }
    return unsignedp;
}

//�㷨�ģ�ֻ����һ�ε�����II
//��һ��������һ�Σ��������������Σ���ֻ����һ�ε�����
int singleNumber(vector<int>& nums)
{
    //ʹ��λ���� (x >> i) & 1 �õ� x �ĵ� i ��������λ��������������ٶ� 3 ȡ�࣬�õ��Ľ��һ��Ϊ 0 �� 1����Ϊ�𰸵ĵ� i ��������λ��
    int ret = 0;
    for (int i = 0; i < 32; i++)
    {
        int sum = 0;
        for (const auto& e : nums)
        {
            sum += (e >> i) & 1;
        }
        ret |= ((sum %= 3) << i);
    }
    return ret;
}

//�㷨�壺��ʧ����������
//��ͨ�ⷨ��������ÿ���±��Ӧ���֣���Ӧʧ����i--�Ƶ�����
vector<int> missingTwo1(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
    int count = 0; int i = 0; int num = 1;
    vector<int> ret;
    for (i = 0; count < 2 && i < nums.size(); i++)
    {
        if (nums[i] != num)
        {
            count++;
            ret.push_back(num++);
            i--;
        }
        else
        {
            num++;
        }
    }
    if (count == 0)
    {
        ret.push_back(num);
        ret.push_back(num + 1);
    }
    else if (count == 1)
    {
        ret.push_back(num);
    }
    return ret;
}
//λ����ⷨ��������ǰ������˼·�����ã�ע��һ����������nums.size()+2����
//��Ҫ��������������ݣ���Ҫ������������Χ
vector<int> missingTwo2(vector<int>& nums) 
{
        int tmp = 0; int wei = 0;
        for (const auto& e : nums) tmp ^= e;
        for (int i = 1; i <= nums.size() + 2; i++) tmp ^= i;
        //�ҳ���һ��1��Ҳ���ǲ�ͬ��λ���������ַ���
        for (wei = 0; wei < 32; wei++) if ((tmp >> wei) & 1) break;
        int ret1 = 0; int ret2 = 0;
        for (const auto& e : nums)
        {
            if ((e >> wei) & 1) ret1 ^= e;
            else ret2 ^= e;
        }
        for (int i = 1; i <= nums.size() + 2; i++)
        {
            if ((i >> wei) & 1) ret1 ^= i;
            else ret2 ^= i;
        }
        return vector<int>({ ret1,ret2 });
 }
