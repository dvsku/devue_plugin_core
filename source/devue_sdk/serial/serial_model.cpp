#include "devue_sdk/serial/serial_model.hpp"
#include "devue_sdk/utilities/util_string.hpp"

#include <json/json.hpp>

////////////////////////////////////////////////////////////////////////////////
// INTERNAL

void convert_to_json(devue::sdk::devue_model& model, nlohmann::ordered_json& json);
void convert_to_json(devue::sdk::devue_mesh& mesh, nlohmann::ordered_json& json);
void convert_to_json(devue::sdk::devue_vertex& vertex, nlohmann::ordered_json& json);
void convert_to_json(devue::sdk::devue_material& material, nlohmann::ordered_json& json);
void convert_to_json(devue::sdk::devue_material_phong& material, nlohmann::ordered_json& json);
void convert_to_json(devue::sdk::devue_material_blinn_phong& material, nlohmann::ordered_json& json);

void convert_to_json(glm::vec2& vec, nlohmann::ordered_json& json);
void convert_to_json(glm::vec3& vec, nlohmann::ordered_json& json);

void convert_from_json(devue::sdk::devue_model& model, nlohmann::ordered_json& json);
void convert_from_json(devue::sdk::devue_mesh& mesh, nlohmann::ordered_json& json);
void convert_from_json(devue::sdk::devue_vertex& vertex, nlohmann::ordered_json& json);
void convert_from_json(devue::sdk::devue_material& material, nlohmann::ordered_json& json);
void convert_from_json(devue::sdk::devue_material_phong& material, nlohmann::ordered_json& json);
void convert_from_json(devue::sdk::devue_material_blinn_phong& material, nlohmann::ordered_json& json);

void convert_from_json(glm::vec2& vec, nlohmann::ordered_json& json);
void convert_from_json(glm::vec3& vec, nlohmann::ordered_json& json);

////////////////////////////////////////////////////////////////////////////////
// PUBLIC

void devue::sdk::encode(devue_model& model, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::object();
        convert_to_json(model, json);
        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode model. | {}", msg));
    }
}

void devue::sdk::decode(devue_model& model, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);
        convert_from_json(model, json);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode model. | {}", msg));
    }
}

////////////////////////////////////////////////////////////////////////////////
// CONVERTING TO JSON

void convert_to_json(devue::sdk::devue_model& model, nlohmann::ordered_json& json) {
    json["name"]   = model.name;
    json["meshes"] = nlohmann::ordered_json::array();

    for (devue::sdk::devue_mesh& mesh : model.meshes) {
        json["meshes"].push_back(nlohmann::ordered_json::object());
        convert_to_json(mesh, json["meshes"].back());
    }
}

void convert_to_json(devue::sdk::devue_mesh& mesh, nlohmann::ordered_json& json) {
    json["name"]     = mesh.name;
    json["vertices"] = nlohmann::ordered_json::array();
    json["indices"]  = nlohmann::ordered_json::array();

    for (devue::sdk::devue_vertex& vertex : mesh.vertices) {
        json["vertices"].push_back(nlohmann::ordered_json::object());
        convert_to_json(vertex, json["vertices"].back());
    }

    for (uint32_t index : mesh.indices) {
        json["indices"].push_back(index);
    }

    if (!mesh.material)
        return;

    devue::sdk::devue_material_type material_type = mesh.material->get_type();
    if (material_type == devue::sdk::devue_material_type::undefined)
        return;

    json["material"]         = nlohmann::ordered_json::object();
    json["material"]["type"] = static_cast<uint8_t>(material_type);

    convert_to_json(*mesh.material, json["material"]);

    switch (material_type) {
        case devue::sdk::devue_material_type::phong: {
            auto material = std::static_pointer_cast<devue::sdk::devue_material_phong>(mesh.material);
            convert_to_json(*material.get(), json["material"]);
            break;
        }
 
        case devue::sdk::devue_material_type::blinn_phong: {
            auto material = std::static_pointer_cast<devue::sdk::devue_material_blinn_phong>(mesh.material);
            convert_to_json(*material.get(), json["material"]);
            break;
        }
            
        default: break;
    }
}

void convert_to_json(devue::sdk::devue_vertex& vertex, nlohmann::ordered_json& json) {
    json["position"] = nlohmann::ordered_json::object();
    json["normal"]   = nlohmann::ordered_json::object();
    json["uv"]       = nlohmann::ordered_json::object();

    convert_to_json(vertex.position, json["position"]);
    convert_to_json(vertex.normal,   json["normal"]);
    convert_to_json(vertex.uv,       json["uv"]);
}

void convert_to_json(devue::sdk::devue_material& material, nlohmann::ordered_json& json) {
    json["name"]        = material.name;
    json["transparent"] = material.transparent;
}

void convert_to_json(devue::sdk::devue_material_phong& material, nlohmann::ordered_json& json) {
    json["color"]          = nlohmann::ordered_json::object();
    json["color_specular"] = nlohmann::ordered_json::object();

    convert_to_json(material.color,          json["color"]);
    convert_to_json(material.color_specular, json["color_specular"]);

    json["color_map"]  = material.color_map;
    json["normal_map"] = material.normal_map;

    json["shininess"] = material.shininess;
}

