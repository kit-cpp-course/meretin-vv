#pragma once
#include "pch.h"
#include <string>

namespace constants {

	const std::string tryAgain = "Want to try again? (Y/N)";
	const std::string incorrectAnswer = "Incorrect answer. Type 'Y' for 'Yes' or 'N' for 'No': ";
	const std::string enterFromFolder = "Enter the path to directory with files for sorting: ";
	const std::string inputWarning = "Note: path cannot contain non-english letters!";
	const std::string newFolderWarning = "Note: if you enter nothing but a folder name, the folder with that name will be created in the software directory.";
	const std::string wrongInput = "Incorrect path. Try again: ";
	const std::string enterToFolder = "Enter the path to directory where sorted files should be saved: ";
	const std::string errorMessage = "Something went wrong.";
	const std::string working = "...Working...";
	const std::string infoFile = "Info.txt";
	const std::string brokenFiles = "Uncategorized due to an error and ignored:";
	const std::string failure = " - Failure =(";
	const std::string success = " - Success!";

	const std::string imgExt[] = { ".jpg", ".jfif", ".jpeg2000", ".exif", ".tiff", ".tif" ".gif", ".bmp", ".png", ".ppm", ".pgm", ".pbm", ".pnm", ".webp", ".raw",
										".hdr", ".heif", ".bat", ".bpg", ".cgm", ".svg", ".cr2", ".nef", ".orf", ".sr2" }; // 25 types.

	const std::string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	const short maxNum = 3; // Max number of images before a special folder is created for that day.
}