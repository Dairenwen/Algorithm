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

//���ֲ����㷨��
//���ֲ�����ʵ��һ��Ҫ����һ�뻮�֣�Ŀ���ǰ��ն�����������
//Ҳ���԰��������������֣�Ҳ���԰����ķ���������
//���Ƕ��ֲ��ҵ�ʱ�临�Ӷ���O(logn)�������ֲ��ҵ�ʱ�临�Ӷ���O(log3n)
//���Զ��ֲ��ҵ�ʱ�临�Ӷ������ŵģ��������ͨ����ѧ������֤��

//ϸ�����⣺
//1.ѭ��������������left<=right����Ϊ���������С��1ʱ��Ȼ��Ҫ�ж�
//2.��ȷ�ԣ���Ϊ���ж����ԣ����Կ���ʹ�ö��ֲ��ң����������в���������������
//3.ʱ�临�Ӷȣ�O(logn)
//4.�ռ临�Ӷȣ�O(1)
//5.ע�⣺mid�����ʱ��Ҫʹ��left+(right-left)/2,������(left+right)/2,��Ϊ���ܻ����

//������ʱһ��Ҫ��סϸ������Ĵ���ѭ��������mid��ѡȡ��ʽ

//�ܽ᣺���ض��ֲ���ģ��
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

//�㷨1:�ؼ���Ѱ�����Ҷ˵�
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
    //Ѱ�����Ҷ˵�
    int left = 0; int right = nums.size() - 1;
    //Ѱ����˵㣬
    //mid<t��ôleft=mid+1 mid>=t right=mid
    //ѭ��������������Ϊleft<=right�������������ж��Ѿ�����Ҫ�󣬷�����ѭ��
    //mid��ȡֵ��Ҫѡ����ߣ����ѡ���ұ�right�������ƶ���ѭ��
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    ret.push_back(left);
    left = 0; right = nums.size() - 1;
    //Ѱ���Ҷ˵㣬mid>t right=mid-1 mid<=t left=mid
    //ѭ������������ͬ������midȡ����ͬ��Ҫȡ�ұߣ�������ѭ��
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (nums[mid] > target) right = mid - 1;
        else left = mid;
    }
    ret.push_back(left);
    return ret;
}

//�㷨2:Ѱ��ƽ������ʹ�ö��ֲ���ȥ1-x��Χ��Ѱ��
//˼·������һ����Ѱ�����������˵�ֵȻ��ȡƽ��ֵ
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

//Ҳ������Ѱ�����Ҷˣ�Ҳ��������������������ֵ
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

//�㷨3������λ��
int searchInsert(vector<int>& nums, int target) {
    if (target < nums[0]) return 0;
    if (target > nums[nums.size() - 1]) return nums.size();
    //ֻ��Ѱ����˵�Ϳ����ˣ�������ھ��ҵ���λ�ã���������ھͻ����Դ���targetԪ�ص�λ��
    //�ܶ����ļ��⣡����ǡ���ǲ����λ�ã�
    int left = 0; int right = nums.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}

//��������ע�����mid-1����ômid��ȡֵһ��Ҫ+1��������ѭ��
//������right=mid-1����left=mid+1Ҫ����ĿҪ��
//�㷨4��Ѱ��ɽ��Ԫ�أ�������Ͳ�������ʹleft=mid+1�����п�����������Ԫ��
//��������arr[mid]Ϊtarget
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

//�㷨5��Ѱ����ת�������Сֵ���ؼ���Ѱ��target��������ע�⣡
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

//Ѱ��ȱ�������ṩ����˼·��
//1.��ϣ��2.���ֲ���3.�Ȳʽ4.���
//�㷨6��Ѱ��ȱʧ������ʹ�ö��ֲ���
int takeAttendance1(vector<int>& r) {
    int left = 0; int right = r.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (r[mid] == mid) left = mid + 1;//һ��ʼմ����һ�㣬��Ҫ���ݳ���ȥ��
        //���ǻ��Ǵ��ˣ��ж������в�Ӧ�ó����й���left��right�����ﻹ��Ӧ�ø���mid�Ƿ�ƥ�����ж�
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

//�㷨7��Ѱ����ת�������Сֵ��ʹ�ö��ֲ���,plus�汾������һ���Ĵ�����
//˼·������ǰ����㷨���ҳ���Сֵ���±꣬Ȼ������±�ȥ�ж�target����߻����ұ�
//�������ߣ���ô�Ϳ���ֱ��ʹ�ö��ֲ���ȥ��target
//������ұߣ���ô�Ϳ���ֱ��ʹ�ö��ֲ���ȥ��target
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

//�㷨8��Ѱ����ת�������Сֵ��ʹ�ö��ֲ���,plusplus�汾����ע������������ظ�Ԫ��
//�������������ظ�Ԫ�ص���������ֲ���ʱ���ܻ��� a[l]=a[mid]=a[r]����ʱ�޷��ж����� [l,mid] ������ [mid+1,r] �ĸ�������ġ�
//����ϻأ��������ҵ���Сֵ���������ٽ��ж��ֲ��ҵģ���������ظ�Ԫ�صĻ�����ô�޷���֤�����䶼���ϸ����target��Ҳ��������ѡ���Ŀ��ֵ
//��������һ��Ԫ�أ���ô��Ҫ��left�ƶ�������target��ȵ�Ԫ����

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