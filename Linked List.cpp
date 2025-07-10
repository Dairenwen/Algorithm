#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<queue>
#include<map>
#include<set>
#include<list>
#include<unordered_map>
#include<unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//链表常用技巧和总结：
//1.画图！！！！
//2.注意使用带哨兵位点的链表，哨兵位点的作用是简化边界条件的判断
//3.不要吝啬变量，大胆定义来连接结点，不要全部用指针
//4.快慢双指针，解决链表是否有环/环的入口/倒数第n个结点等问题
//5.链表中常用操作：创建一个新节点，尾插，头插

//算法一：链表相加
//思路：就采用模拟的思想，根据数字的进位来进行相加，
//注意最后需要判断一下是否还有进位
//采用一个哨兵位点可以不用判断第一个头结点
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    //可以用一个哨兵位点，也可以不使用，需要判断一下头结点是否为空
    ListNode* guard = new ListNode; ListNode* tail = guard;
    int count = 0;
    while (l1 && l2)
    {
        ListNode* tmp = new ListNode((l1->val + l2->val + count) % 10);
        count = (l1->val + l2->val + count) / 10;
        tail->next = tmp;
        tail = tmp;
        l1 = l1->next; l2 = l2->next;
    }
    while (l1)
    {
        ListNode* tmp = new ListNode((l1->val + count) % 10);
        count = (l1->val + count) / 10;
        tail->next = tmp;
        tail = tmp;
        l1 = l1->next;
    }
    while (l2)
    {
        ListNode* tmp = new ListNode((l2->val + count) % 10);
        count = (l2->val + count) / 10;
        tail->next = tmp;
        tail = tmp;
        l2 = l2->next;
    }
    if (count)
    {
        ListNode* tmp = new ListNode((count) % 10);
        count = (count) / 10;
        tail->next = tmp;
        tail = tmp;
    }
    if (tail) tail->next = nullptr;
    return guard->next;
}

//算法二：链表节点的交换
//注意head，first等等可能为空，不要对空指针进行解引用了！
ListNode* swapPairs(ListNode* head) {
    ListNode* frist = head;
    ListNode* second = nullptr;
    if (head) second = head->next;
    ListNode* guard = new ListNode; ListNode* tail = guard;
    while (frist && second)
    {
        ListNode* next1 = second->next;
        tail->next = second;
        tail = second;
        tail->next = frist;
        tail = frist;
        frist = next1;
        if (frist) second = frist->next;
        else second = nullptr;
    }
    if (frist)
    {
        tail->next = frist;
        tail = frist;
    }
    if (tail) tail->next = nullptr;
    return guard->next;
}
//注意！一定要画图分析，tail的尾部置nullptr，以及指针死循环的处理！很重要！

//算法三：链表的重排
//思路：先将链表的结点存储到一个数组中，然后使用双指针的方式来进行重排
//也可以使用快慢指针来找到链表的中间结点，然后将链表分成两段，
//然后将后半段的链表进行反转，然后再进行重排
//本人首先想到的是第一个方法，实际面试建议使用第二个
void reorderList1(ListNode* head) {
    vector<ListNode*> arr;
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    ListNode* cur = head;
    while (cur)
    {
        arr.push_back(cur);
        cur = cur->next;
    }
    int begin = 0; int end = arr.size() - 1;
    while (begin < (arr.size() + 1) / 2)
    {
        tail->next = arr[begin];
        tail = arr[begin++];
        if (begin >= (arr.size() + 1) / 2) break;
        tail->next = arr[end];
        tail = arr[end--];
    }
    if (begin == end)
    {
        tail->next = arr[end];
        tail = arr[end--];
    }
    if (tail) tail->next = nullptr;
    head = guard->next;
}

//以下是第二种方法的实现
//思路：使用快慢指针来找到链表的中间结点，然后将链表分成两段，
//然后将后半段的链表进行反转，然后再进行重排
//注意！一定要画图分析，tail的尾部置nullptr，以及指针死循环的处理！很重要！
ListNode* findmidnode(ListNode* head)
{
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* prev = head;
    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = nullptr;//这里记得将后面置空否则会出现问题
    return slow;
}

ListNode* reverselist(ListNode* head)
{
    ListNode* p1 = nullptr;
    ListNode* p2 = head;
    ListNode* p3 = nullptr;
    if (head) p3 = head->next;
    while (p2)
    {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        if (p3) p3 = p3->next;
    }
    return p1;
}

void reorderList2(ListNode* head) {
    if (head->next == nullptr) return;
    ListNode* mid = findmidnode(head);
    ListNode* begin2 = reverselist(mid);
    ListNode* begin1 = head;
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    while (begin1 && begin2)
    {
        tail->next = begin1;
        tail = begin1;
        begin1 = begin1->next;
        tail->next = begin2;
        tail = begin2;
        begin2 = begin2->next;
    }
    if (begin1)
    {
        tail->next = begin1;
    }
    if (begin2)
    {
        tail->next = begin2;
    }
    head = guard->next;
}

//算法四：多个链表的合并
//思路一：使用优先级队列来进行合并，建小堆，每次取堆顶的元素进行尾插，
//如果下一个结点不为空，入堆
//时间复杂度为nklogk
struct Greater
{
public:
    bool operator()(const ListNode* p1, const ListNode* p2)
    {
        return p1->val > p2->val;
    }
};

