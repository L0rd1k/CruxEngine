#include <gtest/gtest.h>

#include "src/sage/dstructs/array/array.h"
#include "src/sage/dstructs/iterators/iterator_reverse.h"

sage::array<int, 6> arr = {2, 7, 3, 82, 21, 55};

TEST(IteratorReverse, BaseInterator) {
    sage::array<int, 6>::iterator itr = arr.begin() + 2; 
    sage::reverse_iterator<sage::array<int, 6>::iterator> ritr(itr);
    EXPECT_EQ(*ritr.base(), arr[2]);
}

TEST(IteratorReverse, DereferenceOperator) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3; 
    sage::reverse_iterator<sage::array<int, 6>::iterator> ritr(itr);
    EXPECT_EQ(*ritr.base(), arr[3]);
}

TEST(IteratorReverse, AdditionOperator) {
    sage::array<int, 6>::riterator itr1 = arr.rbegin(); 
    sage::array<int, 6>::riterator itr2 = itr1;
    itr2 = itr1 + 2;
    EXPECT_EQ(*itr2.base(), arr[4]);
}

TEST(IteratorReverse, IncrementIteratorPosition) {
    sage::array<int, 6>::riterator itr = arr.rbegin(); 
    itr++;
    EXPECT_EQ(*itr, arr[4]);
}

TEST(IteratorReverse, DecreaseIteratorPosition) {
    sage::array<int, 6>::riterator itr = arr.rend(); 
    itr--;
    EXPECT_EQ(*itr, arr.front());
}

TEST(IteratorReverse, RetrocedeIterator) {
    sage::array<int, 6>::riterator itr = arr.rend();
    itr -= 3;
    EXPECT_EQ(*itr.base(), arr[3]);
}

TEST(IteratorReverse, AdvanceIterator ) {
    sage::array<int, 6>::riterator itr = arr.rbegin();
    itr += 3;
    EXPECT_EQ(*itr, arr[2]);
}

TEST(IteratorReverse, EqualityLessOrEqueal) {
    const sage::array<int, 6>::riterator itr1 = arr.rbegin() + 1;
    sage::array<int, 6>::riterator itr2 = itr1;
    EXPECT_EQ(itr2 <= itr1, true);
    EXPECT_EQ(itr1 <= itr2, true);
}

TEST(IteratorReverse, EqualityMoreOrEqueal) {
    const sage::array<int, 6>::riterator itr1 = arr.rbegin() + 1;
    sage::array<int, 6>::riterator itr2 = itr1 + 2;
    EXPECT_EQ(itr2 >= itr1, true);
    EXPECT_EQ(itr1 >= itr2, false);
}

