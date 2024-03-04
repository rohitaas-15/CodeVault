
/*You start with an initial power of power, an initial score of 0, and a bag of tokens given as an integer array tokens, where each tokens[i] donates the value of tokeni.

Your goal is to maximize the total score by strategically playing these tokens. In one move, you can play an unplayed token in one of the two ways (but not both for the same token):

Face-up: If your current power is at least tokens[i], you may play tokeni, losing tokens[i] power and gaining 1 score.
Face-down: If your current score is at least 1, you may play tokeni, gaining tokens[i] power and losing 1 score.
Return the maximum possible score you can achieve after playing any number of tokens.
https://leetcode.com/problems/bag-of-tokens/description/?envType=daily-question&envId=2024-03-04*/

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int bagOfTokensScore(vector<int> &tokens, int power)
    {
        int n = tokens.size();
        int score = 0;
        sort(tokens.begin(), tokens.end());
        int i = 0, j = n - 1;
        while (i <= j)
        {
            while (i <= j && power >= tokens[i])
            {
                power -= tokens[i];
                score++;
                i++;
            }
            if (i < j && score)
            {
                score--, power += tokens[j--];
            }
            else
                break;
        }
        return score;
    }
};