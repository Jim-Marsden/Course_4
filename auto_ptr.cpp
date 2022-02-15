
//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 2/12/22.
// https://Github.com/Jim-Marsden/Course_4
// =====================================================================
// auto_ptr.cpp Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
//
// Tests for my auto_ptr
// =====================================================================
//

#include "auto_ptr.h"
using namespace JimMarsden;
#include "unit_test/UnitTest++.h"

TEST(auto_ptr_Constructor){
    {
        auto ptr = new int{0};
        auto_ptr x(ptr);
        CHECK(ptr==x.get());
    }
    {
        auto_ptr<int> x{};
        CHECK(x.get() == nullptr);
    }
    {
        auto ptr = new int{0};
        auto_ptr old_ptr(ptr);
        auto new_ptr = old_ptr;
        CHECK(ptr==new_ptr.get());
        CHECK(old_ptr.get() == nullptr);
    }
}

TEST(auto_ptr_Destructor){
    bool check_value{true};
    int * test_ptr;
    try{
        auto_ptr<int> x{};
    }
    catch (...){
        check_value = false;
    }
    CHECK(check_value);

}

TEST(auto_ptr_get){
    {
        auto ptr = new int(0);
        auto_ptr v(ptr);

        CHECK(*v.get() == 0);
        ++(*ptr);
        CHECK(*v.get() == 1);
    }
}

TEST(auto_ptr_operator_star){
    {
        auto ptr = new int(0);
        auto_ptr v(ptr);

        CHECK(*v == 0);
        ++(*ptr);
        CHECK(*v == 1);
    }
}

TEST(auto_ptr_member_access_oprator){
    struct test_struck{
        bool value{false};
    };

    auto_ptr ptr(new test_struck);
    CHECK(!ptr->value);
    ptr->value = true;
    CHECK(ptr->value);
}

TEST(auto_ptr_release){
    auto int_ptr = new int(0);
    {
        auto_ptr ptr(int_ptr);
        (*ptr)++;
        ptr.release();
    }
    CHECK(*int_ptr == 1);
    (*int_ptr)++;
    CHECK(*int_ptr == 2);
}

TEST(auto_ptr_reset){
    bool destructor_called{};
    struct destructor_test_object{
        bool & e;
        destructor_test_object() = delete;
        destructor_test_object(bool & in) : e{in}{ e = false;}
        ~destructor_test_object(){e = true;}

    };
    {
        auto_ptr ptr(new destructor_test_object{destructor_called});
        CHECK(!destructor_called);
        ptr.reset();
        CHECK(destructor_called);
        ptr.reset(new destructor_test_object(destructor_called));

    }
    CHECK(destructor_called);
}

int main(){
    auto tests = UnitTest::RunAllTests();

    return tests;
}