#pragma once

#include "devue_vertex.hpp"
#include "devue_mesh.hpp"
#include "devue_material.hpp"

namespace devue::sdk {
    struct devue_model {
        std::vector<devue_vertex>   vertices;
    	std::vector<devue_mesh>     meshes;
        std::vector<devue_material> materials;
    };
}
