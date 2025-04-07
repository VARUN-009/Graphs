//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
private:
    // base case issi ke andar hai ki jab saare visit ho h gaye end ho jayega and usko mark karo vis and then uske bache m jao depth m jaa rahe hai iske andar hum
    void dfshelper(int node, vector<vector<int>> &adj, vector<bool> &vis)
    {
        vis[node] = 1;
        ans.push_back(node);

        for (auto child : adj[node])
        {
            if (!vis[child])
            {
                dfshelper(child, adj, vis);
            }
        }
    }

public:
    vector<int> ans;

    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(vector<vector<int>> &adj)
    {
        // Code here
        int n = adj.size();
        vector<bool> vis(n, 0);

        // bss agr vo visited nhi hai toh jao visit karo iss se kya hoga agr components hai na graph m toh vo bhi manage ho jayege ye toh karna hi hai same as BFS
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                dfshelper(i, adj, vis);
            }
        }

        return ans;
    }

    //{ Driver Code Starts.
};

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E;
        cin >> V >> E;

        vector<vector<int>> adj(V); // Use vector of vectors instead of array of vectors.

        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        Solution obj;
        vector<int> ans = obj.dfsOfGraph(adj);
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
        cout << "~" << endl;
    }
    return 0;
}

// } Driver Code Ends
// can also send ans as by reference from below function and good practice to make new functions inside private