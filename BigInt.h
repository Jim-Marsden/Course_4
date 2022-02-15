
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


#ifndef COURSE_4_BIGINT_H
#define COURSE_4_BIGINT_H

#include <string>
#include <iostream>

//#include <vector>
#include <algorithm>

namespace Project1 {

    enum class BigIntSign {
        default_positive, // used for varification of proper initialization. Internally only checks agianst negative.
        positive,
        negative, // should be what's checked for
    };

    class BigInt {

        // [Friend Operators] ======================================================================= [Friend Operators]
        friend const BigInt operator+(const BigInt&, const BigInt&);

        friend const BigInt operator-(const BigInt&, const BigInt&);

        friend bool operator==(const BigInt&, const BigInt&);

        friend bool operator!=(const BigInt&, const BigInt&);

        friend bool operator<(const BigInt&, const BigInt&);

        friend bool operator<=(const BigInt&, const BigInt&);

        friend bool operator>(const BigInt&, const BigInt&);

        friend bool operator>=(const BigInt&, const BigInt&);

        friend std::ostream& operator<<(std::ostream&, const BigInt&);

        friend std::istream& operator>>(std::istream&, BigInt&);

    public:
        // [Constructors] =============================================================================== [Constructors]
        BigInt() = default;

        BigInt(const BigInt&) = default;

        /*implicit*/ BigInt(long long);

        /*implicit*/ BigInt(const std::string&);

        const BigInt& operator=(const BigInt&);

        const BigInt& operator+=(const BigInt&);

        const BigInt& operator-=(const BigInt&);

    private:
        std::string data{"0"};
        BigIntSign sign{};
    };


    // [Helper Functions] =========================================================================== [Helper Functions]

    // Returns the sum of the two strings, does not indicate negative.
    std::string adder(std::string const&, std::string const&);

    // returns the result of subtracting two strings, does not indicate negative.
    std::string subtractor(std::string const&, std::string const&);

    bool is_less_than(std::string const& a, std::string const& b);

    // Returns a structure that holds the key bits for a BigInt. It validates value and if it's invalid, it throws an invalid argument.
    inline auto validate_and_parse_string(std::string const& value)
    {
        struct result_struct_ {// Structured Binding for a bigint, to be used to construct one.
            BigIntSign sign{};
            std::string numbers;
        } result_struct{{}, value};

        if (value.empty()) throw std::invalid_argument("Numeric string contains non numeric values");
        //Ensures that if there is only one element, it's a digit (ergo, valid).
        if (value.size()==1) {
            if (!std::isdigit(value.front())) throw std::invalid_argument("Numeric string contains non numeric values");
        }

        //Skipps the first element, and validates the rest to be digits.
        std::for_each(value.begin()+1, value.end(), [](auto const& e) {
            if (!std::isdigit(e))
                throw std::invalid_argument("Numeric string contains non numeric values");
        });

        // throws if there are leading 0s
        if (value.find_first_not_of('0')==std::string::npos && value.size()>1)
            throw std::invalid_argument(
                    "String must be 0, or \"\"");


        // validates the first element to be a valid operator.
        switch (result_struct.numbers.front()) {
        case '+':
            result_struct.sign = BigIntSign::positive;
            break;
        case '-':
            result_struct.sign = BigIntSign::negative;
            break;
        default:
            if (!isdigit(value.front())) throw std::invalid_argument("Numeric string contains non numeric values");
            result_struct.sign = BigIntSign::default_positive;
            break;
        }

        if (result_struct.sign!=BigIntSign::default_positive) {
            result_struct.numbers = std::string(result_struct.numbers.begin()+1, result_struct.numbers.end());
        }

        if (result_struct.numbers.size()==1 && result_struct.numbers.front()=='0')
            result_struct.sign = BigIntSign::positive;

        return result_struct;
    };

