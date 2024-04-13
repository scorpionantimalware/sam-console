#include "scanbutton.hpp"

#include <QWidget>

ScanButton::ScanButton()
{
    this->setFixedSize(100, 100);
}

ScanButton::~ScanButton()
{
}

void ScanButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};
    
    QPointF center {width() * 0.5f, height() * 0.5f};

    float vc_length {min_side * 0.25f}; // Length from each triangle's vertex to the center of the widget

    // Calculate the vertices of the triangle based on the center of the widget
    QPointF top_v {center + QPointF(vc_length, 0)};
    QPointF bottom_left_v {center - QPointF(vc_length, vc_length)};
    QPointF bottom_right_v {center - QPointF(vc_length, -vc_length)};

    // Draw the triangle
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    painter.drawPolygon(QPolygonF() << top_v << bottom_left_v << bottom_right_v);
}
