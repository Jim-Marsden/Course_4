//
// Created by james on 1/17/2022.
//


#include "unit_test/UnitTest++.h"
#include <stdexcept>
#include <iostream>

template<typename T>
class Queue {
public:
    /* [Defaulted Constructors] ================================================================================ [Defaulted Constructors] */
    Queue() = default;                        // Construct empty queue
    Queue(Queue&&) noexcept = default;        // Move constructor

    /* [Constructors] ================================================================================ [Constructors] */
    ~Queue() { // Destructor
        delete[] v_;
    }

    Queue(const Queue& elements) // Copy constructor
    {
        T* temp_v = new T[elements.size_]; // if this fails, let the caller handle the error. An out of memory expetion would be best not hidden.

        for (auto i = 0; i<elements.size_; ++i) {
            temp_v[i] = elements.v_[i];
        }
        delete[] v_;
        v_ = temp_v;
        size_ = elements.size_;
    }
    void push(const T& element){            // Add elem to back of queue
        {
            if (v_==nullptr) {
                v_ = new T[1];
                size_ = 1;
                v_[0] = element;
                return;
            }

            auto temp_size{size_+1};
            auto temp_array = new T[temp_size];

            for (auto i{0}; i<size_; ++i) {
                temp_array[i] = v_[i];
            }
            temp_array[temp_size-1] = element;

            delete[] v_;
            v_ = temp_array;
            size_ = temp_size;

        }
    }

    Queue& operator=(const Queue& elements) // Copy assignment operator
    {
        T* temp_v = new T[elements.size_]; // if this fails, let the caller handle the error. An out of memory expetion would be best not hidden.

        for (auto i = 0; i<elements.size_; ++i) {
            temp_v[i] = elements.v_[i];
        }
        delete[] v_;
        v_ = temp_v;
        size_ = elements.size_;
    }
    // [Mutators/Accessors] ======================================================================= [Mutators/Accessors]
    void pop(){
        if (empty()) throw std::out_of_range("Queue is empty");
        auto temp_size = size_-1;
        auto temp_v = new T[temp_size];
        for (auto i{0}; i<temp_size; ++i) {
            temp_v[i] = v_[i];
        }
        delete[] v_;
        v_ = temp_v;
        size_ = temp_size;
    } // Remove front elem from queue
    [[nodiscard("front is an accessor")]] T& front(){
        {
            if (v_!=nullptr)
                return v_[0];
            throw std::out_of_range("Queue is empty");
        }

    } // Return ref to front elem in queue
    [[nodiscard("front is an accessor")]] const T& front() const {
        {
            if (size_>0)
                return v_[0];
            throw std::out_of_range("Queue is empty");
        }

    }; // Return ref to front elem in queue
    // Return whether queue is empty
    [[nodiscard("Only checks if there aren't any elements")]] bool empty() const noexcept {return size() == 0;}
    [[nodiscard("size is an accessor")]] size_t size() const noexcept { return size_; };// Return # of elems in queue


private:
    T* v_{nullptr};                           // Elems in queue
    size_t size_{0};
    /* Any other private members you need */
};

TEST(Queue_push)
{
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

TEST(Queue_Copy_Constor)
{
    constexpr auto test_number1{0xDEAD};
    constexpr auto test_number2{0xC0FFEE};
    Queue<int> queue1;

    queue1.push(test_number1);

    Queue<int> queue2(queue1);
    CHECK(queue2.front()==test_number1);
    queue1.front() = test_number2;
    CHECK(queue2.front()==test_number1);

}

TEST(Queue_Pop)
{
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


TEST(Queue_Default_Constructor){
    Queue<int> queue;
    CHECK(queue.empty());
    CHECK(queue.size() == 0);
}

TEST(Queue_Front){
    Queue<int> queue;
    bool catch_check{};

    try{
        auto v = queue.front();
    }
    catch (std::out_of_range & e){
        catch_check = true;
    }

    CHECK(catch_check);
    queue.push(1);
    CHECK(queue.front());
}


TEST(Queue_Const_Front){
    Queue<int> queue;
    bool catch_check{};

    try{
        [](auto const & queue) {
            auto v = queue.front();
        }(queue);
    }
    catch (std::out_of_range & e){
        catch_check = true;
    }

    CHECK(catch_check);
    queue.push(1);
    CHECK([](auto const & queue){ return queue.front();}(queue));
}



//TEST(Queue_)

int main()
{
    auto test_status = UnitTest::RunAllTests(); // test runner.
    return test_status;
}