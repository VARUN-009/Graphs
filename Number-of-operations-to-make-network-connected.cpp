class DisjointSet
{
public:
    vector<int> size;
    vector<int> parent;

    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
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
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        int edges = connections.size();
        // agr mere pass 4 nodes hai and 4 ki 4 nodes ko connect karna hai toh
        // minimum 4-1=3 nodes chahiye hogi mujhe par agr uss se bhi km hai toh
        // mere pass cables ki kami hai kyuki yahan likha hai ki cables jo hai
        // vahi leni hai
        if (edges < n - 1)
        {
            return -1;
        }
        DisjointSet ds(n);

        for (auto ele : connections)
        {
            ds.unionBySize(ele[0], ele[1]);
        }

        // mujhe iss se pta chl jayega ki kitne components hai and to connect k
        // components, k-1 edges are required, so at the end k-1 return or
        // count-1
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (ds.parent[i] == i)
            {
                count++;
            }
        }

        return count - 1;
    }
};

/*
- This can also be done using DFS. Jitni baar DFS call karna padega means utni
hi baar ek aisi node mili hai jo connected ni thi toh usko connect karne ke liye
ek edge chahiye.

- Can also be solved by DSU as jis node ka ultimate parent ek ni hai means vo
pakka ek alg hi component m hai toh +1. Using this will result in O(1) TC. and
O(n) space.


*/