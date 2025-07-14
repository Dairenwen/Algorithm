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

//分治算法：
//分治算法的思想是将一个大问题分解成若干个小问题，然后将小问题的解合并成大问题的解

//算法一：相同元素排序
//归并排序：
void _sortColors(int* nums, int* tmp, int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    _sortColors(nums, tmp, left, mid); _sortColors(nums, tmp, mid + 1, right);
    int begin1 = left; int end1 = mid;
    int begin2 = mid + 1; int end2 = right;
    int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (nums[begin1] < nums[begin2])
        {
            tmp[i++] = nums[begin1++];
        }
        else if (nums[begin1] > nums[begin2])
        {
            tmp[i++] = nums[begin2++];
        }
        else
        {
            tmp[i++] = nums[begin1++];
            tmp[i++] = nums[begin2++];
        }
    }
    while (begin1 <= end1)
    {
        tmp[i++] = nums[begin1++];
    }
    while (begin2 <= end2)
    {
        tmp[i++] = nums[begin2++];
    }
    memcpy(nums + left, tmp + left, sizeof(int) * (right - left + 1));
}
void sortColors1(vector<int>& num) {
    auto tmp = new int[num.size()];
    int nums[300] = { 0 }; int i = 0;
    for (const auto& e : num) { nums[i++] = e; }
    int left = 0; int right = num.size() - 1;
    _sortColors(nums, tmp, left, right);
    num.assign(nums, nums + num.size());
    delete[] tmp; tmp = nullptr;
}

//上述方法时间复杂度高，不推荐
//分治：类似于三路划分，但其实不是，区别很明显！只是思想相似罢了
void sortColors2(vector<int>& nums) {
    int left = 0; int right = nums.size() - 1; int cur = left;
    while (cur <= right)
    {
        if (nums[cur] == 0)
        {
            swap(nums[left], nums[cur]);
            left++; cur++;
        }
        else if (nums[cur] == 1)
        {
            cur++;
        }
        else
        {
            swap(nums[right], nums[cur]);
            right--;
        }
    }
}

