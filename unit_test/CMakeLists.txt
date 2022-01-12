cmake_minimum_required(VERSION 3.8)
project(unittest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Posix/SignalTranslator.cpp
        Posix/SignalTranslator.h
        Posix/TimeHelpers.cpp
        Posix/TimeHelpers.h
        AssertException.cpp
        AssertException.h
        CheckMacros.h
        Checks.cpp
        Checks.h
        Config.h
        CurrentTest.cpp
        CurrentTest.h
        DeferredTestReporter.cpp
        DeferredTestReporter.h
        DeferredTestResult.cpp
        DeferredTestResult.h
        ExecuteTest.h
        MemoryOutStream.cpp
        MemoryOutStream.h
        ReportAssert.cpp
        ReportAssert.h
        Test.cpp
        Test.h
        TestDetails.cpp
        TestDetails.h
        TestList.cpp
        TestList.h
        TestMacros.h
        TestReporter.cpp
        TestReporter.h
        TestReporterStdout.cpp
        TestReporterStdout.h
        TestResults.cpp
        TestResults.h
        TestRunner.cpp
        TestRunner.h
        TestSuite.h
        TimeConstraint.cpp
        TimeConstraint.h
        TimeHelpers.h
        UnitTest++.h
        XmlTestReporter.cpp
        XmlTestReporter.h ../../HW1/main.cpp)

add_library(unittest ${SOURCE_FILES})