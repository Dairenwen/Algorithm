#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<list>
using namespace std;

//算法1：移动0
//适用于：数组分块/分区，数据的移动
void moveZeroes(vector<int>& nums) {
    //定义两个指针，prev和cur，将区间划分为0，prev//prev+1，cur-1//cur，尾
    //分别代表非0，0，未处理三部分
    //设置循环条件为cur！=nums.size()
    int prev = -1;//prev指向开头之前
    int cur = 0;
    while (cur != nums.size())
    {
        //如果碰到0，cur++
        if (nums[cur] == 0)
        {
            cur++;
        }
        else if (nums[cur] != 0)//要加入到非0区间，先让prev++，交换再让cur++
        {
            prev++;
            swap(nums[prev], nums[cur]);
            cur++;
        }
    }
}

//算法2：重写0
//适用于：数组内添加数据，解决数据覆盖的问题
void duplicateZeros(vector<int>& arr) {
    //还是使用双指针法，但是是从数组的末尾开始使用
    //先定义两个指针cur和dest，dest指向数组的最后一个元素，方便修改数组
    //cur要先找到最后一个复写在数组中的元素
    int cur = 0;
    int dest = -1;//dest设为0/-1完全不同
    //你以为去算有效个数是对的吗？奇数偶数相加有可能不等于数组大小！真坑
    //这里还是要双指针算法
    //cur先判断值->dest指向开头决定是走一步还是两步->dest是否越界->cur++
    // int count=0;
    // for(auto e:arr)
    // {
    //     if(count==arr.size())
    //     {
    //         break;
    //     }
    //     if(e==0)
    //     {
    //         count+=2;
    //     }
    //     else
    //     {

    //         count++;
    //     }
    //     cur++;
    // }
    while (cur < arr.size())
    {
        if (arr[cur] == 0)
        {
            dest += 2;
        }
        else
        {
            dest++;
        }
        if (dest >= arr.size() - 1)
        {
            break;
        }
        cur++;
    }
    //dest=arr.size()-1;不能修改dest位置，cur与dest位置都是一一对应的，修改了会越界
    //如果dest越界了，进行特殊处理，只可能因为cur指向0越界
    if (dest >= arr.size())
    {
        arr[arr.size() - 1] = 0;
        dest -= 2;
        cur--;

    }
    //开始从后往前书写
    while (cur >= 0)
    {
        if (arr[cur]) arr[dest--] = arr[cur--];
        else
        {
            arr[dest--] = 0;
            arr[dest--] = 0;
            cur--;
        }
    }
}


//鸽巢原理（Pigeonhole Principle）是组合数学中的一个基本定理，描述了一种看似简单但应用广泛的逻辑关系：当物品数量超过容器数量时，至少有一个容器必须容纳多个物品。以下是通俗解释和核心要点：

//经典比喻：
//如果有 10 只鸽子飞进 9 个鸽巢，至少有一个鸽巢里会有至少 2 只鸽子。
//核心思想：资源不足时，必然出现 “超额分配”。
//算法3：一个数的每一位的平方之和为一个新数，一直重复下去
//快慢指针思想：最后一定会有一个重复的数，也就是结环，。。。
int count(int n)
{
    int ret = 0;
    while (n)
    {
        ret += (int)pow(n % 10, 2);
        n /= 10;
    }
    return ret;
}
int fast1(int n)
{
    int ret = count(n);
    return count(ret);
}
int slow1(int n)
{
    return count(n);
}
    bool isHappy(int n) {
        //经过鸽巢原理的分析，只有两种情况，并且一定会成环
        //如果是1那么成环相遇就为1，如果不是1，那么成环相遇不是1
        int fastret = n;
        int slowret = n;
        while (1)
        {
            int fast = fast1(fastret);
            int slow = slow1(slowret);
            if (fast == slow)
            {
                if (fast == 1 && slow == 1)
                {
                    return true;
                }
                else
                {
                    return false;
                }

            }
            else
            {
                fastret = fast;
                slowret = slow;
            }
        }
    }

//算法4：初阶贪心
//每次移动较矮的指针，为什么?
//涉及贪心，如果移动较大指针，那么水量是由较矮的指针决定的，那么距离减小，新的指针高度<=较矮指针
//如果移动较小指针，那么有一定几率获得更大水量
//贪杯哦~
   /* int countvolumn(const vector<int>& arr, int& i, int& j)
    {
        int di = j - i;
        int gao = arr[i];
        if (arr[j] < arr[i])
            gao = arr[j];
        return di * gao;
    }
public:              //普通n方的复杂度不满足题目要求
    int maxArea(vector<int>& height) {
        int maxvolumn = 0;
        int i = 0;
        for (i = 0; i < height.size() - 1; i++)
        {
            int j = 0;
            for (j = i + 1; j < height.size(); j++)
            {
                int tempvolumn = countvolumn(height, i, j);
                if (tempvolumn > maxvolumn)
                {
                    maxvolumn = tempvolumn;
                }
            }
        }
        return maxvolumn;
    }*/

