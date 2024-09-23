#pragma once

#include <string>

namespace devue::sdk {
    struct devue_ec {
        int64_t     code    = 0;
        std::string message = "";

        explicit operator bool() {
            return code != 0;
        }
    };
}
