class Solution
{
public:
    void dfs(int src, vector<vector<int>> &adj, vector<int> &visited)
    {
        visited[src] = 1;
        for (auto child : adj[src])
        {
            if (!visited[child])
            {
                dfs(child, adj, visited);
            }
        }
    }
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isConnected[i][j] == 1 and i != j)
                {
                    adj[i].push_back(j);
                }
            }
        }
        vector<int> visited(n, 0);
        int components = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(i, adj, visited);
                components++;
            }
        }

        return components;
    }
};
/*
isme bss adj bnake no. of components hi nikalne the ki total kitne components
hai. We can either use BFS or DFS dono m hi same hoga bss BFS m queue hogi.

TC - O(n*n) + O(V + V+2E)  2E because har edge ko m 2 baar visit karunga aisa ni
hai ki ek edge ek baar dekha and baad m dekha hi ni, SC - O(V + E) + O(V) + O(V)
recursion ~ O(V) near to this

*/
