You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one
and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0

-----------------------------------------------------------------------------------------------------

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n < 2) return 0;
        vector<int>buy(n), sell(n), rest(n);
        buy[0] = -prices[0];
        sell[0] = 0;
        rest[0] = 0;
        for(int i = 1; i < n; i++){
            buy[i] = max(buy[i - 1], rest[i - 1] - prices[i]);
            sell[i] = max(sell[i - 1], buy[i - 1] + prices[i]);
            rest[i] = max(rest[i - 1], sell[i - 1]);
        }
        return max(rest[n - 1], sell[n - 1]);
    }
};

// Since day `i` relies only on `i-1`, we can reduce the O(n) space to O(1). 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n < 2) return 0;
        int buy = -prices[0], sell = 0, rest = 0, preBuy, preSell;
        for(int i = 1; i < n; i++){
            preBuy = buy;
            preSell = sell;
            buy = max(buy, rest - prices[i]);
            sell = max(sell, preBuy + prices[i]);
            rest = max(rest, preSell);
        }
        return max(rest, sell);
    }
};