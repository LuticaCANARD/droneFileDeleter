#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <filesystem>


using namespace std;
using namespace filesystem;
set<string> findActivateFiles(time_t now, path startPath ,time_t aliveTime);
vector <string> getActivateFilesData(time_t aliveTime);

#endif // DATABASECONNECTOR_H