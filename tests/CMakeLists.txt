INCLUDE(GoogleTest)

##############################################################################
## SDK

ADD_EXECUTABLE(build_sdk build_sdk.cpp)

TARGET_LINK_LIBRARIES(build_sdk PRIVATE devue_sdk)

##############################################################################
## SDK INTERFACE

ADD_EXECUTABLE(build_sdk_interface build_sdk_interface.cpp)

TARGET_LINK_LIBRARIES(build_sdk_interface PRIVATE devue_sdk_interface)

##############################################################################
## SERIAL

ADD_EXECUTABLE(test_serial test_serial.cpp)

TARGET_LINK_LIBRARIES(test_serial PRIVATE devue_sdk_serial)
TARGET_LINK_LIBRARIES(test_serial PRIVATE GTest::gtest_main)

gtest_discover_tests(test_serial)
