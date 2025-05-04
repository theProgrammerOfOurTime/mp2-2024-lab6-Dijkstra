#include <gtest.h>
#include "BinHeap.h"

TEST(BinHeap, canCreateBinHeap)
{
    ASSERT_NO_THROW(BinHeap<int>());
}

TEST(BinHeap, canCreateFromVectorBinHeap)
{
    Vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(1);
    ASSERT_NO_THROW(BinHeap<int>(vec));
}

TEST(BinHeap, canCallEmpty)
{
    BinHeap<int> heap;
    ASSERT_NO_THROW(heap.empty());
}

TEST(BinHeap, canCallSize)
{
    BinHeap<int> heap;
    ASSERT_NO_THROW(heap.size());
}

TEST(BinHeap, DefaultConstructorCreatesEmptyHeap)
{
    BinHeap<int> heap;
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
}

TEST(BinHeap, canCallMin)
{
    BinHeap<int> heap;
    ASSERT_NO_THROW(heap.getMin());
}

TEST(BinHeap, ConstructFromVector)
{
    Vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(1);

    BinHeap<int> heap(vec);
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.getMin(), 1);
}

TEST(BinHeap, canCallAdd)
{
    BinHeap<int> heap;
    ASSERT_NO_THROW(heap.add(5));
}

TEST(BinHeap, AddElementsMaintainsHeapProperty)
{
    BinHeap<int> heap;
    heap.add(5);
    heap.add(3);
    heap.add(8);
    heap.add(1);

    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.getMin(), 1);
}

TEST(BinHeap, extructMinReturnsInOrder)
{
    BinHeap<int> heap;
    heap.add(5);
    heap.add(3);
    heap.add(8);
    heap.add(1);
    heap.add(2);

    EXPECT_EQ(heap.extructMin(), 1);
    EXPECT_EQ(heap.extructMin(), 2);
    EXPECT_EQ(heap.extructMin(), 3);
    EXPECT_EQ(heap.extructMin(), 5);
    EXPECT_EQ(heap.extructMin(), 8);
    EXPECT_TRUE(heap.empty());
}

TEST(BinHeap, HeapifyCreatesValidHeap)
{
    Vector<int> vec;
    vec.push_back(9);
    vec.push_back(2);
    vec.push_back(7);
    vec.push_back(1);
    vec.push_back(5);

    BinHeap<int> heap;
    heap.heapily(vec);

    EXPECT_EQ(heap.size(), 5);
    EXPECT_EQ(heap.getMin(), 1);

    EXPECT_EQ(heap.extructMin(), 1);
    EXPECT_EQ(heap.extructMin(), 2);
    EXPECT_EQ(heap.extructMin(), 5);
    EXPECT_EQ(heap.extructMin(), 7);
    EXPECT_EQ(heap.extructMin(), 9);
}

TEST(BinHeap, HandlesDuplicateValues)
{
    BinHeap<int> heap;
    heap.add(3);
    heap.add(3);
    heap.add(1);
    heap.add(1);
    heap.add(2);

    EXPECT_EQ(heap.extructMin(), 1);
    EXPECT_EQ(heap.extructMin(), 1);
    EXPECT_EQ(heap.extructMin(), 2);
    EXPECT_EQ(heap.extructMin(), 3);
    EXPECT_EQ(heap.extructMin(), 3);
}

TEST(BinHeap, LargeNumberOfElements)
{
    BinHeap<int> heap;
    size_t size = 1000;

    for (int i = size; i > 0; i--)
    {
        heap.add(i);
    }

    EXPECT_EQ(heap.size(), size);
    EXPECT_EQ(heap.getMin(), 1);

    for (int i = 1; i <= size; i++)
    {
        EXPECT_EQ(heap.extructMin(), i);
    }

    EXPECT_TRUE(heap.empty());
}

TEST(BinHeap, StringTypeWorks)
{
    BinHeap<std::string> heap;
    heap.add("bbb");
    heap.add("aaa");
    heap.add("ccc");
    heap.add("ddd");

    EXPECT_EQ(heap.getMin(), "aaa");
    EXPECT_EQ(heap.extructMin(), "aaa");
    EXPECT_EQ(heap.extructMin(), "bbb");
    EXPECT_EQ(heap.extructMin(), "ccc");
    EXPECT_EQ(heap.extructMin(), "ddd");
}