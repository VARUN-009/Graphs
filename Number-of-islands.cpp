class Solution
{
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    // in case, in question diagonally was also given
    // int dx[8] = {-1, -1 , 0, 1, 1, 1 , 0, -1};
    // int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    // can also a loop from -1 to 1 and inside -1 to 1 and then add i and j row
    // loop and then col loop for(row -1 to 1 then inside col -1 to 1)

    void dfs(int row, int col, vector<vector<int>> &visited,
             vector<vector<int>> &island, int n, int m)
    {
        visited[row][col] = 1;

        for (int i = 0; i < 4; i++)
        {
            int x = row + dx[i];
            int y = col + dy[i];

            if (x >= 0 && x < n && y >= 0 && y < m && island[x][y] == 1 &&
                !visited[x][y])
            {
                dfs(x, y, visited, island, n, m);
            }
        }
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));
        vector<vector<int>> island(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    island[i][j] = 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (island[i][j] == 1 && !visited[i][j])
                {
                    dfs(i, j, visited, island, n, m);
                    ans++;
                }
            }
        }

        return ans;
    }
};
// It's almost like finding components in the graph. It can also be solved using
// BFS exactly the same way. Bss recursion ki jagah queue leni hai else sab same

// agr sab hi 1 ho gaye toh bss 1 hi baar hoga DFS , n*m for checking ki 1 hai
// hi ni traverse karne ke liye and then jitni bhi possible node hai uske 4
// direction m jana. hai TC - O(n*m) + O(n*m * 4) ~ O(n*m)

// SC - O(n*m) + O(n*m)
// + O(n*m) recursion stack ~ O(n*m) because in worst case we have to traverse
// every node in the matrix so n*m