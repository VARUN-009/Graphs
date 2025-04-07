#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{

public:
    // Function to return list containing vertices in Topological order.
    vector<int> topologicalSort(vector<vector<int>> &adj)
    {
        // Your code here
        int n = adj.size();
        vector<int> indegree(n, 0);

        // jo child hai usme iterate karo and then usko ++ karte raho means ki iss bache m mein parent se
        // aa sakta hu alg alg ho sakte hai parents toh jitni baar aaye child ++
        for (int i = 0; i < n; i++)
        {
            for (auto child : adj[i])
            {
                indegree[child]++;
            }
        }

        vector<int> ans;

        queue<int> q;

        // jaroori ni ki har baar components hi ho uske bina bhi ho sakta hai like in this 1 hi component hoga bss graph m and starting m sabki indegree meine mark karli hai visited wala chakkar ni hai isme, isme toh hum indegree dekh rahe hai bss 

        for (int node = 0; node < adj.size(); node++)
        {
            if (indegree[node] == 0)
            {
                q.push(node);
            }
        }

        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            ans.push_back(node);

            for (auto child : adj[node])
            {
                indegree[child]--;
                if (indegree[child] == 0)
                {
                    q.push(child);
                }
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