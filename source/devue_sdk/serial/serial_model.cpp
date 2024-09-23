#include "devue_sdk/serial/serial_model.hpp"
#include "devue_sdk/utilities/util_string.hpp"

#include <json/json.hpp>

void devue::sdk::encode(devue_model_pack& models, std::vector<uint8_t>& buffer) {
    nlohmann::ordered_json json;

    try {
        json           = nlohmann::ordered_json::object();
        json["models"] = nlohmann::ordered_json::array();

        for (size_t i = 0; i < models.models.size(); i++) {
            auto& model = models.models[i];

            if (!model.meshes.size())
                continue;

            json["models"][i] = nlohmann::ordered_json::object();
            auto& jmodel      = json["models"][i];
            
            jmodel["vertices"]  = nlohmann::ordered_json::array();
            jmodel["meshes"]    = nlohmann::ordered_json::array();
            jmodel["materials"] = nlohmann::ordered_json::array();

            for (size_t j = 0; j < model.vertices.size(); j++) {
                jmodel["vertices"][j] = nlohmann::ordered_json::object();

                auto& vertex  = model.vertices[j];
                auto& jvertex = jmodel["vertices"][j];

                jvertex["position"]["x"] = vertex.position.x;
                jvertex["position"]["y"] = vertex.position.y;
                jvertex["position"]["z"] = vertex.position.z;

                jvertex["normal"]["x"] = vertex.normal.x;
                jvertex["normal"]["y"] = vertex.normal.y;
                jvertex["normal"]["z"] = vertex.normal.z;

                jvertex["uv"]["x"] = vertex.uv.x;
                jvertex["uv"]["y"] = vertex.uv.y;
            }

            for (size_t j = 0; j < model.meshes.size(); j++) {
                jmodel["meshes"][j] = nlohmann::ordered_json::object();

                auto& mesh  = model.meshes[j];
                auto& jmesh = jmodel["meshes"][j];

                jmesh["name"]           = mesh.name;
                jmesh["material_index"] = mesh.material_index;
                jmesh["indices"]        = nlohmann::ordered_json::array();

                for (size_t k = 0; k < mesh.indices.size(); k++) {
                    jmesh["indices"][k] = mesh.indices[k];
                }
            }

            for (size_t j = 0; j < model.materials.size(); j++) {
                jmodel["materials"][j] = nlohmann::ordered_json::object();

                auto& material  = model.materials[j];
                auto& jmaterial = jmodel["materials"][j];

                jmaterial["name"]            = material.name;
                jmaterial["diffuse_texture"] = material.diffuse_texture;
            }
        }

        nlohmann::ordered_json::to_cbor(json, buffer);
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to encode models. | {}", msg));
    }
}

void devue::sdk::decode(devue_model_pack& models, uint8_t* dst, uint64_t size) {
    nlohmann::ordered_json json;

    try {
        json = nlohmann::ordered_json::from_cbor(dst, dst + size);

        if (!json.contains("models") || !json["models"].is_array())
            return;

        for (auto& jmodel : json["models"]) {
            devue_model model;

            if (jmodel.contains("vertices") && jmodel["vertices"].is_array()) {
                for (auto& jvertex : jmodel["vertices"]) {
                    devue_vertex vertex;

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

                    model.vertices.push_back(vertex);
                }
            }

            if (jmodel.contains("meshes") && jmodel["meshes"].is_array()) {
                for (auto& jmesh : jmodel["meshes"]) {
                    devue_mesh mesh;

                    if (jmesh.contains("name") && jmesh["name"].is_string())
                        mesh.name = jmesh["name"];

                    if (jmesh.contains("material_index") && jmesh["material_index"].is_number())
                        mesh.material_index = jmesh["material_index"];

                    if (jmesh.contains("indices") && jmesh["indices"].is_array()) {
                        for (auto& jindex : jmesh["indices"]) {
                            if (!jindex.is_number()) continue;

                            mesh.indices.push_back(jindex);
                        }
                    }

                    model.meshes.push_back(mesh);
                }
            }

            if (jmodel.contains("materials") && jmodel["materials"].is_array()) {
                for (auto& jmaterial : jmodel["materials"]) {
                    devue_material material;

                    if (jmaterial.contains("name") && jmaterial["name"].is_string())
                        material.name = jmaterial["name"];

                    if (jmaterial.contains("diffuse_texture") && jmaterial["diffuse_texture"].is_string())
                        material.diffuse_texture = jmaterial["diffuse_texture"];

                    model.materials.push_back(material);
                }
            }

            models.models.push_back(model);
        }
    }
    catch (const std::exception& e) {
        std::string msg = e.what();
        throw std::runtime_error(STR_FORMAT("Failed to decode models. | {}", msg));
    }
}
