//
// Created by Ivo Georgiev on 5/3/16.
//

#ifndef UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
#define UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H

// Naive partial implementation of a custom iterator.
// After Jeet Sukumaran https://github.com/jeetsukumaran

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

namespace CS2312 {

    template<typename T>
    class fixed_array {

    public:

        typedef std::size_t size_type;

        class iterator {

        public:

            typedef iterator self_type;
            typedef T value_type;
            typedef T &reference;
            typedef T *pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            //Constructor
            iterator(pointer ptr) {
                __ptr = ptr;
            }

            // prefix increment . little cofusing looks like postfix.
            self_type operator++() {
                __ptr++;
                // 'this' is pointer to iterator(double pointer because iterator itself is a pointer)
                // to obtain iterator we need to deference 'this'. it still pointer
                return *this;
            };

            // postfix increment.
            self_type operator++(int junk) {
                // similar explanation from above
                self_type temp = *this;
                __ptr++;
                return temp;
            };

            //deference would give value pointed by iterator.
            // __ptr is iterator in our case.
            reference operator*() {
                return *__ptr;
            };


            pointer operator->() {
                // need to return pointer show we cand use arrow pointer to the member variable
                // of data type T if T is class or structure.
                return __ptr;
            };

            // comparing two pointers
            bool operator==(const self_type &rhs) const {
                return __ptr == rhs.__ptr;
            }

            // comparing two pointer if they are not equal
            bool operator!=(const self_type &rhs) const {
                return __ptr != rhs.__ptr;
            }


        private:

            pointer __ptr;

        };

        // no comment is necessary for the following code because it is pretty much the same as above except
        // following code is for constant
        // this means the iterator from following implementation wouldn't be able to change the object.
        // It is like ready only file :-)
        class const_iterator {

        public:

            typedef const_iterator self_type;
            typedef T value_type;
            typedef T &reference;
            typedef T *pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            const_iterator(pointer ptr) {
                __ptr = ptr;
            };

            self_type operator++() {
                __ptr++;
                return *this;
            };

            self_type operator++(int junk) {
                self_type temp = *this;
                __ptr++;
                return temp;
            };

            const value_type &operator*() const {
                return *__ptr;
            };

            const value_type *operator->() const {
                return __ptr;
            };

            bool operator==(const self_type &rhs) const {
                return __ptr == rhs.__ptr;
            };

            bool operator!=(const self_type &rhs) const {
                return __ptr != rhs.__ptr;
            };

        private:

            pointer __ptr;

        };


        // array of size __size
        // __data would work as array name and __size keep track of size
        fixed_array(size_type size) {
            //
            __data = new T[size];
            __size = size;
        };

        // initilizer_list is STL container. haven't used before but simple like list/vector.
        fixed_array(std::initializer_list<T> list) {
            __size = list.size();
            __data = new T[__size];

            // 'auto' would work just fine but I wanted to see what real iterator type is
            // 'typename' is required for Template because 'it' is dependant on 'T' and forward 'typename'  is
            // required for the dependant variables.
            typename std::initializer_list<T>::iterator it = list.begin();
            for (int i = 0; i < list.size(); ++i) {
                __data[i] = *it;
                ++it;
            }
        };

        // destructor for dynamic array.
        ~fixed_array() {
            delete[] __data;
        };

        // size is unsigned int.
        size_type size() const {
            return __size;
        };

        // return required index element
        T &operator[](size_type index) {
            return __data[index];
        };

        // same but constant
        const T &operator[](size_type index) const {
            return __data[index];
        };

        // return the pointer(iterator) to first element of array
        iterator begin() {
            return iterator(&__data[0]);
        };

        // this is actually one pass to the last element.
        // differencing this would give garbage value
        // but important for the 'for loop' because
        // it would be the end condition.
        iterator end() {
            return iterator(&__data[__size]);
        };

        //similar for both of the following.
        const_iterator begin() const {
            return const_iterator(&__data[0]);
        };

        const_iterator end() const {
            return const_iterator(&__data[__size]);
        };

    private:

        T *__data;
        size_type __size;

    };
}

#endif //UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
