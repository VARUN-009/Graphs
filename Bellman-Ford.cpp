#include <cstdio> // for freopen
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    /*  Function to implement Bellman Ford
     *   edges: vector of vectors which represents the graph
     *   src: source vertex
     *   V: number of vertices
     */
    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
    {
        // Code here
        // vector hai ek and uski har bucket ek vector<int> ki hai means kai saare number ho sakte hai that we can access through 0 1 2 index. 
        int m = edges.size();
        vector<int> distance(V, 1e8);
        distance[src] = 0;

        // We have to do this V-1 times only.
        for (int i = 0; i < V; i++)
        {
            // Direct traverse karo and km distacne mile toh distance m update karo.
            for (auto &child : edges)
            {
                auto u = child[0];
                auto v = child[1];
                auto wt = child[2];
                if (distance[u] != 1e8 && distance[u] + wt < distance[v])
                {
                    distance[v] = distance[u] + wt;

                    // Accurate distance V-1 times m pta chl jayega par agr V times bhi update hua distance toh dikkat hai means negative edges hai negative cycle bhi ho sakti hai.
                    if (i == V - 1)
                    {
                        return {-1};
                    }
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
    cin.ignore();
    while (t--)
    {
        int N, m;
        cin >> N >> m;

        vector<vector<int>> edges;

        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;

            vector<int> edge(3);
            edge[0] = u;
            edge[1] = v;
            edge[2] = w;
            edges.push_back(edge);
        }

        int src;
        cin >> src;
        cin.ignore();

        Solution obj;
        vector<int> res = obj.bellmanFord(N, edges, src);

        for (size_t i = 0; i < res.size(); i++)
        {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}