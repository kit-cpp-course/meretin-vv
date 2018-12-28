#pragma once
#include "pch.h"
#include "functions.h"
#include "Constants.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <boost/filesystem.hpp>


using namespace std;
using namespace constants;
using namespace ::boost::filesystem;

const bool isDirExists(const path folder) // Checking if the path is correct.
{
	try {
		if (exists(folder) && is_directory(folder)) return true;
		else return false;
	}

	catch(runtime_error) { 
		return false;
	}
};

const bool shouldRepeat()
{
	cout <<"\n" << tryAgain << "\n";
	string answer;
	
	while (true) {
		cin >> answer;
		if (answer == "Y" || answer == "y") return true;
		if (answer == "N" || answer == "n") return false;
		cout << "\n" << incorrectAnswer << "\n";
	}

}

const void inputAgain(path* folder) // Repeat input.
{
	string input;
	cout << wrongInput << endl;
	getline(cin, input);
	*folder = path(input);
}

const bool isImage(const path route)
{
	if (route.extension().string().empty() || !is_regular_file(route)) return false;
	
	string ext = route.extension().string();
	short j = sizeof(imgExt);

	for (short i = 0; i < j; i++) {
		if (ext == imgExt[i]) return true;
	}
	
	return false;
}

const void showStatus(const string route, const bool status)
{
	if (status) cout << "\n" << route << success << "\n";
	else cout << "\n" << route << failure << "\n";
}