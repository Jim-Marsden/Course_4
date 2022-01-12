//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 1/11/22.
// https://Jim-Marsden/Course_4
// =====================================================================
// main.cpp Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
// Testing bits of the STD algorithms libraries.
// =====================================================================
//

#include "unit_test/UnitTest++.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>

TEST(DequeGenerate){
    std::deque<int> testDeque;
    // The back_inserter pushes elements to the 'testDeque', and the lambda increments based on the last assigned value.
    std::generate_n(std::back_inserter(testDeque), 10, [i=1]() mutable {return i++;});
    CHECK(std::accumulate(testDeque.begin(),  testDeque.end(), 0) == 55); // 1..10 should equal 55
}

TEST(StringToUpper){
    std::string testString{"abcdefghijklmnopqrstuvwxyz"};
    std::transform(testString.begin(),  testString.end(), testString.begin(), [](unsigned char letter )-> unsigned char{ return std::toupper(letter); });
    CHECK(testString == "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(VectorSort){
    std::ostringstream stringStream; // for ostream tests
    const auto defaultArray = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // for ranged based initialization
    std::vector<int> testVector(std::begin(defaultArray), std::end(defaultArray));

    auto partitionPoint = std::partition(testVector.begin(), testVector.end(), [](int i){return i % 2 == 0;}); // Split it by if it's even or not.
    std::sort(testVector.begin(), partitionPoint );    std::sort(partitionPoint, testVector.end()); // Sort both halves

    // Writes the even half, then the odd half to stringStream
    std::copy(testVector.begin(), partitionPoint, std::ostream_iterator<int>(stringStream));
    std::copy(partitionPoint, testVector.end(), std::ostream_iterator<int>(stringStream));
    CHECK(stringStream.str() == "24681013579"); // "24681013579" is what both halves sorted then put together should look like.
}

int main(){
    auto test_status = UnitTest::RunAllTests(); // test runner.
    return test_status;
}