class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        if (grid.size() == 1 && grid[0][0] == 0)
            return 1;
        int n = grid.size();
        int m = grid[0].size();
        if (grid[0][0] == 1)
            return -1;

        // {distance, x, y}
        // priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
        //     minheap;
        // No need to take a priority_queue here as sabka distance unit wise badh rha hai toh +1 har baar 8 directions m toh distance same hi aayega toh fayeda ni so we removed tc logn
        queue<vector<int>> q;
        q.push({0, 0, 0});
        vector<vector<int>> distance(n, vector<int>(m, 1e9));
        // Initially sabka distance 1e9 and startnode ka 0
        distance[0][0] = 0;

        while (!q.empty())
        {
            auto vec = q.front();
            auto dist = vec[0];
            auto row = vec[1];
            auto col = vec[2];
            q.pop();

            // It can move in 9 directions so 9 directions. Bss jo naya point
            // aaya hai usks distance mera jyada hai curr dist + 1 se toh bhai
            // km distance mil gya mark karo and then isko q m daaldo and
            // also do check ki ye jo naya point aaya hai ye kahin n-1, m-1
            // point toh nhi if yes then iska distance + 1 as starting humne 0
            // se kari thi that's why

            // in this one point 0 0 will be added which means nothing so effectively it will run for 8 times.
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int dx = row + i;
                    int dy = col + j;

                    // Isme eg - test case 2 - faltu point jo aaya (0,2) usme
                    // jab aaoge then dekhoge uske aaspass ke sab visited hoge
                    // toh uska fayeda ni basically sabka distance mera km hi
                    // hoga toh pop, so iss karke km wale points hi use hoge.
                    // dist + 1 as sab 1 distance ki di toh doori m hai toh curr
                    // dist + 1.
                    if (dx >= 0 && dx < n && dy >= 0 && dy < m &&
                        grid[dx][dy] == 0 && dist + 1 < distance[dx][dy])
                    {
                        distance[dx][dy] = dist + 1;
                        if (dx == n - 1 && dy == m - 1)
                        {
                            return distance[dx][dy] + 1;
                        }
                        q.push({distance[dx][dy], dx, dy});
                    }
                }
            }
        }

        // answer milna hoga toh andar tak hi mil jayega nhi mila toh bhai -1.
        return -1;
    }
};

/*
TC - O(n*m*8)
SC - O(n*m) + O(n*m)

*/