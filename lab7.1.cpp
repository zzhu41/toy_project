#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using namespace std;

string primeFactor(int num) {
    if (num == 0 || num == 1) {
        return "Input not valid";
    }
    bool negative = false;
    if (num < 0) {
        num = abs(num);
        negative = true;
    }
    map<int, int> result;
    while (num % 2 == 0) { 
        num = num / 2;
        result[2] ++;
    }
    for (int i = 3; i <= sqrt(num); i = i+2) { 
        while (num % i == 0) { 
            result[i] ++;
            num = num/i; 
        } 
    } 

    if (num > 2) {
        result[num]++;
    }

    string retStr = "";
    for (auto it : result) {
        if (negative) {
            retStr += "(-" + to_string(it.first) + ")^" + to_string(it.second) + " ";
        } else {
            retStr += "(" + to_string(it.first) + ")^" + to_string(it.second) + " ";
        }
    }
    return retStr;
}

int main() {
    vector<string> results;
    while(true) {
        string line;
        getline(cin, line);
        if (line == "end") {
            cout<<"Output: "<<endl;
                for (int i = 0 ; i < results.size(); i++) {
                cout<<results[i]<<endl;
            }
            results.clear();
        } else {
            string result = primeFactor(stoi(line));
            results.push_back(result);
        }
    }
}