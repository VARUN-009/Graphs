class Solution
{
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    void dfs(int row, int col, vector<vector<int>> &grid,
             vector<vector<int>> &visited, int n, int m)
    {
        visited[row][col] = 1;

        for (int i = 0; i < 4; i++)
        {
            int x = row + dx[i];
            int y = col + dy[i];

            // ab mujhe bss ye check karna hai ki ye point mere grid ke andar ho
            // and koi bhi agr 1 ho toh m usme hi chle jau
            if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] &&
                grid[x][y] == 1)
            {
                dfs(x, y, grid, visited, n, m);
            }
        }
    }

public:
    int numEnclaves(vector<vector<int>> &grid)
    { // code here
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                // Boundary point se hi iterate karna hai kyuki mujhe dekhna hai ki boundary 1 se m kitna andar tak kitne 1 tak jaa sakta hu kyuki kisi 1 ke region m agr 1 bhi point aisa hai jo boundary point hai then travel karke m bahar jaa sakta hu uss grid se. M bss chahta hu ki kuch points aise rahe jinke charo taraf bss 0 hi ho.
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                {
                    if (grid[i][j] == 1)
                    {
                        dfs(i, j, grid, visited, n, m);
                    }
                }
            }
        }

        /* can also do like this boundary m iterate karna bss it's like the
        question surrounded regions
        // Moving on the first col and last col
        for (int i = 0; i < n; i++)
        {
            if (grid[i][0] == 1 && !visited[i][0])
            {
                dfs(i, 0, grid, visited, n, m);
            }

            if (grid[i][m - 1] == 1 && !visited[i][m - 1])
            {
                dfs(i, m - 1, grid, visited, n, m);
            }
        }

        // Moving on the first row and last row
        for (int i = 0; i < m; i++)
        {
            if (grid[0][i] == 1 && !visited[0][i])
            {
                dfs(0, i, grid, visited, n, m);
            }

            if (grid[n - 1][i] == 1 && !visited[n - 1][i])
            {
                dfs(n - 1, i, grid, visited, n, m);
            }
        }
        */

        // vo points jo 1 hai and visited ni hai means vo safe hai from boundary points basically unse directly indirectly connected nhi hai toh vo hi mera answer hai. Just count them.    
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j] && grid[i][j] == 1)
                {
                    count++;
                }
            }
        }

        return count;
    }
};

/*
To solve this using DFS, jo jo boundary m hai unko pehle tum queue m daldo then iterate karo bss no need to take a size loop inside queue kyuki rotten oranges m har minute m sab hi infect kar rahe the isliye, usme tum minute ko as a pair m le sakte ho queue m. 

jo jo possible hai boundary m bss unko dalke then iterate karo traverse karo ji 
TC - O(n*m) + O(n*m) + O(n*m*4) + O(n*m)

SC - O(n*m) + O(n*m) recursion


*/
