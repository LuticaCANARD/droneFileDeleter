#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <thread>
#include <filesystem>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;


int findAndDeleteFilesInDirectory(string startPath, set<string> vaildFiles,bool isRecursive);
vector<fs::path> getUnvaildFilesInDirectory(string startPath, set<string> vaildFiles);
static void deleteFiles(vector<fs::path> files);

#endif