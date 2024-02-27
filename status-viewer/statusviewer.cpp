#include "statusviewer.h"

#include "summary.h"

#include <QProgressBar>

#include <iostream>

StatusViewer::StatusViewer()
{
    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(10);
    
    Summary *summary = new Summary();

    QProgressBar *progress_bar = new QProgressBar();
    progress_bar->setRange(0, 0); // Indeterminate progress
    progress_bar->setAlignment(Qt::AlignCenter); // Center align the progress bar

    main_layout->addWidget(progress_bar, 1);
    main_layout->addWidget(summary, 1);

    setEnabled(false);
}

StatusViewer::~StatusViewer()
{
    
}

void StatusViewer::on_scan_clicked()
{
    setEnabled(true);
    std::cout << "Scan clicked" << std::endl;
}
