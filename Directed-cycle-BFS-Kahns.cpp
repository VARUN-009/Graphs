#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<vector<int>> adj)
    {
        // Your code here
        vector<int> indegree(V, 0);

        // jo child hai usme iterate karo and then usko ++ karte raho means ki iss bache m mein parent se
        // aa sakta hu alg alg ho sakte hai parents toh jitni baar aaye child ++
        for (int i = 0; i < V; i++)
        {
            for (auto child : adj[i])
            {
                indegree[child]++;
            }
        }

        vector<int> ans;

        queue<int> q;

        // jaroori ni ki har baar components hi ho uske bina bhi ho sakta hai like in this 1 hi component hoga bss graph m and starting m sabki indegree meine mark karli hai visited wala chakkar ni hai isme, isme toh hum indegree dekh rahe hai bss

        for (int node = 0; node < V; node++)
        {
            if (indegree[node] == 0)
            {
                q.push(node);
            }
        }

        // Toplogical sort is all about DAG so agr m directed graph hi lu and then usme topological sort BFS kahns lagau toh toh agr mera end m linear ordering aajaye means ans vector m V nodes aajaye poori means pakka DAG hai means acyclic but agr mera ans array m V nodes ni aayegi toh dikkat hai toh means cycle hai usme present toh iss tareeke se hum pehchan sakte hai.
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

        return ans.size() == V ? false : true;
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