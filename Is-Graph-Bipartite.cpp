class Solution
{
private:
    bool bfs(int src, vector<vector<int>> &graph, vector<int> &colors)
    {
        queue<int> q;
        q.push(src);
        colors[src] = 1;

        // if I got a child who is not colored I will color it and put in inside
        // queue. But if as soon as I encounter a child which is already colored
        // by a different node having same color as that of current parent jahan
        // se m aaya hu so false kyuki vo node raste m padd rahi hai toh dikkat
        // degi hi.
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto child : graph[node])
            {
                if (colors[child] == -1)
                {
                    colors[child] = !colors[node];
                    q.push(child);
                }
                else if (colors[node] == colors[child])
                {
                    return false;
                }
            }
        }

        return true;
    }

public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, -1);
        // no need to take visited array as it's work is already done by colors
        // array it was failing on larger test cases so whenever code fails on
        // larger test cases, make sure to include all components.
        for (int i = 0; i < n; i++)
        {
            if (colors[i] == -1)
            {
                if (!bfs(i, graph, colors))
                {
                    return false;
                }
            }
        }

        return true;
    }
};
/*
TC - O(n) components + O(n + 2*e) as n nodes and at max 2*e edges as undirected so ek edge 2 baar count.
SC - O(n) colored + O(n) queue ~ O(n)

BI partite means ki m graph ko 2 color se color kar sakta hu ya ni toh iske liye meine 2 color leliye 0 and 1.
*/

// DFS APPROACH
class Solution
{
private:
    // color m neeche se lekar aarha hu and ye hi color se current node ko color karna hai and then child m jab call karoge toh ye color opposite kardena by !color so basically 2 colors hoge 0 and 1.
    bool dfs(int src, int col, vector<vector<int>> &graph, vector<int> &colors)
    {
        colors[src] = col;
        for (auto child : graph[src])
        {
            if (colors[child] == -1)
            {
                // agr koi bhi dfs call se answer mera false aagya means ki direct return false, aage check karne ki need ni hai na -- DFS m ye hi hota hai as ek bhi false means I cannot make it so directly return false no need to check other calls.
                if(!dfs(child, !col, graph, colors)) {
                    return false;
                }
            }
            else if (colors[src] == colors[child])
            {
                return false;
            }
        }

        return true;
    }

public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, -1);
        // no need to take visited array as it's work is already done by colors
        // array it was failing on larger test cases so whenever code fails on
        // larger test cases, make sure to include all components.
        for (int i = 0; i < n; i++)
        {
            if (colors[i] == -1)
            {
                if (!dfs(i, 1, graph, colors))
                {
                    return false;
                }
            }
        }

        return true;
    }
};
/*
TC - O(n) components + O(n + 2*e)
SC - O(n) colors + O(n) recursion ~ O(n)

*/
