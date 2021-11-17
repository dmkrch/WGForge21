#include <iostream>
#include <deque>

class GroupInQueue {
private:    
    int totalWaitingTime;

public: 
    GroupInQueue(int waitTime) : totalWaitingTime(waitTime) {}
    int GetWaitTime() { return totalWaitingTime; }
    void IncreaseWaitTime(int incTime) { totalWaitingTime += incTime; }
};


class Newcomers {
private:
    int pos;
    int delayTime;
    int waitTime;

public:
    Newcomers(int p, int d, int t) : pos(p), delayTime(d), waitTime(t) {}
    int GetPos() { return pos; }
    int GetDelayTime() { return delayTime; }
    int GetWaitTime() { return waitTime; }
};


int main() {
    try {
        std::deque<GroupInQueue> groupsInQueue;

        // n - amount of groups before Ada(including Ada)
        // m - amount of groups after Ada
        int n = 0;
        int m = 0;
        std::cin >> n >> m;

        // forming queue before Ada + Ada
        int t = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> t;
            GroupInQueue g{t};
            groupsInQueue.push_back(t);
        }

        std::deque<Newcomers> newcomers;

        int pos = 0;
        int delayTime = 0;
        int waitTime = 0;
        for (int i = 0; i < m; ++i) {
            std::cin >> pos >> delayTime >> waitTime;

            Newcomers newcomer{pos, delayTime, waitTime};
            newcomers.push_back(newcomer);
        }

        // we have formed active groups in queue in 'groupsInQueue'
        // and we formed newcomers in 'newcomers'

        

        return 0;
    }
    catch(...) {
        std::cout << "some general error\n";
        return 1;   
    }
}