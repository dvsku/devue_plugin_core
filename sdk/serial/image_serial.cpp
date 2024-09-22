#include "image_serial.hpp"
#include "util_string.hpp"

#include <json/json.hpp>

void devue::sdk::encode_image(devue_image& image, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::object();

        json["width"]      = image.width;
        json["height"]     = image.height;
        json["components"] = image.components;
        json["data"]       = nlohmann::json::binary(std::move(image.data));

        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode image. | {}", msg));
    }
}

void devue::sdk::decode_image(devue_image& image, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);

        if (json.contains("width") && json["width"].is_number())
            image.width = json["width"];

        if (json.contains("height") && json["height"].is_number())
            image.height = json["height"];

        if (json.contains("components") && json["components"].is_number())
            image.components = json["components"];

        if (json.contains("data") && json["data"].is_binary())
            image.data = std::move(json["data"].get_binary());
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode image. | {}", msg));
    }
}