void convert_to_json(devue::sdk::devue_material_blinn_phong& material, nlohmann::ordered_json& json) {
    return convert_to_json(static_cast<devue::sdk::devue_material_phong&>(material), json);
}

void convert_to_json(glm::vec2& vec, nlohmann::ordered_json& json) {
    json["x"] = vec.x;
    json["y"] = vec.y;
}

void convert_to_json(glm::vec3& vec, nlohmann::ordered_json& json) {
    json["x"] = vec.x;
    json["y"] = vec.y;
    json["z"] = vec.z;
}

////////////////////////////////////////////////////////////////////////////////
// CONVERTING FROM JSON

void convert_from_json(devue::sdk::devue_model& model, nlohmann::ordered_json& json) {
    if (json.contains("name") && json["name"].is_string())
        model.name = json["name"];

    if (json.contains("meshes") && json["meshes"].is_array()) {
        for (auto& mesh : json["meshes"]) {
            if (!mesh.is_object())
                continue;

            model.meshes.push_back({});
            convert_from_json(model.meshes.back(), mesh);
        }
    }
}

void convert_from_json(devue::sdk::devue_mesh& mesh, nlohmann::ordered_json& json) {
    if (json.contains("name") && json["name"].is_string())
        mesh.name = json["name"];

    if (json.contains("vertices") && json["vertices"].is_array()) {
        for (auto& vertex : json["vertices"]) {
            if (!vertex.is_object())
                continue;

            mesh.vertices.push_back({});
            convert_from_json(mesh.vertices.back(), vertex);
        }
    }

    if (json.contains("indices") && json["indices"].is_array()) {
        for (auto& index : json["indices"]) {
            if (!index.is_number_unsigned())
                continue;

            mesh.indices.push_back(index);
        }
    }

    if (!json.contains("material") || !json["material"].is_object())
        return;

    if (!json["material"].contains("type") || !json["material"]["type"].is_number_unsigned())
        return;

    devue::sdk::devue_material_type material_type = static_cast<devue::sdk::devue_material_type>(json["material"]["type"]);

    if (material_type == devue::sdk::devue_material_type::undefined)
        return;

    switch (material_type) {
        case devue::sdk::devue_material_type::phong: {
            auto material = std::make_shared<devue::sdk::devue_material_phong>();
            auto base     = std::static_pointer_cast<devue::sdk::devue_material>(material);

            convert_from_json(*base.get(),     json["material"]);
            convert_from_json(*material.get(), json["material"]);

            mesh.material = material;
            break;
        }
        case devue::sdk::devue_material_type::blinn_phong: {
            auto material = std::make_shared<devue::sdk::devue_material_blinn_phong>();
            auto base     = std::static_pointer_cast<devue::sdk::devue_material>(material);

            convert_from_json(*base.get(),     json["material"]);
            convert_from_json(*material.get(), json["material"]);

            mesh.material = material;
            break;
        }

        default: break;
    }
}

void convert_from_json(devue::sdk::devue_vertex& vertex, nlohmann::ordered_json& json) {
    if (json.contains("position") && json["position"].is_object())
        convert_from_json(vertex.position, json["position"]);

    if (json.contains("normal") && json["normal"].is_object())
        convert_from_json(vertex.normal, json["normal"]);

    if (json.contains("uv") && json["uv"].is_object())
        convert_from_json(vertex.uv, json["uv"]);
}

void convert_from_json(devue::sdk::devue_material& material, nlohmann::ordered_json& json) {
    if (json.contains("name") && json["name"].is_string())
        material.name = json["name"];

    if (json.contains("transparent") && json["transparent"].is_boolean())
        material.transparent = json["transparent"];
}

void convert_from_json(devue::sdk::devue_material_phong& material, nlohmann::ordered_json& json) {
    if (json.contains("color") && json["color"].is_object())
        convert_from_json(material.color, json["color"]);

    if (json.contains("color_specular") && json["color_specular"].is_object())
        convert_from_json(material.color_specular, json["color_specular"]);

    if (json.contains("color_map") && json["color_map"].is_string())
        material.color_map = json["color_map"];

    if (json.contains("normal_map") && json["normal_map"].is_string())
        material.normal_map = json["normal_map"];

    if (json.contains("shininess") && json["shininess"].is_number_float())
        material.shininess = json["shininess"];
}

void convert_from_json(devue::sdk::devue_material_blinn_phong& material, nlohmann::ordered_json& json) {
    return convert_from_json(static_cast<devue::sdk::devue_material_phong&>(material), json);
}

void convert_from_json(glm::vec2& vec, nlohmann::ordered_json& json) {
    if (json.contains("x") && json["x"].is_number_float())
        vec.x = json["x"];

    if (json.contains("y") && json["y"].is_number_float())
        vec.y = json["y"];
}

void convert_from_json(glm::vec3& vec, nlohmann::ordered_json& json) {
    if (json.contains("x") && json["x"].is_number_float())
        vec.x = json["x"];

    if (json.contains("y") && json["y"].is_number_float())
        vec.y = json["y"];

    if (json.contains("z") && json["z"].is_number_float())
        vec.z = json["z"];
}
