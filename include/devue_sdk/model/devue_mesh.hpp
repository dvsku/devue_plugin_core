#pragma once

#include "devue_sdk/model/devue_vertex.hpp"
#include "devue_sdk/model/material/devue_material.hpp"
#include "devue_sdk/model/material/devue_material_phong.hpp"
#include "devue_sdk/model/material/devue_material_blinn_phong.hpp"

#include <string>
#include <vector>
#include <memory>

namespace devue::sdk {
    struct devue_mesh {
        std::string name = "";
        
        std::vector<devue_vertex> vertices;
        std::vector<uint32_t>     indices;

        std::shared_ptr<devue_material> material = nullptr;
    };
}
