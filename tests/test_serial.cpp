#include <devue_sdk.hpp>

#include <gtest/gtest.h>
#include <vector>

TEST(serial, model) {
    devue::sdk::devue_model_pack input;
    devue::sdk::devue_model_pack output;

    std::vector<uint8_t> buffer;

    {
        devue::sdk::devue_model model_1;
        model_1.vertices = {
            { { 0.0f, 0.1f, 0.2f }, { 0.3f, 0.4f, 0.5f }, { 0.6f, 0.7f } },
            { { 1.0f, 1.1f, 1.2f }, { 1.3f, 1.4f, 1.5f }, { 1.6f, 1.7f } }
        };
        model_1.materials = {
            { "abc", "dfg" },
            { "123", "456" }
        };
        model_1.meshes = {
            { "abc", 0, { 1, 2, 3, 4, 5, 6 } },
            { "dfg", 1, { 7, 8, 9, 10, 11, 12 } }
        };

        devue::sdk::devue_model model_2;
        model_2.vertices = {
            { { 1.0f, 1.1f, 1.2f }, { 1.3f, 1.4f, 1.5f }, { 1.6f, 1.7f } },
            { { 0.0f, 0.1f, 0.2f }, { 0.3f, 0.4f, 0.5f }, { 0.6f, 0.7f } }
        };
        model_2.materials = {
            { "123", "456" },
            { "abc", "dfg" }
        };
        model_2.meshes = {
            { "dfg", 1, { 7, 8, 9, 10, 11, 12 } },
            { "abc", 0, { 1, 2, 3, 4, 5, 6 } }
        };

        input.models.push_back(model_1);
        input.models.push_back(model_2);
    }

    devue::sdk::encode(input, buffer);
    devue::sdk::decode(output, buffer.data(), (uint64_t)buffer.size());

    ASSERT_TRUE(input.models.size() == input.models.size());

    for (size_t i = 0; i < output.models.size(); i++) {
        auto& imodel = input.models[i];
        auto& omodel = output.models[i];

        ASSERT_TRUE(imodel.vertices.size() == omodel.vertices.size());
        ASSERT_TRUE(imodel.meshes.size() == omodel.meshes.size());
        ASSERT_TRUE(imodel.materials.size() == omodel.materials.size());

        for (size_t j = 0; j < omodel.vertices.size(); j++) {
            auto& ivertex = imodel.vertices[i];
            auto& overtex = omodel.vertices[i];

            ASSERT_TRUE(ivertex == overtex);
        }

        for (size_t j = 0; j < omodel.meshes.size(); j++) {
            auto& imesh = imodel.meshes[i];
            auto& omesh = omodel.meshes[i];

            ASSERT_TRUE(imesh.name == omesh.name);
            ASSERT_TRUE(imesh.material_index == omesh.material_index);
            ASSERT_TRUE(imesh.indices.size() == omesh.indices.size());

            for (size_t k = 0; k < omesh.indices.size(); k++) {
                ASSERT_TRUE(imesh.indices[k] == omesh.indices[k]);
            }
        }

        for (size_t j = 0; j < omodel.materials.size(); j++) {
            auto& imaterial = imodel.materials[i];
            auto& omaterial = omodel.materials[i];

            ASSERT_TRUE(imaterial.name == omaterial.name);
            ASSERT_TRUE(imaterial.diffuse_texture == omaterial.diffuse_texture);
        }
    }
}

TEST(serial, image) {
    devue::sdk::devue_image input;
    devue::sdk::devue_image output;

    std::vector<uint8_t> buffer;
    std::vector<uint8_t> data;

    input.width      = 1920;
    input.height     = 1080;
    input.components = 3;
    input.data       = data;

    devue::sdk::encode(input, buffer);
    devue::sdk::decode(output, buffer.data(), (uint64_t)buffer.size());

    EXPECT_TRUE(input.width == output.width);
    EXPECT_TRUE(input.height == output.height);
    EXPECT_TRUE(input.components == output.components);
    EXPECT_TRUE(output.data == data);
}

TEST(serial, ec) {
    devue::sdk::devue_ec input;
    devue::sdk::devue_ec output;

    std::vector<uint8_t> buffer;

    input.code    = 16;
    input.message = "ABCD";

    devue::sdk::encode(input, buffer);
    devue::sdk::decode(output, buffer.data(), (uint64_t)buffer.size());

    EXPECT_TRUE(input.code == output.code);
    EXPECT_TRUE(input.message == output.message);
}

TEST(serial, desc) {
    devue::sdk::devue_plugin_desc input;
    devue::sdk::devue_plugin_desc output;

    std::vector<uint8_t> buffer;

    input.name    = "DSADgdfsgs";
    input.author  = "jhgfnvbn";
    input.website = "gdsftye";
    input.version = "iuudhdhgf";
    
    input.model_types = {
        { "gdsfg", "gfdgdfg" },
        { "itweryo", "pu"}
    };
    
    input.image_types = {
        { "itweryo", "pu"},
        { "gdsfg", "gfdgdfg" }
    };

    devue::sdk::encode(input, buffer);
    devue::sdk::decode(output, buffer.data(), (uint64_t)buffer.size());

    EXPECT_TRUE(input.name == output.name);
    EXPECT_TRUE(input.author == output.author);
    EXPECT_TRUE(input.website == output.website);
    EXPECT_TRUE(input.version == output.version);
    ASSERT_TRUE(input.model_types.size() == output.model_types.size());
    ASSERT_TRUE(input.image_types.size() == output.image_types.size());

    for (size_t i = 0; i < output.model_types.size(); i++) {
        EXPECT_TRUE(input.model_types[i].name == output.model_types[i].name);
        EXPECT_TRUE(input.model_types[i].extensions == output.model_types[i].extensions);
    }

    for (size_t i = 0; i < output.image_types.size(); i++) {
        EXPECT_TRUE(input.image_types[i].name == output.image_types[i].name);
        EXPECT_TRUE(input.image_types[i].extensions == output.image_types[i].extensions);
    }
}