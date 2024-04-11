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

    float min_side = qMin(width(), height());

    QPointF center = QPointF(width() / 2, height() / 2);

    float separation = min_side * 0.15;
    float pen_width = separation;

    QPen pen(Qt::black);
    pen.setWidth(pen_width);
    painter.setPen(pen);

    painter.drawLine(QPointF(center.x() - separation, center.y() - separation), QPointF(center.x() - separation, center.y() + separation));
    painter.drawLine(QPointF(center.x() + separation, center.y() - separation), QPointF(center.x() + separation, center.y() + separation));
}
