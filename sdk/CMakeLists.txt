################################################################################
## ENCODING/DECODING

FILE(GLOB_RECURSE SDK_SERIAL_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/serial/*.cpp"
)

ADD_LIBRARY(devue_plugin_sdk_serial STATIC
    ${SDK_SERIAL_SOURCES}
)

TARGET_COMPILE_DEFINITIONS(devue_plugin_sdk_serial PUBLIC -DGLM_ENABLE_EXPERIMENTAL)

TARGET_INCLUDE_DIRECTORIES(devue_plugin_sdk_serial PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include/model")
TARGET_INCLUDE_DIRECTORIES(devue_plugin_sdk_serial PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include/image")
TARGET_INCLUDE_DIRECTORIES(devue_plugin_sdk_serial PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/serial")
TARGET_INCLUDE_DIRECTORIES(devue_plugin_sdk_serial PUBLIC  "${PROJECT_SOURCE_DIR}/libraries")
TARGET_INCLUDE_DIRECTORIES(devue_plugin_sdk_serial PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/utilities")

