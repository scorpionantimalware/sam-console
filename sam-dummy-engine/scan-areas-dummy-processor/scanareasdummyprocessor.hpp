#ifndef SAM_SCAN_AREAS_DUMMY_PROCESSOR_H
#define SAM_SCAN_AREAS_DUMMY_PROCESSOR_H

#include <string>
#include <vector>

typedef std::vector<std::string> pathls; // path lines are vector of strings.

const std::string SCAN_AREAS_FILENAME = "scanareasprocessor_output.pathl";

class ScanAreasDummyProcessor {
public:
    ScanAreasDummyProcessor() = default;
    ~ScanAreasDummyProcessor() = default;

    bool load_or_init(pathls& scan_areas);

    bool add_area([[maybe_unused]] const std::string& area);
};

#endif // SAM_SCAN_AREAS_DUMMY_PROCESSOR_H
