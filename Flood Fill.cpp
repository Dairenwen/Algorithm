#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//����˵��
// 
//�ݹ� DFS ʵ�֣�
//ͨ���ݹ���ô����ĸ���������ڵ㡣
//���߽���������ɫƥ�䣬����Խ����ظ�����
//ʱ�临�Ӷȣ�O(N)������ N ����Ҫ������������
//�ռ临�Ӷȣ������� O(N)���ݹ�ջ��ȣ���
// 
//����1���ݹ�ʵ�֣�DFS��
class SolutionDFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int targetColor = image[sr][sc];
        if (targetColor != newColor) {
            dfs(image, sr, sc, targetColor, newColor);
        }
        return image;
    }

private:
    void dfs(vector<vector<int>>& image, int r, int c, int targetColor, int newColor) {
        // ���߽���������ɫ�Ƿ�ƥ��
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() ||
            image[r][c] != targetColor) {
            return;
        }

        // �滻��ɫ���ݹ鴦�����ڵ�
        image[r][c] = newColor;
        dfs(image, r + 1, c, targetColor, newColor); // ��
        dfs(image, r - 1, c, targetColor, newColor); // ��
        dfs(image, r, c + 1, targetColor, newColor); // ��
        dfs(image, r, c - 1, targetColor, newColor); // ��
    }
};

//���� BFS ʵ�֣�
//ʹ�ö��д洢����������ص㡣
//ͨ��ѭ����������е�ÿ���㣬�������ڷ��������ĵ������С�
//ʱ�临�Ӷȣ�O(N)��
//�ռ临�Ӷȣ������� O(N)�����д洢���д�����㣩��
//
//����2������ʵ�֣�BFS��
class SolutionBFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int rows = image.size();
        int cols = image[0].size();
        int targetColor = image[sr][sc];

        if (targetColor == newColor) {
            return image; // �����ظ�����
        }

        queue<pair<int, int>> q;
        q.push({ sr, sc });
        image[sr][sc] = newColor; // ������

        // �����ĸ������¡��ϡ��ҡ���
        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            // �����ĸ���������ڵ�
            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                // ����Ƿ�Խ������ɫ�Ƿ�ƥ��
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && image[nr][nc] == targetColor) 
                {
                    image[nr][nc] = newColor;
                    q.push({ nr, nc });
                }
            }
        }

        return image;
    }
};

//����ʾ����
//����ͼ��Ϊ 3x3 �������Ϊ(1, 1)������ɫΪ 2��
//�ֱ�ʹ�� DFS �� BFS ������䣬����������
//���ַ������������ͬ���� DFS �����ڴ�����ģ����ʱ����ջ������� BFS ���ʺ��ڴ��������ʵ������ѡ����ʵ�ʵ�ַ�ʽ��
//���Դ���
void testFloodFill() 
{
    // ʾ������ͼ��
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    int sr = 1, sc = 1; // �������
    int newColor = 2;   // ����ɫ

    // ʹ�� DFS ����
    SolutionDFS dfsSolver;
    vector<vector<int>> resultDFS = dfsSolver.floodFill(image, sr, sc, newColor);

    cout << "DFS �����:" << endl;
    for (const auto& row : resultDFS) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // ʹ�� BFS ������ע�⣺��Ҫ���³�ʼ�� image����Ϊ DFS �Ѿ��޸�������
    vector<vector<int>> imageBFS = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    SolutionBFS bfsSolver;
    vector<vector<int>> resultBFS = bfsSolver.floodFill(imageBFS, sr, sc, newColor);

    cout << "\nBFS �����:" << endl;
    for (const auto& row : resultBFS) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

}


//�㷨һ��������������ѧϵfloodfill�����ӣ��Լ�д��һ�飨BFS��
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newcolor) {
    //���ж��ŵ�floodfill������������һ�°ɣ�
    int rows = image.size();
    int cols = image[0].size();
    int color = image[sr][sc];//Ҫ����һ��ԭ������ɫ���ں��������ж�
    if (image[sr][sc] == newcolor) return image;
    else image[sr][sc] = newcolor;
    //�ö�����ģ��BFS
    queue<pair<int, int>> q; q.push({ sr,sc });//������
    //��������ģ���ĸ�����
    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            //�����ĸ�����ɢ����ע�����ж�Խ�������
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && image[nr][nc] == color)
            {
                image[nr][nc] = newcolor;
                q.push({ nr,nc });
            }
        }
    }
    return image;
}

