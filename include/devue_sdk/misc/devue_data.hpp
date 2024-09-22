#pragma once

#include <cstdint>

namespace devue::sdk {
    struct devue_data {
        uint8_t* data = nullptr;
        uint64_t size = 0U;

        explicit operator bool() const {
            return data && size;
        }
    };
}
