/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * statusbuiltinterminal.cpp
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

#include "statusbuiltinterminal.hpp"
#include <QScrollBar>

StatusBuiltinTerminal::StatusBuiltinTerminal(QWidget *parent) : QTextEdit(parent)
{
    this->setReadOnly(true);

    // Set black background
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    this->setPalette(p);
}

void StatusBuiltinTerminal::append_message(const std::string& status, const sam_engine::SAMEngineStatusMessage& message_type)
{
    QColor color;

    switch (message_type) {
        case sam_engine::SAMEngineStatusMessage::INFO:
            color = Qt::white;
            break;
        case sam_engine::SAMEngineStatusMessage::CLEAN_FILE:
            color = Qt::green;
            break;
        case sam_engine::SAMEngineStatusMessage::SUSPICIOUS_FILE:
        case sam_engine::SAMEngineStatusMessage::ERROR:
            color = Qt::red;
            break;
    }

    // Append message to the text edit with the specified color
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(QString("<font color=\"%1\">%2</font><br>").arg(color.name(), QString::fromStdString(status)));
    this->setTextCursor(cursor);

    // Scroll to the bottom
    QScrollBar *scrollBar = verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

