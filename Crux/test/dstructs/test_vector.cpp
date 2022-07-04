#include <gtest/gtest.h>

#include "src/utility/dstructs/iterators/iterator_lagacy_random_access.h"
#include "src/utility/dstructs/vector/vector.h"

crux::vector<int> vec;

TEST(Vector, DefaultConstuctor) {
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, InitializerListConstructor) {
    crux::vector<int> vec_t{1, 3, 5, 7, 9};
    EXPECT_EQ(vec_t.size(), 5);
    EXPECT_EQ(vec_t.capacity(), 5);
    EXPECT_EQ(vec_t[3], 7);
}

TEST(Vector, NCopiesConstructor) {
    crux::vector<int> vec1(7, 3);
    EXPECT_EQ(vec1.size(), 7);
    EXPECT_EQ(vec1.capacity(), 7);
    int sum = 0;
    for (auto elem : vec1) {
        sum += elem;
    }
    EXPECT_EQ(sum, 21);
}

TEST(Vector, CopyConstruct) {
    crux::vector<int> vec1 = {1, 2, 3, 4, 5};
    crux::vector<int> vec2(vec1);
    EXPECT_EQ(vec2.capacity(), 5);
    EXPECT_EQ(vec2.size(), 5);
    EXPECT_EQ(vec1[3], vec2[3]);
}

TEST(Vector, MoveConstruct) {
    crux::vector<int> vec1 = {1, 2, 3, 4, 5};
    crux::vector<int> vec2(std::move(vec1));
    EXPECT_EQ(vec2.capacity(), 5);
    EXPECT_EQ(vec2.size(), 5);
    EXPECT_EQ(vec2[3], 4);
}

TEST(Vector, CopyAssignmentOperator) {
    crux::vector<int> vec1 = {1, 2, 3, 4, 5};
    crux::vector<int> vec2 = vec1;
    EXPECT_EQ(vec2.capacity(), 5);
    EXPECT_EQ(vec2.size(), 5);
    EXPECT_EQ(vec1[3], vec2[3]);
}

TEST(Vector, CopyMoveAssignmentOperator) {
    crux::vector<int> vec1 = {1, 2, 3, 4, 5};
    crux::vector<int> vec2 = std::move(vec1);
    EXPECT_EQ(vec2.capacity(), 5);
    EXPECT_EQ(vec2.size(), 5);
    EXPECT_EQ(vec2[4], 5);
}

crux::vector<int> vec1;
TEST(Vector, AssignOperator) {
    vec1.assign(7, 33);
    EXPECT_EQ(vec1.capacity(), 7);
    EXPECT_EQ(vec1.size(), 7);
    EXPECT_EQ(vec1.at(3), 33);
}

crux::vector<int> vec_a;
TEST(Vector, GetAllocator) {
    int *ptr = vec_a.get_allocator().allocate(1);
    vec_a.get_allocator().construct(ptr, int(101));
    EXPECT_EQ(*ptr, 101);
    vec_a.get_allocator().destroy(ptr);
    vec_a.get_allocator().deallocate(ptr, 1);
}

TEST(Vector, DataAtPosOperator) {
    crux::vector<int> vec = {12, 23, 42, 12, 32};
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec.at(i), vec[i]);
    }
}

TEST(Vector, FrontAndBack) {
    crux::vector<int> vec{12, 23, 42, 12, 32};
    EXPECT_EQ(vec.front(), 12);
    EXPECT_EQ(vec.back(), 32);
}

TEST(Vector, GetData) {
    crux::vector<int> vec{16, 92, 71};
    EXPECT_EQ(*(vec.data() + 1), 92);
}

TEST(Vector, IteratorOperation) {
    crux::vector<int> vec{84, 38, 12};
    EXPECT_EQ(*(vec.begin() + 1), 38);
    EXPECT_EQ(*(vec.begin() - 1), 0);
    EXPECT_EQ(*(vec.end() - 2), 38);
}

TEST(Vector, ConstIteratorOperation) {
    const crux::vector<int> vec{84, 38, 12};
    EXPECT_EQ(*(vec.cbegin() + 1), 38);
    EXPECT_EQ(*(vec.cbegin() - 1), 0);
    EXPECT_EQ(*(vec.cend() - 2), 38);
}

TEST(Vector, ReverseOperation) {
    const crux::vector<int> vec{84, 38, 12};
    EXPECT_EQ(*vec.rbegin(), 12);
    EXPECT_EQ(*(vec.rend() - 1), 84);
}

TEST(Vector, ConstReverseOperation) {
    const crux::vector<int> vec{84, 38, 12};
    EXPECT_EQ(*vec.crbegin(), 12);
    EXPECT_EQ(*(vec.crend() - 2), 38);
}

TEST(Vector, EmptyAndClear) {
    crux::vector<int> vec{84, 38, 12};
    EXPECT_FALSE(vec.empty());
    vec.clear();
    EXPECT_TRUE(vec.empty());
}

crux::vector<int> vec_m;
TEST(Vector, ReserveMemory) {
    EXPECT_EQ(vec_m.capacity(), 0);
    vec_m.reserve(7);
    EXPECT_EQ(vec_m.capacity(), 7);
}

TEST(Vector, ShrinkToFit) {
    crux::vector<int> vec(6, 10);
    vec.pop_back();
    vec.pop_back();
    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), 4);
}

crux::vector<int> vec_i;
TEST(Vector, InsertData) {
    vec_i.insert(vec_i.begin(), 303);
    vec_i.insert(vec_i.begin(), 304);
    vec_i.insert(vec_i.begin(), 305);
    EXPECT_EQ(vec_i[0], 305);
    EXPECT_EQ(vec_i[1], 304);
    EXPECT_EQ(vec_i[2], 303);
}

class TestClass {
public:
    TestClass() = default;
    TestClass(int value) { test = value; }
    int getTest() { return test; }
private:
    int test = 10;
};

crux::vector<TestClass> vec_e;
TEST(Vector, EmplaceData) {
    TestClass tc;
    vec_e.emplace(vec_e.begin(), tc);
    EXPECT_EQ(vec_e[0].getTest(), tc.getTest());
}

TEST(Vector, EraseData) {
    vec_i.erase(vec_i.begin() + 1);
    EXPECT_EQ(vec_i[1], 303);
}

TEST(Vector, PushBackData) {
    vec_i.push_back(784);
    EXPECT_EQ(*(vec_i.end() - 1), 784);
}

TEST(Vector, EmplaceBackData) {
    TestClass tc(5678);
    vec_e.emplace_back(tc);
    EXPECT_EQ(vec_e[1].getTest(), tc.getTest());
}

TEST(Vector, PopBackData) {
    vec_e.pop_back();
    EXPECT_EQ(vec_e[0].getTest(), 10);
}

TEST(Vector, ResizeData) {
    vec_e.resize(6);
    EXPECT_EQ(vec_e.capacity(), 6);
}

TEST(Vector, SwapData) {
    crux::vector<int> v1 = {1,2,3};
    crux::vector<int> v2 = {3,4,1};
    crux::swap(v1, v2);
    EXPECT_EQ(v1.front(), 3);
}