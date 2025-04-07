#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    // We only want parent and rank.
    vector<int> parent, rank;

public:
    DisjointSet(int n)
    {
        // rank is initially set to 0 kyuki sab akele hai and kisi ke neeche koi nhi hai.
        // Doing n+1 as it will work in the case of nodes starting from 0 to n-1 ans also for 1 to n.
        // Agr 0 to n-1 hai toh 0 se hi loop but 1 to n hai toh loop will run til n times not n-1. <=n
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Ultimately we have to find who is the ultimate parent of every node. We are doing path compression here.
    int findUltimateParent(int node)
    {
        // you have found parent of a node as a node then start returning that node. Every step, it will return this node and then parent[node] will be this node.
        if (parent[node] == node)
        {
            return node;
        }

        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        // find ultimate parent of both. If same, they belong to the same component.
        int ultimate_parent_u = findUltimateParent(u);
        int ultimate_parent_v = findUltimateParent(v);

        // Means they both belong to the same component.
        if (ultimate_parent_u == ultimate_parent_v)
        {
            return;
        }

        // If not, then see their rank, jis parent ki badi rank hogi usko ultimate parent bna diya jayega dusre ultimate parent ka and vice versa too.
        // else if and else ko simple ek m hi kar sakte hai by using a single else kyuki same wale m choice hai jaise marzi kisi ko bhi join kardo.
        if (rank[ultimate_parent_u] > rank[ultimate_parent_v])
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
        }
        else if (rank[ultimate_parent_v] > rank[ultimate_parent_u])
        {
            parent[ultimate_parent_u] = ultimate_parent_v;
        }

        // if same, they you can take anyone but make sure to increase the rank as at the last rank will increase.
        else
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            rank[ultimate_parent_u]++;
        }
    }
};

int32_t main()
{
    // To have 2 separate disjoint set data structures, you can create two separate objects ds1(7) ds2(5) etc.
    DisjointSet ds(7);

    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    // if 3 and 7 belong to the same component or not.
    if (ds.findUltimateParent(3) == ds.findUltimateParent(7))
    {
        cout << "Yes, they belong to the same component.\n";
    }
    else
    {
        cout << "No, they do not belong to the same component.\n";
    }

    ds.unionByRank(3, 7);

    if (ds.findUltimateParent(3) == ds.findUltimateParent(7))
    {
        cout << "Yes, they belong to the same component.\n";
    }
    else
    {
        cout << "No, they do not belong to the same component.\n";
    }

    return 0;
}