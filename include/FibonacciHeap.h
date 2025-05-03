#pragma once
#include "stack.h"

template <class T>
class FibonacciHeap
{
private:
    struct Node
    {
        int degree;
        T data;
        Node* child;
        Node* left;
        Node* right;
        Node()
        {
            degree = 0;
            data = T();
            child = nullptr;
            left = nullptr;
            right = nullptr;
        }
        
        Node(const T& _data) : data(_data), degree(0)
        {
            child = nullptr;
            left = nullptr;
            right = nullptr;
        }
        Node& operator=(const Node& node)
        {
            degree = node.degree;
            data = node.data;
            child = node.child;
            left = node.left;
            right = node.right;
            return *this;
        }
    };
    Node* mergeFibonacciHeap(Node* head1, Node* head2)
    {
        if (head1 == nullptr) return head2;
        if (head2 == nullptr) return head1;
        Node* newHead = (head1->data < head2->data) ? head1 : head2;
        while (head1->right != nullptr) head1 = head1->right;
        while (head2->left != nullptr) head2 = head2->left;
        head1->right = head2;
        head2->left = head1;
        return newHead;
    }
    Node* head;
    size_t size;
public:
    FibonacciHeap() : head(nullptr), size(0) { }
    ~FibonacciHeap()
    {
        if (head != nullptr)
        {
            Stack<Node*> nodes;
            nodes.push(head);
            while (!nodes.empty())
            {
                Node* t = nodes.top();
                nodes.pop();
                if (t->left != nullptr) nodes.push(t->left);
                if (t->right != nullptr) nodes.push(t->right);
                if (t->child != nullptr) nodes.push(t->child);
                delete t;
            }
        }
    }
    //вегда поддерживаем минимум в head
    T top() const
    {
        return head->data;
    }
    void add(const T& item)
    {
        size++;
        if (head == nullptr)
        {
            head = new Node(item);
        }
        else
        {
            Node* newNode = new Node(item);
            newNode->right = head->right;
            newNode->left = head;
            if (newNode->right != nullptr) newNode->right->left = newNode;
            head->right = newNode;
            if (head->data > newNode->data) head = newNode;
        }
        return;
    }
    T extructMin()
    {
        T res = head->data;
        Node* t = head;
        if (head->right != nullptr)
        {
            head->right->left = head->left;
        }
        if (head->left != nullptr)
        {
            head->left->right = head->right;
        }
        if (head->left != nullptr) head = head->left;
        else if (head->right != nullptr) head = head->right;
        else if (head == t)
        {
            head = head->child;
            delete t;
            size--;
            return res;
        }
        head = mergeFibonacciHeap(head, t->child);
        delete t;
        Vector<Node*> nodes((int)2 * std::log2(size));
        Node* cur = head;
        while (cur->left != nullptr) cur = cur->left;
        while (cur != nullptr)
        {
            if (cur->degree >= nodes.length())
            {
                nodes.resize(cur->degree + 1);
                nodes[cur->degree] = cur;
                t = cur;
                cur = cur->right;
                t->left = nullptr;
                t->right = nullptr;
                if (cur == nullptr) continue;
                cur->left = nullptr;
            }
            else if (nodes[cur->degree] == nullptr)
            {
                nodes[cur->degree] = cur;
                t = cur;
                cur = cur->right;
                t->left = nullptr;
                t->right = nullptr;
                if (cur == nullptr) continue;
                cur->left = nullptr;

            }
            else
            {
                t = cur->right;
                cur->right = nullptr;
                Node* cur2 = nodes[cur->degree];
                nodes[cur->degree] = nullptr;
                if (cur2->data < cur->data) std::swap(cur, cur2);
                cur->child = mergeFibonacciHeap(cur->child, cur2);
                cur->degree++;
                cur->right = t;
            }
        }
        t = nullptr;
        for (size_t i = 0; i < nodes.length(); i++)
        {
            if (nodes[i] != nullptr)
            {

                if (t == nullptr)
                {
                    t = nodes[i];
                    head = t;
                }
                else
                {
                    if (head->data > nodes[i]->data) head = nodes[i];
                    t->right = nodes[i];
                    nodes[i]->left = t;
                    t = t->right;
                }

            }
        }
        size--;
        return res;
    }
    bool empty() const noexcept
    {
        return size == 0;
    }
};