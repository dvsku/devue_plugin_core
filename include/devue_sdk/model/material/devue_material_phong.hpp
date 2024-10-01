#pragma once

#include "devue_sdk/model/material/devue_material.hpp"

namespace devue::sdk {
    struct devue_material_phong : devue_material {
        std::string color_map = "";

        devue_material_type get_type() override {
            return devue_material_type::phong;
        }
    };
}
