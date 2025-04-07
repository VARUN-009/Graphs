//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  private: 
  bool detect(int src, int parent, vector<vector<int>>& adj, vector<bool>& vis) {
      vis[src] = 1;
      
      for(auto child : adj[src]) {
          if(!vis[child]) {
              if(detect(child, src, adj, vis)) {
                  return true;
              };
          }
          else if(parent != child) {
              return true;
          }
      }
      
      return false;
  }
  
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(vector<vector<int>>& adj) {
        // Code here
        int n = adj.size();
        
        vector<bool> vis(n, 0);
        
        // kai saare components ho sakte hai n toh iss karke har component m traverse karo
        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                if(detect(i, -1, adj, vis)) return true;
            }
        }
        
        return false;
        
        
        
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj(V);
        for (int i = 0; i < E; i++) {
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