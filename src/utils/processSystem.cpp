#include "processSystem.h"

vector<path> ProcessSystem::tasks = vector<path>();
pthread_mutex_t ProcessSystem::mutex = PTHREAD_MUTEX_INITIALIZER;
long long ProcessSystem::nowCount = 0;
uint ProcessSystem::nowSuccessCount = 0;
uint ProcessSystem::failCount = 0;
uint ProcessSystem::maxFailCount;
uint ProcessSystem::maxTaskCount;
bool ProcessSystem::isCanRun = false;
vector<thread> ProcessSystem::threads = vector<thread>();


ProcessSystem::ProcessSystem()
{
    isRun = false;
}

ProcessSystem::~ProcessSystem()
{

}
ProcessSystem::ProcessSystem(uint _threadNumber)
{
    threadNumber = _threadNumber;
    isRun = false;
}

void ProcessSystem::init(vector<path> task, uint _maxFailCount)
{
    pthread_mutex_init(&mutex, NULL);
    tasks = task;
    maxFailCount = _maxFailCount;
    nowCount = 0;
    failCount = 0;
    maxTaskCount = task.size();
    nowSuccessCount = 0;
    isCanRun = maxTaskCount > 0;
    threads = vector<thread>(maxTaskCount);
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
