#include "statusviewer.hpp"

#include <iostream>

#include "samdummyengine.hpp"

// If the real engine is active, include the real engine.
#ifdef SAM_ENGINE_ACTIVE
#include "samengine.hpp"
#elif SAM_DUMMY_ENGINE_ACTIVE // If the dummy engine is active, include the dummy engine.
#include "samdummyengine.hpp"
typedef SAMDummyEngine SAMEngine;
#else // If no engine is active, throw an error.
#error "No engine found"
#endif

StatusViewer::StatusViewer() : main_layout(nullptr), progress_bar(nullptr), summary(nullptr)
{
    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(10);
    
    progress_bar = new QProgressBar();
    progress_bar->setRange(0, 0); // Indeterminate progress
    progress_bar->setAlignment(Qt::AlignCenter); // Center align the progress bar
    
    summary = new Summary();

    main_layout->addWidget(progress_bar, 1);
    main_layout->addWidget(summary, 1);

    this->setEnabled(false);
}

StatusViewer::~StatusViewer()
{
    if (progress_bar)
    {
        delete progress_bar;
        progress_bar = nullptr;
    }

    if (summary)
    {
        delete summary;
        summary = nullptr;
    }
}

void StatusViewer::on_scan_clicked()
{
    this->setEnabled(true);
    std::cout << "Scanning..." << std::endl;
    SAMEngine engine;
    engine.scan();
}
