#ifndef SCANBUTTON_H
#define SCANBUTTON_H

#include <QPushButton>
#include <QPainter>

class ScanButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ScanButton();
    ~ScanButton();

private:
    QPointF rotate_point(const QPointF& point, const QPointF& center, float angle);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCANBUTTON_H
