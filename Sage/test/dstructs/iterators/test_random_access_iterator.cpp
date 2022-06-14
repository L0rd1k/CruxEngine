#include <gtest/gtest.h>

#include "src/sage/dstructs/array/array.h"
#include "src/sage/dstructs/iterators/iterator_bidirectional.h"

sage::array<int, 6> arr = {2, 7, 3, 82, 21, 55};

TEST(IteratorRandomAccess, RValueDereference) {
    sage::array<int, 6>::iterator itr = arr.begin();
    EXPECT_EQ(*itr, 2);
}

TEST(IteratorRandomAccess, RValueDereferencePtr) {
    sage::array<int, 6>::iterator itr = arr.begin() + 4;  
    EXPECT_EQ(*(itr.operator->()), 21); 
}

TEST(IteratorRandomAccess, CopyConstructible) {
    sage::array<int, 6>::iterator itr = arr.begin() + 2;
    sage::array<int, 6>::iterator cp_itr(itr);
    EXPECT_EQ(*cp_itr, 3); 
}

TEST(IteratorRandomAccess, CopyAssignable) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3;
    sage::array<int, 6>::iterator cp_itr = itr;
    EXPECT_EQ(*cp_itr, 82);    
}

TEST(IteratorRandomAccess, PostfixIncrement) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3;
    itr++;
    EXPECT_EQ(*itr, 21);  
}

TEST(IteratorRandomAccess, PrefixIncrement) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3;
    EXPECT_EQ(*(++itr), 21);  
}

TEST(IteratorRandomAccess, EqualitySupport) {
    sage::array<int, 6>::iterator itr1 = arr.begin() + 4;  
    sage::array<int, 6>::iterator itr2 = arr.begin() + 4;
    bool result = itr1 == itr2;
    EXPECT_EQ(result, true); 
}

TEST(IteratorRandomAccess, InequalitySupport) {
    sage::array<int, 6>::iterator itr1 = arr.begin() + 4;  
    sage::array<int, 6>::iterator itr2 = arr.begin() + 4;
    bool result = itr1 != itr2;
    EXPECT_EQ(result, false); 
}

TEST(IteratorRandomAccess, PostfixDecrement) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3;
    itr--;
    EXPECT_EQ(*itr, 3);  
}

TEST(IteratorRandomAccess, PrefixDecrement) {
    sage::array<int, 6>::iterator itr = arr.begin() + 3;
    EXPECT_EQ(*(--itr), 3);  
}

TEST(IteratorRandomAccess, Addition) {
    sage::array<int, 6>::iterator itr = arr.begin();
    sage::array<int, 6>::iterator result = itr + 3;
    EXPECT_EQ(*result, 82);  
}

TEST(IteratorRandomAccess, Subtraction) {
    sage::array<int, 6>::iterator itr = arr.end();
    sage::array<int, 6>::iterator result = itr - 5;
    EXPECT_EQ(*result, 7);  
}

TEST(IteratorRandomAccess, ItrSubtraction) {
    sage::array<int, 6>::iterator itr1 = arr.begin();
    sage::array<int, 6>::iterator itr2 = arr.begin() + 5;
    EXPECT_EQ(itr2 - itr1, 5);  
}

TEST(IteratorRandomAccess, EqualityMore) {
    sage::array<int, 6>::iterator itr1 = arr.begin();
    sage::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 > itr2, false);  
}

TEST(IteratorRandomAccess, EqualityLess) {
    sage::array<int, 6>::iterator itr1 = arr.begin();
    sage::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 < itr2, true);  
}

TEST(IteratorRandomAccess, EqualityMoreOrEqueal) {
    sage::array<int, 6>::iterator itr1 = arr.begin();
    sage::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 >= itr2, false);  
}

TEST(IteratorRandomAccess, EqualityLessOrEqueal) {
    sage::array<int, 6>::iterator itr1 = arr.begin();
    sage::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 <= itr2, true);  
}

TEST(IteratorRandomAccess, IteratorDereference) {
    sage::array<int, 6>::iterator itr = arr.begin();
    EXPECT_EQ(itr[3], 82);  
}