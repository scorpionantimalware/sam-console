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

    QPointF center {width() * 0.5f, height() * 0.5f};

    float square_side_length {min_side * 0.4f}; // Side length of the square

    // Draw the square
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen); // Set the pen to Qt::NoPen to remove the stroke
    
    QRectF square {center - QPointF(square_side_length * 0.5f, square_side_length * 0.5f), QSizeF(square_side_length, square_side_length)};
    painter.drawRect(square);
}
