You are given an array prices where prices[i] is the price of a given stock on the ith day.
Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously
(i.e., you must sell the stock before you buy again).

 Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions
at the same time. You must sell before buying again.

-----------------------------------------------------------------------------------------------------


Approach :
We just to need to build the recursive solution after that recursive -> iterative conversion and optimisations
can be done easily.

Everyday, We have two choices : Buy/Sell this stock OR ignore and move to the next one.
Along with day, we also need to maintain a transactionsLeft variable which will tell us how many transactions 
are remaining and it will be of which type (Buy or Sell) and According to that we will make recursive calls 
and calculate the answer
We can do atmost 4 transactions (Buy, Sell, Buy, Sell) in this order.
// No transaction today :
	ans1 = solve(day + 1, transactionsLeft); 
// transaction today :
   bool buy = (transactionsLeft % 2 == 0);
	if(buy == true) {
		ans2 = -prices[day] + solve(day + 1, transactionsLeft - 1);
	}else{
		ans2 = prices[day] + solve(day + 1, transactionsLeft - 1);
	}
Now Choosing the best one among them and returning the required answer.
We will stop the recursion when day >= prices.size() or transactionsLeft == 0 and return 0.
Recursive Solution

-----------------------------------------------------------------------------------------------------
class Solution {
public:
    
    int solve(vector<int>&prices, int day, int transactionsLeft){
        
        if(day == prices.size()){
            return 0;
        }
        
        if(transactionsLeft == 0){
            return 0;
        }
        
        // choice 1
        // no transaction today
        int ans1 = solve(prices, day + 1, transactionsLeft);
        
        
        // choice 2
        // doing the possible transaction today     
        int ans2 = 0;
        bool buy = (transactionsLeft % 2 == 0);
        
        if(buy == true){ // buy
            ans2 = -prices[day] + solve(prices, day + 1, transactionsLeft - 1);
        }else{ // sell
            ans2 = prices[day] + solve(prices, day + 1, transactionsLeft - 1);
        }
        
        return max(ans1, ans2);
        
        
    }
    
    
    int maxProfit(vector<int>& prices) {
        
        int ans = solve(prices, 0, 4); // starting with day 0 and max 4 transactions can be done
        return ans;
        
    }
};
Time Complexity : O(2^N)
Space Complexity : O(N)

Memoization Solution
Exact same code as above just store the answer of all states to avoid solving subproblems that have 
already been solved

-----------------------------------------------------------------------------------------------------
class Solution {
public:
    
    int solve(vector<int>&prices, int day, int transactionsLeft, vector<vector<int>> &Memo){
        
        if(day == prices.size()){
            return 0;
        }
        
        if(transactionsLeft == 0){
            return 0;
        }
        
        int &ans = Memo[day][transactionsLeft]; 
        
        if(ans != -1){ // if problem has already been solved 
            return ans;
        }
        
        // choice 1
        // no transaction today
        int ans1 = solve(prices, day + 1, transactionsLeft, Memo);
        
        
        // choice 2
        // doing the possible transaction today     
        int ans2 = 0;
        bool buy = (transactionsLeft % 2 == 0);
        
        if(buy == true){ // buy
            ans2 = -prices[day] + solve(prices, day + 1, transactionsLeft - 1, Memo);
        }else{ // sell
            ans2 = prices[day] + solve(prices, day + 1, transactionsLeft - 1, Memo);
        }
        
        return ans = max(ans1, ans2); // store ans in memo before returning
        
        
    }
    
    
    int maxProfit(vector<int>& prices) {
        
        vector<vector<int>> Memo(prices.size(), vector<int>(5, -1));
        int ans = solve(prices, 0, 4, Memo);
        return ans;
        
    }
};
Time Complexity : O(N)
Space Complexity : O(N)
Accepted
DP solution with O(N) space

-----------------------------------------------------------------------------------------------------
Converting the recursive solution to iterative, Again exact same code just reverse the direction.
class Solution {
public:
    
    int maxProfit(vector<int>& prices) {
        
        int dp[prices.size() + 1][5];
        
        
        for(int day = (int) prices.size();day >= 0;day--){
            
            for(int transactionsLeft = 0;transactionsLeft <= 4;transactionsLeft++){
                
                int &ans = dp[day][transactionsLeft];
                
                if(day == prices.size()){
                    ans = 0;
                }else if(transactionsLeft == 0){
                    ans = 0;
                }else{
                    
                    // choice 1
                    // no transaction today
                    int ans1 = dp[day + 1][transactionsLeft];
                    
                    // choice 2
                    // doing the possible transaction today     
                    int ans2 = 0;
                    bool buy = (transactionsLeft % 2 == 0);

                    if(buy == true){ // buy
                        ans2 = -prices[day] + dp[day + 1][transactionsLeft - 1];
                    }else{ // sell
                        ans2 = prices[day] + dp[day + 1][transactionsLeft - 1];
                    }

                    ans = max(ans1, ans2);

                }
                
            }
        }
        return dp[0][4];
        
    }
};
Time Complexity : O(N)
Space Complexity : O(N)
Accepted
DP solution with O(1) space

-----------------------------------------------------------------------------------------------------

Observation : For any day we just need the answers of the next day (day + 1) => Optimising it further to O(1) space
class Solution {
public:
    
    int maxProfit(vector<int>& prices) {
        
        int dp[2][5];
        
        
        for(int day = (int) prices.size();day >= 0;day--){
            
            for(int transactionsLeft = 0;transactionsLeft <= 4;transactionsLeft++){
                
                
                int &ans = dp[day % 2][transactionsLeft];
                
                if(day == prices.size()){
                    ans = 0;
                }else if(transactionsLeft == 0){
                    ans = 0;
                }else{
                    
                    // choice 1
                    // no transaction today
                    int ans1 = dp[(day + 1) % 2][transactionsLeft];
                    
                    // choice 2
                    // doing the possible transaction today     
                    int ans2 = 0;
                    bool buy = (transactionsLeft % 2 == 0);

                    if(buy == true){ // buy
                        ans2 = -prices[day] + dp[(day + 1) % 2][transactionsLeft - 1];
                    }else{ // sell
                        ans2 = prices[day] + dp[(day + 1) % 2][transactionsLeft - 1];
                    }

                    ans = max(ans1, ans2);

                }
                
            }
        }
        return dp[0][4];
        
    }
};
Time Complexity : O(N)
Space Complexity : O(1)
Accepted