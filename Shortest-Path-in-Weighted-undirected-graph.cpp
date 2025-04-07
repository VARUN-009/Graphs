#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        // Code here
        vector<vector<pair<int, int>>> adj(n + 1);
        vector<int> distance(n + 1, 1e9);
        distance[1] = 0;
        for (int i = 0; i < m; i++)
        {
            auto help = edges[i];
            auto node = help[0];
            auto neighbour = help[1];
            auto weight = help[2];

            // graph undirected hai toh dono jagah edges hoge toh dono hi side add karo.
            adj[node].push_back({neighbour, weight});
            adj[neighbour].push_back({node, weight});
        }

        vector<int> parent(n + 1, 1);
        // initially sabka parent vo node number hi bna do - can also make it 1 as initially mujhe node 1 ka distance 1 hi chahiye baaki se matlab ni vo baad m update ho jayega.
        // for (int i = 0; i <= n; i++)
        // {
        //     parent[i] = i;
        // }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});

        while (!pq.empty())
        {
            auto dist = pq.top().first;
            auto node = pq.top().second;
            pq.pop();

            for (auto &child : adj[node])
            {
                auto adjnode = child.first;
                auto adjweight = child.second;

                if (distance[adjnode] > dist + adjweight)
                {
                    // uska parent bhi mark karna hai ki bhai shortest distance ye hai toh iska parent bhi mark kardo ki sabse shortest yahan se ye aayi hai.
                    distance[adjnode] = dist + adjweight;
                    parent[adjnode] = node;
                    pq.push({distance[adjnode], adjnode});
                }
            }
        }

        vector<int> ans;
        // bss last wala dekhna padega bss ki agr ye 1e9 hai means dikkat hai ya toh yahan tak ki pahoch paye ya pehle hi ksii node m ni pahoch paye...sabko dekhne ki need hi ni ji.
        if (distance[n] == 1e9)
        {
            return {-1};
        }

        int node = n;
        while (node != parent[node])
        {
            ans.push_back(node);
            node = parent[node];
        }

        // 1 reh jayega kyuki usme node = parent[node] so usko alg se add kardo. 
        ans.push_back(1);
        reverse(ans.begin(), ans.end());

        // distance 1 node ka n node se toh distance[n] dedo starting m.
        ans.insert(ans.begin(), distance[n]);
        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    // your code goes here
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> edges;
        map<pair<int, int>, int> mp;
        for (int i = 0; i < m; ++i)
        {
            vector<int> temp;
            for (int j = 0; j < 3; ++j)
            {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
            mp[{edges.back()[0], edges.back()[1]}] = edges.back()[2];
            mp[{edges.back()[1], edges.back()[0]}] = edges.back()[2];
        }

        Solution obj;
        vector<int> res = obj.shortestPath(n, m, edges);
        int ans = 0;
        for (int i = 2; i < res.size(); i++)
        {
            ans += mp[{res[i], res[i - 1]}];
        }
        if (ans == res[0])
        {
        }
        else if (res.size() == 1 && res[0] == -1)
            ans = res[0];
        else
            ans = -2;
        cout << ans << endl;
        cout << "~" << endl;
    }
}