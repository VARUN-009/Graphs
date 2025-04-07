class Solution
{
public:
    int mod = 1e9 + 7;
    int countPaths(int n, vector<vector<int>> &roads)
    {
        vector<vector<pair<long long, long long>>> adj(n);

        // Had to take because of constraints.
        for (int i = 0; i < roads.size(); i++)
        {
            long long node = roads[i][0];
            long long child = roads[i][1];
            long long weight = roads[i][2];
            adj[node].push_back({child, weight});
            adj[child].push_back({node, weight});
        }

        vector<long long> distance(n, 1e18);
        vector<long long> ways(n, 0);

        // Initially m source node m hu toh wahan tak 1 hi step se aaya means abhi wahin khada hu m by 1 step and it's distance is 0
        ways[0] = 1;
        distance[0] = 0;
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> minheap;

        // {Distance, node}
        minheap.push({0, 0});

        while (!minheap.empty())
        {
            long long dist = minheap.top().first;
            long long node = minheap.top().second;
            minheap.pop();

            // dekho aisa bhi ho sakta hai ki ek hi node m kai baar aa sakta hu m and 1 hi node kai baar meri minheap m aa sakti hai toh agr aisa hua abhi jo aayi meri uska jo distance hai vo distance vector m jo distance stored hai uss se km hai toh usko dekhne ke fayeda hi ni agla pair nikalo ji.  
            if (dist > distance[node])
                continue;

            for (auto childs : adj[node])
            {
                long long ch = childs.first;
                long long wt = childs.second;

                // agr naya acha distance mila hai toh usko store karo and puane jo ways hai unko htao kyuki unka jyada distance tha ab jis node se aaya hai uske equal rakhdo iske ways
                if (distance[ch] > dist + wt)
                {
                    distance[ch] = dist + wt;
                    ways[ch] = ways[node];
                    minheap.push({distance[ch], ch});
                }

                // agr distance same aaya hai means one more way to arrive at this node so abhi ke ways m add jahan se aaya hai matlab +1 ni, jahan se aaya hai vo saare ways ki kitni tareeke se aa sakte hai. Mod to prevent integer overflow. 
                else if (distance[ch] == dist + wt)
                {
                    ways[ch] = (ways[ch] + ways[node]) % mod;
                }
            }
        }

        return ways[n - 1] % mod;
    }
};

// TC - O(E) + O(E log V)
// SC - O(V + 2*E) + O(V)