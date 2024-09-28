#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <thread>

using namespace std;
using namespace filesystem;
set<string> findActivateFiles(time_t now, path strartPath ,time_t aliveTime =  604800000);


#endif