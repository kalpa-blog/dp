You are climbing a staircase. It takes n steps to reach the top. 
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

 Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

---------------------------------------------------------------------------------------------
 * Idea:
 * Get to stair n has two ways:
 * 1. Stand at stair n - 1, take step = 1 forward.
 * 2. Stand at stair n - 2, take step = 2 forward.
 * So the total ways to get to the stair(n) = total ways to stair(n - 1) + total ways to stair(n - 2).
 
---------------------------------------------------------------------------------------------

class Solution {
public:
    int climbStairs(int n) {
        vector<int>dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i < n + 1; i++)
            dp[i] = dp[i - 1] + dp[i - 2];
        return dp[n];
    }
};

---------------------------------------------------------------------------------------------

Then we notice that dp[i] only concerns with dp[i - 1] and dp[i - 2], 
So we could use two variables to replace the array, reduce space to O(1).

---------------------------------------------------------------------------------------------

class Solution {
public:
    int climbStairs(int n) {
        int one = 1, two = 1, result = 1;
        for(int i = 2; i < n + 1; i++){
            result = one + two;
            one = two;
            two = result;
        }
        return result;
    }
};