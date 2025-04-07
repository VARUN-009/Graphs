class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        int n = prerequisites.size();
        vector<vector<int>> adj(numCourses);
        for (int i = 0; i < n; i++)
        {
            vector<int> help = prerequisites[i];

            // 1 -> 0 means for [0,1] complete 1 first and then 0
            adj[help[1]].push_back(help[0]);
        }

        // Find the indegree of each node and then push those nodes in queue
        // whose indegree is 0.
        vector<int> indegree(numCourses, 0);
        for (int i = 0; i < numCourses; i++)
        {
            for (auto node : adj[i])
            {
                indegree[node]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        vector<int> ans;

        while (!q.empty())
        {
            auto top = q.front();
            q.pop();
            ans.push_back(top);

            for (auto child : adj[top])
            {
                indegree[child]--;
                if (indegree[child] == 0)
                {
                    q.push(child);
                }
            }
        }

        // If there is a cycle in the graph then we cannot have all numCourses
        // nodes in he topo sort vector so return false and if there is no cycle
        // in the graph then we can get all numCourses nodes in the graph son
        // ans is true we can complete all courses in the graph.
        return ans.size() == numCourses;
    }
};
/*
We can also use cycle detection in this as if there is a cycle then courses cannot be done. Cycle detection can be done via DFS taking vis and pathvis and also via topo sort Kahn's algo.

TC - O(V+E)
SC - O(v+E)

*/