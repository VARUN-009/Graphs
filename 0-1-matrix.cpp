class Solution
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> result(n, vector<int>(m, 0)); // result matrix
        int visited[n][m];                                // initially all not visited
        memset(visited, -1, sizeof(visited));
        // always use memset to initialise a 2d array
        // but by memset you can only initialise to -1
        // only as it works on bits.
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 0)
                {
                    q.push({i, j});
                    visited[i][j] = 1; // visited
                    result[i][j] = 0;  // mark their distance as 0 as their
                                       // distance from 0 will be 0
                }
            }
        }
        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                // now let's iterate in all 4 directions
                for (int i = 0; i < 4; i++)
                {
                    int newrow = row + drow[i];
                    int newcol = col + dcol[i];

                    if (newrow >= 0 && newrow < n && newcol >= 0 &&
                        newcol < m && visited[newrow][newcol] != 1 &&
                        mat[newrow][newcol] == 1)
                    {
                        visited[newrow][newcol] = 1;
                        result[newrow][newcol] = result[row][col] + 1;
                        q.push({newrow, newcol});
                    }
                }
            }
        }

        return result;
    }
};
/*

we will start from bfs from all 0s. we are inserting all 0s in the queue, on
iterating when we encounter a 1, we will increase it's distance to +1. Don't
go 1 to 0 i.e. don't do BFS from 1 as we have to see the distance from 0 not
1, just like rotten oranges m, humne pehle rotten oranges push kare the then
uss se distance dekha tha ki fresh kitni durri m hai whenever we want
shortest path, shortest time use BFS, dfs will take time.

jab kabhi aisa ho matrix type ki pehle hi possible cheeje queue m dalni
hai toh phir queue m then ek size wala loop bhi lagega jiss se ki level
by level hi jau m

Marzi hai 0 ka 1 se distance nikal le ya 1 ka 0 se nikal le dono hi case m
minimum aayega by BFS like in rotting oranges ache ka sade se nikalo ya sade
ka ache se nikalo -- jiss se dekhna hai jiss se karna hai usko queue m dalo

0 ka 0 se 0 hi rahega and jahan 1 aaya koi means 1 ka 0 se ho jayega current
parent tak aane ka distance + 1 kyuki jahan se aaya hai wahan se + 1

saari 0s se jitna meine karna tha karliya ab eg - test case 2 m dekhunga ki 1
se kaise jaa sakta hu m 1 ka distance + 1

Graphs m minimum and shortest is always find by BFS kyuki hume level by level
saari direction m jana hai na ki DFS ki tarah 1 hi direction m end tak

TC - O(n*m) + O(n*m * 4) traversing all cells
SC - O(n*m) + O(n*m) + O(n*m)
*/