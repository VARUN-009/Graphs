// GFG BFS Question

// } Driver Code Ends
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(vector<vector<int>> &adj)
    {
        // Code here
        vector<int> ans;
        queue<int> q;
        int n = adj.size();
        vector<bool> vis(n, 0);
        q.push(0);
        vis[0] = 1;
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            ans.push_back(node);

            // iterating in all elements of 0th index basically 2 3 1
            for (auto child : adj[node])
            {
                if (!vis[child])
                {
                    vis[child] = 1;
                    q.push(child);
                }
            }
        }

        return ans;
    }
};

//{ Driver Code Starts.

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E;
        cin >> V >> E;

        // Now using vector of vectors instead of array of vectors
        vector<vector<int>> adj(V);

        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u); // For undirected graph, add both u->v and v->u
        }

        Solution obj;
        vector<int> ans = obj.bfsOfGraph(adj);
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}