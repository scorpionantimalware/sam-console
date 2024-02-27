#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include <QHBoxLayout>

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    ControlBar();
    ~ControlBar();

signals:
    void scan_started();

private slots:
    void scan_button_clicked();

private:
    QHBoxLayout *main_layout;
    
};

#endif // CONTROLBAR_H
