################################################################################
## SDK

ADD_LIBRARY(devue_sdk STATIC
    "devue_sdk/plugin/devue_plugin_base.cpp"
    "devue_sdk/plugin/devue_plugin.cpp"
)

TARGET_COMPILE_DEFINITIONS(devue_sdk PUBLIC -DGLM_ENABLE_EXPERIMENTAL)
TARGET_COMPILE_DEFINITIONS(devue_sdk PUBLIC -DDEVUE_SDK)

TARGET_INCLUDE_DIRECTORIES(devue_sdk PUBLIC "${PROJECT_SOURCE_DIR}/source")

TARGET_LINK_LIBRARIES(devue_sdk PUBLIC devue_sdk_interface)
TARGET_LINK_LIBRARIES(devue_sdk PUBLIC devue_sdk_serial)

################################################################################
## SDK INTERFACE

ADD_LIBRARY(devue_sdk_interface INTERFACE)

TARGET_COMPILE_DEFINITIONS(devue_sdk_interface INTERFACE -DGLM_ENABLE_EXPERIMENTAL)

TARGET_INCLUDE_DIRECTORIES(devue_sdk_interface INTERFACE "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES(devue_sdk_interface INTERFACE "${PROJECT_SOURCE_DIR}/libraries")

################################################################################
## ENCODING/DECODING

ADD_LIBRARY(devue_sdk_serial STATIC
    "devue_sdk/serial/serial_image.cpp"
    "devue_sdk/serial/serial_model.cpp"
    "devue_sdk/serial/serial_misc.cpp"
)

TARGET_COMPILE_DEFINITIONS(devue_sdk_serial PUBLIC -DGLM_ENABLE_EXPERIMENTAL)
TARGET_COMPILE_DEFINITIONS(devue_sdk_serial PUBLIC -DDEVUE_SDK_SERIAL)

TARGET_INCLUDE_DIRECTORIES(devue_sdk_serial PUBLIC  "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES(devue_sdk_serial PUBLIC  "${PROJECT_SOURCE_DIR}/libraries")
TARGET_INCLUDE_DIRECTORIES(devue_sdk_serial PRIVATE "${PROJECT_SOURCE_DIR}/source")
