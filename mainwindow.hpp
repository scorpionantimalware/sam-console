#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>

#include "samconsolemain.hpp"

#include "control-bar/controlbar.hpp"
#include "status-viewer/statusviewer.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    StatusViewer* get_status_viewer();

private:
    QVBoxLayout *main_layout;

    ControlBar* control_bar;
    StatusViewer* status_viewer;
};

#endif // MAINWINDOW_H
