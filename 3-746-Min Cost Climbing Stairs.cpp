You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, 
you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

Example 1:

Input: cost = [10,15,20]
Output: 15

Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.
Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]

Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.

---------------------------------------------------------------------------------------------

Recursion: `dp[i] = min{dp[i - 1], dp[i - 2]} + cost[i];`
A straightforward solution is:

---------------------------------------------------------------------------------------------

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int>dp(n);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i = 2; i < n; i++)
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        return min(dp[n - 2], dp[n - 1]);
    }
};

---------------------------------------------------------------------------------------------

If we take a look at the solution above, we can see the result dp[i] only depends on previous 2 steps(dp[i - 1] and dp[i - 2]).
So we can replace the 'dp' array with 2 variables.
Here is the final solution:

---------------------------------------------------------------------------------------------
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size(), a = cost[0], b = cost[1], c;
        for(int i = 2; i < n; i++, a = b, b = c)
            c = min(a, b) + cost[i];
        return min(a, b);
    }
};