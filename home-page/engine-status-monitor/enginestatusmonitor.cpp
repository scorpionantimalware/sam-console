/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * enginestatusmonitor.cpp
 * 
 * Copyright (c) 2024-present Scorpion Anti-malware (see AUTHORS.md).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

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

