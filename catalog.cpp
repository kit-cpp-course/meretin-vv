#pragma once
#include "pch.h"
#include "catalog.h"
#include "Constants.h"
#include "functions.h"
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <boost\filesystem.hpp>

using namespace std;
using namespace ::boost::filesystem;

	Catalog::Catalog()
	{
		this->routes = map<const unsigned short, map<const string, map<const unsigned short, vector<path>>>>();
		this->brokenRoutes = vector<path>();
	}

	const void Catalog::_convertDate(const string route, unsigned short* year, string* month, unsigned short* day) 
	{
		try
		{
			FILETIME FT;
			if (!GetFileTime(CreateFileA(route.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL), &FT, NULL, NULL)) throw 11;
			SYSTEMTIME ST;
			if (!FileTimeToSystemTime(&FT, &ST)) throw 11;
			
			*year = ST.wYear;
			*month = constants::months[ST.wMonth - 1];
			*day = ST.wDay;
		}
		catch (runtime_error)
		{
			*year = 0; *month = "-"; *day = 0;
		}
	}


	void Catalog::Add(path route)
	{
		unsigned short year, day;
		string month;
		_convertDate(route.string(), &year, &month, &day);

		if (year != 0) {
			this->routes.insert({ year, map<const string, map<const unsigned short, vector<path>>>() });
			this->routes[year].insert({ month, map<const unsigned short, vector<path>>() });
			this->routes[year][month].insert({ day, vector<path>() });
			this->routes[year][month][day].push_back(route);
		}

		else brokenRoutes.push_back(route);
	}

	const void Catalog::_copyFiles(vector<path> files, const string month, const unsigned short day, string route, boost::filesystem::ofstream* info)
	{	
		if (files.size() > constants::maxNum) {
			route += "\\" + nameByDay(month, day);
			CreateDirectoryA(route.c_str(), NULL);
		}

		for (auto const file : files) {
			try {
				copy_file(file, path(route + "\\" + file.filename().string()));
				showStatus(file.string(), true);
				*info << "\t \t \t" << file.string() << "\n";
			}
			catch (runtime_error) {
				brokenRoutes.push_back(file);
				showStatus(file.string(), false);
			}
		}
	}

	const bool Catalog::CreateCatalog(const path route) 
	{
		string routeByYear, routeByMonth;
		boost::filesystem::ofstream info;
		info.open(path(route.string() + "\\" + constants::infoFile));

		try {
			for (auto const year : routes) {
				info << year.first << ":" << "\n";
				routeByYear = route.string() + "\\" + to_string(year.first);
				CreateDirectoryA(routeByYear.c_str(), NULL);

				for (auto const month : year.second) {
					info << "\t" << month.first << ":" << "\n";
					routeByMonth = routeByYear + "\\" + month.first;
					CreateDirectoryA(routeByMonth.c_str(), NULL);

					for (auto const day : month.second) {
						info << "\t \t" << day.first << ":" << "\n";
						_copyFiles(day.second, month.first, day.first, routeByMonth, &info);
					}
				}
			}

			if (brokenRoutes.size() > 0) {
				info << "\n" << constants::brokenFiles << "\n \n";
				for (auto const file : brokenRoutes) info << "\t" << file.string() << "\n";
			}
			
			info.close();
			return true;
		}
		catch (runtime_error) { return false; }
		
	}
