#include "./processSystem.h"

namespace fs = std::filesystem;
ProcessSystem::ProcessSystem()
{
    isRun = false;
}

ProcessSystem::~ProcessSystem()
{

}
ProcessSystem::ProcessSystem(uint threadNumber)
{
    ProcessSystem::threadNumber = threadNumber;
    ProcessSystem::isRun = false;
}

void ProcessSystem::init(vector<path> task, uint maxFailCount = 100)
{
    pthread_mutex_init(&mutex, NULL);
    ProcessSystem::tasks = task;
    ProcessSystem::maxFailCount = maxFailCount;
    ProcessSystem::nowCount = 0;
    ProcessSystem::failCount = 0;
    ProcessSystem::maxTaskCount = task.size();
    ProcessSystem::nowSuccessCount = 0;
    ProcessSystem::isCanRun = ProcessSystem::maxTaskCount > 0;
    ProcessSystem::threads = vector<thread>(maxTaskCount);
}
path ProcessSystem::nextTask()
{
    pthread_mutex_lock(&mutex);
    if(nowSuccessCount >= maxTaskCount)
    {
        pthread_mutex_unlock(&mutex);
        return "";
    }
    nowPath = tasks[nowCount];
    nowCount++;
    pthread_mutex_unlock(&mutex);
    return nowPath;
}
void ProcessSystem::fali()
{
    pthread_mutex_lock(&mutex);
    tasks.push_back(nowPath);
    failCount++;
    pthread_mutex_unlock(&mutex);
    if(failCount > ProcessSystem::maxFailCount)
    {
        // 10번 이상 실패시 프로세스 종료
        std::cout << "Process is terminated because it has failed more than " << ProcessSystem::maxFailCount << " times." << std::endl;
        std::cout << "Please check the file system." << std::endl;
        exit(1);
        return;
    }
}
void ProcessSystem::success()
{
    pthread_mutex_lock(&mutex);
    nowSuccessCount++;
    pthread_mutex_unlock(&mutex);
}

void ProcessSystem::run()
{
    while(true)
    {
        if(nowPath == "")
        {
            // 작업이 끝났을 때
            break; 
        }
        // 작업 수행
        // 성공시 success();
        // 실패시 fail();
        threadTask() ? success() : fali();
        nowPath = this->nextTask();
    }

}

inline bool ProcessSystem::threadTask()
{

    return fs::remove(nowPath);

}
