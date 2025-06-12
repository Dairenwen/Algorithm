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
//也算是复习一下bitset吧：
//位运算：
//1.先来熟悉常见的位操作符：
//&：按位与，有0就是0
//|：按位或，有1就是1
//^：按位异或，相同为0，不同为1
//2.给一个数，确定二进制数的第x位是0/1
//右移x位，&1
//3.将一个数二进制第x位修改成1
//将1左移x位，|(1<<x)
//4.将一个数的二进制第x位修改成0
// 将1左移x位，&(~1<<x)
//5.提取一个数二进制表示中最右侧的1（lowbit）
// n & (-n) -n这相当于将最右侧的1的左边区域全部按位取反
// -相当于先~再+1，0110101000
//			取反   1001010111
//			+1     1001011000
//			&      0000001000
//6.干掉一个数二进制表示中最右侧的1
// n & (n - 1) n-1这相当于将最右侧的1的右边区域全部按位取反
//  n  011010100
// n-1 011010011 -1需要借位，将最右侧的1变为0
// &   011010100
//     011010000
// 
//异或的运算率：
// 0^x = x
// x^x = 0
// x^y^x = y
// x^y^z = x^(y^z) = y^(x^z) = z^(x^y)
// 
//运算符的优先级：
//能加括号就加括号，不用刻意记忆优先级顺序

//算法1:判断字符串中是否有重复字符
//方法：哈希表统计次数
//优化：使用int [128]数组代替哈希表
// 同时由于都是小写字符，可以缩短为26
// 进一步优化，可以使用位图
//更进一步优化，根据鸽巢原理，当字符串长度大于26时，必然有重复字符，可以直接返回false 

//ASCII码复习：A65 a97
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
		else bitset |= (1 << (e - 97));//注意是|=，不是|
    }
    return true;
}

//算法2:判断一个数是否存在
//方法：使用位图
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

//方法二：使用排序+二分查找
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

//方法三：等差数列求和
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

//方法四：异或，非常巧妙，将0-n和nums中的数进行异或
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

//算法三：求和
//思路：两个数无进位相加使用异或，求进位使用按位与
//请注意进位后需要左移一位，进位给下一个数
//直到进位为0，返回无进位相加的结果就是两数之和
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

//算法四：只出现一次的数字II
//有一个数出现一次，其他数出现三次，求只出现一次的数字
int singleNumber(vector<int>& nums)
{
    //使用位运算 (x >> i) & 1 得到 x 的第 i 个二进制位，并将它们相加再对 3 取余，得到的结果一定为 0 或 1，即为答案的第 i 个二进制位。
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

//算法五：消失的两个数字
//普通解法：先排序每个下标对应数字，对应失败则i--推倒重来
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
//位运算解法：这里是前面两种思路的运用，注意一共有连续的nums.size()+2个数
//不要局限于数组的内容，而要放眼于整个范围
vector<int> missingTwo2(vector<int>& nums) 
{
        int tmp = 0; int wei = 0;
        for (const auto& e : nums) tmp ^= e;
        for (int i = 1; i <= nums.size() + 2; i++) tmp ^= i;
        //找出第一个1，也就是不同的位，便于区分分组
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
