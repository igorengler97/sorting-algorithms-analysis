#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <Windows.h>
#include <ShObjIdl.h>
#include <string>
#include <shlobj_core.h>
#include <chrono>


VOID GetFolderFiles(PWSTR folderName);
void insertion_sort(std::vector<int>& vec);
void print(std::vector<int>& vec);
void shell_sort(std::vector<int>& vec);
VOID FillVectorFromFile(const wchar_t* fileName);