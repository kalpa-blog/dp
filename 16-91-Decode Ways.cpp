A message containing letters from A-Z can be encoded into numbers using the following mapping:

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:

"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".

Given a string s containing only digits, return the number of ways to decode it.
The test cases are generated so that the answer fits in a 32-bit integer.

Example 1:

Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
Example 3:

Input: s = "06"
Output: 0
Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").

-----------------------------------------------------------------------------------------------------
class Solution {
public:
    int numDecodings(string s) {
        /** dp[i] = 
         * value                            Example
         * 0                                00, 30, 80 - invalid ending
         * dp[i-2]                          10, 20     - valid ending with 0
         * dp[i-2]                          08, 09     - s[i - 1] == '0'      
         * dp[i-1] + dp[i-2]                11, 16     - valid ending
         * dp[i-1]                          32, 56     - large ending, decrease i by 1
         */
        if(s.size() == 0 || s[0] == '0') return 0;
        vector<int>dp(s.size());
        dp[0] = 1;
        for(int i = 1; i < s.size(); i++){
            if(s[i] == '0'){
                if(s[i - 1] == '0' || s[i - 1] - '0' > 2) return 0;
                dp[i] = (i==1) ? dp[0] : dp[i - 2];
            }
            else if(s[i - 1] == '0') dp[i] = dp[i - 2];
            else if(stoi(s.substr(i - 1, 2)) <= 26) dp[i] = (i==1) ? dp[0] + 1 : dp[i - 1] + dp[i - 2];
            else dp[i] = dp[i - 1];
        }
        return dp[s.size()-1];
    }
};

// Solution from here: https://discuss.leetcode.com/topic/7025/a-concise-dp-solution
class Solution {
public:
    int numDecodings(string s) {
        if(s.empty() || s.front() == '0') return 0;
        int p1 = 1, p2 = 1;
        for(int i = 1; i < s.size(); i++){
            if(s[i] == '0') p1 = 0;
            if(s[i - 1] == '1' || s[i - 1] == '2' && s[i] < '7'){
                p1 = p1 + p2;
                p2 = p1 - p2;
            }
            else p2 = p1;
        }
        return p1;
    }
};