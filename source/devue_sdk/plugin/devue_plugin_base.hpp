#pragma once

#include "devue_sdk/plugin/devue_plugin_interface.hpp"
#include "devue_sdk/plugin/devue_plugin_desc.hpp"
#include "devue_sdk/model/devue_model.hpp"
#include "devue_sdk/image/devue_image.hpp"
#include "devue_sdk/misc/devue_ec.hpp"
#include "devue_sdk/misc/devue_data.hpp"

#include <string>
#include <vector>
#include <filesystem>

namespace devue::sdk {
    class devue_plugin_base : public devue_plugin_interface {
    public:
        devue_plugin_base()          = default;
        virtual ~devue_plugin_base() = default;

    protected:
        devue_plugin_desc m_desc = {};

    protected:
        virtual devue_model impl_import_model(const std::filesystem::path& filepath);
        virtual devue_image impl_import_image(const std::filesystem::path& filepath);

    private:
        using buffer_t = std::vector<uint8_t>;

    private:
        buffer_t m_buffer = {};
        devue_ec m_ec     = {};

    private:
        devue_data get_desc()                         noexcept final override;
        devue_data get_ec()                           noexcept final override;
        devue_data import_model(const char* filepath) noexcept final override;
        devue_data import_image(const char* filepath) noexcept final override;
        void       cleanup()                          noexcept final override;
    };
}
