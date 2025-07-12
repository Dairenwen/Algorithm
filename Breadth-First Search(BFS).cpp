#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<bitset>
#include<map>
#include<set>
#include<list>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//开始搜索类算法！
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
//经典算法：多叉树的层序遍历（广度优先搜索）
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> ret;
    queue<Node*> q;//当然运用队列
    if (root) q.push(root);
    while (q.size())
    {
        int sz = q.size();//统计每一层的数量，这样队列前面的sz个就是这一层的结点
        vector<int> tmp;
        for (int i = 0; i < sz; i++)//遍历每一个结点，把它们不为空的孩子入队列
        {
            Node* fro = q.front(); q.pop();
			tmp.push_back(fro->val);//别忘了先把结点的值push一下！
            for (const auto& e : fro->children)
            {
                if (e) q.push(e);
            }
        }
        ret.push_back(tmp);
    }
    return ret;
}

//扩展扩展：
//N叉树的前后序遍历：
void _preorder(Node* root, vector<int>& ret)
{
    if (!root) return;
    ret.push_back(root->val);
    int sz = root->children.size();
    for (int i = 0; i < sz; i++)
    {
        _preorder(root->children[i], ret);
    }
}
vector<int> preorder(Node* root) {
    vector<int> ret;
    _preorder(root, ret);
    return ret;
}

void _postorder(Node* root, vector<int>& ret)
{
    if (!root) return;
    int sz = root->children.size();
    for (int i = 0; i < sz; i++)
    {
        _postorder(root->children[i], ret);
    }
    ret.push_back(root->val);
}
vector<int> postorder(Node* root) {
    vector<int> ret;
    _postorder(root, ret);
    return ret;
}

//二叉树层序遍历（锯齿形）
//给定一个二叉树，返回其节点值的锯齿形层序遍历（即：从左到右，下一层从右到左交替进行）。
enum Status
{
    Right,
    Left
};
vector<vector<int>> zigzagLevelOrder1(TreeNode* root) {
    vector<vector<int>> ret;
    queue<TreeNode*> q;
    bool judge = Right;
    if (root)
    {
        q.push(root);
        judge = Left;
    }
    while (q.size())
    {
        int sz = q.size();
        vector<int> tmp;
        vector<TreeNode*> copy;
		//大致过程差不多，唯一的区别就是要把每一层的结点都放到一个临时的数组中，然后反转一下！
        for (int i = 0; i < sz; i++)
        {
            TreeNode* front = q.front();
            q.pop(); copy.push_back(front);
        }
        reverse(copy.begin(), copy.end());
        //我觉得关键点在这里反转，确定需要反转就可以确定左右节点的入队顺序
        for (int i = 0; i < sz; i++)
        {
            tmp.push_back(copy[i]->val);
            if (judge == Right)
            {
                if (copy[i]->right) q.push(copy[i]->right);
                if (copy[i]->left) q.push(copy[i]->left);
                //注意一下这里的顺序！可以模拟一下
            }
            else
            {
                if (copy[i]->left) q.push(copy[i]->left);
                if (copy[i]->right) q.push(copy[i]->right);
                //注意这里的顺序，可以模拟一下！
            }
        }
        if (judge == Right) judge = Left;
        else judge = Right;
        //其实只需要判断最后这里tmp是否需要反转就行了哈哈哈哈，个人做法麻烦了！
        ret.push_back(tmp);
    }
    return ret;
}
//标准做法：
vector<vector<int>> zigzagLevelOrder2(TreeNode* root)
{
    vector<vector<int>> ret;
    if (root == nullptr) return ret;
    queue<TreeNode*> q;
    q.push(root);
    int level = 1;
    while (q.size())
    {
        int sz = q.size();
        vector<int> tmp;
        for (int i = 0; i < sz; i++)
        {
            auto t = q.front();
            q.pop();
            tmp.push_back(t->val);
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        // 判断是否逆序
        if (level % 2 == 0) reverse(tmp.begin(), tmp.end());
		//最后来个判断是否需要反转就行了，简洁明了！
        ret.push_back(tmp);
        level++;
    }
    return ret;
}

//树的最大宽度
//温馨提醒：这一题不能够使用常规思路，即将空结点也入队列，
//但是最多有3000个结点，这样写会超时！内存也会爆炸！
//正确的做法是：将每个结点的编号编入pair存入队列中，这样就可以通过编号来计算宽度了！
//注意子序号的计算是父亲结点的序号乘以2加上1或2，至于为什么要用unsigned int呢？
//因为如果用int的话，可能会出现负数的情况，这样就会导致计算错误！（待商榷）
int widthOfBinaryTree(TreeNode* root) {
    int ret = 1;
    queue<pair<TreeNode*, unsigned int>> q;
    if (root) q.push({ root,0 });
    while (q.size())
    {
        int sz = q.size();
        unsigned int start, end = 0;
        for (int i = 0; i < sz; i++)
        {
            pair<TreeNode*, unsigned int> front = q.front();
            q.pop();
            if (i == 0) start = front.second;
            if (i == sz - 1) end = front.second;
            if (front.first->left) q.push({ front.first->left,front.second * 2 + 1 });
            if (front.first->right) q.push({ front.first->right,front.second * 2 + 2 });
        }
        if (end - start + 1 > ret) ret = end - start + 1;
    }
    return ret;
}


//白送啊我去，无需多言，基操勿六，拿下！
vector<int> largestValues(TreeNode* root) {
    vector<int> ret;
    queue<TreeNode*> q;
    if (root) q.push(root);
    while (q.size())
    {
        int sz = q.size();
        int max = -INT_MAX - 1;
        for (int i = 0; i < sz; i++)
        {
            TreeNode* front = q.front(); q.pop();
            if (front->val > max) max = front->val;
            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
        ret.push_back(max);
    }
    return ret;
}

//队列+宽搜的题目暂时就更新到这里啦！


//int main()
//{
//	TreeNode* root = new TreeNode(236);
//	root->left = new TreeNode(104);
//	root->right = new TreeNode(701);
//	root->left->right = new TreeNode(227);
//	root->right->right = new TreeNode(911);
//
//	return 0;
//}