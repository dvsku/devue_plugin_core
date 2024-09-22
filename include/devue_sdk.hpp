#pragma once

#include <devue_sdk/defines.hpp>

#include <devue_sdk/model/devue_model_col.hpp>
#include <devue_sdk/model/devue_model.hpp>
#include <devue_sdk/model/devue_mesh.hpp>
#include <devue_sdk/model/devue_material.hpp>
#include <devue_sdk/model/devue_vertex.hpp>

#include <devue_sdk/image/devue_image.hpp>

#include <devue_sdk/plugin/devue_plugin_interface.hpp>
#include <devue_sdk/plugin/devue_plugin_desc.hpp>

#include <devue_sdk/misc/devue_data.hpp>
#include <devue_sdk/misc/devue_ec.hpp>
#include <devue_sdk/misc/devue_file_type.hpp>

#ifdef DEVUE_SDK
    #include <devue_sdk/plugin/devue_plugin_base.hpp>
#endif

#ifdef DEVUE_SDK_SERIAL
    #include <devue_sdk/serial/serial_model.hpp>
    #include <devue_sdk/serial/serial_image.hpp>
    #include <devue_sdk/serial/serial_misc.hpp>
#endif
