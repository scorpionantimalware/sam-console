#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "scanbutton.hpp"
#include "stopbutton.hpp"
#include "pausebutton.hpp"
#include "scanareascontrollerbutton.hpp"

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    ControlBar();
    ~ControlBar();

signals:
    void scan_started();
    void scan_stopped();
    void scan_paused();
    void scan_areas_processor();

private slots:
    void scan_button_clicked();
    void stop_button_clicked();
    void pause_button_clicked();
    void scan_areas_processor_button_clicked();

private:
    QHBoxLayout *main_layout;

    ScanButton *scan_button;
    StopButton *stop_button;
    PauseButton *pause_button;
    ScanAreasControllerButton *scan_areas_processor_button;
    
};

#endif // CONTROLBAR_H
