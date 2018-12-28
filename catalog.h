#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <map>
#include <boost\filesystem.hpp>

using namespace std;
using namespace ::boost::filesystem;

class Catalog
{
private:
	map<const unsigned short, map<const string, map<const unsigned short, vector<path>>>> routes; // This structure contains paths to all element sorted by year, month and day.
	vector<path> brokenRoutes;
	const void _convertDate(const string route, unsigned short* year, string* month, unsigned short* day);
	const void _copyFiles(vector<path> files,const string month, const unsigned short day, string route ,boost::filesystem::ofstream* info);

public:
	Catalog();
	void Add(path route);
	const bool CreateCatalog(const path route);
};