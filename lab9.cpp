#include <iostream>
#include <vector>

using namespace std;

vector<int> diceVal = {4, 6, 8, 10, 12};

void dp(int sum, vector<int> dice, int lower, int upper, int fail, int reward) {
	int col = 0;
    int row = 0;
    for (int i = 0; i < dice.size(); i++) {
        row += dice[i];
    }
    col = upper - sum;
    int newLower = lower - sum;
    int newUpper = upper - sum;
    vector<vector<int> > dp(row+1, vector<int>(col+2));
	dp[0][0] = 1;
    int curRow = 0;
    int prod = 1;
    for (int i = 0; i < 5; i++) {
        int numberOfDice = dice[i];
        int valueOfDice = diceVal[i];
        for (int a = 0 ; a < numberOfDice; a++) {
            curRow++;
            for (int j = 1; j <= newUpper + 1; j++) {
                for (int k = 0; k <= j; k++) {
                    for(int l = 1; l <= valueOfDice; l++) {
                        if (k + l == j)  {
                            dp[curRow][j] += dp[curRow - 1][k];
                        }
                        if (j == newUpper + 1 && l + k > j) {
                            dp[curRow][j] += dp[curRow - 1][k];
                        }
                    }
                }    
            }
        }
    }
    int total = 1;
    for (int i = 0; i < dice.size(); i++) {
        for (int j = 0; j < dice[i]; j++) {
            total *= diceVal[i];
        }
    }
    float probSuccess = (float)dp[row][newUpper + 1]/total;
    cout<<"p(success) = "<<(probSuccess)*100<<"%"<<endl;

    int countFail = 0;
    for(int i = 0; i <= newLower - 1; i++) {
        countFail += dp[row][i];
    }
    float probFail = (float)countFail/total;
    float expectedVal = probSuccess*reward + probFail*fail;
    cout<<"E = "<<expectedVal<<endl;
}

int main() {
    while (true) {
        vector<int> dice;
        cout<<"Enter currently rolled sum"<<endl;
        string sum;
        getline(cin, sum);
        cout<<"Enter number of 4-sided dice to be rolled"<<endl;
        string num4;
        getline(cin, num4);
        dice.push_back(stoi(num4));
        cout<<"Enter number of 6-sided dice to be rolled"<<endl;
        string num6;
        getline(cin, num6);
        dice.push_back(stoi(num6));
        cout<<"Enter number of 8-sided dice to be rolled"<<endl;
        string num8;
        getline(cin, num8);
        dice.push_back(stoi(num8));
        cout<<"Enter number of 10-sided dice to be rolled"<<endl;
        string num10;
        getline(cin, num10);
        dice.push_back(stoi(num10));
        cout<<"Enter number of 12-sided dice to be rolled"<<endl;
        string num12;
        getline(cin, num12);
        dice.push_back(stoi(num12));
        cout<<"Enter inclusive lower bound for draw"<<endl;
        string lower;
        getline(cin, lower);
        cout<<"Enter inclusive upper bound for draw"<<endl;
        string upper;
        getline(cin, upper);
        cout<<"Enter consequence for failure"<<endl;
        string failVal;
        getline(cin, failVal);
        cout<<"Enter reward for success"<<endl;
        string reward;
        getline(cin, reward);
        dp(stoi(sum), dice, stoi(lower), stoi(upper), stoi(failVal), stoi(reward));
    }
}