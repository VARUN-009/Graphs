class DisjointSet
{
public:
    vector<int> size;
    vector<int> parent;
    vector<int> rank;

    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int findUltimateParent(int node)
    {
        // base case
        if (parent[node] == node)
        {
            return node;
        }

        // recursive case
        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ultimate_parent_u = findUltimateParent(u);
        int ultimate_parent_v = findUltimateParent(v);

        if (ultimate_parent_u == ultimate_parent_v)
        {
            return;
        }

        if (rank[ultimate_parent_u] > rank[ultimate_parent_v])
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
        }
        else if (rank[ultimate_parent_v] > rank[ultimate_parent_u])
        {
            parent[ultimate_parent_u] = ultimate_parent_v;
        }

        else
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            rank[ultimate_parent_u]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ult_par_u = findUltimateParent(u);
        int ult_par_v = findUltimateParent(v);

        if (ult_par_u == ult_par_v)
        {
            return;
        }
        else if (size[ult_par_u] > size[ult_par_v])
        {
            parent[ult_par_v] = ult_par_u;
            size[ult_par_u] += size[ult_par_v];
        }
        else
        {
            parent[ult_par_u] = ult_par_v;
            size[ult_par_v] += size[ult_par_u];
        }
    }
};

class Solution
{
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {

        int n = accounts.size();
        // sabse pehle m mails ko map kardunga index se basically konse number ki mail hai vo
        unordered_map<string, int> mailToNode;
        // m har naam ko as a node consider kar rha hu so naam = row no. easy to connect in DSU.

        DisjointSet ds(n);

        // 1. first index is name and rest are emails - mapping emails ki konse row no. m hai vo
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j < accounts[i].size(); j++)
            {
                string email = accounts[i][j];
                
                // agr nhi hai abhi tak map m and ek dum new mail hai toh map m uss mail ke corresponding vo row number save kardo as hum user ke liye vo jis row number m hai vo le rahe hai 
                if (mailToNode.find(email) == mailToNode.end())
                {
                    mailToNode[email] = i;
                }

                // agr pehle se hi hai vo means abhi wali node and jiss se vo map hai dono same hai means connected same parent bole toh ek hi bande ki hai toh dono ko connect karlo
                else
                {
                    ds.unionByRank(i, mailToNode[email]);
                }
            }
        }

        // 2. ab jo meri emails hai unko m node se connect karunga ki 0 index m konsi hai 1st index m konsi hai and connect karte samay m uske ultimate parent se connect karunga na ki sirf uss node no. se
        vector<vector<string>> data(n);
        for (auto ele : mailToNode)
        {
            auto email = ele.first;
            auto node = ele.second;

            // pushing email to the ultimate parent of node --  aise karne se hume pta chl jayega ki 0 m konsi mails hai and then 1 m konsi mails and since 0, 1 humne users ke liye le rakha hai toh baad m asaani se user le sakte hai.
            data[ds.findUltimateParent(node)].push_back(email);
        }

        // 3. ab mere pass har index m emails hai jo belong karti hai uss particular insaan ko bss sort karna hai and push karna hai
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++)
        {
            // aisa bhi ho sakta hai ki vo index m koi mail hi na toh aage badho else sabse pehle user ka naam lo and then sort karke mails daldo
            vector<string> mails = data[i];
            if (mails.size() == 0)
                continue;
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            sort(mails.begin(), mails.end());
            for (auto str : mails)
            {
                temp.push_back(str);
            }

            ans.push_back(temp);
        }

        return ans;
    }
};
