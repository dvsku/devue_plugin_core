#pragma once

#include "devue_model.hpp"

#include <vector>

namespace devue::sdk {
    struct devue_model_col {
        std::vector<devue_model> models;
    };
}
