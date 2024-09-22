#include <devue_sdk.hpp>

class devue_plugin : public devue::sdk::devue_plugin_base {
public:
    devue::sdk::devue_model_col impl_import_model(const std::filesystem::path& filepath) override {
        return {};
    }

    devue::sdk::devue_image impl_import_image(const std::filesystem::path& filepath) override {
        return {};
    }
};

int main() {
    devue_plugin plg;

    return 0;
}