#pragma once

#include <cstdint>
#include <string>

namespace devue::sdk {
    enum class devue_material_type : uint8_t {
        undefined,
        phong,
        blinn_phong
    };

    struct devue_material {
        std::string name        = "";
        bool        transparent = false;

        virtual devue_material_type get_type() {
            return devue_material_type::undefined;
        }
    };
}
