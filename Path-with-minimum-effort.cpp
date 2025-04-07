class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> efforts(n, vector<int>(m, 1e9));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
            minheap;
        minheap.push({0, 0, 0});
        efforts[0][0] = 0;

        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};

        while (!minheap.empty())
        {
            auto diff = minheap.top()[0];
            auto row = minheap.top()[1];
            auto col = minheap.top()[2];
            minheap.pop();

            if (row == n - 1 && col == m - 1)
            {
                return diff;
            }

            for (int i = 0; i < 4; i++)
            {
                int x = row + dx[i];
                int y = col + dy[i];

                if (x >= 0 && x < n && y >= 0 && y < m)
                {
                    int maxDiff =
                        max(diff, abs(heights[row][col] - heights[x][y]));
                    if (efforts[x][y] > maxDiff)
                    {
                        efforts[x][y] = maxDiff;
                        minheap.push({maxDiff, x, y});
                    }
                }
            }
        }

        return -1;
    }
};
/*
-Hume difference maximum lena hai toh ek cell ka dusre se abs karo and check
karo ki abhi ka diff jyada hai ya pehle ka max diff hi lena hai and then jo bhi
max diff hai minimum possible max diff lena padega and this will be done by
dijkstras.
-jaisa hi mera minheap ke top m n-1,m-1 aajayega then uska diff hi
mera answer hoga kyuki m saare possible paths traverse karke aagya hu last cell
m and har jagah m minimum of maxdiff hi lete aarha hu toh minimum diff hi hoga
and also jaise isme 2 aaya and minheap ke top m 2 toh aage mera diff 2 se km bhi
aaya par maxdiff lunga toh 2 hi ho jayega na and diff jyada bhi aagya toh
efforts[n-1][m-1] m mera minimum of max diff hi stored hai so ultimately 2.

TC - O(ElogV)
SC - O(n*m)

*/