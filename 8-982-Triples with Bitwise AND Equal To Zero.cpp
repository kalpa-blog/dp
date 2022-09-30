Given an integer array nums, return the number of AND triples.

An AND triple is a triple of indices (i, j, k) such that:

0 <= i < nums.length
0 <= j < nums.length
0 <= k < nums.length
nums[i] & nums[j] & nums[k] == 0, where & represents the bitwise-AND operator.
 

Example 1:

Input: nums = [2,1,3]
Output: 12
Explanation: We could choose the following i, j, k triples:
(i=0, j=0, k=1) : 2 & 2 & 1
(i=0, j=1, k=0) : 2 & 1 & 2
(i=0, j=1, k=1) : 2 & 1 & 1
(i=0, j=1, k=2) : 2 & 1 & 3
(i=0, j=2, k=1) : 2 & 3 & 1
(i=1, j=0, k=0) : 1 & 2 & 2
(i=1, j=0, k=1) : 1 & 2 & 1
(i=1, j=0, k=2) : 1 & 2 & 3
(i=1, j=1, k=0) : 1 & 1 & 2
(i=1, j=2, k=0) : 1 & 3 & 2
(i=2, j=0, k=1) : 3 & 2 & 1
(i=2, j=1, k=0) : 3 & 1 & 2
Example 2:

Input: nums = [0,0,0]
Output: 27

-----------------------------------------------------------------------------------------------------

dp[0][j] means the number of single numbers whose result is j
dp[1][j] means the number of pairs whose result is j
dp[2][j] means the number of triples whose result is j
thus the final answer = dp[2][0].

-----------------------------------------------------------------------------------------------------

class Solution {
public:
    int countTriplets(vector<int>& A) {
        vector<vector<int>> dp(3, vector<int>(1<<16, 0));
        for (const int a: A) {
            dp[0][a]++;
        }
        for (int i = 1; i < 3; ++i) {
            for (const int a: A) {
                for (int b = 0; b < 1<<16; ++b) {
                    dp[i][a&b] += dp[i-1][b];
                }
            }
        }
        return dp[2][0];
    }
};