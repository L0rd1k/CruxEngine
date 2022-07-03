#include <gtest/gtest.h>

#include "src/crux/dstructs/array/array.h"
#include "src/crux/dstructs/iterators/iterator_reverse.h"

crux::array<int, 6> arr = {2, 7, 3, 82, 21, 55};

TEST(IteratorReverse, BaseInterator) {
    crux::array<int, 6>::iterator itr = arr.begin() + 2; 
    crux::reverse_iterator<crux::array<int, 6>::iterator> ritr(itr);
    EXPECT_EQ(*ritr.base(), arr[2]);
}

TEST(IteratorReverse, DereferenceOperator) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3; 
    crux::reverse_iterator<crux::array<int, 6>::iterator> ritr(itr);
    EXPECT_EQ(*ritr.base(), arr[3]);
}

TEST(IteratorReverse, AdditionOperator) {
    crux::array<int, 6>::riterator itr1 = arr.rbegin(); 
    crux::array<int, 6>::riterator itr2 = itr1;
    itr2 = itr1 + 2;
    EXPECT_EQ(*itr2.base(), arr[4]);
}

TEST(IteratorReverse, IncrementIteratorPosition) {
    crux::array<int, 6>::riterator itr = arr.rbegin(); 
    itr++;
    EXPECT_EQ(*itr, arr[4]);
}

TEST(IteratorReverse, DecreaseIteratorPosition) {
    crux::array<int, 6>::riterator itr = arr.rend(); 
    itr--;
    EXPECT_EQ(*itr, arr.front());
}

TEST(IteratorReverse, RetrocedeIterator) {
    crux::array<int, 6>::riterator itr = arr.rend();
    itr -= 3;
    EXPECT_EQ(*itr.base(), arr[3]);
}

TEST(IteratorReverse, AdvanceIterator ) {
    crux::array<int, 6>::riterator itr = arr.rbegin();
    itr += 3;
    EXPECT_EQ(*itr, arr[2]);
}

TEST(IteratorReverse, EqualityLessOrEqueal) {
    const crux::array<int, 6>::riterator itr1 = arr.rbegin() + 1;
    crux::array<int, 6>::riterator itr2 = itr1;
    EXPECT_EQ(itr2 <= itr1, true);
    EXPECT_EQ(itr1 <= itr2, true);
}

TEST(IteratorReverse, EqualityMoreOrEqueal) {
    const crux::array<int, 6>::riterator itr1 = arr.rbegin() + 1;
    crux::array<int, 6>::riterator itr2 = itr1 + 2;
    EXPECT_EQ(itr2 >= itr1, true);
    EXPECT_EQ(itr1 >= itr2, false);
}

