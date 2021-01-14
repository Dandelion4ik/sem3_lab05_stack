// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#ifndef TEMPLATE_STACK_SECOND_HPP
#define TEMPLATE_STACK_SECOND_HPP

#include "stack.hpp"

template<typename T>
class stack_second : public stack<T> {
public:
    template<typename... Args>
    void push_emplace(Args &&... value);

    void push(T &&value);

    const T &head() const;

    T pop();
};

template<typename T>
template<typename... Args>
void stack_second<T>::push_emplace(Args &&... value) {
    if ((std::is_copy_constructible<T>::value) ||
        (std::is_copy_assignable<T>::value)) {
        throw std::exception();
    }
    stack<T>::head_ =
            new element<T>{{std::forward<Args>(value)...}, stack<T>::head_};
}

template<typename T>
void stack_second<T>::push(T &&value) {
    if ((std::is_copy_constructible<T>::value) ||
        (std::is_copy_assignable<T>::value)) {
        throw std::exception();
    }
    stack<T>::head_ = new element<T>{std::forward<T>(value), stack<T>::head_};
}

template<typename T>
const T &stack_second<T>::head() const {
    if (stack<T>::head_ == nullptr) {
        throw std::exception();
    }
    return stack<T>::head_->value;
}

template<typename T>
T stack_second<T>::pop() {
    if (stack<T>::head_ == nullptr) {
        throw std::exception();
    }
    auto *buf = stack<T>::head_;
    T val = std::move(stack<T>::head_->value);
    stack<T>::head_ = stack<T>::head_->prev;
    delete buf;
    return val;
}

#endif //TEMPLATE_STACK_SECOND_HPP
