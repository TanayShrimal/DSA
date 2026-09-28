class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<pair<int, int>> v; // {score, index}
        for (int i = 0; i < n; i++)
            v.push_back({score[i], i});
        sort(v.rbegin(), v.rend()); // highest score first
        vector<string> res(n);
        for (int r = 0; r < n; r++) {
            int idx = v[r].second;
            if (r == 0)
                res[idx] = "Gold Medal";
            else if (r == 1)
                res[idx] = "Silver Medal";
            else if (r == 2)
                res[idx] = "Bronze Medal";
            else
                res[idx] = to_string(r + 1);
        }
        return res;
    }
};
