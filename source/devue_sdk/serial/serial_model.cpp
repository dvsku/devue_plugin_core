#include "devue_sdk/serial/serial_model.hpp"
#include "devue_sdk/utilities/util_string.hpp"

#include <json/json.hpp>

void devue::sdk::encode(devue_model& model, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::object();

        json["name"]   = model.name;
        json["meshes"] = nlohmann::ordered_json::array();

        for (size_t i = 0; i < model.meshes.size(); i++) {
            json["meshes"][i] = nlohmann::ordered_json::object();

            auto& mesh  = model.meshes[i];
            auto& jmesh = json["meshes"][i];

            jmesh["name"]     = mesh.name;
            jmesh["vertices"] = nlohmann::ordered_json::array();
            jmesh["indices"]  = nlohmann::ordered_json::array();

            for (size_t j = 0; j < mesh.vertices.size(); j++) {
                jmesh["vertices"][j] = nlohmann::ordered_json::object();

                auto& vertex  = mesh.vertices[j];
                auto& jvertex = jmesh["vertices"][j];

                jvertex["position"]["x"] = vertex.position.x;
                jvertex["position"]["y"] = vertex.position.y;
                jvertex["position"]["z"] = vertex.position.z;

                jvertex["normal"]["x"] = vertex.normal.x;
                jvertex["normal"]["y"] = vertex.normal.y;
                jvertex["normal"]["z"] = vertex.normal.z;

                jvertex["uv"]["x"] = vertex.uv.x;
                jvertex["uv"]["y"] = vertex.uv.y;
            }

            for (size_t j = 0; j < mesh.indices.size(); j++) {
                jmesh["indices"][j] = mesh.indices[j];
            }

            if (mesh.material) {
                jmesh["material"] = nlohmann::ordered_json::object();

                auto& jmaterial   = jmesh["material"];
                jmaterial["type"] = mesh.material->get_type();
                jmaterial["name"] = mesh.material->name;

                if (mesh.material->get_type() == devue_material_type::phong) {
                    auto material = std::static_pointer_cast<devue_material_phong>(mesh.material);
                    
                    jmaterial["color_map"] = material->color_map;
                }
            }
        }

        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode models. | {}", msg));
    }
}

void devue::sdk::decode(devue_model& model, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);

        if (json.contains("name") && json["name"].is_string())
            model.name = json["name"];

        if (json.contains("meshes") && json["meshes"].is_array()) {
            for (auto& jmesh : json["meshes"]) {
                model.meshes.push_back({});
                devue_mesh& mesh = model.meshes.back();

                if (jmesh.contains("name") && jmesh["name"].is_string())
                    mesh.name = jmesh["name"];

                if (jmesh.contains("vertices") && jmesh["vertices"].is_array()) {
                    for (auto& jvertex : jmesh["vertices"]) {
                        mesh.vertices.push_back({});
                        devue_vertex& vertex = mesh.vertices.back();

                        if (jvertex.contains("position") && jvertex["position"].is_object()) {
                            auto& jposition = jvertex["position"];

                            if (jposition.contains("x") && jposition["x"].is_number())
                                vertex.position.x = jposition["x"];

                            if (jposition.contains("y") && jposition["y"].is_number())
                                vertex.position.y = jposition["y"];

                            if (jposition.contains("z") && jposition["z"].is_number())
                                vertex.position.z = jposition["z"];
                        }

                        if (jvertex.contains("normal") && jvertex["normal"].is_object()) {
                            auto& jnormal = jvertex["normal"];

                            if (jnormal.contains("x") && jnormal["x"].is_number())
                                vertex.normal.x = jnormal["x"];

                            if (jnormal.contains("y") && jnormal["y"].is_number())
                                vertex.normal.y = jnormal["y"];

                            if (jnormal.contains("z") && jnormal["z"].is_number())
                                vertex.normal.z = jnormal["z"];
                        }

                        if (jvertex.contains("uv") && jvertex["uv"].is_object()) {
                            auto& juv = jvertex["uv"];

                            if (juv.contains("x") && juv["x"].is_number())
                                vertex.uv.x = juv["x"];

                            if (juv.contains("y") && juv["y"].is_number())
                                vertex.uv.y = juv["y"];
                        }
                    }
                }

                if (jmesh.contains("indices") && jmesh["indices"].is_array()) {
                    for (auto& jindex : jmesh["indices"]) {
                        if (!jindex.is_number()) continue;

                        mesh.indices.push_back(jindex);
                    }
                }

                if (jmesh.contains("material") && jmesh["material"].is_object()) {
                    auto& jmaterial = jmesh["material"];
                    
                    if (jmaterial.contains("type")) {
                        devue_material_type type = jmaterial["type"];

                        if (type == devue_material_type::phong) {
                            auto material = std::make_shared<devue_material_phong>();
                            
                            if (jmaterial.contains("name") && jmaterial["name"].is_string())
                                material->name = jmaterial["name"];

                            if (jmaterial.contains("color_map") && jmaterial["color_map"].is_string())
                                material->color_map = jmaterial["color_map"];

                            mesh.material = material;
                        }
                    }
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode models. | {}", msg));
    }
}
