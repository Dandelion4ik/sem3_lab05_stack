// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <string>

#include "stack.hpp"
#include "stack_second.hpp"


TEST(stack, copy) {
    EXPECT_FALSE(std::is_copy_constructible<stack<int>>::value);
    EXPECT_FALSE(std::is_copy_constructible<stack<std::string>>::value);
    EXPECT_FALSE(std::is_copy_assignable<stack<int>>::value);
    EXPECT_FALSE(std::is_copy_assignable<stack<std::string>>::value);
}

TEST(stack, move) {
    EXPECT_TRUE(std::is_move_constructible<stack<int>>::value);
    EXPECT_TRUE(std::is_move_constructible<stack<std::string>>::value);
    EXPECT_TRUE(std::is_move_assignable<stack<int>>::value);
    EXPECT_TRUE(std::is_move_assignable<stack<std::string>>::value);
}

TEST(stack, push) {
    stack<int> st;
    EXPECT_EQ(st.size(), 0);
    st.push(static_cast<const int &>(10));
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.head(), 10);
    st.push(11);
    EXPECT_EQ(st.size(), 2);
    EXPECT_EQ(st.head(), 11);
}

TEST(stack, pop) {
    stack<int> st;
    EXPECT_EQ(st.size(), 0);
    EXPECT_ANY_THROW(st.pop());
    st.push(static_cast<const int &>(10));
    st.push(11);
    EXPECT_EQ(st.size(), 2);
    EXPECT_EQ(st.head(), 11);
    st.pop();
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.head(), 10);
    st.pop();
    EXPECT_EQ(st.size(), 0);
}

TEST(stack, head_) {
    stack<int> st;
    EXPECT_EQ(st.size(), 0);
    EXPECT_ANY_THROW(st.head());
}

TEST(stack_second, copy) {
    EXPECT_FALSE(std::is_copy_constructible<stack_second<int>>::value);
    EXPECT_FALSE(
            std::is_copy_constructible<stack_second<std::string>>::value);
    EXPECT_FALSE(std::is_copy_assignable<stack_second<int>>::value);
    EXPECT_FALSE(
            std::is_copy_assignable<stack_second<std::string>>::value);
}

TEST(stack_second, move) {
    EXPECT_TRUE(std::is_move_constructible<stack_second<int>>::value);
    EXPECT_TRUE(
            std::is_move_constructible<stack_second<std::string>>::value);
    EXPECT_TRUE(std::is_move_assignable<stack_second<int>>::value);
    EXPECT_TRUE(
            std::is_move_assignable<stack_second<std::string>>::value);
}

class checking {
public:
    int arg;

    checking() = default;

    checking(int x) { arg = x; }

    checking(const checking &value) = delete;

    checking(checking &&value) noexcept = default;

    auto operator=(const checking &value) -> checking & = delete;

    auto operator=(checking &&value) noexcept -> checking & = default;
};

TEST(checking, correct_class) {
    EXPECT_TRUE(std::is_move_constructible<checking>::value);
    EXPECT_TRUE(std::is_move_assignable<checking>::value);
    EXPECT_FALSE(std::is_copy_constructible<checking>::value);
    EXPECT_FALSE(std::is_copy_assignable<checking>::value);
}

TEST(stack_second, push) {
    stack_second<checking> st2;
    EXPECT_EQ(st2.size(), 0);
    st2.push(checking(10));
    EXPECT_EQ(st2.size(), 1);
    EXPECT_EQ(st2.head().arg, 10);
    st2.push_emplace(11);
    EXPECT_EQ(st2.size(), 2);
    EXPECT_EQ(st2.head().arg, 11);
}

TEST(stack_second, pop) {
    stack_second<checking> st;
    EXPECT_EQ(st.size(), 0);
    EXPECT_ANY_THROW(st.pop());
    st.push(10);
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.head().arg, 10);
    EXPECT_EQ(st.pop().arg, 10);
    EXPECT_EQ(st.size(), 0);
}

TEST(stack_second, head) {
    stack_second<checking> st;
    EXPECT_EQ(st.size(), 0);
    EXPECT_ANY_THROW(st.head());
    st.push(10);
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.head().arg, 10);
}
