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

//��ʼ�������㷨��
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
 
//�����㷨��������Ĳ���������������������
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> ret;
    queue<Node*> q;//��Ȼ���ö���
    if (root) q.push(root);
    while (q.size())
    {
        int sz = q.size();//ͳ��ÿһ�����������������ǰ���sz��������һ��Ľ��
        vector<int> tmp;
        for (int i = 0; i < sz; i++)//����ÿһ����㣬�����ǲ�Ϊ�յĺ��������
        {
            Node* fro = q.front(); q.pop();
			tmp.push_back(fro->val);//�������Ȱѽ���ֵpushһ�£�
            for (const auto& e : fro->children)
            {
                if (e) q.push(e);
            }
        }
        ret.push_back(tmp);
    }
    return ret;
}

//��չ��չ��
//N������ǰ���������
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

//�������������������Σ�
//����һ����������������ڵ�ֵ�ľ���β�����������������ң���һ����ҵ�������У���
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
		//���¹��̲�࣬Ψһ���������Ҫ��ÿһ��Ľ�㶼�ŵ�һ����ʱ�������У�Ȼ��תһ�£�
        for (int i = 0; i < sz; i++)
        {
            TreeNode* front = q.front();
            q.pop(); copy.push_back(front);
        }
        reverse(copy.begin(), copy.end());
        //�Ҿ��ùؼ��������ﷴת��ȷ����Ҫ��ת�Ϳ���ȷ�����ҽڵ�����˳��
        for (int i = 0; i < sz; i++)
        {
            tmp.push_back(copy[i]->val);
            if (judge == Right)
            {
                if (copy[i]->right) q.push(copy[i]->right);
                if (copy[i]->left) q.push(copy[i]->left);
                //ע��һ�������˳�򣡿���ģ��һ��
            }
            else
            {
                if (copy[i]->left) q.push(copy[i]->left);
                if (copy[i]->right) q.push(copy[i]->right);
                //ע�������˳�򣬿���ģ��һ�£�
            }
        }
        if (judge == Right) judge = Left;
        else judge = Right;
        //��ʵֻ��Ҫ�ж��������tmp�Ƿ���Ҫ��ת�����˹������������������鷳�ˣ�
        ret.push_back(tmp);
    }
    return ret;
}
//��׼������
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
        // �ж��Ƿ�����
        if (level % 2 == 0) reverse(tmp.begin(), tmp.end());
		//��������ж��Ƿ���Ҫ��ת�����ˣ�������ˣ�
        ret.push_back(tmp);
        level++;
    }
    return ret;
}

//���������
//��ܰ���ѣ���һ�ⲻ�ܹ�ʹ�ó���˼·�������ս��Ҳ����У�
//���������3000����㣬����д�ᳬʱ���ڴ�Ҳ�ᱬը��
//��ȷ�������ǣ���ÿ�����ı�ű���pair��������У������Ϳ���ͨ��������������ˣ�
//ע������ŵļ����Ǹ��׽�����ų���2����1��2������ΪʲôҪ��unsigned int�أ�
//��Ϊ�����int�Ļ������ܻ���ָ���������������ͻᵼ�¼�����󣡣�����ȶ��
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


//���Ͱ���ȥ��������ԣ��������������£�
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

//����+���ѵ���Ŀ��ʱ�͸��µ���������


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