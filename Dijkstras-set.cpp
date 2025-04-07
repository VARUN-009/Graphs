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
        set<pair<int,int>> st;
        st.insert({0, src});
        vector<int> distance(n, 1e9);
        distance[src] = 0;

        // min heap le rahe hai jiss se ki har baari minimum distance hi aaye hamare pass and out of all the possible choices, you have to take the smallest distance so you always travel the shortest path and jab jab koi aur acha path mil jaye pehle se usko pq m dalo jiss se ki uss se aur bhi jagah jaya jaa sake in a lower distance.

        // min heap m toh sabse upr humesha mininmum hi aayega par isme minimum  sabse upr ni aayega toh uske liye meine kya kiya jo purani wali entry hai na usko meine hta diya hai ki kaam lagbhg min heap wale tarah hi hone lag jaye .

        while (!st.empty())
        {
            // begin returns an iterator so to have the value of it simply deference it using * operator.
            auto ele = *(st.begin());
            auto dist = ele.first;
            auto node = ele.second;
            st.erase(ele);

            for (auto child : adj[node])
            {
                int adjacent = child.first;
                int weight = child.second;
                
                if (distance[adjacent] > dist + weight)
                {
                    // agr koi distance hai pehle se toh usko hta do kyuki ab mujhe uss se better distance mil gya hai toh usko rakhne ka fayeda ni hai iterations km ho jayegi aise.
                    if(distance[adjacent] != 1e9) {
                        st.erase({distance[adjacent], adjacent});
                    }

                    // distance update karo and then usko set m daldo phirse.
                    distance[adjacent] = dist + weight;
                    st.insert({distance[adjacent], adjacent});
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