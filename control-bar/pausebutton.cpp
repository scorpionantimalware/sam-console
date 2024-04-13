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
    QPointF center {width() * 0.5f, height() * 0.5f};

    float max_height {min_side * 0.18f}; // Max height of the pause symbol from the center.
    float separation {min_side * 0.15f};
    float pen_width {separation};

    QPen pen(Qt::black);
    pen.setWidth(pen_width);
    painter.setPen(pen);

    /*
        From top to bottom, draw the left part.
    */
    painter.drawLine(center - QPointF(separation, max_height), center - QPointF(separation, -max_height));

    /*
        From top to bottom, draw the right part.
    */
    painter.drawLine(center + QPointF(separation, -max_height), center + QPointF(separation, max_height));
}
