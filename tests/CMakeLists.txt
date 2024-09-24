INCLUDE(GoogleTest)

LINK_LIBRARIES(devue_sdk)
LINK_LIBRARIES(GTest::gtest_main)

ADD_EXECUTABLE(test_serial test_serial.cpp)
gtest_discover_tests(test_serial)
