#pragma once

#include "devue_sdk/misc/devue_file_type.hpp"

#include <string>
#include <vector>

namespace devue::sdk {
    struct devue_plugin_desc {
        std::string name    = "";
        std::string author  = "";
        std::string website = "";
        std::string version = "";

        std::vector<devue_file_type> model_types = {};
        std::vector<devue_file_type> image_types = {};
    };
}
