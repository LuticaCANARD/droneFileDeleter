#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <thread>
#include <iostream>
#include "./src/model/database/database.h"
#include "./src/utils/processSystem.h"
#include "./src/model/file/filefinder.h"

using namespace std;

void showDesc(time_t time)
{
    cout << "FILE GC" << endl;
    cout << "This program is to delete files that are not in the list of valid files." << endl;
    cout << "exectue time (UTC) : " << time << " / " << endl;
}
void viewHelp(string processName)
{
    cout << "GC" << endl;
    cout << "This program is to delete files that are not in the list of valid files." << endl;
    cout << "Usage: $ " << processName <<" [absolute path of directory]" << endl;
}

int main(int argc, char *argv[])
{
    std::string current_exec_name = argv[0]; // Name of the current exec program
    std::vector<std::string> all_args;
    if (argc <= 1) {
    // 실행시 인자가 없을 때
        cout << "You need to input the path to the directory you want to search." << endl;
        cout << "Do try : $ " << current_exec_name << " [absolute path of directory]" << endl;
        return 1;
    }
    all_args.assign(argv + 1, argv + argc);

    if(all_args[1] == "-h" || all_args[1] == "--help")
    {
        viewHelp(current_exec_name);
        return 0;
    }
    time_t now = time(NULL);
    showDesc(now);
    if(all_args[1].find("://") == string::npos)
    {
        // 절대경로가 아니다
        cout << "You need to input the absolute path to the directory you want to search." << endl;
        return 1;
    }
    filesystem::path startPath = all_args[1];
    vector<path> path_tasks;
    ProcessSystem::init(path_tasks ,100);
    if(!filesystem::exists(startPath))
    {
        cout << "The directory you want to search does not exist." << endl;
        return 1;
    }
    set<string> validFiles = findActivateFiles(now,startPath);
    int deleteCount = findAndDeleteFilesInDirectory(all_args[1], validFiles,false);
    cout << "The number of files deleted is " << deleteCount << endl;
    
    return 0;
}