#pragma once
#include "pch.h"
#include <string>
#include <boost\filesystem.hpp>
#include <map>

using namespace std;
using namespace ::boost::filesystem;

	const bool isDirExists(const path folder);
	const bool shouldRepeat();
	const void inputAgain(path* folder);
	const bool isImage(const path route);
	const void showStatus(const string route ,const bool status);

	template<class number>
	const string nameByDay(const string month, number day)
	{
		if (day/10 >= 1 && day/10 < 2) return month + ' ' + to_string(day) + "th";

		switch (day % 10) {
			case (number)1:
				return month + ' ' + to_string(day) + "st";
			case (number)2:
				return month + ' ' + to_string(day) + "nd";
			case (number)3:
				return month + ' ' + to_string(day) + "rd";
			default:
				return month + ' ' + to_string(day) + "th";
		}
	}