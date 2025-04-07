//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
private:
    bool detect(int src, vector<vector<int>> &adj, vector<bool> &vis)
    {
        vis[src] = 1;

        // {node, parent}
        queue<pair<int, int>> q;
        q.push({src, -1});
        while (!q.empty())
        {
            auto node = q.front().first;
            auto parent = q.front().second;
            q.pop();

            for (auto child : adj[node])
            {
                if (!vis[child])
                {
                    vis[child] = 1;
                    q.push({child, node});
                }
                // means it is already visited so agr ye pehle se visited hai then pakka
                // ye kisi aur ka bhi bacha hai means ek hi node kisi aur ka bacha bhi
                // ho sakti hai -- abhi wali m mein parent se aaya hu
                else if (parent != child)
                {
                    return true;
                }
            }
        }

        return false;
    }

public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(vector<vector<int>> &adj)
    {
        // Code here
        int n = adj.size();

        vector<bool> vis(n, 0);

        // kai saare components ho sakte hai n toh iss karke har component m traverse karo
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
            {
                bool ans = detect(i, adj, vis);
                if (ans)
                    return true;
            }
        }

        return false;
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
        vector<vector<int>> adj(V);
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends

// Another way is to mark visited after taking out of queue and if already visited then cycle, no need to mark visited inside the for loop of child 
// Another way can be a node can only be visited by it's parent so if not visited count++ and agr count mera 2 ho gya ya uss se jyda toh pakka ek aisi node hai jo meri pehle se visited hai toh pakka cycle 