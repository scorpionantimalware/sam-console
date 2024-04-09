#include "stopbutton.hpp"

#include <QWidget>

StopButton::StopButton()
{
    this->setFixedSize(100, 100);
}

StopButton::~StopButton()
{
}

void StopButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    double min_side = qMin(width(), height());

    QPointF center = QPointF(width() / 2, height() / 2);

    double radius = min_side * 0.3; // Radius of the circle

    // Draw the circle
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    painter.drawEllipse(QPointF(center.x(), center.y()), radius, radius);
}
