/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * status-viewer/resultsstreamviewer.hpp
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

#ifndef SAM_RESULTS_STREAM_VIEWER_HPP
#define SAM_RESULTS_STREAM_VIEWER_HPP

#include <QTableWidget>

class ResultsStreamViewer : public QTableWidget
{
public:
    ResultsStreamViewer();
    ~ResultsStreamViewer();

    void init();

    int add_row(const std::string& filename);

    void set_status_for_row(const int& row_index, const std::string& status, const float& prediction);

    void on_scan_fire();
    void on_scan_complete();
    int on_new_file(const std::string& filename);
    void on_status(const int& row_index, const float& prediction);

public slots:
    void on_scan_button_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief Update the column widths based on the table's width
    */
    void update_column_widths();
};

#endif // SAM_RESULTS_STREAM_VIEWER_HPP
