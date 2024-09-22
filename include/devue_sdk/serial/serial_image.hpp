#pragma once

#include "devue_sdk/image/devue_image.hpp"

#include <vector>

namespace devue::sdk {
    void encode(devue_image& image, std::vector<uint8_t>& buffer);
    void decode(devue_image& image, uint8_t* dst, uint64_t size);
}
