// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#pragma once

#include "Vector.h"

template<class T>
class Stack : protected Vector<T>
{
public:
    Stack() { }
    Stack(const Stack& s) = delete;
    ~Stack() { }
    using Vector<T>::length;
    using Vector<T>::clear;
    Stack& operator=(const Stack& v) = delete;
    void push(const T& item)
    {
        Vector<T>::push_back(item);
        return;
    }
    T& top() const noexcept(noexcept(Vector<T>::back()))
    {
        return Vector<T>::back();
    }
    void pop() noexcept(noexcept(Vector<T>::pop_back()))
    {
        Vector<T>::pop_back();
        return;
    }
    bool empty() const noexcept(noexcept(Vector<T>::length()))
    {
        return length() == 0;
    }
};