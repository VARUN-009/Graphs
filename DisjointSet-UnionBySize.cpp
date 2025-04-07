#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    // In this, we only want size and parent.
    vector<int> size, parent;

public:
    DisjointSet(int n)
    {
        // size is initially set to 1 as sab akele hai means single-single n components are there.
        // Doing n+1 as it will work in the case of nodes starting from 0 to n-1 ans also for 1 to n.
        // Agr 0 to n-1 hai toh 0 se hi loop but 1 to n hai toh loop will run til n times not n-1. <=n
        size.resize(n + 1, 1);
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

    void unionBySize(int u, int v)
    {
        int ultimate_parent_u = findUltimateParent(u);
        int ultimate_parent_v = findUltimateParent(v);

        // Means they both belong to the same component.
        if (ultimate_parent_u == ultimate_parent_v)
        {
            return;
        }

        // else if and else ko simple ek m hi kar sakte hai by using a single else kyuki same wale m choice hai jaise marzi kisi ko bhi join kardo.
        if (size[ultimate_parent_u] > size[ultimate_parent_v])
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            size[ultimate_parent_u] += size[ultimate_parent_v];
        }
        else if (size[ultimate_parent_v] > size[ultimate_parent_u])
        {
            parent[ultimate_parent_u] = ultimate_parent_v;
            size[ultimate_parent_v] += size[ultimate_parent_u];
        }
        else
        {
            parent[ultimate_parent_v] = ultimate_parent_u;
            size[ultimate_parent_u] += size[ultimate_parent_v];
        }
    }
};

int main()
{
    // To have 2 separate disjoint set data structures, you can create two separate objects ds1(7) ds2(5) etc.
    DisjointSet ds(7);

    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);

    // if 3 and 7 belong to the same component or not.
    if (ds.findUltimateParent(3) == ds.findUltimateParent(7))
    {
        cout << "Yes, they belong to the same component.\n";
    }
    else
    {
        cout << "No, they do not belong to the same component.\n";
    }

    ds.unionBySize(3, 7);

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