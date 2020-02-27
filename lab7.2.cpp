#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void printOutput(map<string, int> formulaMap) {
    cout<<"Result: "<<endl;
    for (auto it : formulaMap) {
        if (it.second == 1) {
            cout<<it.first;
        } else {
            cout<<it.first<<it.second;
        }
    }
    cout<<endl;
}

int findGCD(int num1, int num2) {
    int ret = 0;
      while (num2 > 0){
         int tmp = num2;
         num2 = num1 % num2;
         num1 = tmp;
         ret = num1;
      }
      return ret;
}

int findGCDGroup(vector<int> nums) {
    int num1 = nums[0];
    int num2 = nums[1];
    int ret = findGCD(num1,num2);
    for(int i = 2; i < nums.size(); i++){
        ret = findGCD(ret, nums[i]);
    }
    return ret;
}

void simplifyFormula(map<string, int> formulaMap) {
    vector<int> nums;
    for (auto it : formulaMap) {
        nums.push_back(it.second);
    }
    sort(nums.begin(), nums.end());
    int gcd = findGCDGroup(nums);
    for (auto it : formulaMap) {
        formulaMap[it.first] = it.second / gcd;
    }
    printOutput(formulaMap);
}

map<string, int> empiricalFormula(string line) {
    map<string, int> formulaMap;
    int len = line.size();
    stack<int> stk;
    stk.push(1);
    reverse(line.begin(), line.end());
    string elem;
    int count = 1;
    for (int i = 0; i < len; ++i) {
        auto& c = line[i];
        if (isdigit(c)) {
            int val = 0, expo = 1;
            do {
                val += (c - '0') * expo;
                ++i; expo *= 10;
            } while (isdigit(c = line[i]));
            count = val; 
            i -= 1;
        } else if (c == ')') { 
            stk.push(count * stk.top());
            count = 1;
        } else if (c >= 'A' && c <= 'Z') {
            elem += c;
            std::reverse(elem.begin(), elem.end());
            formulaMap[elem] += count * stk.top();
            count = 1;
            elem.clear();
        } else if (c >= 'a' && c <= 'z') {
            elem += c;
        } else {
            stk.pop();
        } 
    } 
    return formulaMap;
}

int main() {
    while(true) {
        string line;
        getline(cin, line);
        map<string, int> formulaMap = empiricalFormula(line);
        simplifyFormula(formulaMap);
        //cout<<"Result: "<<result<<endl;
    }
}