#include "scanareascontrollerbutton.hpp"

#include <QWidget>

ScanAreasControllerButton::ScanAreasControllerButton()
{
    this->setFixedSize(150, 100);
}

ScanAreasControllerButton::~ScanAreasControllerButton()
{
    
}

void ScanAreasControllerButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);

    float min_side = qMin(width(), height());

    int font_size = min_side / 4.0;

    QFont font("Arial", font_size);
    font.setBold(true);
    painter.setFont(font);

    QString text = "AREAS";
    QRect text_rect = painter.boundingRect(rect(), Qt::AlignCenter, text); // Calculate the bounding rectangle for the text

    int x = (width() - text_rect.width()) / 2; // Calculate the x-coordinate for centering
    int y = (height() + text_rect.height()) / 2; // Calculate the y-coordinate for centering

    painter.drawText(x, y, text); // Draw the text at the center position
}
