class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int n = grid.size();    // rows of the grid
        int m = grid[0].size(); // cols of the grid

        // let's make a visited matrix to store which cells you have visited,
        // sometimes taking an array instead of a vecbtor is good and simple
        // because of syntax
        int visited[n][m];

        // first we will put all the rotten oranges cells because at t=0, they
        // will be doing their work of rotting other oranges queue ke andar jo
        // jo hoga vo visited hi hoga, kyuki at t=0, vo sab rotten karna start
        // kardege

        // represents {row, col}
        queue<pair<int, int>> q;
        int freshoranges = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 2)
                { // rotten
                    q.push({i, j});
                    visited[i][j] = 2; // visited
                }
                else
                {
                    visited[i][j] = 1; // not visited
                }

                if (grid[i][j] == 1)
                {
                    freshoranges++;
                }
            }
        }
        // if there are no freshoranges, then no time to convert all fresh to
        // rotten
        if (freshoranges == 0)
            return 0;

        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, 1, 0, -1};
        int minutes = -1; // initially t=-1 because after taking a rotten
                          // orange, my time will start

        while (!q.empty())
        {
            int currsize = q.size();
            minutes++; // at t=minues, it will start doing it work and minutes
                       // neeche ni kyuki uss minute m jitne bhi infected
                       // oranges hai sab hi infect karege ek saath that's why
            while (currsize--)
            {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    // you can go here - 4 direction up righ down leftt
                    int newrow = row + drow[i];
                    int newcol = col + dcol[i];
                    // should not be outside the matrix and should not be a
                    // visited cell and also it should be a freshoranges orange,
                    // if empty cell, don't go
                    if (newrow >= 0 && newrow < n && newcol >= 0 &&
                        newcol < m && visited[newrow][newcol] == 1 &&
                        grid[newrow][newcol] == 1)
                    {
                        visited[newrow][newcol] = 2; // visited marked
                        q.push({newrow, newcol});
                        freshoranges--; // it's a freshoranges orange so
                                        // decrease the count of freshoranges,
                                        // if at last you have visited all the
                                        // freshoranges oranges then good else
                                        // -1
                    }
                }
            }
        }

        if (freshoranges != 0)
            return -1;
        return minutes;
    }
};

// Isme DFS ni chlega kyuki vo level by level ni jayega vo toh ek jagagh gya
// then uss hi taraf jate rahega hume chahiye ki level wise chle hum jiss se ki
// shortest path mile and for shortest path and shortest time BFS is used not
// DFS.

// TC - O(n*m) + O(n*m * 4) ~ O(n*m);
// SC - O(n*m) + O(n*m) ~ O(n*m)