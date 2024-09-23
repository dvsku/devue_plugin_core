#pragma once

#include "devue_sdk/model/devue_model_pack.hpp"

#include <vector>

namespace devue::sdk {
    void encode(devue_model_pack& models, std::vector<uint8_t>& buffer);
    void decode(devue_model_pack& models, uint8_t* dst, uint64_t size);
}

