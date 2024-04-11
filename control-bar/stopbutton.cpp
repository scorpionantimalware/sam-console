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

    float min_side = qMin(width(), height());

    QPointF center = QPointF(width() / 2, height() / 2);

    float side = min_side * 0.4; // Side length of the square

    // Draw the square
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    
    painter.drawRect(center.x() - side / 2, center.y() - side / 2, side, side);
}
