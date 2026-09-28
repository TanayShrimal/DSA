class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {

        // Calculate the sum of the first window of size k
        int sum = 0;

        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }

        // Initially, the first window has the maximum sum
        int maxSum = sum;

        // Start moving the window from index k
        for (int i = k; i < nums.size(); i++) {

            // Remove the element that is leaving the window
            // and add the new element entering the window
            sum = sum - nums[i - k] + nums[i];

            // Update maxSum if the current window has a larger sum
            maxSum = max(maxSum, sum);
        }

        // Average = maximum window sum / window size
        // Cast to double to get a decimal answer
        return (double)maxSum / k;
    }
};