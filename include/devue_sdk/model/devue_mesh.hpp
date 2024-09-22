#pragma once

#include <string>
#include <vector>

namespace devue::sdk {
    struct devue_mesh {
        std::string           name           = "";
        uint64_t              material_index = 0U;
        std::vector<uint32_t> indices;
    };
}
