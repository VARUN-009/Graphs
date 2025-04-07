//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// Position this line where user code will be pasted.
class Solution
{
private:
    void dfs(int src, vector<int> &visited, vector<vector<int>> &adj, stack<int> &stk)
    {
        visited[src] = 1;
        for (auto child : adj[src])
        {
            if (!visited[child])
            {
                dfs(child, visited, adj, stk);
            }
        }

        stk.push(src);
    }

    void dfsKosaraju(int top, vector<vector<int>> &graph, vector<int> &visited, vector<int>&components)
    {
        visited[top] = 1;
        components.push_back(top);
        for (auto child : graph[top])
        {
            if (!visited[child])
            {
                dfsKosaraju(child, graph, visited, components);
            }
        }
    }

public:
    int kosaraju(vector<vector<int>> &adj)
    {
        // code here
        int V = adj.size();

        // 1. Sort all the nodes according to their finishing time.
        stack<int> stk;
        vector<int> visited(V, 0);

        // DFS kar rahe hai na and directed hai toh saari vertices check karni padegi sabpe hi iterate karke check karna padega jiss se ki koi chute na
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs(i, visited, adj, stk);
            }
        }

        // 2. Reverse all the edges in graph.
        vector<vector<int>> graph(V);

        int scc = 0;
        for (int i = 0; i < V; i++)
        {
            // Making it again unvisited so that it can be used again.
            visited[i] = 0;
            for (auto child : adj[i])
            {
                graph[child].push_back(i);
            }
        }

        // Visited.resize work ni karega agr size pehle ki tarah hi hai same, vo bss tab hi work karega jab size badha rahe ho toh naye element ko change kardega purane ek dum waise hi rahege, instead use array fill method.

        // Do DFS on all nodes in the order that is their in the stack.
        vector<vector<int>> strongly_components;
        while (!stk.empty())
        {
            int top = stk.top();
            if (!visited[top])
            {
                scc++;
                vector<int> components;
                dfsKosaraju(top, graph, visited, components);
                strongly_components.push_back(components);
            }
            stk.pop();
        }

        return scc;
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
        cout << obj.kosaraju(adj) << "\n";

        // cout << "~"
        //      << "\n";
    }

    return 0;
}