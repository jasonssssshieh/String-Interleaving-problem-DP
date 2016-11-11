//
//  main.cpp
//  String InterIeaving Problem DP
//
//  Created by Zijian Xie on 2016/11/11.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//

//  Given three strings, return true if third string is interleaving of first and second string.

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class stringInter{
private:
    string s1;
    string s2;
    string s3;
public:
    stringInter(string& s1, string& s2, string& s3){
        this->s1 = s1;
        this->s2 = s2;
        this->s3 = s3;
    }
    
    bool DP(){
        int m = (int)s1.size();
        int n = (int)s2.size();
        int k = (int)s3.size();
        if(m + n != k){return false;}
        else if(!m && !n && !k) return true;
        else if(s1[0] != s3[0] && s2[0] != s3[0]) return false;
 
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
        dp[0][0] = true;
        
        for(int i = 1; i <= m; ++i){
            if(s3[i-1] == s1[i-1]){
                dp[i][0] = dp[i-1][0];
            }else{break;}//这里直接break，因为只要失配了后面的全部为false
        }
        
        for(int j = 1; j <= n; ++j){
            if(s3[j-1] == s2[j-1]){
                dp[0][j] = dp[0][j-1];
            }else{break;}
        }
        
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                if(s1[i-1] == s3[i+j-1]){
                    dp[i][j] = dp[i-1][j] || dp[i][j];
                }
                if(s2[j-1] == s3[i+j-1]){
                    dp[i][j] = dp[i][j] || dp[i][j-1];//此时s2的第j个char已经匹配成功，那么我们就去看s[j-1]的char是否能和当前的s1[i]的char（i之前的全部char）能匹配成功。
                }
            }
        }
        
        cout<<"Result is: " <<to_string(dp[m][n])<<endl;
        return dp[m][n];
    }
};

int main(int argc, const char * argv[]) {
    string s1 = "aab";
    string s2 = "axy";
    string s31 = "aaxaby";
    string s32 = "abaaxy";
    
    stringInter* test1 = new stringInter(s1,s2,s31);
    stringInter* test2 = new stringInter(s1,s2,s32);
    
    cout<<"Test1 result: ";
    test1->DP();
    cout<<"Test2 result: ";
    test2->DP();
    
    return 0;
}
