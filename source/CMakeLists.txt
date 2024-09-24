ADD_LIBRARY(devue_sdk STATIC
    "devue_sdk/plugin/devue_plugin_base.cpp"
    "devue_sdk/serial/serial_image.cpp"
    "devue_sdk/serial/serial_model.cpp"
    "devue_sdk/serial/serial_misc.cpp"
)

TARGET_COMPILE_DEFINITIONS(devue_sdk PUBLIC -DGLM_ENABLE_EXPERIMENTAL)

TARGET_INCLUDE_DIRECTORIES(devue_sdk PUBLIC "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES(devue_sdk PUBLIC "${PROJECT_SOURCE_DIR}/libraries")
TARGET_INCLUDE_DIRECTORIES(devue_sdk PUBLIC "${PROJECT_SOURCE_DIR}/source")

TARGET_COMPILE_OPTIONS(devue_sdk PUBLIC  /std:c++20)
TARGET_COMPILE_OPTIONS(devue_sdk PRIVATE /W3)
