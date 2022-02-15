
//
// Jim Marsden (U09247027)
// JimPMarsden@gmail.com
// 160707 C/C++ Programming IV: Advanced Programming with Objects
// 159167 C/C++ Programming III -- Ray Mitchell
// Created on 2/12/22.
// https://Github.com/Jim-Marsden/Course_4
// =====================================================================
// auto_ptr.h Tested on Linux on Clang 12 and g++ 11.1.0 built with C++17
//
// A simple, potentially unsafe smart pointer.
// =====================================================================
//
// ==========================[notes]====================================
// As throw() is deprecated, I used noexcept as that supplanted it.
// All member functions could safely be marked constexpr in c++14
// =====================================================================
//

#ifndef COURSE_4_AUTO_PTR_H
#define COURSE_4_AUTO_PTR_H
namespace JimMarsden {
    template<typename X>
    class auto_ptr {
    public:
        // Constructors
        explicit auto_ptr(X* = nullptr) noexcept;

        auto_ptr(auto_ptr&) noexcept;

        template<typename Y>
        auto_ptr(auto_ptr<Y>&) noexcept;

        // Destructor
        ~auto_ptr() noexcept;

        // Access
        X* get() const noexcept;

        X& operator*() const noexcept;

        X* operator->() const noexcept;

        // Assignment
        auto_ptr& operator=(auto_ptr&) noexcept;

        template<typename Y>
        auto_ptr& operator=(auto_ptr<Y>&) noexcept;

        // Release & Reset
        X* release() noexcept;

        void reset(X* = nullptr) noexcept;

    private:
        X* xptr_{nullptr};
    };

    template<typename X>
    auto_ptr<X>::auto_ptr(X* xptr) noexcept
    {
        xptr_ = xptr;
    }

    template<typename X>
    auto_ptr<X>::auto_ptr(auto_ptr& auto_ptr1) noexcept
    {
        xptr_ = auto_ptr1.xptr_;
        auto_ptr1.xptr_ = nullptr;
    }

    template<typename X>
    auto_ptr<X>::~auto_ptr() noexcept
    {
        delete xptr_;
        xptr_ = nullptr;
    }

    template<typename X>
    X* auto_ptr<X>::get() const noexcept
    {
        return xptr_;
    }

    template<typename X>
    X& auto_ptr<X>::operator*() const noexcept
    {
        return *xptr_;
    }

    template<typename X>
    X* auto_ptr<X>::operator->() const noexcept
    {
        return xptr_;
    }

    template<typename X>
    auto_ptr<X>& auto_ptr<X>::operator=(auto_ptr& ptr) noexcept
    {
        xptr_ = ptr.xptr_;
        ptr.xptr_ = nullptr;
        return *this;
    }

    template<typename X>
    X* auto_ptr<X>::release() noexcept
    {
        auto t_ptr{xptr_};
        xptr_ = nullptr;
        return t_ptr;
    }

    template<typename X>
    void auto_ptr<X>::reset(X* xptr) noexcept
    {
        delete xptr_;
        xptr_ = xptr;
    }
}
#endif //COURSE_4_AUTO_PTR_H
