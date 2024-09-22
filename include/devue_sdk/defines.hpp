#pragma once

#include <cstdint>

#ifndef DEVUE_API
    #define DEVUE_API extern "C" __declspec(dllexport)
#endif

constexpr uint16_t SDK_VERSION_YEAR  = 2024;
constexpr uint16_t SDK_VERSION_MONTH = 9;
constexpr uint16_t SDK_VERSION_DAY   = 23;
constexpr uint16_t SDK_VERSION_REV   = 0;

#define SDK_VERSION_PACKED                  \
    ((uint64_t)SDK_VERSION_YEAR  << 48) |   \
    ((uint64_t)SDK_VERSION_MONTH << 32) |   \
    ((uint64_t)SDK_VERSION_DAY   << 16) |   \
    ((uint64_t)SDK_VERSION_REV)
    

//#define SDK_VERSION_PACKED                  \
//    ((uint64_t)SDK_VERSION_YEAR  << 48) |   \
//    (((uint64_t)SDK_VERSION_MONTH << 32)) |   \ 
//    (((uint64_t)SDK_VERSION_DAY   << 16)) |   \
//    (((uint64_t)SDK_VERSION_REV))