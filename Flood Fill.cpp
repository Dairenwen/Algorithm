#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//代码说明
// 
//递归 DFS 实现：
//通过递归调用处理四个方向的相邻点。
//检查边界条件和颜色匹配，避免越界或重复处理。
//时间复杂度：O(N)，其中 N 是需要填充的像素数。
//空间复杂度：最坏情况下 O(N)（递归栈深度）。
// 
//方法1：递归实现（DFS）
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
        // 检查边界条件和颜色是否匹配
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() ||
            image[r][c] != targetColor) {
            return;
        }

        // 替换颜色并递归处理相邻点
        image[r][c] = newColor;
        dfs(image, r + 1, c, targetColor, newColor); // 下
        dfs(image, r - 1, c, targetColor, newColor); // 上
        dfs(image, r, c + 1, targetColor, newColor); // 右
        dfs(image, r, c - 1, targetColor, newColor); // 左
    }
};

//迭代 BFS 实现：
//使用队列存储待处理的像素点。
//通过循环处理队列中的每个点，并将相邻符合条件的点加入队列。
//时间复杂度：O(N)。
//空间复杂度：最坏情况下 O(N)（队列存储所有待处理点）。
//
//方法2：迭代实现（BFS）
class SolutionBFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int rows = image.size();
        int cols = image[0].size();
        int targetColor = image[sr][sc];

        if (targetColor == newColor) {
            return image; // 避免重复处理
        }

        queue<pair<int, int>> q;
        q.push({ sr, sc });
        image[sr][sc] = newColor; // 标记起点

        // 定义四个方向：下、上、右、左
        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            // 处理四个方向的相邻点
            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                // 检查是否越界且颜色是否匹配
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

//测试示例：
//输入图像为 3x3 矩阵，起点为(1, 1)，新颜色为 2。
//分别使用 DFS 和 BFS 方法填充，并输出结果。
//两种方法的填充结果相同，但 DFS 可能在处理大规模数据时导致栈溢出，而 BFS 更适合内存管理。根据实际需求选择合适的实现方式。
//测试代码
void testFloodFill() 
{
    // 示例输入图像
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    int sr = 1, sc = 1; // 起点坐标
    int newColor = 2;   // 新颜色

    // 使用 DFS 方法
    SolutionDFS dfsSolver;
    vector<vector<int>> resultDFS = dfsSolver.floodFill(image, sr, sc, newColor);

    cout << "DFS 填充结果:" << endl;
    for (const auto& row : resultDFS) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // 使用 BFS 方法（注意：需要重新初始化 image，因为 DFS 已经修改了它）
    vector<vector<int>> imageBFS = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    SolutionBFS bfsSolver;
    vector<vector<int>> resultBFS = bfsSolver.floodFill(imageBFS, sr, sc, newColor);

    cout << "\nBFS 填充结果:" << endl;
    for (const auto& row : resultBFS) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

}


//算法一：就是上面用来学系floodfill的例子，自己写了一遍（BFS）
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newcolor) {
    //早有耳闻的floodfill，让我来尝试一下吧！
    int rows = image.size();
    int cols = image[0].size();
    int color = image[sr][sc];//要保存一下原来的颜色，在后面用于判断
    if (image[sr][sc] == newcolor) return image;
    else image[sr][sc] = newcolor;
    //用队列来模拟BFS
    queue<pair<int, int>> q; q.push({ sr,sc });//标记起点
    //用数组来模拟四个方向
    vector<pair<int, int>> v = { {0,1},{0,-1},{-1,0},{1,0} };
    while (q.size())
    {
        pair<int, int> front = q.front(); q.pop();
        for (const auto& e : v)
        {
            int nr = front.first + e.first, nc = front.second + e.second;
            //朝着四个方向散开，注意来判断越界情况！
            if (0 <= nr && nr < rows && 0 <= nc && nc < cols && image[nr][nc] == color)
            {
                image[nr][nc] = newcolor;
                q.push({ nr,nc });
            }
        }
    }
    return image;
}

//算法二：如果没有给起始点呢？从哪里开始发散，当然是遍历一遍二维数组，以每一个为起点开始遍历
//那么如何来区分已经遍历过的地方呢？如果不加以区分，就会写成死循环
//有两种做法：1.面试时能否更改数组？如果可以那么直接标记为0就可以了
//            2.如果不能更改，那么就创建一个vector<vector<bool>> 存储false/true来标记是否被遍历过
//（注意行数列数保持不变，同等规模大小！）
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

//算法三：原理与算法二大差不差，无非是多了一个更新步骤
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

//这里附加一下不改变原数组的bool标识方法
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


//算法四：正难则反！！！
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
    //正难则反，先围绕最外层一周依次遍历bfs发散，将联通的统统改为一个无关的字符
    //然后再次全部遍历，中间的O直接改为X即可，因为一定是被包围的，无关的字符改为O即可
    int rows = board.size();
    int cols = board[0].size();
    //将周围一周的O开始发散bfs处理
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