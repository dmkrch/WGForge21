#include <iostream>
#include <deque>
#include <vector>


class GroupInQueue {
private:    
    int totalWaitingTime;

public: 
    GroupInQueue() : totalWaitingTime(0) {}
    GroupInQueue(int waitTime) : totalWaitingTime(waitTime) {}
    int GetWaitTime() { return totalWaitingTime; }
    void IncreaseWaitTime(int incTime) { totalWaitingTime += incTime; }
};


class Newcomer {
private:
    int pos;
    int delayTime;
    int waitTime;

public:
    Newcomer(int p, int d, int t) : pos(p), delayTime(d), waitTime(t) {}
    int GetPos() { return pos; }
    int GetDelayTime() { return delayTime; }
    int GetWaitTime() { return waitTime; }
};


int main() {
    try {
        // n - amount of groups before Ada(including Ada)
        // m - amount of groups after Ada
        int n = 0;
        int m = 0;
        std::cin >> n >> m;

        std::vector<GroupInQueue> groupsInQueue(n);

        // forming queue before Ada + Ada
        int t = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> t;
            GroupInQueue g{t};
            groupsInQueue[i] = g;
        }

        std::deque<Newcomer> newcomers;

        int pos = 0;
        int delayTime = 0;
        int waitTime = 0;
        for (int i = 0; i < m; ++i) {
            std::cin >> pos >> delayTime >> waitTime;

            // if pos is end of queue - its useless to add element, it wont affect ada's waiting time
            if (pos==-1)
                continue;

            Newcomer newcomer{pos, delayTime, waitTime};

            // now we need to push new element so that array would be still sorted 
            // by delayTime ascending

            if (newcomers.size() == 0)
                newcomers.push_back(newcomer);
            else {
                int j;
                for (j = 0; j < newcomers.size(); ++j) {
                    if (newcomer.GetDelayTime() < newcomers[j].GetDelayTime()) {
                        std::deque<Newcomer>::iterator it = newcomers.begin();
                        // than place newcomer after newcomer[i]
                        it += j;
                        newcomers.insert(it, newcomer);
                        break;
                    }
                }

                if (j == newcomers.size())
                    newcomers.push_back(newcomer);
            }
        }

        // now we need to place newcomers to queue
        for (int i = 0; i < newcomers.size(); ++i) {
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

        for (int i = 0; i < n-1; ++i)
            adaWaitTime += groupsInQueue[i].GetWaitTime();

        std::cout << adaWaitTime;

        return 0;
    }
    catch(...) {
        std::cout << "some general error\n";
        return 1;   
    }
}