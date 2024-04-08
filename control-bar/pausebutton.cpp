#include "pausebutton.hpp"

#include <QWidget>

PauseButton::PauseButton()
{
    setFixedSize(100, 100);
}

PauseButton::~PauseButton()
{
    
}

void PauseButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter = QPainter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    double min_side = qMin(width(), height());

    QPointF center = QPointF(width() / 2, height() / 2);

    double separation = min_side * 0.2;

    QPen pen(Qt::black);
    pen.setWidth(min_side * 0.2);
    painter.setPen(pen);

    painter.drawLine(QPointF(center.x() - separation, center.y() - separation), QPointF(center.x() - separation, center.y() + separation));
    painter.drawLine(QPointF(center.x() + separation, center.y() - separation), QPointF(center.x() + separation, center.y() + separation));
}
