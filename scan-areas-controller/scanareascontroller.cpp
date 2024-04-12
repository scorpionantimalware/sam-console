#include "scanareascontroller.hpp"

ScanAreasController::ScanAreasController(QWidget *parent) : QWidget(parent), main_layout(nullptr), scan_areas_column(nullptr)
{
    ScanAreasController::main_layout = new QHBoxLayout(this);

    ScanAreasController::scan_areas_column = new ScanAreasColumn();

    ScanAreasController::main_layout->addWidget(ScanAreasController::scan_areas_column);

    ScanAreasController::controller = new QVBoxLayout();
    ScanAreasController::controller->setSpacing(10);
    ScanAreasController::controller->setAlignment(Qt::AlignTop);

    ScanAreasController::new_area_button = new QPushButton("New");
    ScanAreasController::edit_area_button = new QPushButton("Edit");
    ScanAreasController::browse_area_button = new QPushButton("Browse");
    ScanAreasController::delete_area_button = new QPushButton("Delete");

    ScanAreasController::controller->addWidget(ScanAreasController::new_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::edit_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::browse_area_button);
    ScanAreasController::controller->addWidget(ScanAreasController::delete_area_button);

    ScanAreasController::main_layout->addLayout(ScanAreasController::controller);

    this->connect(ScanAreasController::browse_area_button, &QPushButton::released, this, &ScanAreasController::browse_area);
    this->connect(this, &ScanAreasController::browse_area_button_clicked, scan_areas_column, &ScanAreasColumn::on_browse_area_button_clicked);
}

ScanAreasController::~ScanAreasController()
{
    if (ScanAreasController::scan_areas_column)
    {
        delete ScanAreasController::scan_areas_column;
        ScanAreasController::scan_areas_column = nullptr;
    }

    if (ScanAreasController::new_area_button)
    {
        delete ScanAreasController::new_area_button;
        ScanAreasController::new_area_button = nullptr;
    }

    if (ScanAreasController::edit_area_button)
    {
        delete ScanAreasController::edit_area_button;
        ScanAreasController::edit_area_button = nullptr;
    }

    if (ScanAreasController::browse_area_button)
    {
        delete ScanAreasController::browse_area_button;
        ScanAreasController::browse_area_button = nullptr;
    }

    if (ScanAreasController::delete_area_button)
    {
        delete ScanAreasController::delete_area_button;
        ScanAreasController::delete_area_button = nullptr;
    }

    if (ScanAreasController::controller)
    {
        delete ScanAreasController::controller;
        ScanAreasController::controller = nullptr;
    }

    if (ScanAreasController::main_layout)
    {
        delete ScanAreasController::main_layout;
        ScanAreasController::main_layout = nullptr;
    }
}

void ScanAreasController::add_new_area()
{
}

void ScanAreasController::edit_area()
{
}

void ScanAreasController::browse_area()
{
    emit browse_area_button_clicked();
}

void ScanAreasController::delete_area()
{
}
