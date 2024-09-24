INCLUDE(FetchContent)

SET(FETCHCONTENT_QUIET                OFF)
SET(FETCHCONTENT_UPDATES_DISCONNECTED  ON)

###############################################################################
## googletest

IF(DEVUE_SDK_TOP_LEVEL AND DEVUE_SDK_TEST)
    IF(DEVUE_SDK_STATIC_CRT)
        SET(gtest_force_shared_crt OFF)
    ELSE()
        SET(gtest_force_shared_crt  ON)
    ENDIF()
    
	FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
	)

	FetchContent_MakeAvailable(googletest)
ENDIF()
