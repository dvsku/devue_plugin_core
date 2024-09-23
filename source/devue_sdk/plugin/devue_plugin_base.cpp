#include "devue_sdk/plugin/devue_plugin_base.hpp"
#include "devue_sdk/serial/serial_model.hpp"
#include "devue_sdk/serial/serial_image.hpp"
#include "devue_sdk/serial/serial_misc.hpp"

using namespace devue::sdk;

////////////////////////////////////////////////////////////////////////////////
// PROTECTED

devue_model_pack devue_plugin_base::impl_import_model(const std::filesystem::path& filepath) {
    throw std::runtime_error("Not implemented");
}

devue_image devue_plugin_base::impl_import_image(const std::filesystem::path& filepath) {
    throw std::runtime_error("Not implemented");
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE

devue_data devue_plugin_base::get_desc() noexcept {
    try {
        cleanup();
        encode(m_desc, m_buffer);
    }
    catch (const std::exception& e) {
        m_ec.code    = -1;
        m_ec.message = e.what();
        return {};
    }

    return { m_buffer.data(), (uint64_t)m_buffer.size() };
}

devue_data devue_plugin_base::get_ec() noexcept {
    try {
        cleanup();
        encode(m_ec, m_buffer);
    }
    catch (...) {
        return {};
    }

    return { m_buffer.data(), (uint64_t)m_buffer.size() };
}

devue_data devue_plugin_base::import_model(const char* filepath) noexcept {
    try {
        devue_model_pack models = impl_import_model(filepath);

        cleanup();
        encode(models, m_buffer);
    }
    catch (const std::exception& e) {
        m_ec.code    = -1;
        m_ec.message = e.what();
        return {};
    }

    return { m_buffer.data(), (uint64_t)m_buffer.size() };
}

devue_data devue_plugin_base::import_image(const char* filepath) noexcept {
    try {
        devue_image image = impl_import_image(filepath);

        cleanup();
        encode(image, m_buffer);
    }
    catch (const std::exception& e) {
        m_ec.code    = -1;
        m_ec.message = e.what();
        return {};
    }

    return { m_buffer.data(), (uint64_t)m_buffer.size() };
}

void devue_plugin_base::cleanup() noexcept {
    m_ec.code = 0;
    m_ec.message.clear();

    m_buffer.clear();
}