ListNode* mergeKLists1(vector<ListNode*>& lists) {
    //这题的关键是使用优先级队列
    //建小堆，每次取堆顶的元素进行尾插，如果下一个结点不为空，入堆
    priority_queue<ListNode*, vector<ListNode*>, Greater> heap;
    //优先级队列的使用全都忘光了，复习一下
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    for (int i = 0; i < lists.size(); i++)
    {
        if (lists[i]) heap.push(lists[i]);
    }
    while (heap.size())
    {
        tail->next = heap.top();
        tail = heap.top();
        heap.pop();
        if (tail->next) heap.push(tail->next);
    }
    return guard->next;
}

//思路二：使用递归
//时间复杂度为nklogk
ListNode* Merge(ListNode* p1, ListNode* p2);

ListNode* Mysort(vector<ListNode*>& arr, int left, int right)
{
    if (left > right) return nullptr;
    if (left == right) return arr[left];//注意这里边界情况的处理，不能返回nullptr
    int mid = left + (right - left) / 2;
    ListNode* begin1 = Mysort(arr, left, mid);
    ListNode* begin2 = Mysort(arr, mid + 1, right);
    return Merge(begin1, begin2);
}

ListNode* Merge(ListNode* p1, ListNode* p2)
{
    if (p1 == nullptr) return p2;
    if (p2 == nullptr) return p1;
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    while (p1 && p2)
    {
        if (p1->val < p2->val)
        {
            tail->next = p1;
            tail = p1;
            p1 = p1->next;
        }
        else
        {
            tail->next = p2;
            tail = p2;
            p2 = p2->next;
        }
    }
    if (p1)  tail->next = p1;
    if (p2)  tail->next = p2;
    return guard->next;
}

ListNode* mergeKLists2(vector<ListNode*>& lists) {
    //归并排序
    int n = lists.size();
    return Mysort(lists, 0, n - 1);
}

//算法五：链表的模拟反转
//思路：说是模拟，其实就是一步一步走，请注意这一类题型的结点保存
//否则会出现死循环或者空指针异常，最后对尾部的处理也要注意
//如果length < k，就直接连接
//如果length == k，就需要进行反转后再进行连接
ListNode* reversesingle(ListNode* head)
{
    ListNode* p1 = nullptr;
    ListNode* p2 = head;
    ListNode* p3 = nullptr;
    if (head) p3 = head->next;
    while (p2)
    {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        if (p3) p3 = p3->next;
    }
    return p1;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    int length = 0; int count = 0;
    ListNode* cur = head;
    ListNode* prev = head;
    ListNode* save = head;
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    while (cur)
    {
        length++;
        cur = cur->next;
    }
    cur = head;
    while (cur && length >= k)
    {
        if (count == k)
        {
            save->next = nullptr;//一定要记得处理尾部
            tail->next = reversesingle(prev);
            tail = prev;
            prev = cur;
            count = 0;//计数置为0
            length -= k;
        }
        else
        {
            count++;
            save = cur;
            cur = cur->next;
        }
    }
    if (length < k)
    {
        tail->next = prev;
    }
    if (length == k)
    {
        tail->next = reversesingle(prev);
    }
    return guard->next;
}

//非常考验代码能力的一道题目！很好
ListNode* swapNodes(ListNode* head, int k) {
    int length = 0;
    int count = 0;
    ListNode* cur = head;
    ListNode* first = nullptr;
    ListNode* second = nullptr;
    ListNode* next1 = nullptr;
    ListNode* next2 = nullptr;
    ListNode* next = nullptr;
    ListNode* guard = new ListNode;
    ListNode* tail = guard;
    while (cur)
    {
        length++;
        cur = cur->next;
    }
    cur = head;
    while (cur)
    {
        count++;
        if (count == k)
        {
            first = cur;
            next1 = cur->next;
        }
        if (count == length + 1 - k)
        {
            second = cur;
            next2 = cur->next;
        }
        cur = cur->next;
    }
    cur = head; count = 0;
    next = k < length + 1 - k ? next2 : next1;
    while (cur)
    {
        count++;
        if (count == k)
        {
            tail->next = second;
            tail = second;
        }
        else if (count == length + 1 - k && first != second)
        {
            tail->next = first;
            tail = first;
        }
        else if (count != k && count != length + 1 - k)
        {
            if (k < length + 1 - k && count == length + 2 - k) cur = next;
            else if (k > length + 1 - k && count == k + 1) cur = next;
            tail->next = cur;
            tail = cur;
        }
        if (count == length) break;
        cur = cur->next;
    }
    if (tail) tail->next = nullptr;
    return guard->next;
}


//int main()
//{
//	ListNode* head = new ListNode(7);
//	ListNode* head1 = new ListNode(9);
//	ListNode* head2 = new ListNode(6);
//	ListNode* head3 = new ListNode(6);
//	ListNode* head4 = new ListNode(7);
//	ListNode* head5 = new ListNode(8);
//	ListNode* head6 = new ListNode(3);
//	ListNode* head7 = new ListNode(0);
//	ListNode* head8 = new ListNode(9);
//	ListNode* head9 = new ListNode(5);
//	head->next = head1;
//	head1->next = head2;
//	head2->next = head3;
//	head3->next = head4;
//	head4->next = head5;
//	head5->next = head6;
//	head6->next = head7;
//	head7->next = head8;
//	head8->next = head9;
//	swapNodes(head, 5);
//	return 0;
//}