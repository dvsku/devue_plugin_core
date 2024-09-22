#include "devue_sdk/serial/serial_misc.hpp"
#include "devue_sdk/utilities/util_string.hpp"

#include <json/json.hpp>

void devue::sdk::encode(devue_plugin_desc& desc, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::object();

        json["name"]        = desc.name;
        json["author"]      = desc.author;
        json["website"]     = desc.website;
        json["version"]     = desc.version;
        json["model_types"] = nlohmann::ordered_json::array();
        json["image_types"] = nlohmann::ordered_json::array();

        for (size_t i = 0; i < desc.model_types.size(); i++) {
            auto& type = desc.model_types[i];

            json["model_types"][i]               = nlohmann::json::object();
            json["model_types"][i]["name"]       = type.name;
            json["model_types"][i]["extensions"] = type.extensions;
        }

        for (size_t i = 0; i < desc.image_types.size(); i++) {
            auto& type = desc.image_types[i];

            json["image_types"][i]               = nlohmann::json::object();
            json["image_types"][i]["name"]       = type.name;
            json["image_types"][i]["extensions"] = type.extensions;
        }

        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode desc. | {}", msg));
    }
}

void devue::sdk::decode(devue_plugin_desc& desc, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);

        if (json.contains("name") && json["name"].is_string())
            desc.name = json["name"];

        if (json.contains("author") && json["author"].is_string())
            desc.author = json["author"];

        if (json.contains("website") && json["website"].is_string())
            desc.website = json["website"];

        if (json.contains("version") && json["version"].is_string())
            desc.version = json["version"];

        if (json.contains("model_types") && json["model_types"].is_array()) {
            for (auto& jtype : json["model_types"]) {
                devue_file_type type;

                if (jtype.contains("name") && jtype["name"].is_string())
                    type.name = jtype["name"];

                if (jtype.contains("extensions") && jtype["extensions"].is_string())
                    type.extensions = jtype["extensions"];

                desc.model_types.push_back(type);
            }
        }

        if (json.contains("image_types") && json["image_types"].is_array()) {
            for (auto& jtype : json["image_types"]) {
                devue_file_type type;

                if (jtype.contains("name") && jtype["name"].is_string())
                    type.name = jtype["name"];

                if (jtype.contains("extensions") && jtype["extensions"].is_string())
                    type.extensions = jtype["extensions"];

                desc.image_types.push_back(type);
            }
        }
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode desc. | {}", msg));
    }
}

void devue::sdk::encode(devue_ec& ec, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::object();

        json["code"]    = ec.code;
        json["message"] = ec.message;

        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode ec. | {}", msg));
    }
}

void devue::sdk::decode(devue_ec& ec, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);

        if (json.contains("code") && json["code"].is_number())
            ec.code = json["code"];

        if (json.contains("message") && json["message"].is_string())
            ec.message = json["message"];
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode ec. | {}", msg));
    }
}
