#pragma once

#include "devue_sdk/model/devue_model.hpp"

#include <vector>

namespace devue::sdk {
    void encode(devue_model& model, std::vector<uint8_t>& buffer);
    void decode(devue_model& model, uint8_t* dst, uint64_t size);
}

