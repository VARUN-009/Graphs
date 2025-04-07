#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // code here
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minheap;
        vector<int> visited(V, 0);
        // int n = adj.size();
        vector<vector<pair<int,int>>> graph(V);
        for(int i=0; i<V; i++) {
            // ek index m kai saare vectors hai means uss particular node se kai saari nodes connect ho sakti hai and isme pair lene ki jagah vector hi leliya hai toh kai saare vectors hai jisme pehla index child hai and dusra weight hai.
            for(auto ele : adj[i]) {
                int child = ele[0];
                int weight = ele[1];
                graph[i].push_back({child, weight});
                graph[child].push_back({i, weight});
            }
        }
        
        // pushing (weigh, node, parent);
        // sabse km distance ka hume sabse upr chahiye that's why we have taken weight first 
        minheap.push({0, 0, -1});
        int weight = 0;
        
        // Don't need this in the question but this is to find the graph basically the minimum spanning tree.
        vector<vector<pair<int,int>>> mst(V);
        
        while(!minheap.empty()) {
            auto top = minheap.top();
            minheap.pop();
            int wt = top[0];
            int node = top[1];
            int parent = top[2];
            
            // agr node pehle hi visit ho chuki hai then usko htao continue karo phirse kaam karne ka fayeda ni kyuki ek node ek hi baar chahiye 
            if(visited[node]) continue;
            
            visited[node] = 1;
            
            // this is for node 0, it's parent is -1 so no need to push it first.
            if(parent != -1) {
                mst[parent].push_back({node, wt});
                mst[node].push_back({parent, wt});
            }
            weight += wt;
            
            for(auto child : graph[node]) {
                if(!visited[child.first]) {
                    minheap.push({child.second, child.first, node});
                }
            }
        }
        
        // to also return the MST, you can return a pair<int, vector<vector<pair<int,int>>>> 
        return weight;
        
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i = 0;
        while (i++ < E) {
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