//每次移动较矮的指针！yyds！
    int countvolumn(const vector<int>& arr, int& i, int& j)
    {
        int di = j - i;
        int gao = arr[i];
        if (arr[j] < arr[i])
            gao = arr[j];
        return di * gao;
    }

    int findmax(vector<int>& volumn)
    {
        int max = volumn[0];
        for (const auto& e : volumn)
        {
            if (e > max)
            {
                max = e;
            }
        }
        return max;
    }

    int maxArea(vector<int>& height) {
        vector<int> volumn;
        int left = 0;
        int right = height.size() - 1;
        while (left < right)
        {
            volumn.push_back(countvolumn(height, left, right));
            if (height[left] > height[right])
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return findmax(volumn);
    }


//算法5：寻找构成三角形的个数
//1.先固定最大的数
//2.在左边的区间内，使用双指针法寻找合适的值
    bool judge(int a, int b, int c)
    {
        return a + b > c;//因为数组已经有序，那么直接判断最小的两个大于第三个即可
    }

    int triangleNumber(vector<int>& nums) {
        //先固定最大的那个值，左边为left和right，如果left+right>c，那么right-left都有效
        //如果left+right<=c，那么left++去寻找可能有效的值，right--的值必定比c小，miao~
        int count = 0;//这样时间复杂度为n方
        sort(nums.begin(), nums.end());//使用nlogn排序
        for (int i = nums.size() - 1; i >= 2; i--)
        {
            int left = 0;
            int right = i - 1;
            while (left < right)
            {
                if (judge(nums[left], nums[right], nums[i]))
                {
                    count += right - left;
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
        return count;
    }

//算法6：还是双指针算法，但要注意边界值的处理！！！
    vector<vector<int>> threeSum(vector<int>& nums) {
        // vector<vector<int>> v;
        // set<vector<int>> s;//最后要利用set去重，这样会导致最后一个用例超时！
        // //必须要对left和right进行去重优化
        // sort(nums.begin(),nums.end());
        // for(int i=nums.size()-1;i>=2;i--)
        // {
        //     int left=0;
        //     int right=i-1;
        //     while(left<right)
        //     {
        //         if(nums[left]+nums[right]>-nums[i])
        //         {
        //             right--;
        //         }
        //         else if(nums[left]+nums[right]<-nums[i])
        //         {
        //             left++;
        //         }
        //         else
        //         {
        //             vector<int> tmp;
        //             tmp.push_back(nums[left]);
        //             tmp.push_back(nums[right]);
        //             tmp.push_back(nums[i]);
        //             s.insert(tmp);
        //             left++;
        //             right--;//已经相等，left或者right移动，左边既然变大了，那么右边一定要变，这里可以优化一点
        //         }
        //     }
        // }
        // for(const auto& e:s)
        // {
        //     v.push_back(e);
        // }
        // return v;

        vector<vector<int>> ret;
        // 1. 排序
        sort(nums.begin(), nums.end());
        // 2. 利⽤双指针解决问题
        int n = nums.size();
        for (int i = 0; i < n; ) // 固定数 a
        {
            if (nums[i] > 0) break; // ⼩优化
            int left = i + 1, right = n - 1, target = -nums[i];
            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum > target) right--;
                else if (sum < target) left++;
                else
                {
                    ret.push_back({ nums[i], nums[left], nums[right] });
                    left++, right--;
                    // 去重操作 left 和 right
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
            // 去重 i 
            i++;
            while (i < n && nums[i] == nums[i - 1]) i++;
        }
        return ret;

    }

//算法7：四数之和
	vector<vector<int>> fourSum(vector<int>& nums, long long int target) {//这里的target是为了防止溢出，所以要用long long int
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        if (nums.size() < 4)//这里不知道为何要传参小于4个的数组，不得而知，直接返回
        {
            return ret;
        }
        for (int i = 0; i < nums.size() - 3;)
        {
            for (int j = i + 1; j < nums.size() - 2;)
            {
                long long int Target = target - nums[i];
                int left = j + 1;
                int right = nums.size() - 1;
                long long judge = Target - nums[j];
                while (left < right)
                {
                    if (nums[left] + nums[right] > judge)
                    {
                        right--;
                    }
                    else if (nums[left] + nums[right] < judge)
                    {
                        left++;
                    }
                    else
                    {
                        vector<int> v;
                        v.push_back(nums[i]);
                        v.push_back(nums[j]);
                        v.push_back(nums[left]);
                        v.push_back(nums[right]);
                        ret.push_back(v);
                        left++; right--;
                        while (left < right && nums[left] == nums[left - 1]) left++;
                        while (left < right && nums[right] == nums[right + 1]) right--;
                    }

                }
                j++;
                while (j < nums.size() - 2 && nums[j] == nums[j - 1]) j++;
            }
            i++;
            while (i < nums.size() - 3 && nums[i] == nums[i - 1]) i++;
        }
        return ret;
    }
