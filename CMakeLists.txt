cmake_minimum_required(VERSION 3.20)
project(course_4 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


#add_subdirectory(division)


set(UnitTest_src_regular
        unit_test/AssertException.cpp
        unit_test/AssertException.h
        unit_test/CheckMacros.h
        unit_test/Checks.cpp
        unit_test/Checks.h
        unit_test/Config.h
        unit_test/CurrentTest.cpp
        unit_test/CurrentTest.h
        unit_test/DeferredTestReporter.cpp
        unit_test/DeferredTestReporter.h
        unit_test/DeferredTestResult.cpp
        unit_test/DeferredTestResult.h
        unit_test/ExecuteTest.h
        unit_test/MemoryOutStream.cpp
        unit_test/MemoryOutStream.h
        unit_test/ReportAssert.cpp
        unit_test/ReportAssert.h
        unit_test/Test.cpp
        unit_test/Test.h
        unit_test/TestDetails.cpp
        unit_test/TestDetails.h
        unit_test/TestList.cpp
        unit_test/TestList.h
        unit_test/TestMacros.h
        unit_test/TestReporter.cpp
        unit_test/TestReporter.h
        unit_test/TestReporterStdout.cpp
        unit_test/TestReporterStdout.h
        unit_test/TestResults.cpp
        unit_test/TestResults.h
        unit_test/TestRunner.cpp
        unit_test/TestRunner.h
        unit_test/TestSuite.h
        unit_test/TimeConstraint.cpp
        unit_test/TimeConstraint.h
        unit_test/TimeHelpers.h
        unit_test/UnitTest++.h
        unit_test/XmlTestReporter.cpp
        unit_test/XmlTestReporter.h
        )
set(UnitTest_src_Posix
        unit_test/Posix/SignalTranslator.cpp
        unit_test/Posix/SignalTranslator.h
        unit_test/Posix/TimeHelpers.cpp
        unit_test/Posix/TimeHelpers.h)

set(UnitTest_src_Windows unit_test/Win32/TimeHelpers.cpp unit_test/Win32/TimeHelpers.h)

IF (WIN32)
    set(UnitTest_src_platform ${UnitTest_src_Windows})
ELSE()
    set(UnitTest_src_platform ${UnitTest_src_Posix})
ENDIF()

add_executable(HW1prog ${UnitTest_src_regular} ${UnitTest_src_platform} HW1_main.cpp HW3_main.cpp auto_ptr.cpp auto_ptr.h)
add_executable(HW2 ${UnitTest_src_regular} ${UnitTest_src_platform} HW2_main.cpp)
add_executable(HW3 ${UnitTest_src_regular} ${UnitTest_src_platform} HW3_main.cpp)
add_executable(PR1 ${UnitTest_src_regular} ${UnitTest_src_platform} PR1_main.cpp BigInt.cpp BigInt.h)

add_executable(HW5 ${UnitTest_src_regular} ${UnitTest_src_platform} auto_ptr.cpp auto_ptr.h)


add_executable(PR2_scratch dlist.h PR2_scratch.cpp)
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

#find_package(Catch2 REQUIRED)
add_executable(PR2 ${UnitTest_src_regular} ${UnitTest_src_platform} PR2_main_temp.cpp dlist.h)
target_link_libraries(PR2 Catch2::Catch2)

add_executable(PR2a ${UnitTest_src_regular} ${UnitTest_src_platform} PR2_main.cpp dlist.h)



#
#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
#include(CTest)
#include(Catch)
#catch_discover_tests()