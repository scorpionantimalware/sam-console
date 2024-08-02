/**********************************************************************************/
/*                                                                                */
/* mainwindow.hpp                                                                 */
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

#ifndef SAM_MAIN_WINDOW_HPP
#define SAM_MAIN_WINDOW_HPP

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QWidget>

#include "samconsolemain.hpp"

#include "fimpage.hpp"
#include "homepage.hpp"
#include "pageswitcherbar.hpp"
#include "samconsolesplash.hpp"

class MainWindow : public QWidget {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	HomePage *get_home_page_p() const;
	FIMPage *get_fim_page_p() const;

private slots:
	void on_home_page_switch_button_clicked() const;
	void on_fim_page_switch_button_clicked() const;

private:
	SAMConsoleSplash *splash_screen;

	QHBoxLayout *main_layout;

	PageSwitcherBar *page_switcher_bar;

	QStackedWidget *pages_stack;

	HomePage *home_page;

	FIMPage *fim_page;

	void show_main_ui();
};

#endif // SAM_MAIN_WINDOW_HPP
