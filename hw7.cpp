
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

unordered_map<char, int> map;
void init() {
    map['I'] = 1;
    map['V'] = 5;
    map['X'] = 10;
    map['L'] = 50;
    map['C'] = 100;
    map['D'] = 500;
    map['M'] = 1000;
}

string intToRoman(string line) {
    int num = stoi(line);
    string ret = "";
    vector<string> roman = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    vector<int> digit = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    for (int i = 0; i < digit.size(); i++) {
        while (num >= digit[i]) {
            num -= digit[i];
            ret += roman[i];
        }
    }
    return ret;
}

int romanToInt(string line) {
    int ret = map[line[line.size()-1]];
    for (int i = line.size() - 2; i >= 0; i--) {
        if (map[line[i]] < map[line[i + 1]]) {
            ret -= map[line[i]];
        } else {
            ret += map[line[i]];
        }
    }
   return ret;
}

int main() {
    init();
    while(true) {
        string line;
        getline(cin, line);
        if(isdigit(line[0])) {
            string ret = intToRoman(line);
            cout<<"Result: "<<ret<<endl;
        } else if (isalpha(line[0])) {
            int ret = romanToInt(line);
            cout<<"Result: "<<ret<<endl;
        }
    }
    return 0;
}