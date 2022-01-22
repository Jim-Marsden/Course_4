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
// A queue and related tests.
// =====================================================================
//

#include "unit_test/UnitTest++.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstring>

namespace JimMarsden {

    template<typename T>
    T* copyNew(T* src, size_t srcsize, size_t destsize)
    {
        assert(srcsize<=destsize);
        auto dest = new T[destsize];
        try {
            std::copy(src, src+srcsize, dest);
        }
        catch (...) {
            delete[] dest;
            throw;
        }
        return dest;
    }

    template<typename T>
    T* shrinkNew(T* src, size_t size, size_t to_shrink)
    {
        auto new_size = +size-to_shrink;
        auto dest = new T[+(size-to_shrink)];
        try {
            memcpy(&dest[0], &src[to_shrink], new_size*sizeof(T));
            //std::copy(src, src + new_size, dest);
        }
        catch (...) {
            delete[] dest;
            throw;
        }
        return dest;
    }

    template<typename T>
    class Queue {
    public:
        /* [Defaulted Constructors] ======================================================== [Defaulted Constructors] */
        Queue() noexcept = default;                        // Construct empty queue
        Queue(Queue&&) noexcept = default;        // Move constructor

        /* [Constructors] ============================================================================= [Constructors] */
        ~Queue() noexcept; // Destructor

        Queue(const Queue& elements); // Copy constructor

        Queue& operator=(const Queue& elements) = default;// Copy assignment operator

        // [Mutators/Accessors] =================================================================== [Mutators/Accessors]

        void push(const T& element);

        void pop();

        [[nodiscard("front is an accessor")]] T& front(); // Return ref to front elem in queue
        [[nodiscard("front is an accessor")]] const T& front() const;; // Return ref to front elem in queue
        // Return whether queue is empty
        [[nodiscard("Only checks if there aren't any elements")]] bool empty() const noexcept;

        [[nodiscard("size is an accessor")]] size_t
        size() const noexcept;;// Return # of elems in queue


    private:
        T* v_{nullptr};                           // Elems in queue
        size_t size_{0};
        /* Any other private members you need */
    };

    template<typename T>
    Queue<T>::Queue(const Queue& elements){
        T* temp_v = new T[elements.size_];

        for (auto i = 0; i<elements.size_; ++i) {
            temp_v[i] = elements.v_[i];
        }
        delete[] v_;
        v_ = temp_v;
        size_ = elements.size_;
    }

    template<typename T>
    Queue<T>::~Queue() noexcept
    {
        delete[] v_;
    }

    template<typename T>
    void Queue<T>::pop()
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        auto x = shrinkNew(v_, size_, 1);
        delete[] v_;
        v_ = x;
        size_--;
    }

    template<typename T>
    void Queue<T>::push(const T& element) {            // Add elem to back of queue
        size_t size1 = size_;
        v_ = copyNew<T>(v_, size1, size1+1);
        v_[size_] = element;
        size_++;
    }

    template<typename T>
    T& Queue<T>::front() {
        if (v_!=nullptr)
            return v_[0];
        throw std::logic_error("Queue is empty");

    }

    template<typename T>
    const T& Queue<T>::front() const {
        {
            if (size_>0)
                return v_[0];
            throw std::logic_error("Queue is empty");
        }

    }

    template<typename T>
    bool Queue<T>::empty() const noexcept { return size()==0; }

    template<typename T>
    size_t Queue<T>::size() const noexcept { return size_; }
}



// [TESTS] ===================================================================================================== [TESTS]

TEST(Queue_Default_Constructor)
{
    using namespace JimMarsden;

    Queue<int> queue;
    CHECK(queue.empty());
    CHECK(queue.size()==0);
}

TEST(Queue_Copy_Constor)
{
    using namespace JimMarsden;

    constexpr auto test_number1{0xDEAD};
    constexpr auto test_number2{0xC0FFEE};
    Queue<int> queue1;

    queue1.push(test_number1);

    Queue<int> queue2(queue1);
    CHECK(queue2.front()==test_number1);
    queue1.front() = test_number2;
    CHECK(queue2.front()==test_number1);

}

TEST(Queue_Copy_Assignment){
    using namespace JimMarsden;
    Queue<int> queue;

    queue.push(0);
    auto q2 = queue;
    CHECK(q2.front() == 0);
    queue.pop();
    CHECK(q2.front() == 0);
}

TEST(Queue_push)
{
    using namespace JimMarsden;
    constexpr auto test_number1{0xDEAD};
    constexpr auto test_number2{0xC0FFEE};
    Queue<int> queue1;
    CHECK(queue1.size()==0);
    queue1.push(test_number1);
    CHECK(queue1.size()==1);
    CHECK(queue1.front()==test_number1);
//
    queue1.push(test_number2);
    CHECK(queue1.size()==2);
    CHECK(queue1.front()==test_number1);
}

TEST(Queue_Pop)
{
    using namespace JimMarsden;

    bool catch_check{};
    Queue<int> queue;
    try {
        queue.pop();
    }
    catch (std::out_of_range& e) {
        catch_check = true;
    }

    CHECK(catch_check);

    queue.push(0);
    queue.push(0);
    queue.push(0);
    queue.push(0);
    int v{};
    while (!queue.empty()) {
        queue.pop();
        v++;
    }
    CHECK(v==4);
    catch_check = false;
    try {
        queue.pop();
    }
    catch (std::out_of_range& e) {
        catch_check = true;
    }
    CHECK(catch_check);
}

TEST(Queue_Front)
{
    using namespace JimMarsden;

    Queue<int> queue;
    bool catch_check{};

    try {
        auto v = queue.front();
    }
    catch (std::logic_error& e) {
        catch_check = true;
    }

    CHECK(catch_check);
    queue.push(1);
    CHECK(queue.front());
}

TEST(Queue_Const_Front)
{
    using namespace JimMarsden;

    Queue<int> queue;
    bool catch_check{};

    try {
        [](auto const& queue) {
            auto v = queue.front();
        }(queue);
    }
    catch (std::logic_error& e) {
        catch_check = true;
    }

    CHECK(catch_check);
    queue.push(1);
    CHECK([](auto const& queue) { return queue.front(); }(queue));
}

TEST(Queue_Empty){
    using namespace JimMarsden;
    Queue<int> queue;

    CHECK(queue.empty());
    try {
        queue.pop();
    }
    catch (...){}
    CHECK(queue.empty());
    queue.push({});
    CHECK(!queue.empty());
}



TEST(Queue_Size){
    using namespace JimMarsden;
    Queue<int> queue;

    CHECK(queue.size()==0);
    try {
        queue.pop();
    }
    catch (...){}
    CHECK(queue.size() == 0);
    queue.push({});
    CHECK(queue.size() == 1);
}


int main()
{
    auto test_status = UnitTest::RunAllTests(); // test runner.
    return test_status;
}