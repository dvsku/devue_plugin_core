#pragma once

#include "devue_sdk/misc/devue_data.hpp"

namespace devue::sdk {
    class devue_plugin_interface {
    public:
        virtual devue_data get_desc()                         noexcept = 0;
        virtual devue_data get_ec()                           noexcept = 0;
        virtual devue_data import_model(const char* filepath) noexcept = 0;
        virtual devue_data import_image(const char* filepath) noexcept = 0;
        virtual void       cleanup()                          noexcept = 0;
    };
}