//算法二：快速排序
//三数取中
int GetMidNumi(vector<int>& arr, int left, int right)
{
    int mid = (left + right) / 2;
    if (arr[mid] > arr[left])
    {
        if (arr[right] > arr[mid])
        {
            return mid;
        }
        else if (arr[right] < arr[left])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    else
    {
        if (arr[right] < arr[mid])
        {
            return mid;
        }
        else if (arr[left] < arr[right])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

void Mysort(vector<int>& nums, int left, int right)
{
    if (left >= right) return;
    int begin = left;
    int end = right;
    int cur = left + 1;
    int key = GetMidNumi(nums, left, right);
    swap(nums[left], nums[key]);
    key = nums[left];
    while (cur <= right)
    {
        if (nums[cur] < key)
        {
            swap(nums[left++], nums[cur++]);
        }
        else if (nums[cur] == key)
        {
            cur++;
        }
        else
        {
            swap(nums[cur], nums[right--]);
        }
    }
    Mysort(nums, begin, left - 1);//最后left和right分别指向相同元素区间的首尾
    Mysort(nums, right + 1, end);
}

vector<int> sortArray(vector<int>& nums) {
    int left = 0; int right = nums.size() - 1;
    Mysort(nums, left, right);
    return nums;
}

//算法四：topK问题
//有四类：前k大前k小，第k大第k小
//这里运用快排来将时间复杂度从O(nlogn)降到O(n)
int getMidNumi(vector<int>& arr, int left, int right)
{
    int mid = (left + right) / 2;
    if (arr[mid] > arr[left])
    {
        if (arr[right] > arr[mid])
        {
            return mid;
        }
        else if (arr[right] < arr[left])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    else
    {
        if (arr[right] < arr[mid])
        {
            return mid;
        }
        else if (arr[left] < arr[right])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}
//注意这里分为三部分，小于key等于key和大于key
//三个部分的长度分别为：left-begin，right-left+1，end-right
//记作lengtha，lengthb，lengthc，当k<=lengthc时，说明第k大在第三部分，
//当k<=lengthb+lengthc时，说明第k大在第二部分，直接返回key即可，
//否则说明第k大在第一部分，递归调用Mysort函数
//注意细节的处理，和长度的计算，left和right指向相同元素区间的首尾！
int Mysort(vector<int>& nums, int left, int right, int k)
{
    int begin = left; int end = right;
    int key = getMidNumi(nums, left, right);
    swap(nums[left], nums[key]);
    key = nums[left];
    int cur = left + 1;
    while (cur <= right)
    {
        if (nums[cur] < key)
        {
            swap(nums[cur++], nums[left++]);
        }
        else if (nums[cur] == key)
        {
            cur++;
        }
        else
        {
            swap(nums[cur], nums[right--]);
        }
    }
    //第三部分长度为
    int lengthc = end - right;
    //第二部分长度为
    int lengthb = right - left + 1;
    if (k <= lengthc) return Mysort(nums, right + 1, end, k);
    else if (k <= lengthb + lengthc) return key;
    else return Mysort(nums, begin, left - 1, k - lengthb - lengthc);
}

int findKthLargest(vector<int>& nums, int k) {
    int left = 0; int right = nums.size() - 1;
    return Mysort(nums, left, right, k);
}


//一个小的总结：这种k问题可以有多个解法：
//1.各种排序
//2.建堆
//3.快速选择排序

//算法五：//将归并排序的分治思想具体应用到寻找逆序对上
//具体过程与归并排序类似，在两个数组进行归并时，来统计逆序对的个数
// ！！！！！！！！！！！！！！
//找出该数有多个数比他大：仅能采用升序
//left[begin1]>right[begin2]，说明left从begin1到end1的所有元素都大于right[begin2]，
//在right[begin2]放入辅助数组之前，ret+=end1-begin1+1;
//left[begin1]==right[begin2],只将left[begin1]放入辅助数组，ret不更新
//left[begin1]<right[begin2]，说明left[begin1]放入辅助数组，ret不更新

//处理剩余元素：
//如果是左边出现剩余，说明左边剩下的所有元素都是⽐右边元素⼤的，但是它们都是已经被计算过
//的（我们以右边的元素为基准的），因此不会产⽣逆序对，仅需归并排序即可。
//如果是右边出现剩余，说明右边剩下的元素都是⽐左边⼤的，不符合逆序对的定义，因此也不需要
//处理，仅需归并排序即可。

//找出该数有多个数比他小：仅能采用降序
//left[begin1]<right[begin2]，将left[begin2]放入辅助数组，ret不更新
//left[begin1]==right[begin2]，只将left[begin2]放入辅助数组，ret不更新
//left[begin1]>right[begin2]，说明left从begin1到end1的所有元素都大于right[begin2]，
//但是，如果将begin1-left+1加入ret的话，前面就会重复计算了，right从begin2到end1的所有元素都小于left[begin1]，
//在right[begin1]放入辅助数组之前，ret+=end2-begin2+1;

//按照升序方法实现：
void Mysort(vector<int>& arr,int left,int right,vector<int>& tmp,int& ret)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    Mysort(arr, left, mid, tmp, ret); Mysort(arr, mid + 1, right, tmp, ret);
    int begin1 = left; int end1 = mid; int begin2 = mid + 1; int end2 = right; int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (arr[begin1] > arr[begin2])
        {
            tmp[i++] = arr[begin2++];
            ret += end1 - begin1 + 1;
        }
        else
        {
            tmp[i++] = arr[begin1++];
        }
    }
    while (begin1 <= end1)
    {
        tmp[i++] = arr[begin1++];
    }
    while (begin2 <= end2)
    {
        tmp[i++] = arr[begin2++];
    }
    for (int a = left; a < left + end2 - left + 1; a++)
    {
        arr[a] = tmp[a];
    }
}

int reversePairs(vector<int>& r) {
    vector<int> tmp(r.size()); int ret = 0;
    Mysort(r, 0, r.size() - 1, tmp, ret);
    return ret;
}

//按照降序方法实现：
void Mysort1(vector<int>& arr, int left, int right, vector<int>& tmp, int& ret)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    Mysort1(arr, left, mid, tmp, ret); Mysort(arr, mid + 1, right, tmp, ret);
    int begin1 = left; int end1 = mid; int begin2 = mid + 1; int end2 = right; int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (arr[begin1] > arr[begin2])
        {
            tmp[i++] = arr[begin1++];//仅仅只有这里改动
            ret += end2 - begin2 + 1;
        }
        else
        {
            tmp[i++] = arr[begin2++];//这里改动
        }
    }
    while (begin1 <= end1)
    {
        tmp[i++] = arr[begin1++];
    }
    while (begin2 <= end2)
    {
        tmp[i++] = arr[begin2++];
    }
    for (int a = left; a < left + end2 - left + 1; a++)
    {
        arr[a] = tmp[a];
    }
}

//算法六：计算右侧小于当前元素的个数
//和算法五类似，但是这里需要多三个vector
//需要记录原来数组的每一个下标，然后在归并元素的同时和下标一起归并
//这样就可以在计算出右侧小于当前元素的个数的同时，直到原来数组的下标
//push_back到结果数组中
//这里采用第二种方法，按照降序寻找右边小于当前元素的个数
void Mysort2(vector<int>& arr, int left, int right, vector<int>& tmp1,
    vector<int>& sign, vector<int>& tmp2, vector<int>& ret)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    Mysort2(arr, left, mid, tmp1, sign, tmp2, ret);
    Mysort2(arr, mid + 1, right, tmp1, sign, tmp2, ret);
    int begin1 = left; int end1 = mid;
    int begin2 = mid + 1; int end2 = right;
    int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (arr[begin1] > arr[begin2])
        {
            tmp1[i] = arr[begin1];
            tmp2[i] = sign[begin1];
            ret[sign[begin1]] += end2 - begin2 + 1;//这里是重点
            i++; begin1++;
        }
        else
        {
            tmp1[i] = arr[begin2];//这里改动
            tmp2[i] = sign[begin2];
            i++; begin2++;
        }
    }
    while (begin1 <= end1)
    {
        tmp1[i] = arr[begin1];
        tmp2[i] = sign[begin1];
        i++; begin1++;
    }
    while (begin2 <= end2)
    {
        tmp1[i] = arr[begin2];
        tmp2[i] = sign[begin2];
        i++; begin2++;
    }
    for (int a = left; a < left + end2 - left + 1; a++)
    {
        arr[a] = tmp1[a];
        sign[a] = tmp2[a];
    }
}

