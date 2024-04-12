#ifndef SCAN_AREAS_PROCESSOR_BUTTON_H
#define SCAN_AREAS_PROCESSOR_BUTTON_H

#include <QPushButton>
#include <QPainter>

class ScanAreasControllerButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ScanAreasControllerButton();
    ~ScanAreasControllerButton();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCAN_AREAS_PROCESSOR_BUTTON_H
