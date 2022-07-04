#include <gtest/gtest.h>

#include "src/utility/dstructs/array/array.h"
#include "src/utility/dstructs/iterators/iterator_lagacy_random_access.h"

crux::array<int, 5> arr = {9, 7, 5, 3, 1};

TEST(Array, FrontElement) {
    EXPECT_EQ(arr.front(), 9);
}

TEST(Array, BackElement) {
    EXPECT_EQ(arr.back(), 1);
}

TEST(Array, ArrayData) {
    EXPECT_EQ(*(arr.data() + 1), 7);
}

TEST(Array, FillArrayWithData) {
    arr.fill(30);
    int sum = 0;
    for(auto elem : arr) {
        sum += elem;
    }
    EXPECT_EQ(sum, 150);
}

TEST(Array, CheckIfEmpty) {
    EXPECT_FALSE(arr.empty());
}

TEST(Array, GetArraySize) {
    EXPECT_EQ(arr.size(), 5);
}

TEST(Array, GetDataAtPosition) {
    EXPECT_EQ(arr[2], 30);
}

TEST(Array, GetFirstIteratePosition) {
    EXPECT_EQ(*arr.begin(), 30);
}

TEST(Array, GetLastIteratePosition) {
    EXPECT_EQ(*(arr.end() - 1), 30);
}




