#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void outputResult(int n1, int n2, vector<char> res1, vector<char> res2) {
    int index= 1;
    for (int i = n1+n2+1; i >= 1; i--) {
        if (res2[i] == '_' && res1[i] == '_') {
            index = i + 1;
            break;
        }
    } 
    cout<<"Result is:"<<endl;
    for (int i = index; i <= n1+n2; i++) {
        cout<<res1[i]<<" ";
    }
    cout<<endl;
    for (int i = index; i <= n1+n2; i++) {
       cout<<res2[i]<<" ";
    }
    cout<<endl;
}

bool checkConsistancy(char c1, char c2) {
    if (c1 == 'C' && c2 == 'G') {
        return true;
    }
    if (c1 == 'G' && c2 == 'C') {
        return true;
    }
    if (c1 == 'A' && c2 == 'T') {
        return true;
    }
    if (c1 == 'T' && c2 == 'A') {
        return true;
    }
    return false;
}

void dp(string s1, string s2) {
    int n1 = s1.size();
    int n2 = s2.size();
    int i = n1;
    int j = n2;
    int i_dp = n1+n2;
    int j_dp = n1+n2;
    vector<char> res1(n1+n2+1);
    vector<char> res2(n1+n2+1);
    vector<vector<int> > dp(n1+n2+1, vector<int>(n2+1+n1, 0));
    for(int i=0;i<n1+n2+1;i++) {
        dp[0][i]=i;
        dp[i][0]=i;
    }
    for(int i = 1; i < n1+1; i++) {
        for(int j = 1; j < n2+1; j++) {
            if(checkConsistancy(s1[i-1], s2[j-1])) {
                dp[i][j]=dp[i-1][j-1];
            } else {
                dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1);
            }
        }
    }
    while (i != 0 && j != 0) {
        if (checkConsistancy(s1[i-1],s2[j-1])) {
            res1[i_dp] = s1[i-1];
            res2[j_dp] = s2[j-1];
            i_dp--;
            j_dp--;
            i--;
            j--;
        } else if (dp[i][j - 1] + 1 == dp[i][j]) {
            res1[i_dp] = '_';
            res2[j_dp] = s2[j-1];
            i_dp--;
            j_dp--;
            j--;
        } else if (dp[i - 1][j] + 1 == dp[i][j]) {
            res1[i_dp] = s1[i-1];
            res2[j_dp] = '_';
            i--;
            i_dp--;
            j_dp--;
        } 
    }
    while (i_dp > 0) {
        if (i > 0) {
            res1[i_dp] = s1[--i];
        } else {
            res1[i_dp] = '_';
        }
        i_dp--;
    }
    while (j_dp > 0) {
        if (j > 0) {
            res2[j_dp] = s2[--j];
        } else {
            res2[j_dp] = '_';
        }
        j_dp--;
    }
    outputResult(n1, n2, res1, res2);
}

int main() {
    string line;
    cout<<"First DNA sequences: "<<endl;
    getline(cin, line);
    string s1 = line;
    s1.erase(remove(s1.begin(), s1.end(), ' '), s1.end()); 
    cout<<"Second DNA sequences: "<<endl;
    getline(cin, line);
    string s2 = line;
    s2.erase(remove(s2.begin(), s2.end(), ' '), s2.end()); 
    dp(s1, s2);
}