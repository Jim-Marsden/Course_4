#include <algorithm>

// TODO: Change node to force guards
// TODO: Validate email from Ray    

#ifndef COURSE_4_DLIST_H
#define COURSE_4_DLIST_H

namespace Project2 {
    template<typename T>
    class dlist {
    public:
        // Types 
        class iterator;

        typedef size_t size_type;
        [[maybe_unused]] typedef T value_type;
        [[maybe_unused]] typedef const T const_reference;

        struct node {
            node *previous{nullptr}, *next{nullptr};
            T data;
        };
        using node_ptr = node *;

        // Default constructor 
        dlist() {
            initialize();
            front_value = back_value = sentinel;
        }

        // Copy constructor 
        dlist(const dlist &other) {
            initialize();
            for (auto i = other.front_value; i != other.sentinel; i = i->next) {
                push_back(i->data);
            }
        };

        // Iterator range constructor 
        template<typename InputIterator>
        dlist(InputIterator first,
              InputIterator last) {
            initialize();
            std::for_each(first, last, [this](auto &e) { this->push_back(e); });
        };

        // Destructor
        ~dlist() {
            while (!empty()) pop_front();
            delete sentinel;
        }

        // Copy assginment operator 
        dlist &operator=(const dlist &other) {
            dlist temp{other};
            std::swap(temp.front_value, front_value);
            std::swap(temp.back_value, back_value);
            std::swap(temp.size_value, size_value);
            return *this;
        };

        // empty() & size() 
        [[nodiscard("This function is meant only to check if a string is empty")]]
        bool empty() const { return size_value == 0; }

        [[nodiscard("This fucntion is meant to get the size of the string")]] size_type
        size() const { return size_value; }

        // front() & back() 
        T &front() {
            return front_value->data;
        }

        const T &front() const { return front_value->data; }

        T &back() { return back_value->data; }

        const T &back() const { return back_value->data; }

        // Modifiers 
        void push_front(const T &val) {

            if (front_value == sentinel) {
                back_value = front_value = new node{sentinel, sentinel, val};
                sentinel->next = front_value;
                sentinel->previous = back_value;
            } else if (front_value == back_value) {
                front_value = new node{sentinel, back_value, val};
                front_value->next = back_value;
            } else {
                front_value = new node{sentinel, front_value, val};
                front_value->next->previous = front_value;
            }
            ++size_value;
        }

        void pop_front() {

            if (front_value != sentinel) {
                if (front_value == back_value) {
                    delete front_value;
                    front_value = back_value = sentinel;
                } else {
                    auto next = front_value->next;
                    next->previous = sentinel;
                    delete front_value;
                    front_value = next;
                }
            }
            --size_value;
        }

        void push_back(const T &val) {

            if (back_value == sentinel) {
                back_value = front_value = new node{sentinel, sentinel, val};
                sentinel->next = front_value;
                sentinel->previous = back_value;
            } else if (back_value == front_value) {
                back_value = new node{front_value, sentinel, val};
                sentinel->previous = back_value;
                front_value->next = back_value;
            } else {
                back_value = new node{back_value, sentinel, val};
                back_value->previous->next = back_value;
                sentinel->previous = back_value;
            }

            ++size_value;
        }

        void pop_back() {
            {
                if (back_value == front_value) {
                    delete front_value;
                    front_value = sentinel;
                    back_value = sentinel;
                } else {
                    auto old_back = back_value;
                    back_value = back_value->previous;
                    delete old_back;
                }
                --size_value;
            }
        }

        iterator insert(iterator itr, const T &value) {

            if (front_value == back_value || front_value == sentinel) {
                push_back(value);
                return begin();
            } else if (itr == begin()) {
                push_front(value);
                return begin();
            } else if (itr == end()) {
                push_back(value);
                return --(iterator(back_value));
            } else {

                for (auto temp_node = front_value; temp_node != sentinel; temp_node = temp_node->next) {
                    if (iterator(temp_node) == itr) {
                        auto new_node = new node{temp_node, temp_node->next};
                        new_node->previous->next = new_node;
                        new_node->next->previous = new_node;

                        ++size_value;
                        return iterator(new_node->previous);
                    }
                }

                // When it's invalid or at the end.
                push_back(value);
                return --end();


            }
        }

        iterator erase(iterator itr) {

            node_ptr target = front_value;
            iterator itr2(target);
            while (itr2 != itr) {
                ++itr2;
                target = target->next;
                if (itr2 == end()) { return end(); }
            }

            if (front_value == target) {
                pop_front();
                return iterator(front_value);
            } else if (back_value == target) {
                pop_back();
                return iterator(back_value);
            } else {
                auto prev = target->previous;
                auto next = target->next;
                prev->next = next;
                next->previous = prev;

                delete target;
                --size_value;
                target = next;
            }


            return iterator(target);
        }


        // Comparision
        bool operator==(const dlist &other) const {
            if (this == &other) return true;
            if (other.size_value != size_value) return false;
            // Explicit scope
            {
                node_ptr this_current_node = front_value;
                node_ptr other_current_node = other.front_value;
                while (this_current_node != sentinel && other_current_node != sentinel) {

                    if (this_current_node->data != other_current_node->data) return false;

                    other_current_node = other_current_node->next;
                    this_current_node = this_current_node->next;
                }
            }
            return true;
        }

        bool operator!=(const dlist &other) const { return !(operator==(other)); }

        bool operator<(const dlist &other) const {
            if (this == &other) return false;
            if (size_value < other.size_value) return true;
            if (other.size_value != size_value) return false;
            // Explicit scope
            {
                node_ptr this_current_node = front_value;
                node_ptr other_current_node = other.front_value;
                while (this_current_node != sentinel && other_current_node) {

                    if (this_current_node->data >= other_current_node->data) return false;

                    other_current_node = other_current_node->next;
                    this_current_node = this_current_node->next;
                }
            }
            return true;
        }

        bool operator<=(const dlist &other) const { return (operator<(other) || operator==(other)); }

        bool operator>(const dlist &other) const { return !operator<(other) && operator!=(other); }

        bool operator>=(const dlist &other) const { return !operator<(other); }

        // Iterators 
        iterator begin() { return iterator(front_value); }

        const iterator begin() const { return iterator(front_value); }

        iterator end() {
            return iterator(sentinel);
        }

        const iterator end() const { return iterator(back_value); }

    private:
        // You decide what goes here

        size_t size_value{0};
        node_ptr front_value{nullptr};
        node_ptr back_value{nullptr};
        node_ptr sentinel{nullptr};

        void initialize() {
            size_value = 0;
            front_value = back_value = sentinel = new node{nullptr, nullptr, {}};
        }
    };

    template<typename T>
    class dlist<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T>  // depricated in c++17
    {
        friend class dlist<T>;

    public:
        [[maybe_unused]] typedef const T const_reference;

        iterator() = default;

        explicit iterator(typename dlist<T>::node *node_in) : data{node_in} {}

        bool operator==(const iterator &other) const { return other.data == data; }

        bool operator!=(const iterator &other) const { return other.data != data; }

        T &operator*() { return data->data; }

        const T &operator*() const { return data->data; }

        T *operator->() { return data; }

        const T *operator->() const { return data; }

        iterator &operator++() {
            data = data->next;
            return *this;
        }

        const iterator operator++(int) {
            data = data->next;
            return *this;
        }

        iterator &operator--() {
            data = data->previous;
            return *this;
        }

        const iterator operator--(int) {
            data = data->previous;
            return *this;
        }

    private:
        node *data{nullptr};
        // You decide what goes here 
    };
}

#endif //COURSE_4_DLIST_H
