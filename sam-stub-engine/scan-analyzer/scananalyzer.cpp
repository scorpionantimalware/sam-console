/**********************************************************************************/
/*                                                                                */
/* scananalyzer.cpp (stub)                                                        */
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

#include "scananalyzer.hpp"

void ScanAnalyzer::add_malware_pathl(const std::string &pathl) {
	std::lock_guard<std::mutex> lock(ScanAnalyzer::malware_pathls_mtx);
	ScanAnalyzer::malware_pathls.push_back(pathl);
}

void ScanAnalyzer::add_benign_pathl(const std::string &pathl) {
	std::lock_guard<std::mutex> lock(ScanAnalyzer::benign_pathls_mtx);
	ScanAnalyzer::benign_pathls.push_back(pathl);
}

size_t ScanAnalyzer::get_malware_count() {
	std::lock_guard<std::mutex> lock(ScanAnalyzer::malware_pathls_mtx);
	return ScanAnalyzer::malware_pathls.size();
}

size_t ScanAnalyzer::get_benign_count() {
	std::lock_guard<std::mutex> lock(ScanAnalyzer::benign_pathls_mtx);
	return ScanAnalyzer::benign_pathls.size();
}
