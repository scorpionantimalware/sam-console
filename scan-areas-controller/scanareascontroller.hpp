/**
 *                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
 * 
 * scanareascontroller.hpp
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

#ifndef SCAN_AREAS_CONTROLLER_H
#define SCAN_AREAS_CONTROLLER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "scanareascolumn.hpp"

class ScanAreasController : public QWidget
{
    Q_OBJECT

public:
    explicit ScanAreasController(QWidget *parent = nullptr);
    ~ScanAreasController();

signals:
    /**
     * @brief Signal emitted when the new area button is clicked.
    */
    void new_area_button_clicked();

    /**
     * @brief Signal emitted when the edit area button is clicked.
    */
    void edit_area_button_clicked();

    /**
     * @brief Signal emitted when the browse area button is clicked.
     * 
     * @note This is used inside the @c ScanAreasColumn class. It adds
     *       a new area to the list of scan areas.
     * 
     * @note It calls the @c ScanAreasProcessor::add_area method.
     * 
     * @see @c scan-areas-processor/scanareasprocessor.hpp
     * @see @c ScanAreasColumn::on_browse_area_button_clicked
    */
    void browse_area_button_clicked();

    /**
     * @brief Signal emitted when the delete area button is clicked.
    */
    void delete_area_button_clicked();

private slots:
    /**
     * @brief Slot to add a new area.
    */
    void add_new_area();

    /**
     * @brief Slot to edit an area.
    */
    void edit_area();

    /**
     * @brief Slot to browse an area.
    */
    void browse_area();

    /**
     * @brief Slot to delete an area.
    */
    void delete_area();

private:
    QHBoxLayout *main_layout;

    ScanAreasColumn *scan_areas_column;

    QVBoxLayout *controller;

    QPushButton *new_area_button;
    QPushButton *edit_area_button;
    QPushButton *browse_area_button;
    QPushButton *delete_area_button;
};

#endif // SCAN_AREAS_CONTROLLER_H
