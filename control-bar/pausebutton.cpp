#include "pausebutton.hpp"

#include <QWidget>

PauseButton::PauseButton()
{
    this->setFixedSize(100, 100);
}

PauseButton::~PauseButton()
{
    
}

void PauseButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float min_side {(float)qMin(width(), height())};

    // Use Multiplication instead of Division as it is faster
    QPointF center {QPointF(width() * 0.5f, height() * 0.5f)};

    float separation {min_side * 0.15f};
    float pen_width {separation};

    QPen pen(Qt::black);
    pen.setWidth(pen_width);
    painter.setPen(pen);

    painter.drawLine(QPointF(center.x() - separation, center.y() - separation), QPointF(center.x() - separation, center.y() + separation));
    painter.drawLine(QPointF(center.x() + separation, center.y() - separation), QPointF(center.x() + separation, center.y() + separation));
}
