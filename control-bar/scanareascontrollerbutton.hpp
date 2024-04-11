#ifndef SCANAREASPROCESSORBUTTON_H
#define SCANAREASPROCESSORBUTTON_H

#include <QPushButton>
#include <QPainter>

class ScanAreasControllerButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ScanAreasControllerButton();
    ~ScanAreasControllerButton();

private:

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCANAREASPROCESSORBUTTON_H
