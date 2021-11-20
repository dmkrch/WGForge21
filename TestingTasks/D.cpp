#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

int amountOfVariants = 0;

void GetAmountOfSuitablePermutations(string s, string l)
{
    if (s.length() < 1) {
        string resultString = l+s;
        
        // if first we take book - instant return
        if (resultString[0]=='2')
                return;

        // if not - checking balance
        int counter = 0;
        int i = 0;
        while(i < resultString.size() && counter >= 0) {                
            if (resultString[i]=='1')
                counter++;
            else if(resultString[i]=='2')
                counter--;
            
            ++i;
        }

        if (i != resultString.size())
            return;

        ++amountOfVariants;
    }
    unordered_set<char> uset;
    for (int i = 0; i < s.length(); i++) {
        if (uset.find(s[i]) != uset.end()) {
            continue;
        }
        else {
            uset.insert(s[i]);
        }
        string temp = "";
        if (i < s.length() - 1) {
            temp = s.substr(0, i) + s.substr(i + 1);
        }
        else {
            temp = s.substr(0, i);
        }
        GetAmountOfSuitablePermutations(temp, l + s[i]);
    }
}


void PermutationWithRepeats(int symbols, int plusSymbol, int minusSymbol, int zeroSymbol) {
    // here i need to make a string 1{plusSymbol}, 2{minusSymbol}, 3{zeroSymbol}
    std::string s;

    for (int i = 0; i < plusSymbol; ++i)
        s+="1";

    for (int i = 0; i < minusSymbol; ++i)
        s+="2";

    for (int i = 0; i < zeroSymbol; ++i)
        s+="3";

    GetAmountOfSuitablePermutations(s, "");
}

int main() {
    int n, p, a, b;
    std::cin >> n >> p >> a >> b;
    int result = 0;

    for (int x = a; x <= b; ++x) {
        // getting number of permutations for each amount of left books in [a,b]
        int pluses = 0;
        int numberOfVariants = 0;

        int symbLeft = n - x;
        pluses += x;

        int minuses = 0;
        for (int zeros = symbLeft; zeros >= 0; zeros-=2, minuses++) {
            PermutationWithRepeats(n,pluses+minuses,minuses,zeros);
            numberOfVariants += amountOfVariants;
            amountOfVariants = 0;
        }
        
        result += numberOfVariants;
    }
    
    std::cout << result % p;
    return 0;
}