class Solution
{
public:
    string findOrder(vector<string> dict, int k)
    {
        
        vector<vector<int>> adj(k);
        for (int i = 0; i < dict.size() - 1; i++)
        {
            string str1 = dict[i];
            string str2 = dict[i + 1];

            int n = str1.size();
            int m = str2.size();

            for (int j = 0; j < min(n, m); j++)
            {
                if (str1[j] != str2[j])
                {
                    adj[str1[j] - 'a'].push_back(str2[j] - 'a');
                    break;
                }
            }
        }

        vector<int> indegree(k, 0);
        for (int i = 0; i < k; i++)
        {
            for (auto ele : adj[i])
            {
                indegree[ele]++;
            }
        }

        queue<int> q;
        string ans = "";
        for (int i = 0; i < k; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            auto top = q.front();
            q.pop();

            // char means ki character chahiye at that ascii index and int a means ki a ka ascii lo usme top add karo and then jo ascii aaye uss index ka ascii character do.
            // agr int hota bahar toh bss ascii hi aata bsss.
            ans += (char)(top + (int)'a');
            for (auto child : adj[top])
            {
                indegree[child]--;
                if (indegree[child] == 0)
                {
                    q.push(child);
                }
            }
        }

        return ans;
    }
};
/*
Pair by pair take two strings and then check character by character, jaise hi alg mil jaye then usko number m convert karo and then jo pehle aayega uss index m baad m aane walo ko push kardo. 

Aise karke humne words ko ek graph m convert karliya hai and then topo sort laga ke check karliya ki kon pehle aayega and kon baad m aayega. Remember k size ka adj lena hai bhle hi dict m words km ho.

TC - O(n*min(n,m)) + O(k) + O(k) + O(k + k)
SC - O(k + k) + O(k) + O(k)

edge case 1 - jab strings ko abcd and abc dono hi same hai har char toh pehli wali badi hai and char differ bhi ni hai toh ye possible nhi hai whether it is alien or normal dictionary.

edge case - 2 - jab strings ho abc then bcd then ade toh a < b < a not possible, it is a cycle.
*/