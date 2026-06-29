/**
 * @file Sequence.cpp
 * @brief
 *
 * @author
 * @date
 */

#include <ostream>

#include "Sequence.h"

#include <limits>


// we need to say what ElementType is *before* including linked_list.h
// linked_list.h doesn't actually know what ElementType is on its own
using ElementType = Sequence::ElementType;
#include "linked_list.h"

Sequence::Sequence() {
}

Sequence::~Sequence() {
}

void Sequence::push_front(const ElementType& value) {
}

void Sequence::push_back(const ElementType& value) {
}

void Sequence::insert(size_t pos, const ElementType& value) {
}

ElementType Sequence::pop_front() {
    return {};
}

ElementType Sequence::pop_back() {
    return {};
}

ElementType Sequence::erase(size_t pos) {
    return {};
}

const ElementType& Sequence::front() const {
    return dummyElement;
}

const ElementType& Sequence::back() const {
    return dummyElement;
}

const ElementType& Sequence::get(size_t pos) const {
    return dummyElement;
}

bool Sequence::empty() const {
    return true;
}

size_t Sequence::size() const {
    return 0;
}

void Sequence::clear() {
}

std::ostream& operator<<(std::ostream& os, const Sequence& seq) {
    os << "<";

    // output seq to the ostream& os like:
    // A, B, C, D
    // output a ", " if you're not at the end of the list
    // for example:
    //  if(current->next != nullptr){
    //      // output ", "
    //  }

    os << ">";
    return os;
}
