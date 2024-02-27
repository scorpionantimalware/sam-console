#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <QPushButton>
#include <QPainter>

class PauseButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PauseButton();
    ~PauseButton();

private:

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // PAUSEBUTTON_H
