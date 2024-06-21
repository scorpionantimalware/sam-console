/**********************************************************************************/
/*                                                                                */
/* scanbutton.hpp                                                                 */
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


#ifndef SAM_SCAN_BUTTON_HPP
#define SAM_SCAN_BUTTON_HPP

#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>

class ScanButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int loading_arc_angle READ loading_arc_angle WRITE set_loading_arc_angle NOTIFY loading_arc_angle_changed)

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
