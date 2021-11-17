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

            // if (newcomer.GetDelayTime() > )
            newcomers.push_back(newcomer);
        }

        // now main action
        for (int i = 0; i < newcomers.size(); ++i) { // 
            // skipping newcomers that stands in end of queue
            if (newcomers[i].GetPos() == -1)
                continue;

            // this is the time between Ada's coming and newcomer's coming to queue
            delayTime = newcomers[i].GetDelayTime();

            // now we need to find position where to place newcomer in queue if necessary 
            for (int j = 0; j < n-1; ++j) {
                waitTime = groupsInQueue[j].GetWaitTime();
                delayTime -= waitTime;

                if (delayTime < 0) {
                    // we found group that will be first newcomer
                    // this means newcomer pos will be j + newcomer.GetPos()
                    int newcomerIdInQueue = j + newcomers[i].GetPos();
                    groupsInQueue[newcomerIdInQueue].IncreaseWaitTime(newcomers[i].GetWaitTime());
                    break;
                }
            }
        }

        // here we need to calculate waitTime of groups before Ada
        int adaWaitTime = 0;

        for (int i = 0; i < n-1; ++i) {
            adaWaitTime += groupsInQueue[i].GetWaitTime();
        }

        std::cout << adaWaitTime;



        return 0;
    }
    catch(...) {
        std::cout << "some general error\n";
        return 1;   
    }
}