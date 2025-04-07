#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    vector<int> size, parent;

public:
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Ultimately we have to find who is the ultimate parent of every node. We are doing path compression here.
    int findUltimateParent(int node)
    {
        // you have found parent of a node as a node then start returning that node. Every step, it will return this node and then parent[node] will be this node.
        if (parent[node] == node)
        {
            return node;
        }

        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionBySize(int u, int v)
    {
        int ultimate_parent_u = findUltimateParent(u);
        int ultimate_parent_v = findUltimateParent(v);

        // Means they both belong to the same component.
        if (ultimate_parent_u == ultimate_parent_v)
        {
            return;
        }

        // else if and else ko simple ek m hi kar sakte hai by using a single else kyuki same wale m choice hai jaise marzi kisi ko bhi join kardo.
        if (size[ultimate_parent_u] > size[ultimate_parent_v])
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            size[ultimate_parent_u] += size[ultimate_parent_v];
        }
        else if (size[ultimate_parent_v] > size[ultimate_parent_u])
        {
            parent[ultimate_parent_u] = ultimate_parent_v;
            size[ultimate_parent_v] += size[ultimate_parent_u];
        }
        else
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            size[ultimate_parent_u] += size[ultimate_parent_v];
        }
    }
};

// } Driver Code Ends
class Solution
{
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // I just only need edges in this basically in this order {weight, node, child};
        vector<vector<int>> graph;
        for (int i = 0; i < V; i++)
        {
            for (auto vec : adj[i])
            {
                int node = vec[0];
                int weight = vec[1];

                // It is a directed graph but no need to add another edge from child to node as it's DSU, it will automatically discard the second edge kyuki ultimate parent nikaloge toh 2,3 karo ya 3,2 baat ek hi hai ji. karna hai insert toh kar sakte ho 2nd edge koi dikkat ni hai.
                graph.push_back({weight, i, node});
            }
        }

        int edges = graph.size();

        sort(graph.begin(), graph.end());
        int final_weight = 0;

        DisjointSet dsu(V);
        for (int i = 0; i < edges; i++)
        {
            auto vec = graph[i];
            int weight = vec[0];
            int node = vec[1];
            int child = vec[2];

            // Pehle check karna hai na ki dono node same component m lie karti hai ki nhi, agr nhi karti hai toh bhai ye edge leni hai and iske saath jara MST bnana hai toh isko lelo.
            if (dsu.findUltimateParent(node) != dsu.findUltimateParent(child))
            {
                dsu.unionBySize(node, child);
                final_weight += weight;
            }
        }

        return final_weight;
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
        vector<vector<int>> adj[V];
        int i = 0;
        while (i++ < E)
        {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1, t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }

        Solution obj;
        cout << obj.spanningTree(V, adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}
