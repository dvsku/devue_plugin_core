#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"

namespace devue::sdk {
    struct devue_vertex {
        glm::vec3 position{};
        glm::vec3 normal{};
        glm::vec2 uv{};

        bool operator==(const devue_vertex& rhs) const {
            return position == rhs.position && normal == rhs.normal && uv == rhs.uv;
        }
    };
}

namespace std {
    template<> struct hash<devue::sdk::devue_vertex> {
        size_t operator()(devue::sdk::devue_vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^ 
                (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.uv) << 1);
        }
    };
}
