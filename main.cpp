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

					GetFolderFiles(folderName);
				}
			}
		}
	}
	std::cout << "All files have been sorted!" << std::endl <<"Press any key to close";

	getchar();
}

// iterates thru folder and list files
VOID GetFolderFiles(PWSTR folderName)
{
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

		FillVectorFromFile(fileData.cFileName);

	} while (::FindNextFile(hCurFile, &fileData) != 0);
	return;
}


// fill vector from the file
VOID FillVectorFromFile(const wchar_t* fileName)
{
	std::vector<int> myVector;

	std::ifstream inFile(fileName);
	std::string line;

	// read each line and conver to int
	while (std::getline(inFile, line)) {
		myVector.push_back(std::stoi(line));
	}
		
	std::wcout << fileName << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	shell_sort(myVector);
	//insertion_sort(myVector);
	auto elapsed = std::chrono::high_resolution_clock::now() - start;

	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

	std::cout << milliseconds <<" ms "<< std::endl;
	std::cout << std::endl;

	//print(myVector);
}


