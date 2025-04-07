#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
private:
    int timer = 1;

public:
    void dfs(int node, int parent, vector<int> &visited, vector<int> &tin, vector<int> &low,
             vector<int> &mark, vector<int> adj[])
    {
        // Mark the node as visited and also uss node ka insertion time and low
        // time dono mark kardo starting m timer ke equal
        visited[node] = 1;
        tin[node] = low[node] = timer;
        timer++;

        int childs = 0;

        for (auto child : adj[node])
        {
            // agr child parent hai then usme toh jana ni kyuki vahi se aa rahe
            // ho hta do aage ke bacho ko dekho
            if (child == parent)
                continue;

            if (!visited[child])
            {
                dfs(child, node, visited, tin, low, mark, adj);

                // baad m jakr ye visited ho jayegi par abhi ke liye toh ye visited nhi hai na toh abhi lo min
                low[node] = min(low[node], low[child]);

                // isme hum >= lagayege and check karlege ki parent toh nhi hai na -1. >= because mujhe check karna hai ki m uske upr tak pahoch sakta hu ki nhi, >= hoga low[child] agr toh matlab uske insertion time se bhi jyada hai iska low time pakka ye hi ek rasta hai jaane ka toh ye htayi toh upr ka neeche se connection khatam.

                // mark isliye kyuki aisa ho sakta hai kai saari nodes ho toh ek hi node baar baar repeat ho jaye as a articulation point toh uske liye vector leliya ki ek hi baar count ho.
                if (low[child] >= tin[node] && parent != -1)
                {
                    mark[node] = 1;
                }

                // ye unvisited ke andar hi rakhna padega kyuki agr bahar hi rakh diya if else ke toh dikkat ye hai ki kisi aur node ne usko pehle visit kardiya toh vo bhi count ho jayega and 0 ko hta ke phir fayeda ni hoga 0 articulation point ni hoga. /|\ iss tarah ka graph chahiye ki 0 htao toh sab hatt jaye hamara. 
                childs++;
            }
            else
            {
                // bridges m toh low[child] se karte the par isme tin[child] kyuki manlo m vo node hi hta du toh pakka thodi hai ki m upr jaa hi saku kya pta vahi ek rasta ho toh low se nhi kar sakte, we have to only do via tin[child] - visited hai pehle se path m hai toh isko jitna time laga h insertion ka utna hi lo kyuki agr htadi toh uss se upr ni jaa sakta  
                low[node] = min(low[node], tin[child]);
            }
        }

        // /|\ iss case ke liye kyuki first node ke liye hum ye formula ni laga sakte kyuki uske uor kuch nhi hai toh iske liye ye hi hai ki uske bache bohot hai toh 0 htate hi sab khatam. jaroori ni 0 ho starting m kuch bhi ho sakta hai.
        if (childs > 1 && parent == -1)
        {
            mark[node] = 1;
        }
    }

    vector<int> articulationPoints(int V, vector<int> adj[])
    {
        // Code here
        vector<int> visited(V, 0);
        vector<int> tin(V);
        vector<int> low(V);
        vector<int> mark(V, 0);
        dfs(0, -1, visited, tin, low, mark, adj);

        vector<int> ans;
        for (int i = 0; i < V; i++)
        {
            if (mark[i] == 1)
            {
                ans.push_back(i);
            }
        }

        if (ans.size() == 0)
        {
            ans.push_back(-1);
        }

        return ans;
    }
};

//{ Driver Code Starts.

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        vector<int> ans = obj.articulationPoints(V, adj);
        for (auto i : ans)
            cout << i << " ";
        cout << "\n";

        cout << "~" << "\n";
    }
    return 0;
}