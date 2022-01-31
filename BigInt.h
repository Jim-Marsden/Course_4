//
// Created by snizzfox on 1/29/22.
//

#ifndef COURSE_4_BIGINT_H
#define COURSE_4_BIGINT_H

#include <string>
#include <iostream>

#include <vector>

namespace Project1 {
    class BigInt {
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
        BigInt() = default;

        BigInt(const BigInt&) = default;

        BigInt(long long);

// Throws invalid_argument if string malformed (contains
// anything other than a legally formatted number)
        BigInt(const std::string&);

        const BigInt& operator=(const BigInt&);

        const BigInt& operator+=(const BigInt&);

        const BigInt& operator-=(const BigInt&);

    private:
        std::vector<unsigned char> data;
        bool is_negitive{false};
// You decide what goes here...
    };

    std::string
    adder(std::string addend1, std::string addend2 );

    std::string
    substractor(std::string::iterator str1_begin, std::string::iterator str1_end, std::string::iterator str2_begin,
            std::string::iterator str2_end);

    inline BigInt const operator+(BigInt const& addend1, BigInt const& addend2) {

        return {};
    }

    inline BigInt const operator-(BigInt const&, BigInt const&) { return {}; }

    inline bool operator==(const BigInt&, const BigInt&) { return {}; }

    inline bool operator!=(const BigInt&, const BigInt&) { return {}; }

    inline bool operator<(const BigInt&, const BigInt&) { return {}; }

    inline bool operator<=(const BigInt&, const BigInt&) { return {}; }

    inline bool operator>(const BigInt&, const BigInt&) { return {}; }

    inline bool operator>=(const BigInt&, const BigInt&) { return {}; }

    inline std::ostream& operator<<(std::ostream& os, const BigInt& big_int) { return os;}

    inline std::istream& operator>>(std::istream& is, BigInt&) { return is; }

}
#endif //COURSE_4_BIGINT_H
