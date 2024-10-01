#pragma once

#include "devue_sdk/model/devue_mesh.hpp"

#include <string>

namespace devue::sdk {
    struct devue_model {
        std::string name = "";

    	std::vector<devue_mesh> meshes;
    };
}
