
//https://leetcode.com/problems/simplify-path/description/

class Solution
{
public:
    string simplifyPath(string path)
    {
        int n = path.size();
        string npath;
        npath.push_back(path[0]);

        for (int i = 1; i < n; i++)
        {
            if (path[i] == '/' && path[i - 1] == '/')
            {
                continue;
            }
            else
            {
                npath.push_back(path[i]);
            }
        }
        vector<string> pv;

        auto val = strtok((char *)npath.c_str(), "/");
        while (val != NULL)
        {
            pv.push_back(val);
            val = strtok(NULL, "/");
        }

        vector<string> cpv;
        cpv.push_back("/");
        for (auto i : pv)
        {
            cout << i << endl;
            if (i == ".")
            {
                continue;
            }
            else if (i == ".." && cpv.size() > 1)
            {
                if (cpv.size() > 1)
                {
                    cpv.pop_back();
                    cpv.pop_back();
                }
            }
            else if (i != "")
            {

                cpv.push_back(i);
                cpv.push_back("/");
            }
        }

        if (cpv.size() > 1)
            cpv.pop_back();

        string ans;
        for (auto i : cpv)
            ans = ans + i;
        return ans;
    }
};
