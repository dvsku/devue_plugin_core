#pragma once

#include "devue_image.hpp"

#include <vector>

namespace devue::sdk {
    void encode_image(devue_image& image, std::vector<uint8_t>& buffer);
    void decode_image(devue_image& image, uint8_t* dst, uint64_t size);
}
