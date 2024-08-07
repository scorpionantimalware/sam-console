/**********************************************************************************/
/*                                                                                */
/* pepathlsgenerator.hpp (stub)                                                   */
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

#ifndef SAM_PE_PATHLS_STUB_GENERATOR_HPP
#define SAM_PE_PATHLS_STUB_GENERATOR_HPP

#include <string>

const std::string PE_PATHLS_FILENAME = "pepathlsgenerator_output.pathl";

class PEPathlsGenerator {
public:
	PEPathlsGenerator() = default;
	~PEPathlsGenerator();

	bool generate(const std::string &scan_area);

private:
	bool clean();
}; // class PEPathlsGenerator

#endif // SAM_PE_PATHLS_STUB_GENERATOR_HPP
