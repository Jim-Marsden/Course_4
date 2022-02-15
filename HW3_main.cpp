//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 1/17/22.
// https://Github.com/Jim-Marsden/Course_4
// =====================================================================
// main.cpp Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
//
// A stream processor that takes in two stream objects, and processes
// based on filters.
// Unittests based on two sample processors.
// =====================================================================
//

#include "unit_test/UnitTest++.h"

#include <string> // for token strings
#include <sstream> // for strign stream
#include <algorithm> // for find/erase

namespace JimMarsden {
    class StreamProcessorAlgorithm { // Base "Template Method Class" for the Stream Processor
    public:

        // [Constructors] =============================================================================== [Constructors]
        StreamProcessorAlgorithm(std::istream& in, std::ostream& out)
                :in_{in}, out_{out} { }

        StreamProcessorAlgorithm() = delete;

        StreamProcessorAlgorithm(StreamProcessorAlgorithm const&) = delete;

        StreamProcessorAlgorithm(StreamProcessorAlgorithm&&) = default;

        virtual ~StreamProcessorAlgorithm() = default;

        StreamProcessorAlgorithm& operator=(StreamProcessorAlgorithm const&) = default;

        // Processes the in_ stream and based on the pure virtual functions, filterToken, and processToken into the out_ stream.
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
        virtual bool filterToken(const std::string& token) const = 0; // if true, filter, else don't filter

        virtual void processToken(std::string& token) const = 0; // mutates the token

    private:

        std::istream& in_;
        std::ostream& out_;
    };

    class UppercasingSPA : public StreamProcessorAlgorithm { // changes the lowers the case of the input stream
    public:

        UppercasingSPA(std::istream& in, std::ostream& out)
                :StreamProcessorAlgorithm(in, out) { }

    protected:
        [[nodiscard("The whole point of this member function is to decide if the token should be filtered.")]]
        bool filterToken(const std::string& token) const override { return false; }

        void processToken(std::string& token) const override
        {
            std::for_each(token.begin(), token.end(), [](auto& e) { e = std::toupper(e); });
        }
    };

    class DigitStrippingSPA : public StreamProcessorAlgorithm { // Gets everything that has a number, and removes the number.
    public:

        DigitStrippingSPA(std::istream & in, std::ostream& out) : StreamProcessorAlgorithm(in, out) { }

    protected:
        [[nodiscard("The whole point of this member function is to decide if the token should be filtered.")]]
        bool filterToken(const std::string& token) const override {
            bool result{};

            auto found = std::find_if(token.begin(), token.end(), [&result](auto e){
                return std::isdigit(e);;
            });

            return found == token.end();
        }

        void processToken(std::string& token) const override
        {
            token.erase(std::find_if(token.begin(), token.end(), [](auto e){return std::isdigit(e);}));
        }
    };
}


// [Tests] ===================================================================================================== [Tests]

template<class Test_String_T, class Processor_T>
bool simple_test(Test_String_T const & input, Test_String_T const& expected){
    std::stringstream in_stream, out_stream;

    in_stream << input;
    Processor_T Stream_Processor(in_stream, out_stream);
    Stream_Processor.process();

    return out_stream.str()==expected;

}

TEST(UppercasingSPA_Empty)
{
    auto c = simple_test<std::string, JimMarsden::UppercasingSPA>("", "");
    CHECK(c);
}

TEST(UppercasingSPA_Lower)
{
    auto test1  =simple_test<std::string, JimMarsden::UppercasingSPA>("aSdF", "ASDF");
    auto test2  =simple_test<std::string, JimMarsden::UppercasingSPA>("asdf", "ASDF");
    auto test3  =simple_test<std::string, JimMarsden::UppercasingSPA>("asdf asdf", "ASDF ASDF");

    CHECK(test1);
    CHECK(test2);
    CHECK(test3);
}

TEST(DigitStrippingSPA_Empty){
    auto c = simple_test<std::string, JimMarsden::DigitStrippingSPA>("", "");
    CHECK(c);
}


TEST(DigitStrippingSPA_Filter_And_Alter)
{
    auto test1 = simple_test<std::string, JimMarsden::DigitStrippingSPA>("zzz asdf1", "asdf");
    auto test2 = simple_test<std::string, JimMarsden::DigitStrippingSPA>("asdf1 asdf1", "asdf asdf");
    CHECK(test1);
    CHECK(test2);
}

// [Main] ======================================================================================================= [Main]
int main()
{
    auto test_status = UnitTest::RunAllTests(); // test runner.
    return test_status;
}