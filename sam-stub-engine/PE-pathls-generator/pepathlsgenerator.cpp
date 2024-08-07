/**********************************************************************************/
/*                                                                                */
/* pepathlsgenerator.cpp (stub)                                                   */
/*                                                                                */
/**********************************************************************************/
/*                                                                                */
/*    Scorpion Anti-malware Console is a free Open Source Qt-powered frontend     */
/*    framework for SAM Engine.                                                   */
/*                                                                                */
/*    Copyright (c) 2024-present  (see AUTHORS.md).                               */
/*                                                                                */
/*    This program is free software: you can redistribute it and/or modify        */
/*    it under the terms of the GNU General Public License as published by        */
/*    the Free Software Foundation, either version 3 of the License, or           */
/*    (at your option) any later version.                                         */
/*                                                                                */
/*    This program is distributed in the hope that it will be useful,             */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of              */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               */
/*    GNU General Public License for more details.                                */
/*                                                                                */
/*    You should have received a copy of the GNU General Public License           */
/*    along with this program.  If not, see <https://www.gnu.org/licenses/>.      */
/*                                                                                */
/**********************************************************************************/

#include "pepathlsgenerator.hpp"

#include "pepathlscollector.hpp"

#include <fstream>
#include <iostream>

#include <filesystem>

namespace fs = std::filesystem;

PEPathlsGenerator::~PEPathlsGenerator() {
	PEPathlsGenerator::clean();
}

bool PEPathlsGenerator::clean() {
	bool status{ false };

	status = fs::exists(PE_PATHLS_FILENAME);

	if (!status) {
		return status;
	}

	status = fs::remove(PE_PATHLS_FILENAME);

	if (!status) {
		std::cerr << "Error: Unable to delete file " << PE_PATHLS_FILENAME << std::endl;
		return status;
	}

	status = true;
	return status;
}

bool PEPathlsGenerator::generate(const std::string &scan_area) {
	bool status{ false };
	PEPathlsCollector collector;
	pathls pathls_buffer;
	status = collector.collect(pathls_buffer, scan_area);
	if (!status) {
		return status;
	}

	const std::string pe_pathls_file{ PE_PATHLS_FILENAME };

	std::ofstream outfile(pe_pathls_file, std::ios_base::app); // Append mode.
	if (!outfile.is_open()) {
		std::cout << "Error: Unable to open file: " << pe_pathls_file << std::endl;
		return status;
	}

	for (const auto &path : pathls_buffer) {
		outfile << path << "\n";
	}

	outfile.close();

	status = true;

	return status;
}
