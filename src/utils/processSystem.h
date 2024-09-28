#ifndef PROCESSSYSTEM_H
#define PROCESSSYSTEM_H
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <thread>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace filesystem;
namespace fs = std::filesystem;
class ProcessSystem
{
private:
    static vector<path> tasks;
    static pthread_mutex_t mutex;
    static long long nowCount;
    static uint failCount;
    static uint maxFailCount;
    static uint maxTaskCount;
    static uint nowSuccessCount;
    static bool isCanRun;
    static vector<thread> threads;

    bool isRun;
    path nowPath;
    path nextTask();
    void fali();
    void success();
    inline bool threadTask();
    uint threadNumber;
protected:
    ProcessSystem();
    ~ProcessSystem();
public :
    ProcessSystem(uint _threadNumber);
    static void init(const vector<path>& task, uint _maxFailCount = 100);
    void run();

};

#endif