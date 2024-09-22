#pragma once

#include "devue_model_col.hpp"

#include <vector>

namespace devue::sdk {
    void encode_models(devue_model_col& models, std::vector<uint8_t>& buffer);
    void decode_models(devue_model_col& models, uint8_t* dst, uint64_t size);
}

