class Solution
{
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    void dfs(int row, int col, vector<vector<char>> &board,
             vector<vector<int>> &visited, int n, int m)
    {
        visited[row][col] = 1;
        // int cnt = 1

        for (int i = 0; i < 4; i++)
        {
            int x = row + dx[i];
            int y = col + dy[i];

            // ab mujhe bss ye check karna hai ki ye point mere grid ke andar ho
            // and koi bhi agr 1 ho toh m usme hi chle jau
            if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] &&
                board[x][y] == 'O')
            {
                dfs(x, y, board, visited, n, m);
            }
        }
    }

public:
    void solve(vector<vector<char>> &board)
    {
        // code here
        int n = board.size();
        int m = board[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));

        // Boundary m hi move karna hai mujhe bss aur kahin nhi, kyuki boundary
        // se points connect ho rahe hai toh vo surround ni hoge baaki andar ke
        // points jo har taraf se surrounded hai X se vo toh pakka surrounded hi
        // hai toh unko m X se replace kar sakta hu. Boundary ke Os se dikkat
        // hai andar ke toh safe hi rahege vo ek dum
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                {
                    if (!visited[i][j] && board[i][j] == 'O')
                    {
                        dfs(i, j, board, visited, n, m);
                    }
                }
            }
        }

        // This is like a brute force method to move in boundary.
        /*
        // Moving on the first col and last col
        for (int i = 0; i < n; i++)
        {
            if (board[i][0] == 'O' && !visited[i][0])
            {
                dfs(i, 0, board, visited, n, m);
            }

            if (board[i][m - 1] == 'O' && !visited[i][m - 1])
            {
                dfs(i, m - 1, board, visited, n, m);
            }
        }

        // Moving on the first row and last row
        for (int i = 0; i < m; i++)
        {
            if (board[0][i] == 'O' && !visited[0][i])
            {
                dfs(0, i, board, visited, n, m);
            }

            if (board[n - 1][i] == 'O' && !visited[n - 1][i])
            {
                dfs(n - 1, i, board, visited, n, m);
            }
        }
        */

        // andar ka O jo visited ni hai vo mera convert ho sakta hai X m then
        // usko X m convert kardo bss baaki O jo bachega vo convert ni ho sakta
        // hai and bache hue X hai
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j] && board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

/*
TC - O(n*m) + O(n*m*4)

SC - O(n*m) + O(n*m) recursion 


*/
