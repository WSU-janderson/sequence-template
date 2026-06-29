/**
 * @file Sequence.h
 * @brief Header file containing declaration of the Sequence class
 *
 * This file has a few comments, but look in the project PDF for the full assignment description
 *
 * @author
 * @date
 */

#pragma once
#include<string>

struct Node;

class Sequence {
public:
    // allows us to change the type our sequence stores in one place and not have to update it everywhere
    // we could change this to
    // using ElementType = double;
    // and our Sequence stores doubles now
    using ElementType = std::string;

    // constructors/destructor
    Sequence();

    ~Sequence();

    // insertion
    void push_front(const ElementType& value);

    void push_back(const ElementType& value);

    void insert(size_t pos, const ElementType& value);

    // removal

    ElementType pop_front();

    ElementType pop_back();

    ElementType erase(size_t pos);

    // access operations
    const ElementType& front() const;

    const ElementType& back() const;

    const ElementType& get(size_t pos) const;

    // cardinality operations
    bool empty() const;

    size_t size() const;

    // utility operations
    void clear();

    // output operator
    friend std::ostream& operator<<(std::ostream& os, const Sequence& seq);

private:
    // you need to use at least one of these, or you may use both
    // using both can complicate some methods and simplify others
    Node* head = nullptr;
    Node* tail = nullptr;

    // everytime we sucessfully push_back(), push_front(), or insert() we need to manually increment `num_nodes`
    // everytime we successfully pop_back(), pop_front(), or erase() we need to manually decrement `num_nodes`
    size_t num_nodes = 0;

    // I will explain this, but if you need your code to return a reference to an ElementType, and
    // you don't have an ElementType to return, you can use `dummyElement`
    ElementType dummyElement;
};
