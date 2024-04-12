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

    float min_side {(float)qMin(width(), height())};

    QPointF center {QPointF(width() * 0.5, height() * 0.5)};

    float side {static_cast<float>(min_side * 0.4)}; // Side length of the square

    // Draw the square
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    
    painter.drawRect(center.x() - side * 0.5, center.y() - side * 0.5, side, side);
}
