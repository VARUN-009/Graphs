class Solution
{
private:
    int timer = 1;

public:
    void dfs(int node, int parent, vector<int> &visited, vector<int> &tin, vector<int> &low, vector<vector<int>> &adj, vector<vector<int>> &bridges)
    {

        // Mark the node as visited and also uss node ka insertion time and low
        // time dono mark kardo starting m timer ke equal
        visited[node] = 1;
        tin[node] = low[node] = timer;
        timer++;

        for (auto child : adj[node])
        {

            // agr child parent hai then usme toh jana ni kyuki vahi se aa rahe
            // ho hta do aage ke bacho ko dekho
            if (child == parent)
                continue;

            // jo node visited nhi hai usme dfs karo and dfs karne ke baad abhi
            // tum node m ho and child se aarahe ho toh child bhi hai ab tumhe
            // check karna hai ki node and child ke beech jo edge hai usme
            // bridge hai ki ni ab bss check karo ki low of child jyada hai time
            // of insertion of node se toh bridge hai kyuki lowest time bhi
            // leliya vo bhi time of insertion se jyada hai means ki pakka koi
            // aur rasta ni hai jane ka child tak node ke through hi jaa sakte
            // hai toh usko hta diya toh vo akela ho jayega toh bridge hai
            if (!visited[child])
            {
                dfs(child, node, visited, tin, low, adj, bridges);
                low[node] = min(low[node], low[child]);
                if (low[child] > tin[node])
                {
                    bridges.push_back({node, child});
                }

                // agr visited hai pehle toh parent toh nhi hai kyuki vo upr hi
                // check karliya hai toh check karlo ki bhai kahin agr m iss
                // child se aau node m toh kya pta lowest time km ho jaye toh
                // check karlena
            }
            else
            {
                low[node] = min(low[node], low[child]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {
        vector<vector<int>> adj(n);
        int e = connections.size();
        for (int i = 0; i < e; i++)
        {
            int node = connections[i][0];
            int child = connections[i][1];
            adj[node].push_back(child);
            adj[child].push_back(node);
        }

        vector<int> visited(n, 0);

        vector<vector<int>> bridges;

        // time of insertion and lowest time
        vector<int> tin(n);
        vector<int> low(n);
        dfs(0, -1, visited, tin, low, adj, bridges);

        return bridges;
    }
};