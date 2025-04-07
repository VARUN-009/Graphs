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
    int removeStones(vector<vector<int>> &stones)
    {
        // maxrows and maxcols kitni hai ye jaan ne ke liye
        int maxrow = 0;
        int maxcol = 0;

        for (auto point : stones)
        {
            maxrow = max(maxrow, point[0]);
            maxcol = max(maxcol, point[1]);
        }

        // map in order to store rows and cols as nodes ki total meri itni nodes hai as I am treating each row and each col as a node so as to make connection like coordinates like (1,2) means row 1 and col 2 connected.  
        // har row ko ek node and uske baad wali jo cols hai usko m numnber dunga node number as maxrow + col + 1 kyuki I can't count it from 0 as 0 row ho gayi hai m bss map kar rha hu.
        // so total nodes = maxrow + maxcol + 1 (3 rows - 0 1 2 and 3 cols - 0 1 2  so 0+1+2+(3cols) = 5 total and + 1 = 6) 
        unordered_map<int, int> mp;
        DisjointSet ds(maxrow + maxcol + 1);
        for (auto points : stones)
        {
            int row = points[0];
            // col no. 2 means maxrow(say 3) + col(2 here) + 1 (3 + 2 + 1 = 6) so mapping 2nd col as a 6th number nodexz
            int col = maxrow + points[1] + 1;
            ds.unionBySize(row, col);

            mp[row] = 1;
            mp[col] = 1;
        }

         
        int components = 0;
        for (auto point : mp)
        {
            if (ds.findUltimateParent(point.first) == point.first)
            {
                components++;
            }
        }

        return stones.size() - components;
    }
};
/*
har component m end m 1 node toh bachegi hi kyuki sabko toh m hta ni sakta and kai saare components ho sakte hai toh 
c1 + c2 + c3 ... = total stones as sum of all the stones in the components will give us total stones
c1-1 + c2-1 + c3-1 ... so on...
c1 + c2 + c3 -1 -1 -1
c1 + c2 + c3 - (1 + 1 + 1)
total stones - components

DSU will do this in O(1) and O(n) space
*/