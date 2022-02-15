
//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 1/29/22.
// https://Github.com/Jim-Marsden/Course_4
// =====================================================================
// BigInt.h Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
//
// A BigInt -- a dynamically resizing representation of an integer
// =====================================================================
//
// ==========================[notes]====================================
// It does not check for bad_allac, as that would be something I don't
// think if you're out of memory, the big int should try and do something
// strange
// =====================================================================
//

#include <algorithm>
#include <functional>
#include "BigInt.h"

using Project1::BigInt;

// Takes two strings, makes sure they're the same size, and and pads the smaller one with 0s. first will be larger than second
static auto prepareStringsForMath(std::string const& a, std::string const& b)
{
    struct result_struct_ { // a local struct for structured bindings
        std::string first, second;
    } result_struct{a, b};

    // Gets the largest and smallest sizes
    std::size_t const largest_size = result_struct.first.size()>result_struct.second.size() ? result_struct.first.size()
                                                                                            : result_struct.second.size();
    std::size_t const smallest_size =
            result_struct.first.size()<result_struct.second.size() ? result_struct.first.size()
                                                                   : result_struct.second.size();

    // Fills in the smallest with 0s to match the length of the largest string
    if (result_struct.first.size()>result_struct.second.size()) {
        result_struct.second = std::string((largest_size-smallest_size), '0')+result_struct.second;
    }
    if (result_struct.first.size()<result_struct.second.size()) {
        result_struct.first = std::string((largest_size-smallest_size), '0')+result_struct.first;
    }

    return result_struct; // structured binding
}

Project1::BigInt::BigInt(long long int value)
{
    auto[temp_sign, number] = validate_and_parse_string(std::to_string(value));
    data = number;
    sign = temp_sign;
}

Project1::BigInt::BigInt(const std::string& value)
{
    auto[sign_local, str] = validate_and_parse_string(value);
    BigInt::sign = sign_local;
    data = str;
}

const BigInt& Project1::BigInt::operator=(const BigInt& e)
{
    this->data = e.data;
    this->sign = e.sign;
    return *this;
}

const BigInt& Project1::BigInt::operator+=(const BigInt& e)
{
    return *this = *this+e;
}

const BigInt& Project1::BigInt::operator-=(const BigInt& e)
{
    return *this = *this-e;
}

std::string Project1::subtractor(std::string const& s1, std::string const& s2)
{
    // Skip the any allocations if we can.
    if (s1=="0") return s2;
    else if (s2=="0") return s1;

    // A "sort" that values constness.
    std::string const& larger{Project1::is_less_than(s2, s1) ? s1 : s2};
    std::string const& smaller{Project1::is_less_than(s2, s1) ? s2 : s1};

    std::string result;
    result.reserve(larger.size()); // This should be enough to prevent any extra allocations

    auto larger_itr = larger.rbegin();
    auto smaller_itr = smaller.rbegin();

    // This over std::transform so we can keep the position of the large_itr for later use
    while (larger_itr!=larger.rend() && smaller_itr!=smaller.rend()) {
        result.push_back(static_cast<char>((*larger_itr-'0')-(*smaller_itr-'0')));
        larger_itr++;
        smaller_itr++;
    }

    std::for_each(larger_itr, larger.rend(), [&result](auto e) {
        result.push_back((e-'0'));
    });
    std::reverse(result.begin(), result.end());


    // For underflow. Not using for_each so we can better reason about iterators
    for (auto itr = result.rbegin(); itr!=result.rend(); itr++) {

        if (*itr<0) {
            if (itr+1!=result.rend()) {
                --(*(itr+1));
            }
            *itr += 10;
        }
        *itr += '0';
    }

    // Removes all leading 0s
    result.erase(0, result.find_first_not_of('0'));
    return result;
}

std::string Project1::adder(std::string const& addend1, std::string const& addend2)
{
    std::string result; // Will hold the accumulated value of addden1 and adden2
    auto[adder_a, adder_b] = prepareStringsForMath(addend1, addend2);

    auto itr_1 = adder_a.begin();
    auto itr_2 = adder_b.begin();


    // Not a ranged for two reasons. 1) So we can safely iterate over two iterators, and two, so we can resume for adding
    while (itr_1!=adder_a.end() && itr_2!=adder_b.end()) {
        result += static_cast<char>((*itr_1+*itr_2)-'0');

        itr_1++;
        itr_2++;
    }

    // To handle overflow
    auto itr_end = result.rend()-1;
    for (auto itr = result.rbegin(); itr!=itr_end; ++itr) {
        if (*itr>'9') {
            *itr -= 10;
            *(itr+1) += 1;
        }
    }

    // handles adding an extra digit to the front. (You can't have addition add more than a 1, so I can assume it's the case
    if (auto& front = result.front(); front>'9') {
        front -= 10;
        return '1'+result;
    }

    return result;
}

bool Project1::is_less_than(const std::string& a, const std::string& b)
{
    //To avoid iteration
    if (a.size()<b.size()) return true;
    if (a.size()>b.size()) return false;

    // a ranged based for loop isn't too far from a std::for_each, as it internally uses a begin..end
    // It also enables me to return directly from the loop, and use continue.
    for (auto const& element_a: a) {
        for (auto const& element_b: b) {
            if (element_a==element_b) continue;
            else if (element_b<element_a) return false;
            else return true;
        }
    }
    return true;
}
