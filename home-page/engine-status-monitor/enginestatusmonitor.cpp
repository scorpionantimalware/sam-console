/**********************************************************************************/
/*                                                                                */
/* enginestatusmonitor.cpp                                                        */
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


#include "engine-status-monitor/enginestatusmonitor.hpp"

EngineStatusMonitor::EngineStatusMonitor()
{
    this->setReadOnly(true);

    // Set black background
    QPalette p = this->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    this->setPalette(p);

    QFont font = this->font();
    font.setPointSize(12); // Set font size to 12
    this->setFont(font);

}

void EngineStatusMonitor::append_message(const std::string& status_message, const sam_engine::SAMEngine::StatusMessageType& type) {
    // Determine the color based on the message type
    QColor color;
    switch (type) {
        case sam_engine::SAMEngine::StatusMessageType::INFO:
            color = QColor(Qt::white);
            break;
        case sam_engine::SAMEngine::StatusMessageType::WARNING:
            color = QColor(Qt::yellow);
            break;
        case sam_engine::SAMEngine::StatusMessageType::ERROR:
            color = QColor(Qt::red);
            break;
        default:
            color = QColor(Qt::white);
            break;
    }

    // Move the text cursor to the end
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);

    // Set the text color and append the message
    QTextCharFormat format;
    format.setForeground(color);
    cursor.setCharFormat(format);
    cursor.insertText(QString::fromStdString(status_message + "\n"));

    // Ensure the new text is visible
    this->ensureCursorVisible();
}

