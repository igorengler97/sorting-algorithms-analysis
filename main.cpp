#include "Header.h"


int main()
{
	std::cout << "Select the folder containing the files to be sorted" << std::endl;
	// Initialize COM object for folder selection
	HRESULT hResultCom = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hResultCom))
	{
		IFileOpenDialog* pFile;

		hResultCom = ::CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
			IID_IFileOpenDialog, (void**)(&pFile));

		if (SUCCEEDED(hResultCom))
		{
			// show window
			DWORD myOptions;

			if (SUCCEEDED(pFile->GetOptions(&myOptions)))
				// choose folders instead of files
				pFile->SetOptions(myOptions | FOS_PICKFOLDERS);

			// show select dialog
			hResultCom = pFile->Show(nullptr);

			IShellItem* shellItem;

			hResultCom = pFile->GetResult(&shellItem);

			if (SUCCEEDED(hResultCom))
			{
				PWSTR folderName;

				hResultCom = shellItem->GetDisplayName(SIGDN_FILESYSPATH, &folderName);

				if (SUCCEEDED(hResultCom))
				{
					MessageBox(NULL, folderName, L"Got", MB_OK);

					if (!SetCurrentDirectory(folderName))
						::MessageBox(nullptr, L"Failed to set current directory", L"Error", MB_OK);
					system("CLS");
					GetFolderFiles(folderName);
				}
			}
		}
	}
	std::cout << "All files have been sorted!" << std::endl <<"Press ENTER key to close";

	getchar();
}

// iterates thru folder and list files
VOID GetFolderFiles(PWSTR folderName)
{
	int opt;
	std::cout << "press 1 for ShellSort and 2 for InsertionSort: ";
	do {
		std::cin >> opt;
	} while (opt < 1 || opt > 2);
	
	WIN32_FIND_DATA fileData;

	wchar_t newFolder[1024];

	// search everything inside the folder
	wcsncpy_s(newFolder, folderName, 1024);
	wcscat_s(newFolder, L"\\*");

	HANDLE hCurFile = ::FindFirstFile(newFolder, &fileData);

	do {

		if (hCurFile == INVALID_HANDLE_VALUE)
		{
			::MessageBox(nullptr, L"Failed to search file", L"ERROR", MB_OK);
			return;
		}
		// ignore directory inside directory, e.g (., ..)
		else if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		FillVectorFromFile(fileData.cFileName, opt);
		
	} while (::FindNextFile(hCurFile, &fileData) != 0);
	return;
}


// fill vector from the file
VOID FillVectorFromFile(const wchar_t* fileName, int opt)
{
	int aux_name;
	double milliseconds;
	long long microseconds;
	std::vector<int> myVector;

	std::ifstream inFile(fileName);
	std::string line;

	std::wstring ws(fileName);
	std::string file_name(ws.begin(), ws.end());

	if (file_name.substr(file_name.find_last_of(".") + 1) == "txt") {
		// read each line and conver to int
		while (std::getline(inFile, line)) {
			myVector.push_back(std::stoi(line));
		}

		std::cout << file_name << std::endl;

		if (opt == 1) {
			auto start = std::chrono::steady_clock::now();
			shell_sort(myVector);
			auto elapsed = std::chrono::steady_clock::now();
			microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed - start).count();
			aux_name = 1;
		}
		else if (opt ==2){
			auto start = std::chrono::steady_clock::now();
			insertion_sort(myVector);
			auto elapsed = std::chrono::steady_clock::now();
			microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed - start).count();
			aux_name = 2;
		}
		milliseconds = double(microseconds) / 1000;
		std::cout << milliseconds << " ms\n" << std::endl;
		
		SaveInFile(aux_name, milliseconds, file_name);	
	}
	
}

VOID SaveInFile(int aux_name, double milliseconds, std::string file_name) {
	std::ofstream of("output.csv", std::ios::app);

	switch (aux_name) {
	case 1:
		of << "shellsort;" << file_name << ";" << milliseconds << ";" << std::endl;
		break;
	case 2:
		of << "insertionsort;" << file_name << "; " << milliseconds << "; " << std::endl;
		break;
	}
	of.close();
}