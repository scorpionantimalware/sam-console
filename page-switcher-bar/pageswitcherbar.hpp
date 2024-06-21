/**********************************************************************************/
/*                                                                                */
/* pageswitcherbar.hpp                                                            */
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


#ifndef SAM_PAGE_SWITCHER_BAR_HPP
#define SAM_PAGE_SWITCHER_BAR_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class PageSwitcherBar : public QWidget
{
    Q_OBJECT

public:
    explicit PageSwitcherBar(QWidget *parent = nullptr);
    ~PageSwitcherBar();

signals:
    void home_page_switch_button_clicked();
    void fim_page_switch_button_clicked();

private slots:
    void switch_to_home_page();

    /**
     * @brief File Integrity Manager or FIM is a feature that allows users to
     *        monitor changes to files and directories. This function shows the
     *        FIM page. 
     * 
     */
    void switch_to_fim_page();

private:
    QVBoxLayout *main_layout;

    QPushButton *home_page_button;
    QPushButton *fim_page_button;

    // TODO: Add About page
};

#endif // SAM_PAGE_SWITCHER_BAR_HPP
