class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {

        multiset<int> low, high;
        vector<double> result;

        // Balance the two sets
        auto balance = [&]() {

            // low can have at most one extra element
            while (low.size() > high.size() + 1) {
                high.insert(*low.rbegin());
                low.erase(prev(low.end()));
            }

            // high should never have more elements than low
            while (low.size() < high.size()) {
                low.insert(*high.begin());
                high.erase(high.begin());
            }
        };

        for (int i = 0; i < nums.size(); i++) {

            // Insert new element
            if (low.empty() || nums[i] <= *low.rbegin())
                low.insert(nums[i]);
            else
                high.insert(nums[i]);

            balance();

            // Remove element that is outside the window
            if (i >= k) {

                if (low.find(nums[i - k]) != low.end())
                    low.erase(low.find(nums[i - k]));
                else
                    high.erase(high.find(nums[i - k]));

                balance();
            }

            // Calculate median when window size becomes k
            if (i >= k - 1) {

                // Odd k
                if (k % 2 == 1) {
                    result.push_back(*low.rbegin());
                }

                // Even k
                else {
                    result.push_back(
                        ((double)*low.rbegin() + *high.begin()) / 2.0
                    );
                }
            }
        }

        return result;
    }
};

