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

//�����ü��ɺ��ܽ᣺
//1.��ͼ��������
//2.ע��ʹ�ô��ڱ�λ��������ڱ�λ��������Ǽ򻯱߽��������ж�
//3.��Ҫ���ı������󵨶��������ӽ�㣬��Ҫȫ����ָ��
//4.����˫ָ�룬��������Ƿ��л�/�������/������n����������
//5.�����г��ò���������һ���½ڵ㣬β�壬ͷ��

//�㷨һ���������
//˼·���Ͳ���ģ���˼�룬�������ֵĽ�λ��������ӣ�
//ע�������Ҫ�ж�һ���Ƿ��н�λ
//����һ���ڱ�λ����Բ����жϵ�һ��ͷ���
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    //������һ���ڱ�λ�㣬Ҳ���Բ�ʹ�ã���Ҫ�ж�һ��ͷ����Ƿ�Ϊ��
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

//�㷨��������ڵ�Ľ���
//ע��head��first�ȵȿ���Ϊ�գ���Ҫ�Կ�ָ����н������ˣ�
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
//ע�⣡һ��Ҫ��ͼ������tail��β����nullptr���Լ�ָ����ѭ���Ĵ�������Ҫ��

//�㷨�������������
//˼·���Ƚ�����Ľ��洢��һ�������У�Ȼ��ʹ��˫ָ��ķ�ʽ����������
//Ҳ����ʹ�ÿ���ָ�����ҵ�������м��㣬Ȼ������ֳ����Σ�
//Ȼ�󽫺��ε�������з�ת��Ȼ���ٽ�������
//���������뵽���ǵ�һ��������ʵ�����Խ���ʹ�õڶ���
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

//�����ǵڶ��ַ�����ʵ��
//˼·��ʹ�ÿ���ָ�����ҵ�������м��㣬Ȼ������ֳ����Σ�
//Ȼ�󽫺��ε�������з�ת��Ȼ���ٽ�������
//ע�⣡һ��Ҫ��ͼ������tail��β����nullptr���Լ�ָ����ѭ���Ĵ�������Ҫ��
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
    prev->next = nullptr;//����ǵý������ÿշ�����������
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

//�㷨�ģ��������ĺϲ�
//˼·һ��ʹ�����ȼ����������кϲ�����С�ѣ�ÿ��ȡ�Ѷ���Ԫ�ؽ���β�壬
//�����һ����㲻Ϊ�գ����
//ʱ�临�Ӷ�Ϊnklogk
struct Greater
{
public:
    bool operator()(const ListNode* p1, const ListNode* p2)
    {
        return p1->val > p2->val;
    }
};

ListNode* mergeKLists1(vector<ListNode*>& lists) {
    //����Ĺؼ���ʹ�����ȼ�����
    //��С�ѣ�ÿ��ȡ�Ѷ���Ԫ�ؽ���β�壬�����һ����㲻Ϊ�գ����
    priority_queue<ListNode*, vector<ListNode*>, Greater> heap;
    //���ȼ����е�ʹ��ȫ�������ˣ���ϰһ��
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

//˼·����ʹ�õݹ�
//ʱ�临�Ӷ�Ϊnklogk
ListNode* Merge(ListNode* p1, ListNode* p2);

ListNode* Mysort(vector<ListNode*>& arr, int left, int right)
{
    if (left > right) return nullptr;
    if (left == right) return arr[left];//ע������߽�����Ĵ������ܷ���nullptr
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
    //�鲢����
    int n = lists.size();
    return Mysort(lists, 0, n - 1);
}

//�㷨�壺�����ģ�ⷴת
//˼·��˵��ģ�⣬��ʵ����һ��һ���ߣ���ע����һ�����͵Ľ�㱣��
//����������ѭ�����߿�ָ���쳣������β���Ĵ���ҲҪע��
//���length < k����ֱ������
//���length == k������Ҫ���з�ת���ٽ�������
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
            save->next = nullptr;//һ��Ҫ�ǵô���β��
            tail->next = reversesingle(prev);
            tail = prev;
            prev = cur;
            count = 0;//������Ϊ0
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

//�ǳ��������������һ����Ŀ���ܺ�
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