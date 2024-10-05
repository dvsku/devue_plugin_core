#pragma once

#include <glm/glm.hpp>

namespace devue::sdk {
    struct devue_vertex {
        glm::vec3 position{};
        glm::vec3 normal{};
        glm::vec2 uv{};
    };
}
