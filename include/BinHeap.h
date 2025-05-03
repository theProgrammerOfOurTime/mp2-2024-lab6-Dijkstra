#pragma once
#include "Vector.h"

template<class T>
class BinHeap
{
private:
    Vector<T> mas;
    void slideDown(int ind)
    {
        int ind1 = 2 * ind + 1, ind2 = 2 * ind + 2;
        while(2 * ind + 2 < mas.length())
        {
            if (mas[ind1] > mas[ind2] && mas[ind] > mas[ind2])
            {
                std::swap(mas[ind], mas[ind2]);
                ind = ind2;
            }
            else if (mas[ind] > mas[ind1])
            {
                std::swap(mas[ind], mas[ind1]);
                ind = ind1;
            }
            else break;
            ind1 = 2 * ind + 1;
            ind2 = 2 * ind + 2;
        }
        if (ind1 < mas.length() && mas[ind] > mas[ind1])
        {
            std::swap(mas[ind], mas[ind1]);
        }
        return;
    }
    void slideUp(int ind)
    {
        if (ind == 0) return;
        while (ind > 0 && mas[ind] < mas[(ind - 1) / 2])
        {
            std::swap(mas[ind], mas[(ind - 1) / 2]);
            ind = (ind - 1) / 2;
        }
        return;
    }
public:
    BinHeap()
    {

    }
    BinHeap(const Vector<T>& data)
    {
        heapily(data);
    }
    ~BinHeap()
    {

    }
    
    void push(const T& item, const int& ind)
    {
        mas[ind] = item;
        slideDown(ind);
        slideUp(ind);
        return;
    }
    void add(const T& item)
    {
        mas.push_back(item);
        slideUp(mas.length() - 1);
    }
    T extructMin()
    {
        T mn = mas[0];
        mas[0] = mas[mas.length() - 1];
        mas.resize(mas.length() - 1);
        slideDown(0);
        return mn;
    }
    void heapily(const Vector<T>& data)
    {
        mas = data;
        for (int i = mas.length() / 2; i >= 0; i--)
        {
            slideDown(i);
        }
        return;
    }
    T getMin() const
    {
        return mas[0];
    }
    T operator[] (const size_t& ind) const
    {
        return mas[ind];
    }
    size_t size() const
    {
        return mas.length();
    }
    T operator[] (const size_t& ind)
    {
        return mas[ind];
    }
    bool empty() const noexcept
    {
        return  mas.length() != 0;
    }
};