#include "scanareasdummyprocessor.hpp"

bool ScanAreasDummyProcessor::load_or_init(pathls& scan_areas) {
    bool status {false};

    scan_areas.push_back("C:/pesamples1");
    scan_areas.push_back("C:/pesamples2");
    scan_areas.push_back("C:/pesamples3");

    status = true;

    return status;
}

bool ScanAreasDummyProcessor::add_area([[maybe_unused]] const std::string& area) {
    bool status {false};

    status = true;

    return status;
}
