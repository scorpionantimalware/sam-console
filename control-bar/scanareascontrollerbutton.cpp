#include "scanareascontrollerbutton.hpp"

#include <QWidget>

ScanAreasControllerButton::ScanAreasControllerButton()
{
    this->setFixedSize(150, 100);
}

ScanAreasControllerButton::~ScanAreasControllerButton()
{
    
}

void ScanAreasControllerButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};

    QPointF center {QPointF(width() * 0.5f, height() * 0.5f)};

    QPen pen(Qt::SolidLine); // Set pen style to SolidLine
    pen.setColor(Qt::black); // Set pen color
    pen.setWidth(8); // Set pen width to control stroke thickness
    painter.setPen(pen);

    // Draw the lens.
    QPointF lens_circle_center {center - QPointF(min_side * 0.1f, min_side * 0.1f)};
    float lens_circle_radius {min_side * 0.2f};
    painter.drawEllipse(lens_circle_center, lens_circle_radius, lens_circle_radius);

    // Draw the line.
    QPointF line_start {lens_circle_center + QPointF(lens_circle_radius, lens_circle_radius)};
    QPointF line_end {center + QPointF(lens_circle_radius, lens_circle_radius)};
    painter.drawLine(line_start, line_end);
}
