class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                          int k)
    {

        unordered_map<int, vector<pair<int, int>>> adj;
        // vector<pair<int,int>> adj
        // 2d vector -- adjacency list
        // taken 2d vector because ek node ke kayi saare neighbours ho sakte hai
        // na

        for (auto node : flights)
        {
            // Node - {neighbour, distance}
            adj[node[0]].push_back({node[1], node[2]});
        }

        // Apply BFS and make sure that it does not exceed steps
        int steps = 0;
        vector<int> result(n, INT_MAX);
        result[src] = 0;
        queue<pair<int, int>> q;
        // Don't need a priority queue as stops are increasing  by + 1, agr +1
        // se increase hi hote hai toh priority queueki need ni hoti hai
        q.push({0, src});
        while (!q.empty() && steps <= k)
        {
            int m = q.size();

            while (m--)
            {
                int node = q.front().second;
                int distance = q.front().first;
                q.pop();

                for (auto &neighbour : adj[node])
                {
                    // adj list ke andar har node m kai saare pairs store hai
                    // {node,distance} ke
                    int neighbourNode = neighbour.first;
                    int cost = neighbour.second;

                    if (distance + cost < result[neighbourNode])
                    {
                        result[neighbourNode] = distance + cost;
                        q.push({distance + cost, neighbourNode});
                    }
                }
            }

            steps++;
        }

        return result[dst] == INT_MAX ? -1 : result[dst];
    }
};
/*
Dijkstras laga sakte the par isme main jispe focus karna hai vo hai k, hum k se
jyada steps ni le sakte, toh dijkstras har step m abhi tak ka sabse chotta
distance dedeta hai source node se, toh m at max k tak chla lunga BFS ko, aur k
ke baad jo distance hoga vo mera at most k tak ka hi hoga toh vo dedunga uss
destination ka. agr sirf shortest path dete toh ho sakta tha ki tum k ko exceed
kardo, which can become a problem, See test case - 3, shortest to 2 is 200 but
it will give in 1 steps, but steps we can take is 0 so at 0 steps, minimum
distance i get is 500

BFS hai toh no need to take priority_queue and also visited map ki jaroorat ni
hai kyuki ek node m dobara bhi jaa sakte hai kya pta vo shorter distance ki mil
jaye - dijkastras jaisi hai par poori dijkstras ni

O(flights.size()) - kyuki jitni edges hai utni hi baar chlega at max

This is quite similar to rotten oranges in terms ki uss point of time m stops mere sabke liye badhege basically agr 3 jagah hai toh teeno m jaa sakta hu and for whiole 3 stops will increase that's why a size loop inside queue and stops ko hum queue ke andar pair m bhi le sakte hai phir bss !q.empty() and agr steps mere k se jyada continue after popping. No need to take a separate size loop inside queue. 
*/