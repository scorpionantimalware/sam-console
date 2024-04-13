#ifndef SCAN_BUTTON_H
#define SCAN_BUTTON_H

#include <QPushButton>
#include <QPainter>

class ScanButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ScanButton();
    ~ScanButton();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCAN_BUTTON_H
