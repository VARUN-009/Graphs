#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User Function Template
class Solution
{
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex src.
    vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src)
    {
        // Code here
        int n = adj.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        vector<int> distance(n, 1e9);
        distance[src] = 0;

        // min heap le rahe hai jiss se ki har baari minimum distance hi aaye hamare pass and out of all the possible choices, you have to take the smallest distance so you always travel the shortest path and jab jab koi aur acha path mil jaye pehle se usko pq m dalo jiss se ki uss se aur bhi jagah jaya jaa sake in a lower distance.
        
        while (!pq.empty())
        {
            auto dist = pq.top().first;
            auto node = pq.top().second;
            pq.pop();

            for (auto child : adj[node])
            {
                int adjacent = child.first;
                int weight = child.second;

                if (distance[adjacent] > dist + weight)
                {
                    distance[adjacent] = dist + weight;
                    pq.push({distance[adjacent], adjacent});
                }
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
        vector<vector<pair<int, int>>> adj(V);
        int i = 0;
        while (i++ < E)
        {
            int u, v, w;
            cin >> u >> v >> w;
            pair<int, int> t1 = {v, w}, t2 = {u, w};
            adj[u].push_back(t1);
            adj[v].push_back(t2);
        }
        int src;
        cin >> src;
        cin.ignore();

        Solution obj;
        vector<int> res = obj.dijkstra(adj, src);

        for (int i = 0; i < V; i++)
            cout << res[i] << " ";
        cout << endl;

        cout << "~"
             << "\n";
    }

    return 0;
}