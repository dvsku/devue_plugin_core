#pragma once

#include <cstdint>

#ifndef DEVUE_API
    #define DEVUE_API extern "C" __declspec(dllexport)
#endif

constexpr uint16_t DEVUE_SDK_VERSION_YEAR  = 2024;
constexpr uint16_t DEVUE_SDK_VERSION_MONTH = 10;
constexpr uint16_t DEVUE_SDK_VERSION_DAY   = 5;
constexpr uint16_t DEVUE_SDK_VERSION_REV   = 0;

#define DEVUE_SDK_VERSION_PACKED                  \
    ((uint64_t)DEVUE_SDK_VERSION_YEAR  << 48) |   \
    ((uint64_t)DEVUE_SDK_VERSION_MONTH << 32) |   \
    ((uint64_t)DEVUE_SDK_VERSION_DAY   << 16) |   \
    ((uint64_t)DEVUE_SDK_VERSION_REV)
