//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 2/16/22.
// https://Github.com/Jim-Marsden/Course_4
// =====================================================================
// main.cpp Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
//
// Two templated functions:
//
// 1) Palidrome Takes two bidirectional Iterators, and iterates over the
// collection to ensure it's a plandrome
//
// 2) removes duplicate elements from a collection
// =====================================================================
//

#include <algorithm> // For -- for_each
namespace JimMarsden {
    template<typename BidirectionalIterator>
    bool palindrome(BidirectionalIterator first, BidirectionalIterator last){

        //Checks for valid size and ranges
        if(std::distance(first, last) <= 1) return true;
        if(first == last) return false;


        // To have easy end points for the iterators
        auto front_end = last;
        auto last_end = first;

        // evens out the end iterator for safety.
        --last;
        ++last_end;

        do{
            if(*first != *last) return false;
            if(last == first) return true; // We know the size is atleast 1, so if they're equal, it's valid
            if(last != last_end) --last; else break; // valid, skipping
            if(first != front_end) ++first; else break; // valid, skipping

        } while((std::distance(first, last) / 2) <= 1);
        return true;
    }

    template <typename ForwardIterator, typename OutputIterator>
    void compress(ForwardIterator first, ForwardIterator last, OutputIterator result){
        std::for_each(first, last, [&result, is_first = true, prev = *first]  (auto e) mutable {
            [[unlikely]] if(is_first){  // For first loop iteration
                is_first = false;
                *result = e; //
            }
            else{
                if(prev != e){
                    *result = e;
                    prev = e;
                }
            }
        });
    }
}


#include "unit_test/UnitTest++.h"
#include <list>
TEST(Palandron_Match_Even) {
    
    std::list lst = { 1 , 2, 3 ,3 ,2 ,1 };
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));


    lst.pop_back();
    lst.pop_front();
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));
}

TEST(Palandron_Match_Odd) {

    std::list lst = { 1 , 2, 3, 4 ,3 ,2 ,1 };
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(JimMarsden::palindrome(lst.begin(), lst.end()));

}


TEST(Palandron_Missmatch_Even) {

    std::list lst = { 1 , 2, 3 ,4 ,5 ,6 };
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));


    lst.pop_back();
    lst.pop_front();
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));
}

TEST(Palandron_Missmatch_Odd) {

    std::list lst = { 2 , 1, 4, 5 ,3 ,2 ,1 };
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));

    lst.pop_back();
    lst.pop_front();
    CHECK(!JimMarsden::palindrome(lst.begin(), lst.end()));
}

TEST(Compression_valid){
    std::list<int> test_list{1, 2, 2, 1, 1, 3, 3, 4, 5};
    std::list<int>  const correct = {1, 2, 1, 3, 4, 5};
    std::list<int> result;
    JimMarsden::compress(test_list.begin(), test_list.end(), std::back_inserter(result));
    CHECK(result == correct);
}


TEST(Compression_two){
    std::list<int> test_list{1, 2, 2, 1, 1, 3, 3, 4, 5, 1, 1};
    std::list<int>  const correct = {1, 2, 1, 3, 4, 5, 1};
    std::list<int> result;
    JimMarsden::compress(test_list.begin(), test_list.end(), std::back_inserter(result));
    CHECK(result == correct);
}


TEST(Compression_three){
    std::list<int> test_list{1, 2, 3};
    std::list<int>  const correct = {1, 2, 3};
    std::list<int> result;
    JimMarsden::compress(test_list.begin(), test_list.end(), std::back_inserter(result));
    CHECK(result == correct);
}
int main() {
    auto result = UnitTest::RunAllTests();

    return result;

}