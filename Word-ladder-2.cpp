class Solution
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        // check karne m asaani rahe and delete karne m bhi and duplicate ni hogi toh fayeda hoga
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> q;
        q.push({beginWord});
        vector<string> usedWords;
        usedWords.push_back(beginWord);
        vector<vector<string>> ans;
        while (!q.empty())
        {
            int n = q.size();

            while (n--)
            {
                auto vec = q.front();
                q.pop();

                auto word = vec.back();

                if (word == endWord)
                {
                    ans.push_back(vec);
                    continue;
                }

                for (int k = 0; k < word.size(); k++)
                {
                    char ch = word[k];
                    for (int i = 0; i < 26; i++)
                    {
                        word[k] = (char)'a' + i;
                        if (st.find(word) != st.end())
                        {
                            vec.push_back(word);
                            q.push(vec);
                            vec.pop_back();
                            usedWords.push_back(word);
                        }
                    }

                    word[k] = ch;
                }
            }

            for (auto &str : usedWords)
            {
                if (st.find(str) != st.end())
                {
                    st.erase(str);
                }
            }
        }

        return ans;
    }
};

/*
Estimating the TC of this is next to impossible as it vary from examples to examples. This will give MLE on leetcode.

*/

// OPTIMISED APPROACH - CP
class Solution
{
    unordered_map<string, int> mp;
    vector<vector<string>> ans;

    void dfs(string word, vector<string> &sequence, string beginWord)
    {
        // base case
        // m neeche se upr jaa rha hu par mujhe upr se neeche ka chahiye toh reverse karna padega na and also return karne se pehle mujhe usko purane sequence m hi dalna hoga as vo use hoga mera baad ke cases ke liye toh reverse again.
        if (word == beginWord)
        {
            reverse(sequence.begin(), sequence.end());
            ans.push_back(sequence);
            reverse(sequence.begin(), sequence.end());
            return;
        }

        // recursive case
        // mere pass word hai then mujhe isko change karna hai possible words m and check karna hai ki ye mera map m hai ki nhi and also hai toh iska map m km hona chahiye current word se.
        int sz = word.size();

        // current word ke steps toh change karne ke baad steps + 1 should be equal to this step kyuki 1 km chahiye na
        int steps = mp[word];
        for (int i = 0; i < sz; i++)
        {
            char original = word[i];

            for (int j = 0; j < 26; j++)
            {
                word[i] = (char)'a' + j;
                if (mp.find(word) != mp.end() && mp[word] + 1 == steps)
                {
                    // push karna hai then pop because aage ke sequence bhi check karne hai na like combinations.
                    sequence.push_back(word);
                    dfs(word, sequence, beginWord);
                    sequence.pop_back();
                }
            }
            word[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        queue<string> q;
        q.push(beginWord);
        mp[beginWord] = 0;

        // sab word ki length same hi hogi kyuki m naya character add ni kar rha bss swap kar rha hu changekar rha hu
        int sz = beginWord.size();
        unordered_set<string> st(wordList.begin(), wordList.end());

        // ye htana padega as ni htaya toh ye hi phirse aajayega aata rahega toh tle. isko hta diya means ab aage ke words dekhne padege jo hai.
        st.erase(beginWord);
        while (!q.empty())
        {
            auto word = q.front();
            q.pop();

            // just a little optimisation
            if (word == endWord)
                break;

            // abhi tak ka jo uska step hai current word ka store karlo
            int steps = mp[word];
            for (int i = 0; i < sz; i++)
            {
                char original = word[i];

                for (int j = 0; j < 26; j++)
                {
                    // int + char will give me a int result so then I am type casting it too char.
                    word[i] = (char)'a' + j;
                    if (st.count(word))
                    {
                        q.push(word);
                        st.erase(word);
                        mp[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }

        // now ab agr map ke andar mera end word hai hi ni means m end word m nhi pahoch sakta toh return {} and agr hai toh dfs with the last word.
        if (mp.find(endWord) != mp.end())
        {
            vector<string> sequence;
            sequence.push_back(endWord);
            dfs(endWord, sequence, beginWord);
        }

        return ans;
    }
};

/*
1. Mein start word se end word m jaa rha hu and jate jate steps ko store kar rha hu har string ke liye map ke andar. 
2. Then m end word se start word ki taraf jaa rha hu so that m bekar ke combinations path na lu only valid hi lu and optimised ho jaye.
3. Mujhe end word se start word m jana hai toh change karne ke baad word ka steps should be 1 less than the current word step.
4. Possible jo jo words bane sabko le and then call dfs. Isme remove karne ki need ni wordlist se as m humesha ek km step wala hi lunga.
5.  
*/

