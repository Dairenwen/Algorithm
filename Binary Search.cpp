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

//二分查找算法：
//二分查找其实不一定要按照一半划分，目的是按照二分性来划分
//也可以按照三分性来划分，也可以按照四分性来划分
//但是二分查找的时间复杂度是O(logn)，而三分查找的时间复杂度是O(log3n)
//所以二分查找的时间复杂度是最优的，具体过程通过数学期望来证明

//细节问题：
//1.循环继续的条件是left<=right，因为最后区间缩小到1时仍然需要判断
//2.正确性：因为具有二段性，所以可以使用二分查找，大胆抛弃所有不符合条件的数据
//3.时间复杂度：O(logn)
//4.空间复杂度：O(1)
//5.注意：mid计算的时候要使用left+(right-left)/2,而不是(left+right)/2,因为可能会溢出

//在做题时一定要记住细节问题的处理，循环条件，mid的选取方式

//总结：朴素二分查找模板
//int binarySearch(vector<int>& nums, int target) {
//	int left = 0, right = nums.size() - 1;
//	while (left <= right)
//	{
//		int mid = left + (right - left) / 2;
//		if (.....) return mid;
//		else if (.....) left = mid + 1;
//		else return .....;
//	}
//	return -1;
//}

//算法1:关键点寻找左右端点
bool check(vector<int>& nums, int target)
{
    int left = 0; int right = nums.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (nums[mid] > target) right = mid - 1;
        else if (nums[mid] < target) left = mid + 1;
        else return true;
    }
    return false;
}
vector<int> searchRange(vector<int>& nums, int target) {
    if (!check(nums, target)) return vector<int>{-1, -1};
    vector<int> ret;
    //寻找左右端点
    int left = 0; int right = nums.size() - 1;
    //寻找左端点，
    //mid<t那么left=mid+1 mid>=t right=mid
    //循环条件不能设置为left<=right，如果相等无需判断已经满足要求，否则死循环
    //mid的取值需要选择左边，如果选择右边right不会再移动死循环
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    ret.push_back(left);
    left = 0; right = nums.size() - 1;
    //寻找右端点，mid>t right=mid-1 mid<=t left=mid
    //循环条件上面相同，但是mid取法不同，要取右边，否则死循环
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (nums[mid] > target) right = mid - 1;
        else left = mid;
    }
    ret.push_back(left);
    return ret;
}

//算法2:寻找平方数，使用二分查找去1-x范围中寻找
//思路与上面一样，寻找左右两个端点值然后取平均值
int mySqrt(int x) {
    if (x == 0) return 0;
    int left = 1; int right = x;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (pow(mid, 2) < x) left = mid + 1;
        else right = mid;
    }
    int tmp = left;
    left = 1; right = x;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (pow(mid, 2) > x) right = mid - 1;
        else left = mid;
    }
    return (left + tmp) / 2;
}

//也可以是寻找最右端，也就是最大可以满足条件的值
int mySqrteasy(int x) {
    if (x == 0) return 0;
    int left = 1; int right = x;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (pow(mid, 2) > x) right = mid - 1;
        else left = mid;
    }
    return left;
}

//算法3：插入位置
int searchInsert(vector<int>& nums, int target) {
    if (target < nums[0]) return 0;
    if (target > nums[nums.size() - 1]) return nums.size();
    //只用寻找左端点就可以了，如果存在就找到了位置，如果不存在就会是稍大于target元素的位置
    //很独到的见解！而那恰好是插入的位置！
    int left = 0; int right = nums.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}

//这种题请注意如果mid-1，那么mid的取值一定要+1，否则死循环
//具体是right=mid-1还是left=mid+1要看题目要求
//算法4：寻找山峰元素，这种题就不能轻易使left=mid+1否则有可能跳过最大的元素
//此题是以arr[mid]为target
int peakIndexInMountainArray(vector<int>& arr) {
    int left = 0; int right = arr.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (arr[mid - 1] < arr[mid]) left = mid;
        else if (arr[mid - 1] > arr[mid]) right = mid - 1;
    }
    return left;
}

//算法5：寻找旋转数组的最小值，关键是寻找target，还请多加注意！
int findMin(vector<int>& nums) {
    int left = 0; int right = nums.size() - 1;
    int target = nums[right];
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target) left = mid + 1;
        else if (nums[mid] < target) right = mid;
    }
    return nums[left];
}

//寻找缺的数，提供多种思路：
//1.哈希表2.二分查找3.等差公式4.异或
//算法6：寻找缺失的数，使用二分查找
int takeAttendance1(vector<int>& r) {
    int left = 0; int right = r.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (r[mid] == mid) left = mid + 1;//一开始沾边了一点，想要根据长度去算
        //但是还是错了，判断条件中不应该出现有关于left和right，这里还是应该根据mid是否匹配来判断
        else right = mid;
    }
    if (left == r[left]) return left + 1;
    return left;
}

int takeAttendance2(vector<int>& records) {
    char arr[10000] = { 0 };
    for (const auto& e : records) arr[e]++;
    for (size_t i = 0; i < 10000; i++)
    {
        if (arr[i] == 0) return i;
    }
    return 0;
}

//算法7：寻找旋转数组的最小值，使用二分查找,plus版本，具有一定的代表性
//思路：按照前面的算法，找出最小值的下标，然后根据下标去判断target在左边还是右边
//如果在左边，那么就可以直接使用二分查找去找target
//如果在右边，那么就可以直接使用二分查找去找target
int findmin(vector<int>& arr)
{
    int left = 0; int right = arr.size() - 1; int target = arr[right];
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) left = mid + 1;
        else right = mid;
    }
    return left;
}

int search(vector<int>& nums, int target) {
    if (nums.size() == 1)
    {
        if (nums[0] == target) return 0;
        else return -1;
    }
    int min = findmin(nums);
    int left = 0; int right = nums.size() - 1;
    if ((min - 1) > -1 && target >= nums[0] && target <= nums[min - 1]) right = min - 1;
    else  left = min;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else if (nums[mid] > target) right = mid - 1;
        else return mid;
    }
    return -1;
}

//算法8：寻找旋转数组的最小值，使用二分查找,plusplus版本，请注意这里面存在重复元素
//对于数组中有重复元素的情况，二分查找时可能会有 a[l]=a[mid]=a[r]，此时无法判断区间 [l,mid] 和区间 [mid+1,r] 哪个是有序的。
//书接上回，我们是找到最小值划分区间再进行二分查找的，如果存在重复元素的话，那么无法保证左区间都是严格大于target，也就是我们选择的目标值
//数组的最后一个元素，那么就要将left移动到不与target相等的元素上

int findmin1(vector<int>& arr)
{
    int left = 0; int right = arr.size() - 1; int target = arr[right];
    while (left + 1 < arr.size() && arr[left] == target) left++;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) left = mid + 1;
        else right = mid;
    }
    return left;
}

int search1(vector<int>& nums, int target) {
    if (nums.size() == 1)   return nums[0] == target;
    int min = findmin1(nums);
    int left = 0; int right = nums.size() - 1;
    if ((min - 1) > -1 && target >= nums[0] && target <= nums[min - 1]) right = min - 1;
    else  left = min;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else if (nums[mid] > target) right = mid - 1;
        else return true;
    }
    return false;
}