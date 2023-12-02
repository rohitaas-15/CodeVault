/*Letter Combinations of a Phone Number
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Make sure the returned strings are lexicographically sorted.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters. Typing a number once 
can correspond to all its letters. */





#include<bits/stdc++.h>
using namespace std;

 map<string, vector<string> > m;
 
 
 vector<string>  ans;
 
 
 void calculate(int index, string sub,string &digits)
 {

  
     
     if(index==digits.size())
     {
         if(sub.size())
         ans.push_back(sub);
         return ; 
     }
     
     for(auto i : m[to_string(digits[index]-48)])
     {
       sub.push_back(i[0]);
       calculate(index+1,sub,digits);
       sub.pop_back();
     }
     
     return ;
     
 }


vector<string> letterCombinations(string digits) {
    
    
    ans.clear();
    
   
     m["2"]={"a","b","c"};
    
    m["3"]={"d","e","f"};
    
    m["4"]={"g","h","i"};
     
    m["5"]={"j","k","l"};
      
    m["6"]={"m","n","o"};
       
    m["7"]={"p","q","r","s"};
        
    m["8"]={"t","u","v"};
         
    m["9"]={"w","x","y","z"};
    
 
    
    
    calculate(0,"",digits);

    sort(ans.begin(),ans.end());
    return ans;
    
    
    
    
    
}
