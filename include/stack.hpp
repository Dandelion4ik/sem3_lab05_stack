// Copyright 2021 Kavykin Andrey Kaviandr@yandex.ru
#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP

#include <stdexcept>
#include <utility>
#include <algorithm>
#include <type_traits>


template<class T>
struct element {
    T value;
    element<T> *prev = nullptr;
};

template<typename T>
class stack {
protected:
    element<T> *head_ = nullptr;
public:
    stack() = default;

    stack(const stack &st) = delete;

    auto operator=(const stack &st) -> stack & = delete;

    stack(stack &&st) noexcept = default;

    auto operator=(stack &&st) noexcept -> stack & = default;

    ~stack();  // деструктор

    void push(const T &value);

    void push(T &&value);

    void pop();

    const T &head() const;

    size_t size() const;
};

template<typename T>
void stack<T>::push(const T &value) {
    auto *new_element = new element<T>{value, head_};
    head_ = new_element;
}

template<typename T>
void stack<T>::push(T &&value) {
    auto *new_element = new element<T>{std::forward<T>(value), head_};
    head_ = new_element;
}

template<typename T>
void stack<T>::pop() {
    if (head_) {
        auto *FIRST = head_;
        head_ = head_->prev;  // теперь "вершина" стека - это предыдущий элемент
        delete FIRST;
    } else {
        throw std::out_of_range("Stack is empty!");
    }
}

template<typename T>
const T &stack<T>::head() const {
    if (!head_) {
        throw std::out_of_range("Stack is empty!");
    }
    return head_->value;  // возвращаем значение элемента
}

template<typename T>
stack<T>::~stack() {
    while (head_) {
        auto *current_element = head_;  // текущий элемент - теперь "вершина"
        head_ = head_->prev;  // "вершина" является предыдущим элементом
        delete current_element;  // уничтожаем текущий элемент
    }
}

template<typename T>
size_t stack<T>::size() const {
    size_t size = 0;
    element<T> *buf = head_;
    while (buf != nullptr) {
        ++size;
        buf = buf->prev;
    }
    return size;
}

#endif //TEMPLATE_STACK_HPP