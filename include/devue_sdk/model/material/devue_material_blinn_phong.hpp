#pragma once

#include "devue_sdk/model/material/devue_material_phong.hpp"

namespace devue::sdk {
    struct devue_material_blinn_phong : devue_material_phong {
        devue_material_type get_type() override {
            return devue_material_type::blinn_phong;
        }
    };
}
