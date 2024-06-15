/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanbutton.hpp - A class that represents the scan button in the control bar.
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

#ifndef SAM_SCAN_BUTTON_HPP
#define SAM_SCAN_BUTTON_HPP

#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>

class ScanButton : public QPushButton
{
    Q_OBJECT
    // Q_PROPERTY(int loading_arc_angle READ loading_arc_angle WRITE set_loading_arc_angle NOTIFY loading_arc_angle_changed)

public:
    explicit ScanButton();
    ~ScanButton();

    enum class TextureState
    {
        IDLE,
        SCANNING,
        ERROR
    };

    void set_state(const ScanButton::TextureState& new_state);

    int loading_arc_angle() const;
    void set_loading_arc_angle(const int& angle);

signals:
    void loading_arc_angle_changed();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TextureState state;
    int current_loading_arc_angle;
    
    QPropertyAnimation* loading_arc_animator;
};

#endif // SAM_SCAN_BUTTON_HPP
