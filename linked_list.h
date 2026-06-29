/**
* @file linked_list.h
* @brief Functions for linked list operations
*
* Before we #include "linked_list.h" anywhere, we need to define what `ElementType` is
* We are doing that in `Sequence.cpp`
*
* You should not need to #include "linked_list.h" anywhere except `Sequence.cpp`
* If you can only get the project to work by doing so, there is something set up incorrectly
* with your C++ environment or IDE.
*
* For the most part we've written these functions, but there are three additional ones we need to implement:
*
* Node* get_node_at(Node* head, size_t position)
* Node* insert_at(Node*& head, Node* new_node, size_t position)
* Node* erase_at(Node*& head, size_t position)
*
* Refer to the project description PDF for how these functions should behave
*
* @author
* @date
*/

#pragma once
#include <string>

// This file won't compile on its own anymore. We *could* change `ElementType` to a concrete type, like std::string,
// or we could say
// using ElementType = std::string
// but leaving it unknown here lets us decide somewhere else what ElementType is
// and nothing in this file should need to know what ElementType is anyway
// This is our attempt to template Node so that `ElementType` could be anything we want
struct Node {
    ElementType value{};
    Node* next{};
};


// insertion
void push_front(Node*& head, Node* newNode) {
}

void push_back(Node*& head, Node* newNode) {
}

Node* insert_at(Node*& head, Node* new_node, size_t position) {
    return nullptr;
}

// removal
Node* pop_front(Node*& head) {
    return nullptr;
}

Node* pop_back(Node*& head) {
    return nullptr;
}

Node* erase_at(Node*& head, size_t position) {
    return nullptr;
}

// Accessing nodes
Node* get_node_at(Node* head, size_t position) {
    return nullptr;
}

// cleanup
void clear(Node*& head) {
}
