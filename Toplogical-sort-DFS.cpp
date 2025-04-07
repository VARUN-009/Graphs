//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
private:
    void dfsHelper(int src, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &ans)
    {
        vis[src] = 1;

        for (auto child : adj[src])
        {
            if (!vis[child])
            {
                dfsHelper(child, adj, vis, ans);
            }
        }

        // jab koi na bache back aate samay ye add karni hai vector m jiss se ki jo node hume ek dum end m chahiye toh ek dum end m hi rahe 
        ans.insert(ans.begin(), src);
    }

public:
    // Function to return list containing vertices in Topological order.
    vector<int> topologicalSort(vector<vector<int>> &adj)
    {
        // Your code here
        int n = adj.size();
        vector<bool> vis(n, 0);
        vector<int> ans;

        for (int node = 0; node < n; node++)
        {
            if (!vis[node])
            {
                dfsHelper(node, adj, vis, ans);
            }
        }

        return ans;
    }
};

//{ Driver Code Starts.

/*  Function to check if elements returned by user
 *   contains the elements in topological sorted form
 *   V: number of vertices
 *   *res: array containing elements in topological sorted form
 *   adj[]: graph input
 */
int check(int V, vector<int> &res, vector<vector<int>> adj)
{

    if (V != res.size())
        return 0;

    vector<int> map(V, -1);
    for (int i = 0; i < V; i++)
    {
        map[res[i]] = i;
    }
    for (int i = 0; i < V; i++)
    {
        for (int v : adj[i])
        {
            if (map[i] > map[v])
                return 0;
        }
    }
    return 1;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, E;
        cin >> N >> E;
        int u, v;

        vector<vector<int>> adj(N);

        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        vector<int> res = obj.topologicalSort(adj);

        cout << check(N, res, adj) << endl;

        cout << "~"
             << "\n";
    }

    return 0;
}