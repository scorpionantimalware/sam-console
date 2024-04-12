#ifndef STOP_BUTTON_H
#define STOP_BUTTON_H

#include <QPushButton>
#include <QPainter>

class StopButton : public QPushButton
{
    Q_OBJECT

public:
    explicit StopButton();
    ~StopButton();

protected:
    void paintEvent(QPaintEvent *event) override;
    
private:

};

#endif // STOP_BUTTON_H
