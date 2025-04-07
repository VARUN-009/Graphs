class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();

        // Reverse the edges first.
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++)
        {
            for (auto ele : graph[i])
            {
                adj[ele].push_back(i);
            }
        }

        // Count the indegree now
        vector<int> indegree(n, 0);
        for (int i = 0; i < n; i++)
        {
            for (auto ele : adj[i])
            {
                indegree[ele]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> ans;
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            ans.push_back(node);

            for (auto child : adj[node])
            {
                indegree[child]--;
                if (indegree[child] == 0)
                {
                    q.push(child);
                }
            }
        }

        sort(ans.begin(), ans.end());
        return ans;
    }
};
/*
vo node jiski outdegree 0 hai vo vo meri terminal node bn jayegi and
then vo nodes jiske saare path terminal nodes ya safe nodes m jaa
rahe hai vo ek safe node hai and also every terminal node is a safe
node too
edges reverse karne ke baad then m indegree 0 wali se start karunga
and ek ek karke indegree child ki km karte rahunga and then jiski 0
hoti rahegi vo mere ans ka part hogi. Jo nodes cycle ka part hai ya
connected hai unki indegree humesha 1 ya 1 se upr hi rahegi so cycle
wali nodes waise bhi meri safe nodes ni bn sakti hai so vo mera part
ni hog
Hum kindoff backtrack kar rahe hai toh jo jo meri terminal nodes se
connected hai bss vahi aayegi, bachi hui nodes meri terminal hai hi
ni means unke kai aur paths bhi hai

TC - O(nlogn) sorting + O(n+m) + O(n+m) + O(n+m) queue
*/

// This is done via cycle detection DFS.

class Solution
{
private:
    bool dfs(int node, vector<vector<int>> &graph, vector<int> &visited,
             vector<int> &pathvis)
    {
        visited[node] = 1;
        pathvis[node] = 1;

        for (auto child : graph[node])
        {
            if (!visited[child])
            {
                if (dfs(child, graph, visited, pathvis))
                {
                    // ki cycle hai meri
                    return true;
                }
            }
            else if (pathvis[child])
            {
                return true;
            }
        }

        pathvis[node] = 0;
        return false;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> visited(n, 0);
        vector<int> pathvis(n, 0);

        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                // even tough it is bool function par hume sab nodes m jana hai
                // and ans se koi lena dena ni toh direct function call
                dfs(i, graph, visited, pathvis);
            }
        }

        // agr cycle hoti toh uss poore path ki nodes pathvis = 1 hota kyuki m
        // usko pathvis 0 kar hi ni pata kyuki direct return karta cycle dekhne
        // ke baad. toh vo nodes jiska pathvis 0 hai vahi mera ans hai kyuki vo
        // kisi cycle ka part ni hai na connected hai cycle se.
        for (int i = 0; i < n; i++)
        {
            if (pathvis[i] == 0)
            {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

/*
meine node se start kara and m aage jata rha but agr mujhe cycle mil gayi toh
uss cycle m koi bhi node meri terminal node toh ni hogi kyuki outgoing hogi sab
so no terminal and hence no safe. ab uss path ki saari nodes bhi meri terminal
nhi hogi kyuki at the end sab ek cycle m jaa rahi hai and vo terminal safe toh
hai ni and also direct return true karunga m pathvis ko 0 kare bina as agr cycle
ni hoti child wale loop se bahar aake m pathvis 0 karta and return false. so at
the end jo nodes pathvis 0 hai vahi meri safe nodes hai.
*/