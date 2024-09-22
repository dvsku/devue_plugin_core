INCLUDE(GoogleTest)
LINK_LIBRARIES(GTest::gtest_main)

##############################################################################
## SERIAL

ADD_EXECUTABLE(test_serial test_serial.cpp)

TARGET_LINK_LIBRARIES(test_serial PRIVATE devue_plugin_sdk_serial)
gtest_discover_tests(test_serial)
