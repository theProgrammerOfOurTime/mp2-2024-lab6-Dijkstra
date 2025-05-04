#include <gtest.h>
#include "FibonacciHeap.h"

TEST(FibonacciHeap, canCreateFibonacciHeap)
{
    ASSERT_NO_THROW(FibonacciHeap<int>());
}

TEST(FibonacciHeap, canCallEmpty)
{
    FibonacciHeap<int> heap;
    ASSERT_NO_THROW(heap.empty());
}

TEST(FibonacciHeap, canCallSize)
{
    FibonacciHeap<int> heap;
    ASSERT_NO_THROW(heap.getSize());
}

TEST(FibonacciHeap, DefaultConstructorCreatesEmptyHeap)
{
    FibonacciHeap<int> heap;
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.getSize(), 0);
}

TEST(FibonacciHeap, canCallAdd)
{
    FibonacciHeap<int> heap;
    ASSERT_NO_THROW(heap.add(5));
}

TEST(FibonacciHeap, AddElementsMaintainsHeapProperty)
{
    FibonacciHeap<int> heap;
    heap.add(5);
    heap.add(3);
    heap.add(8);
    heap.add(1);

    EXPECT_EQ(heap.getSize(), 4);
    EXPECT_EQ(heap.top(), 1);
}

TEST(FibonacciHeap, extructMinReturnsInOrder)
{
    FibonacciHeap<int> heap;
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

TEST(FibonacciHeap, HandlesDuplicateValues)
{
    FibonacciHeap<int> heap;
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

TEST(FibonacciHeap, LargeNumberOfElements)
{
    FibonacciHeap<int> heap;
    size_t size = 1000;

    for (int i = size; i > 0; i--)
    {
        heap.add(i);
    }

    EXPECT_EQ(heap.getSize(), size);
    EXPECT_EQ(heap.top(), 1);

    for (int i = 1; i <= size; i++)
    {
        EXPECT_EQ(heap.extructMin(), i);
    }

    EXPECT_TRUE(heap.empty());
}

TEST(FibonacciHeap, StringTypeWorks)
{
    FibonacciHeap<std::string> heap;
    heap.add("bbb");
    heap.add("aaa");
    heap.add("ccc");
    heap.add("ddd");

    EXPECT_EQ(heap.top(), "aaa");
    EXPECT_EQ(heap.extructMin(), "aaa");
    EXPECT_EQ(heap.extructMin(), "bbb");
    EXPECT_EQ(heap.extructMin(), "ccc");
    EXPECT_EQ(heap.extructMin(), "ddd");
}