    // [inline operators] =========================================================================== [inline operators]
    inline BigInt const operator+(BigInt const& addend1, BigInt const& addend2)
    {
        // To minimize code.
        auto negative_check = [](auto const& e1, auto const& e2) {
            auto v = subtractor(e1.data, e2.data);
            if (e1.sign==BigIntSign::negative && is_less_than(e2.data, e1.data)) {
                return "-"+v;
            }
            return v;
        };

        if (addend1.sign==addend2.sign) {
            if (addend1.sign==BigIntSign::negative) return '-'+adder(addend1.data, addend2.data);
            else return adder(addend1.data, addend2.data);
        }
        else {
            if (addend1.data!=addend2.data) {
                if (addend1.sign==BigIntSign::negative) {
                    return negative_check(addend1, addend2);
                }
                else return negative_check(addend2, addend1);
            }
            else return {"0"};

        }
    }

    inline BigInt const operator-(BigInt const& a, BigInt const& b)
    {
        // Try to avoid any complicated string manipulations
        if (a.data==b.data) return {"0"};
        else if (a.data=="0") { return "-" + b.data; }
        else if (b.data=="0") { return a; }

       if (a.sign==b.sign) { // If they're both positive or negative Do simple subtraction
            auto result = subtractor(a.data, b.data);
            if (a.sign==BigIntSign::negative) {
                if (is_less_than(b.data, a.data)) {
                    return "-"+result;
                }
                else return result;
            }
            else {
                if (is_less_than(a.data, b.data)) {
                    return "-"+result;
                }
                else return result;
            }

        }
        else { // If mixed signs do addition
            auto result = adder(a.data, b.data);
            if (a.sign==BigIntSign::negative && is_less_than(a.data, b.data)) {
                return "-"+result;
            }
            if (a.sign==BigIntSign::negative && is_less_than(a.data, a.data)) {
                return "-"+result;
            }
            else {
                return result;
            }
        }
    }

    // [Comparison Operators] =================================================================== [Comparison Operators]
    inline bool operator==(const BigInt& comp1, const BigInt& comp2)
    {
        return comp1.data==comp2.data && comp1.sign==comp2.sign;
    }

    inline bool operator!=(const BigInt& comp1, const BigInt& comp2) { return !(comp1==comp2); }

    inline bool operator<(const BigInt& comp1, const BigInt& comp2)
    {
        if (comp1.sign==BigIntSign::negative && comp2.sign!=BigIntSign::negative) return true;
        if (comp1.sign==BigIntSign::negative && comp2.sign==BigIntSign::negative) return comp1.data>comp2.data;
        return comp1.data<comp2.data;
    }

    inline bool operator<=(const BigInt& comp1, const BigInt& comp2) { return comp1<comp2 || comp1==comp2; }

    inline bool operator>(const BigInt& comp1, const BigInt& comp2)
    {
        if (comp1.sign!=BigIntSign::negative && comp2.sign==BigIntSign::negative) return true;
        if (comp1.sign==BigIntSign::negative && comp2.sign==BigIntSign::negative) return comp1.data<comp2.data;
        return comp1.data>comp2.data;
    }

    inline bool operator>=(const BigInt& comp1, const BigInt& comp2) { return comp1>comp2 || comp1==comp2; }

    // [Stream Operators] =========================================================================== [Stream Operators]
    inline std::ostream& operator<<(std::ostream& os, const BigInt& big_int)
    {
        if (big_int.data.empty()) return os << '0';
        if (big_int.sign==BigIntSign::negative) os << '-';
        return os << big_int.data;
    }

    inline std::istream& operator>>(std::istream& is, BigInt& big_int)
    {
        std::string temp_string;
        is >> temp_string;
        // Validate from istream, if it is invalid, it will throw.
        auto[sign_local, str] = validate_and_parse_string(temp_string);
        big_int.sign = sign_local;
        big_int.data = str;
        return is;
    }


}
#endif //COURSE_4_BIGINT_H
