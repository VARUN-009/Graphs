class Solution
{
private:
    // up right down left
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0, -1};

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                                  int color)
    {
        int n = image.size();
        int m = image[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        visited[sr][sc] = 1;
        int initial_color = image[sr][sc];

        while (!q.empty())
        {
            auto row = q.front().first;
            auto col = q.front().second;
            q.pop();
            image[row][col] = color;

            for (int i = 0; i < 4; i++)
            {
                int x = row + dx[i];
                int y = col + dy[i];
                if (x >= 0 && x < n && y >= 0 && y < m &&
                    image[x][y] == initial_color && !visited[x][y])
                {
                    visited[x][y] = 1;
                    q.push({x, y});
                }
            }
        }

        return image;
    }
};
// Ek point se uske baaki adjacent points m jana hai toh BFS/DFS toh coordinates
// lelo and simple BFS, uske childs hoge adjacent wale cells.

// DFS
class Solution
{
private:
    // up right down left
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0, -1};

    void dfs(int row, int col, vector<vector<int>> &image, int color,
             int initial_color, vector<vector<int>> &visited, int n, int m)
    {
        visited[row][col] = 1;
        image[row][col] = color;

        for (int i = 0; i < 4; i++)
        {
            int x = row + dx[i];
            int y = col + dy[i];

            if (x >= 0 && x < n && y >= 0 && y < m &&
                image[x][y] == initial_color && !visited[x][y])
            {
                dfs(x, y, image, color, initial_color, visited, n, m);
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                                  int color)
    {
        int n = image.size();
        int m = image[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        int initial_color = image[sr][sc];
        dfs(sr, sc, image, color, initial_color, visited, n, m);
        return image;
    }
};
// Ek point se uske baaki adjacent points m jana hai toh BFS/DFS toh coordinates
// lelo and simple BFS, uske childs hoge adjacent wale cells.
// It's a good practice ki humesha naya data bnaye from the data given in question so that data ganda na ho jo given hai -- isko bina visited liye bhi kar sakte hai bss usme ek copy bnani padegi pehle data ki.

// TC - maanlo poori hi matrix ko traverse karna hai toh total X nodes and for every node, you travel in 4 directions so X*4 basically n*m*4 ~ O(n*m);
// SC - O(n*m) + O(n*m) for stack recursion + O(n) ~ O(n*m)