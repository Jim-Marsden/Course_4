//
// Created by snizzfox on 1/27/22.
//

#include "unit_test/UnitTest++.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace JimMarsden {
    class StreamProcessorAlgorithm {
    public:
        StreamProcessorAlgorithm(std::istream& in, std::ostream& out)
                :in_{in}, out_{out} { }

        StreamProcessorAlgorithm() = delete;

        StreamProcessorAlgorithm(StreamProcessorAlgorithm const&) = delete;

        StreamProcessorAlgorithm(StreamProcessorAlgorithm&&) = default;

        virtual ~StreamProcessorAlgorithm() = default;

        StreamProcessorAlgorithm& operator=(StreamProcessorAlgorithm const&) = default;

        void process()
        {
            bool padding{};
            std::string token;
            while (in_ >> token) {
                if (!filterToken(token)) {
                    processToken(token);
                    if (!padding) {
                        out_ << token;
                        padding = true;
                    }
                    else {
                        out_ << ' ' << token;
                    }
                }
            }
        }

    protected:
        [[nodiscard("The whole point of this member function is to decide if the token should be filtered.")]]
        virtual bool filterToken(const std::string& token) const = 0;

        virtual void processToken(std::string& token) const = 0;

    private:

        std::istream& in_;
        std::ostream& out_;
    };

    class UppercasingSPA : public StreamProcessorAlgorithm {
    public:

        UppercasingSPA(std::istream& in, std::ostream& out)
                :StreamProcessorAlgorithm(in, out) { }

    protected:
        [[nodiscard("The whole point of this member function is to decide if the token should be filtered.")]]
        bool filterToken(const std::string& token) const override { return false; }

        void processToken(std::string& token) const override
        {
            std::for_each(token.begin(), token.end(), [](auto& e) { e = std::toupper(e, std::locale()); });
        }
    };

    class DigitStrippingSPA : public StreamProcessorAlgorithm {
    public:

        DigitStrippingSPA(std::istream & in, std::ostream& out) : StreamProcessorAlgorithm(in, out) { }

    protected:
        [[nodiscard("The whole point of this member function is to decide if the token should be filtered.")]]
        bool filterToken(const std::string& token) const override {
            bool result{};

            auto found = std::find_if(token.begin(), token.end(), [&result](auto e){
                return std::isdigit(e, std::locale());;
            });

            return found == token.end();
        }

        void processToken(std::string& token) const override
        {
            token.erase(std::find_if(token.begin(), token.end(), [](auto e){return std::isdigit(e, std::locale());}));
        }
    };
}
TEST(UppercasingSPA_Empty)
{
    std::stringstream in, out;
    JimMarsden::UppercasingSPA uppercasing_spa(in, out);
    uppercasing_spa.process();

    CHECK(out.str().empty());
}

TEST(UppercasingSPA_Lower)
{

    {
        constexpr auto lower_test_lower{"asdf"};
        constexpr auto lower_test_upper{"ASDF"};
        std::stringstream in_only_lower, out_only_lower;
        in_only_lower << lower_test_lower;
        JimMarsden::UppercasingSPA uppercasing_lower(in_only_lower, out_only_lower);
        uppercasing_lower.process();

        CHECK(out_only_lower.str()==lower_test_upper);
    }

    {
        constexpr auto lower_test_lower{"aSdF"};
        constexpr auto lower_test_upper{"ASDF"};
        std::stringstream in_only_lower, out_only_lower;
        in_only_lower << lower_test_lower;
        JimMarsden::UppercasingSPA uppercasing_lower(in_only_lower, out_only_lower);
        uppercasing_lower.process();
        CHECK(out_only_lower.str()==lower_test_upper);
    }
}

TEST(DigitStrippingSPA_Empty){
    std::stringstream in, out;
    JimMarsden::UppercasingSPA uppercasing_spa(in, out);
    uppercasing_spa.process();

    CHECK(out.str().empty());
}

TEST(DigitStrippingSPA_HasNumbers)
{

    {
        constexpr auto lower_test_lower{"zzzz asdf1"};
        constexpr auto lower_test_upper{"asdf"};
        std::stringstream in_only_lower, out_only_lower;
        in_only_lower << lower_test_lower;
        JimMarsden::DigitStrippingSPA uppercasing_lower(in_only_lower, out_only_lower);
        uppercasing_lower.process();
        CHECK(out_only_lower.str()==lower_test_upper);
    }

    {
        constexpr auto lower_test_lower{"asdf1 asdf1"};
        constexpr auto lower_test_upper{"asdf asdf"};
        std::stringstream in_only_lower, out_only_lower;
        in_only_lower << lower_test_lower;
        JimMarsden::DigitStrippingSPA uppercasing_lower(in_only_lower, out_only_lower);
        uppercasing_lower.process();
        CHECK(out_only_lower.str()==lower_test_upper);
    }
}

int main()
{
    auto test_status = UnitTest::RunAllTests(); // test runner.
    return test_status;
}