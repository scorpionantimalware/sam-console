#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H

#include <QPushButton>
#include <QPainter>

class PauseButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PauseButton();
    ~PauseButton();
    
protected:
    void paintEvent(QPaintEvent *event) override;

private:

};

#endif // PAUSE_BUTTON_H
