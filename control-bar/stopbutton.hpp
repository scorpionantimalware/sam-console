#ifndef STOPBUTTON_H
#define STOPBUTTON_H

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

#endif // STOPBUTTON_H
