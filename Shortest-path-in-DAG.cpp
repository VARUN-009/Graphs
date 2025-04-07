//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
class Solution
{
private:
    void dfsHelper(int src, vector<vector<pair<int, int>>> &adj, vector<bool> &vis, stack<int> &ans)
    {
        vis[src] = 1;

        for (auto child : adj[src])
        {
            auto node = child.first;
            if (!vis[node])
            {
                dfsHelper(node, adj, vis, ans);
            }
        }

        // jab koi na bache back aate samay ye add karni hai vector m jiss se ki jo node hume ek dum end m chahiye toh ek dum end m hi rahe
        ans.push(src);
    }

    stack<int> topologicalSort(vector<vector<pair<int, int>>> &adj)
    {
        // Your code here
        int n = adj.size();
        vector<bool> vis(n, 0);
        stack<int> ans;

        for (int node = 0; node < n; node++)
        {
            if (!vis[node])
            {
                dfsHelper(node, adj, vis, ans);
            }
        }

        return ans;
    }

public:
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges)
    {
        vector<vector<pair<int, int>>> adj(V);

        for (int i = 0; i < E; i++)
        {
            auto src = edges[i][0];
            auto neighbour = edges[i][1];
            auto weight = edges[i][2];
            adj[src].push_back({neighbour, weight});
        }
        // code here
        stack<int> stk = topologicalSort(adj);
        vector<int> distance(V, 1e9);
        distance[0] = 0;

        while (!stk.empty())
        {
            auto node = stk.top();
            stk.pop();

            for (auto child : adj[node])
            {
                auto adjacent = child.first;
                auto wt = child.second;

                // When we add a value to INT_MAX it becomes negative so in some cases, always check first with a if block whether we want to modify or not.
                if (distance[adjacent] > distance[node] + wt)
                {
                    distance[adjacent] = distance[node] + wt;
                }
            }
        }

        // Always make sure to add & in for auto loop when you want to change it modify the elements. Basically always use for auto loop with a &.
        for (int i = 0; i < V; i++)
        {
            if (distance[i] == 1e9)
            {
                distance[i] = -1;
            }
        }

        return distance;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        for (int i = 0; i < m; ++i)
        {
            vector<int> temp;
            for (int j = 0; j < 3; ++j)
            {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
        }
        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        for (auto x : res)
        {
            cout << x << " ";
        }
        cout << "\n";

        cout << "~"
             << "\n";
    }
}

// Iske andar hume src node ni pta hai ki shuruwaat kahan se kare matlab starting node konsi hai linear ordering m toh vo pta karne ki liye topological sort kardiya pehle jiss se ki minimum number of steps se hi pta chl jaye source node se sabka distance. 