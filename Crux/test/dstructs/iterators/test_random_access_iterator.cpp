#include <gtest/gtest.h>

#include "src/utility/dstructs/array/array.h"
#include "src/utility/dstructs/iterators/iterator_bidirectional.h"

crux::array<int, 6> arr = {2, 7, 3, 82, 21, 55};

TEST(IteratorRandomAccess, RValueDereference) {
    crux::array<int, 6>::iterator itr = arr.begin();
    EXPECT_EQ(*itr, 2);
}

TEST(IteratorRandomAccess, RValueDereferencePtr) {
    crux::array<int, 6>::iterator itr = arr.begin() + 4;  
    EXPECT_EQ(*(itr.operator->()), 21); 
}

TEST(IteratorRandomAccess, CopyConstructible) {
    crux::array<int, 6>::iterator itr = arr.begin() + 2;
    crux::array<int, 6>::iterator cp_itr(itr);
    EXPECT_EQ(*cp_itr, 3); 
}

TEST(IteratorRandomAccess, CopyAssignable) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3;
    crux::array<int, 6>::iterator cp_itr = itr;
    EXPECT_EQ(*cp_itr, 82);    
}

TEST(IteratorRandomAccess, PostfixIncrement) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3;
    itr++;
    EXPECT_EQ(*itr, 21);  
}

TEST(IteratorRandomAccess, PrefixIncrement) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3;
    EXPECT_EQ(*(++itr), 21);  
}

TEST(IteratorRandomAccess, EqualitySupport) {
    crux::array<int, 6>::iterator itr1 = arr.begin() + 4;  
    crux::array<int, 6>::iterator itr2 = arr.begin() + 4;
    bool result = itr1 == itr2;
    EXPECT_EQ(result, true); 
}

TEST(IteratorRandomAccess, InequalitySupport) {
    crux::array<int, 6>::iterator itr1 = arr.begin() + 4;  
    crux::array<int, 6>::iterator itr2 = arr.begin() + 4;
    bool result = itr1 != itr2;
    EXPECT_EQ(result, false); 
}

TEST(IteratorRandomAccess, PostfixDecrement) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3;
    itr--;
    EXPECT_EQ(*itr, 3);  
}

TEST(IteratorRandomAccess, PrefixDecrement) {
    crux::array<int, 6>::iterator itr = arr.begin() + 3;
    EXPECT_EQ(*(--itr), 3);  
}

TEST(IteratorRandomAccess, Addition) {
    crux::array<int, 6>::iterator itr = arr.begin();
    crux::array<int, 6>::iterator result = itr + 3;
    EXPECT_EQ(*result, 82);  
}

TEST(IteratorRandomAccess, Subtraction) {
    crux::array<int, 6>::iterator itr = arr.end();
    crux::array<int, 6>::iterator result = itr - 5;
    EXPECT_EQ(*result, 7);  
}

TEST(IteratorRandomAccess, ItrSubtraction) {
    crux::array<int, 6>::iterator itr1 = arr.begin();
    crux::array<int, 6>::iterator itr2 = arr.begin() + 5;
    EXPECT_EQ(itr2 - itr1, 5);  
}

TEST(IteratorRandomAccess, EqualityMore) {
    crux::array<int, 6>::iterator itr1 = arr.begin();
    crux::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 > itr2, false);  
}

TEST(IteratorRandomAccess, EqualityLess) {
    crux::array<int, 6>::iterator itr1 = arr.begin();
    crux::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 < itr2, true);  
}

TEST(IteratorRandomAccess, EqualityMoreOrEqueal) {
    crux::array<int, 6>::iterator itr1 = arr.begin();
    crux::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 >= itr2, false);  
}

TEST(IteratorRandomAccess, EqualityLessOrEqueal) {
    crux::array<int, 6>::iterator itr1 = arr.begin();
    crux::array<int, 6>::iterator itr2 = arr.begin() + 2;
    EXPECT_EQ(itr1 <= itr2, true);  
}

TEST(IteratorRandomAccess, IteratorDereference) {
    crux::array<int, 6>::iterator itr = arr.begin();
    EXPECT_EQ(itr[3], 82);  
}