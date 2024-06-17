/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * pageswitcherbar.hpp
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
};

#endif // SAM_PAGE_SWITCHER_BAR_HPP
