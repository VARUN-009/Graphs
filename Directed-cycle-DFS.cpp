#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
private:
    bool detect(int src, vector<vector<int>> adj, vector<bool> &vis, vector<bool> &pathvis)
    {
        vis[src] = 1;
        pathvis[src] = 1;

        for (auto child : adj[src])
        {
            if (!vis[child])
            {
                if (detect(child, adj, vis, pathvis))
                {
                    return true;
                };
            }
            else if (pathvis[child])
            {
                return true;
            }
        }

        // back jate time bss uss path ko pehle jaisa karte jao kyuki ab tum kisi dusre path m chloge main cheej isme ye hi hai node phirse visit honi chahiye same hi path ki 
        pathvis[src] = 0;
        return false;
    }

public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<vector<int>> adj)
    {
        // code here
        vector<bool> vis(V, 0);
        vector<bool> pathvis(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (detect(i, adj, vis, pathvis))
                    return true;
            }
        }

        return false;
    }
};

//{ Driver Code Starts.

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int V, E;
        cin >> V >> E;

        vector<vector<int>> adj(V);

        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        cout << obj.isCyclic(V, adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}