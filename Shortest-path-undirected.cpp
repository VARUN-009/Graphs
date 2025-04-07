//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// Back-end complete function Template for C++

// } Driver Code Ends
class Solution
{
public:
    // Function to find the shortest path from source to all other nodes
    vector<int> shortestPath(vector<vector<int>> &adj, int src)
    {
        // code here
        int n = adj.size();
        vector<int> distance(n, 1e9);
        distance[src] = 0;
        queue<int> q;
        q.push(src);

        // Visited bhi lene ki need ni hai kyuki tum linear order m traverse kar rahe ho level by level and starting se hi shortest distance hi aajyega node m automatically kyuki first to last move kar rahe hai linear order m src pta hai na toh visited node ka phirse distance calculate karoge toh jyada hi aayega pehle se - jis node ka distance jyada aagya bss usko add kardo queue m means vo visited ni thi pehle se and then usko queue m add karo.
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();

            for (auto &child : adj[node])
            {
                if (distance[child] > distance[node] + 1)
                {
                    distance[child] = distance[node] + 1;
                    q.push(child);
                }
            }
        }

        for (auto &ele : distance)
        {
            if (ele == 1e9)
            {
                ele = -1;
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

        int src;
        cin >> src;

        Solution obj;

        vector<int> res = obj.shortestPath(adj, src);

        for (auto x : res)
        {
            cout << x << " ";
        }
        cout << "\n";
        cout << "~\n";
    }
}