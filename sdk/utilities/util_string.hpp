#pragma once

#include <format>

#define STR_FORMAT(fmt, ...)	\
    std::vformat(fmt, std::make_format_args(__VA_ARGS__))