//�㷨�������û�и���ʼ���أ������￪ʼ��ɢ����Ȼ�Ǳ���һ���ά���飬��ÿһ��Ϊ��㿪ʼ����
//��ô����������Ѿ��������ĵط��أ�������������֣��ͻ�д����ѭ��
//������������1.����ʱ�ܷ�������飿���������ôֱ�ӱ��Ϊ0�Ϳ�����
//            2.������ܸ��ģ���ô�ʹ���һ��vector<vector<bool>> �洢false/true������Ƿ񱻱�����
//��ע�������������ֲ��䣬ͬ�ȹ�ģ��С����
void floodFill(vector<vector<char>>& arr, int sr, int sc, int newchar)
{
    int rows = arr.size();
    int cols = arr[0].size();
    int charat = arr[sr][sc];

    queue<pair<int, int>> q; q.push({ sr,sc });
    arr[sr][sc] = newchar;

    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && arr[nr][nc] == charat)
            {
                arr[nr][nc] = newchar;
                q.push({ nr,nc });
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int ret = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == '1')
            {
                floodFill(grid, i, j, '0');
                ret++;
            }
        }
    }
    return ret;
}

//�㷨����ԭ�����㷨������޷��Ƕ���һ�����²���
void FloodFill(vector<vector<int>>& arr, int sr, int sc, int newnum, int& Size)
{
    int rows = arr.size();
    int cols = arr[0].size();
    int num = arr[sr][sc];
    int count = 1;

    queue<pair<int, int>> q;
    q.push({ sr,sc });
    arr[sr][sc] = newnum;

    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && arr[nr][nc] == num)
            {
                q.push({ nr,nc });
                count++;
                arr[nr][nc] = newnum;
            }
        }
    }
    if (count > Size) Size = count;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int Size = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
            {
                FloodFill(grid, i, j, 0, Size);
            }
        }
    }
    return Size;
}

//���︽��һ�²��ı�ԭ�����bool��ʶ����
bool judge[50][50] = { 0 };

void floodFillbool(vector<vector<int>>& arr, int sr, int sc, int& Size)
{
    int rows = arr.size();
    int cols = arr[0].size();
    int num = arr[sr][sc];
    int count = 1;

    queue<pair<int, int>> q;
    q.push({ sr,sc });
    judge[sr][sc] = true;

    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && arr[nr][nc] == num && !judge[nr][nc])
            {
                q.push({ nr,nc });
                count++;
                judge[nr][nc] = true;
            }
        }
    }
    if (count > Size) Size = count;
}

int MaxAreaOfIsland(vector<vector<int>>& grid) {
    int Size = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1 && !judge[i][j])
            {
                floodFillbool(grid, i, j, Size);
            }
        }
    }
    return Size;
}


//�㷨�ģ������򷴣�����
void floodFill(vector<vector<char>>& arr, int sr, int sc, char newchar)
{
    int rows = arr.size();
    int cols = arr[0].size();
    int charat = arr[sr][sc];

    queue<pair<int, int>> q;
    q.push({ sr,sc });
    arr[sr][sc] = newchar;

    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && arr[nr][nc] == charat)
            {
                q.push({ nr,nc });
                arr[nr][nc] = newchar;
            }
        }
    }
}

void solve(vector<vector<char>>& board) {
    //�����򷴣���Χ�������һ�����α���bfs��ɢ������ͨ��ͳͳ��Ϊһ���޹ص��ַ�
    //Ȼ���ٴ�ȫ���������м��Oֱ�Ӹ�ΪX���ɣ���Ϊһ���Ǳ���Χ�ģ��޹ص��ַ���ΪO����
    int rows = board.size();
    int cols = board[0].size();
    //����Χһ�ܵ�O��ʼ��ɢbfs����
    for (int i = 0; i < cols; i++)
    {
        if (board[0][i] == 'O') floodFill(board, 0, i, 'T');
        if (board[rows - 1][i] == 'O') floodFill(board, rows - 1, i, 'T');
    }
    for (int j = 1; j < rows - 1; j++)
    {
        if (board[j][0] == 'O') floodFill(board, j, 0, 'T');
        if (board[j][cols - 1] == 'O') floodFill(board, j, cols - 1, 'T');
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] == 'T') board[i][j] = 'O';
            else if (board[i][j] == 'O') board[i][j] = 'X';
        }
    }
}


//int main()
//{
//    testFloodFill();
//    return 0;
//}