vector<int> countSmaller(vector<int>& r) {
    vector<int> tmp1(r.size());
    vector<int> tmp2(r.size());
    vector<int> ret(r.size());
    vector<int> sign;
    for (int i = 0; i < r.size(); i++) sign.push_back(i);
    Mysort2(r, 0, r.size() - 1, tmp1, sign, tmp2, ret);
    return ret;
}

//算法七：计算nums[i] > 2*nums[j]中的偶序对个数
//很相似但是不一样，这里需要在归并之前使用双指针来计算偶序对个数
//还是按照升序计算end1-cur1+1，降序计算end2-cur2+1来计算吧
//双指针的思想还是要运用起来啊，这题自己写的时候超时了，不知道为什么
class Solution
{
    int tmp[50010];
public:
    int reversePairs(vector<int>& nums)
    {
        return mergeSort(nums, 0, nums.size() - 1);
    }
    int mergeSort(vector<int>& nums, int left, int right)
    {
        if (left >= right) return 0;
        int ret = 0;
        // 1. 先根据中间元素划分区间
        int mid = (left + right) >> 1;
        // [left, mid] [mid + 1, right]
        // 2. 先计算左右两侧的翻转对
        ret += mergeSort(nums, left, mid);
        ret += mergeSort(nums, mid + 1, right);
        // 3. 先计算翻转对的数量
        int cur1 = left, cur2 = mid + 1, i = left;
        while (cur2 <= right) // 升序的情况
        {
            while (cur1 <= mid && nums[cur2] >= nums[cur1] / 2.0) cur1++;
            if (cur1 > mid)
                break;
            ret += mid - cur1 + 1;
            cur2++;
        }
        // 4. 合并两个有序数组
        cur1 = left, cur2 = mid + 1;
        while (cur1 <= mid && cur2 <= right)
            tmp[i++] = nums[cur1] <= nums[cur2] ? nums[cur1++] : nums[cur2++];
        while (cur1 <= mid) tmp[i++] = nums[cur1++];
        while (cur2 <= right) tmp[i++] = nums[cur2++];
        for (int j = left; j <= right; j++)
            nums[j] = tmp[j];

        return ret;
    }
};
