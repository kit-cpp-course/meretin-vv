#pragma once
#include "pch.h"
#include "Constants.h"
#include "functions.h"
#include "catalog.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <boost\filesystem.hpp>

using namespace std;
using namespace constants;
using namespace::boost::filesystem;

int main()
{
	start:
	string fFolder, sFolder;
	path fromFolder, toFolder;

	cout << inputWarning << "\n" << enterFromFolder << "\n \n";
	getline(cin, fFolder);
	fromFolder = path(fFolder);
	while (!isDirExists(fromFolder)) inputAgain(&fromFolder); // For incorrect input.

	cout << "\n" << newFolderWarning << "\n" << enterToFolder << "\n \n";
	getline(cin, sFolder);
	toFolder = path(sFolder);
	while (!isDirExists(toFolder) && !CreateDirectoryA(sFolder.c_str(), NULL))  inputAgain(&toFolder); // When folder doesn't exists and cannot be created.

	fFolder.clear(); sFolder.clear();
	cout << "\n" << working << "\n";

	Catalog myCatalog = Catalog();
	recursive_directory_iterator it(fromFolder);
	recursive_directory_iterator theEnd;

	try {
		while (it != theEnd) {
			if (isImage(it->path())) myCatalog.Add(it->path()); 
			it++;
		}
	}

	catch (runtime_error) {
		cout << errorMessage << "\n";
		if (shouldRepeat()) goto start;
		else return 0;
	}

	if (!myCatalog.CreateCatalog(toFolder)) cout << "\n" << errorMessage << "\n" << "\n";

	if (shouldRepeat()) goto start;
	else return 0;

};
