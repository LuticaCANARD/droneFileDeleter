#include "database.h"
/// @brief 
/// @param now 탐색할 당시의 시간입니다.
/// @param aliveTime now로부터 몇 밀리초 이전에 생성된 파일들을 탐색할 것인지 결정합니다. 
/// @return 참조된 파일들의 (상대)경로를 반환합니다.
set<string> findActivateFiles(time_t now,path startPath ,time_t aliveTime = 604800000) 
{
    // 데이터베이스에서 파일들을 가져온다.
    vector<string> activateFilesData;

    // 쿼리 후 데이터를 직렬화.
    set<string> activateFiles;
    for(const auto & entry : activateFilesData)
    {
        activateFiles.insert(filesystem::absolute(startPath / entry).string());
    }

    return activateFiles;
}

vector <string> getActivateFilesData(time_t aliveTime)
{
    // 데이터베이스에서 파일들을 가져온다.
    vector<string> activateFilesData;

    return activateFilesData;
}