class Solution
{
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    void dfs(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &visited, int inrow, int incol, vector<pair<int, int>> &ans, int n, int m)
    {
        visited[row][col] = 1;

        // jo initial row and col hai usme se minus kardo toh agr same hue toh same hi ans aayega minus karke hum bss un points ko vector m daal rahe hai and then set m same ki entry ni hogi dobara set hai and minus karege base se toh agr dusri jagah same hai bhle hi coordinates alg hai toh subtract karke same hi coordinates aayege 
        ans.push_back({row - inrow, col - incol});

        for (int i = 0; i < 4; i++)
        {
            int x = row + dx[i];
            int y = col + dy[i];

            if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && grid[x][y] == 1)
            {
                // again inrow and incol kyuki base column and base row toh vahi hai hum wahin se hi baaki jagah jaa rahe hai isliye 
                dfs(x, y, grid, visited, inrow, incol, ans, n, m);
            }
        }
    }

public:
    int countDistinctIslands(vector<vector<int>> &grid)
    {
        // code here
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> st;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                // agr 1 hai tab hi dekhna hai meine bss unvisited ho bss vo
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    vector<pair<int, int>> ans;
                    dfs(i, j, grid, visited, i, j, ans, n, m);

                    // set ke andar mere vectors hai and har ek vector ke andar mere pairs stored hai {i,j}
                    st.insert(ans);
                }
            }
        }

        return st.size();
    }
};
/*
jab bhi unique cheej aaye toh mann m set jaroor aana chahiye kyuki set ke andar unique hi cheeje store hoti hai vo bhi sorted ascending order m hi.

for ordered set, TC for insertion is O(1) and for ordered it is O(log n) 
The unordered_set container in C++ requires that the elements it stores must be hashable. This means there must be a valid hash function defined for the type of elements stored in the set.

By default, C++ provides hash functions for basic types like int, string, etc., but it does not provide a hash function for complex types like vector<pair<int, int>>.

2. Why vector<pair<int, int>> Cannot Be Directly Used
A vector<pair<int, int>> is a complex type, and the C++ standard library does not provide a default hash function for it.

To use such a type in an unordered_set, you would need to define a custom hash function for vector<pair<int, int>>.

TC - O(n*m) + O(n*m*4) + O(log(n*m))  set pushing ordered + O(n*m) recursion
Sc - O(n*m) + O(n*m) 

*/