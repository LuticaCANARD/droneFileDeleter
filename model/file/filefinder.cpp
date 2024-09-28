
#include "filefinder.h"

/// @brief 지정되지 않은 파일들을 찾아서 삭제합니다.
/// @param startPath 시작할 디렉토리의 경로입니다.
/// @param fileExtensions 삭제할 파일들의 (상대)경로입니다.
/// @return 삭제된 파일의 개수를 반환합니다.
int findAndDeleteFilesInDirectory(string startPath, set<string> vaildFiles,bool isRecursive = true)
{
    int deleteCount = 0;
    string path = startPath;

    for (const auto & entry : fs::directory_iterator(startPath))
    {
        // "./NAO/VIL/ashe.s" ...
        if (vaildFiles.find(entry.path().string()) == vaildFiles.end())
        {
            fs::remove(entry.path());
            deleteCount++;
        }
        else if(fs::is_directory(entry.path()))
        {
            deleteCount += findAndDeleteFilesInDirectory(entry.path().string(), vaildFiles);
        }
    }
    return deleteCount;
}
vector<fs::path> getUnvaildFilesInDirectory(string startPath, set<string> vaildFiles)
{
    vector<fs::path> deadFiles;
    for(const auto & entry : fs::directory_iterator(startPath))
    {
        if(fs::is_directory(entry.path()))
        {
            // 멀티스레딩이 가능하게 수정해야함.
            // 가능한 방법으로는 각 스레드마다 디렉토리를 나눠서 작업하게 하거나
            // 각 스레드마다 작업한 파일들을 모아서 마지막에 한번에 삭제하게 하는 방법이 있다.

            // 다만, 탐색만 재귀적으로 하고, 삭제는 한번에 하는 방법을 선택하였다.
            vector<fs::path> subFiles = getUnvaildFilesInDirectory(entry.path().string(), vaildFiles);
            deadFiles.insert(deadFiles.end(),subFiles.begin(),subFiles.end());
        }
        else if(vaildFiles.find(entry.path().string()) == vaildFiles.end())
        {
            deadFiles.push_back(entry);
        }
            
    }
    return deadFiles;
}

static void deleteFiles(vector<fs::path> files)
{
    for(const auto & file : files)
    {
        fs::remove(file);
    }
}