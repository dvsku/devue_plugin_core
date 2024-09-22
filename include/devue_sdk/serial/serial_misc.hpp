#pragma once

#include "devue_sdk/plugin/devue_plugin_desc.hpp"
#include "devue_sdk/misc/devue_ec.hpp"

#include <vector>

namespace devue::sdk {
    void encode(devue_plugin_desc& desc, std::vector<uint8_t>& buffer);
    void decode(devue_plugin_desc& desc, uint8_t* dst, uint64_t size);

    void encode(devue_ec& ec, std::vector<uint8_t>& buffer);
    void decode(devue_ec& ec, uint8_t* dst, uint64_t size);
}
