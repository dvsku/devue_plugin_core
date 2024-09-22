#pragma once

#include <vector>

namespace devue::sdk {
    struct devue_image {
        int32_t              width      = 0;
        int32_t              height     = 0;
        int8_t               components = 0;
        std::vector<uint8_t> data;
    };
}
