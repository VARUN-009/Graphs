class Solution
{
public:
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        // It can be solved both by dijkstras as well as simple BFS. In dijkstras, no need to take a minheap as steps +1 se increase karege toh minheap ka fayeda ni.

        // Edge case jahan jana hai vahi ho toh steps 0 hi lagege
        if (start == end)
        {
            return 0;
        }
        vector<int> visited(100000, 0);
        visited[start] = 1;
        queue<int> q;
        q.push(start);
        int steps = 0;

        // jab ek hi time step m kai saari cheeje ho rahi ho toh q.size lena padega jiss se ki count rakha jaa sake, iske baad hi steps badh rahe hai mere.
        while (!q.empty())
        {
            int n = q.size();

            // hum ek step m sabse multiply karege then next step m bhi same, hume bss step se matlab hai uss se ni ki kahan kahan se kaise aaya. Saare possible ans nikalo and then unko store karlo visited m and jis case m number == end then steps return abhi tak ke.
            for (int i = 0; i < n; i++)
            {
                int top = q.front();
                q.pop();

                if (top == end)
                {
                    return steps;
                }

                for (auto ele : arr)
                {
                    int ans = (top * ele) % 100000;
                    // mod le rahe hai 1000000 toh ans repeat bhi karege from [0, 99999] so iss wajah se visited ka ki jo aagya hai pehle usko phirse compute na kare.
                    if (!visited[ans])
                    {
                        visited[ans] = 1;
                        q.push(ans);
                    }
                }
            }

            steps++;
        }

        return -1;
    }
};
// TC - O(100000 * arr.size()); -  hypothtically it is not possible as saare ke saare numbers generate karna 0 se 99999 tak toh kaafi km chance hai
// SC - O(100000)

// USING DIJKSTRAS ALGORITHM
class Solution
{
public:
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        // It can be solved both by dijkstras as well as simple BFS. In dijkstras, no need to take a minheap as steps +1 se increase karege toh minheap ka fayeda ni
        if (start == end)
        {
            return 0;
        }
        vector<int> distance(100000, 1e9);
        distance[start] = 0;
        queue<int> q;
        q.push(start);
        int steps = 0;
        while (!q.empty())
        {
            int n = q.size();

            for (int i = 0; i < n; i++)
            {
                int top = q.front();
                q.pop();

                if (top == end)
                {
                    return steps;
                }

                // Saari cheeje same hi hai isme bss isme steps store kar rahe hai usme ki pehle aa chuka tha km steps m toh agr phirse ye hi number aaya hai toh isko store ni karna na queue m push karna hai.
                for (auto ele : arr)
                {
                    int ans = (top * ele) % 100000;
                    if (steps + 1 < distance[ans])
                    {
                        distance[ans] = steps + 1;
                        q.push(ans);
                    }
                }
            }
            steps++;
        }

        return -1;
    }
};
// TC - O(arr.size() log 1000000) -- hypothtically it is not possible as saare ke saare numbers generate karna 0 se 99999 tak toh kaafi km chance hai 
// SC - O(100000)
