#include <iostream>
#include <vector>

class Elevator {
private:
    int floor;
    bool isAway;
    bool isUpElevator;
    void MoveUp() { floor++; isAway=true; }
    void MoveDown() { floor--; isAway=false; }
public:
    Elevator(int f) : isAway{false}, floor{f} {}
    bool IsAway() { return isAway; }
    void SetDefaultPosition() { isAway = false; }
};

int main() {
    int n; // amount of floors
    int m; // amount of lift pairs
    int k; // amount of employee
    int a; // just a constant
    int b; // just a constant
    std::cin >> n >> m >> k >> a >> b;

    // on which floor employee stand
    std::vector<int> employeePositions(k);
    
    for (int i = 0; i < k; ++i)
        std::cin >> employeePositions[i];
    
    int c;
    int d;


    for (int i = 0; i < m; ++i) {
        std::cin >> c >> d;

    }

    return 0;
}