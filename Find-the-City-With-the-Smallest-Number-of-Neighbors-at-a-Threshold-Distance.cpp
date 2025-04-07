class Solution
{
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {
        int e = edges.size();
        vector<vector<int>> adj(n, vector<int>(n, 1e9));
        for (int i = 0; i < e; i++)
        {
            int node = edges[i][0];
            int child = edges[i][1];
            int weight = edges[i][2];

            adj[node][child] = weight;
            adj[child][node] = weight;
        }

        // via means m a to b via jaunga toh kya pta chotta distance mil jaye
        for (int via = 0; via < n; via++)
        {

            // row wise chlta hu m ab
            for (int row = 0; row < n; row++)
            {

                // col wise chlta hu m ab
                for (int col = 0; col < n; col++)
                {
                    // ye if ke bina bhi accept ho sakta hai par ye faltu computations se bachane ke liye hai ki agr rasta hai hi ni m ni jaa sakta toh kyu hi jana uss raste se answer tumahra 1e9 hi aayega toh that's why
                    if (adj[row][via] != 1e9 && adj[via][col] != 1e9)
                    {
                        adj[row][col] = min(adj[row][col], adj[row][via] + adj[via][col]);
                    }
                }
            }
        }

        // abhi tak max kitni cities aayi and unka city no. konsi city se jaa sakta hu unko store karne ke liye  
        int check = 1e9;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int count = 0;
            for (int j = 0; j < n; j++)
            {
                // not counting the edge from 0-0, but it doesn't affect you may or may not count it.
                if (i != j && adj[i][j] <= distanceThreshold)
                    count++;
            }

            if (count <= check)
            {
                check = count;
                ans = i;
            }
        }

        return ans;
    }
};
/*
- Mujhe har node se har node tak ka shortest distance find karna tha and then chceck karna tha ki ek node se sab nodes ke liye jo distance hai kya vo mera threshold se km hai, jitni nodes ke liye threshold se km hai unko lelo count karlo jaise 0 se m 1 2 jaa sakta hu less than threshold setoh 2 ho gya then 3 se bhi 1 2 toh count 2 but 3 > 0 so ans=3
- ab m isme dijkstras bhi laga sakta tha par usme mujhe har node ke liye lagana padta and end m check karna padta ki kitni nodes tak km m jaa sakta hu
- Floyd warshall use kari yahan pe toh multi source shortest algorithm hai ye.
TC - O(E) + O(V^3) + O(V^2)
SC - O(V^2)

*/