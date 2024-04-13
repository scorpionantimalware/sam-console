#include "scanareascontrollerbutton.hpp"

#include <QWidget>
#include <cmath>

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

    QPointF center {width() * 0.5f, height() * 0.5f};

    QPen pen(Qt::SolidLine); // Set pen style to SolidLine
    pen.setColor(Qt::black); // Set pen color
    pen.setWidth(min_side * 0.08f); // Set pen width to control stroke thickness
    painter.setPen(pen);

    // Draw the lens.
    QPointF lens_circle_center {center - QPointF(min_side * 0.1f, min_side * 0.1f)};
    float lens_circle_radius {min_side * 0.22f};
    painter.drawEllipse(lens_circle_center, lens_circle_radius, lens_circle_radius);

    // Draw the line.

    /*
        Here we start from the circle boundary (we get the circle boundary by adding the radius
        on the lens' center toward -45 direction).
    */
    float direction {qDegreesToRadians(45.0f)};
    QPointF line_start {lens_circle_center + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction))};

    /*
        Here we add the radius to the line start point (toward -45 direction) to get the 
        line end point.
    */
    QPointF line_end {line_start + QPointF(lens_circle_radius * cos(direction), lens_circle_radius * sin(direction))};
    painter.drawLine(line_start, line_end);
}
