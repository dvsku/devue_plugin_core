#pragma once

#include "devue_sdk/model/material/devue_material.hpp"

#include <glm/glm.hpp>

namespace devue::sdk {
    struct devue_material_phong : devue_material {
        glm::vec3 color          = { 0.961f, 0.961f, 0.961f };
        glm::vec3 color_specular = { 0.067f, 0.067f, 0.067f };

        std::string color_map  = "";
        std::string normal_map = "";

        float shininess = 30.0f;

        virtual devue_material_type get_type() override {
            return devue_material_type::phong;
        }
    };
}
