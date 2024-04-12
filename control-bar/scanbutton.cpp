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
    
    QPointF center {QPointF(width() * 0.5f, height() * 0.5f)};

    float vc_length {min_side * 0.25f}; // Length from each triangle's vertex to the center of the widget

    // Calculate the vertices of the triangle based on the center of the widget
    QPointF v1 {QPointF(center.x(), center.y() - vc_length)};
    QPointF v2 {QPointF(center.x() - vc_length, center.y() + vc_length)};
    QPointF v3 {QPointF(center.x() + vc_length, center.y() + vc_length)};

    // Rotate the triangle vertices by 90 degrees clockwise around the center of the widget
    float angle {90}; // Rotation angle in degrees
    float radian {qDegreesToRadians(angle)};
    v1 = rotate_point(v1, center, radian);
    v2 = rotate_point(v2, center, radian);
    v3 = rotate_point(v3, center, radian);

    // Draw the triangle
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    painter.drawPolygon(QPolygonF() << v1 << v2 << v3);
}

QPointF ScanButton::rotate_point(const QPointF& point, const QPointF& center, float angle)
{
    // Rotate a point around a center point by a given angle in radians
    float s {sin(angle)};
    float c {cos(angle)};
    float x {static_cast<float>(point.x() - center.x())};
    float y {static_cast<float>(point.y() - center.y())};
    float new_x {x * c - y * s};
    float new_y {x * s + y * c};
    return QPointF(new_x + center.x(), new_y + center.y());
}
