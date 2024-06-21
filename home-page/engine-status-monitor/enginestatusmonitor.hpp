/**********************************************************************************/
/*                                                                                */
/* enginestatusmonitor.hpp                                                        */
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


#ifndef SAM_ENGINE_STATUS_MONITOR_HPP
#define SAM_ENGINE_STATUS_MONITOR_HPP

#include <QTextEdit>

#include "samconsolemain.hpp"

class EngineStatusMonitor : public QTextEdit
{
    Q_OBJECT

public:
    explicit EngineStatusMonitor();

    void append_message(const std::string& status_message, const sam_engine::SAMEngine::StatusMessageType& type = sam_engine::SAMEngine::StatusMessageType::INFO);
};

#endif // SAM_ENGINE_STATUS_MONITOR_HPP
