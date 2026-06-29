/**
* SequenceTestHarness.cpp
 * CS 3100
 * Project 1
 *
 * This source file contains the test harness used when grading the Sequence project.
 *
 * For students: DO NOT modify this file. If you cannot get your project to compile, it is not
 * because of this file. Also, modifying this file can give you false-positives or false-negatives
 * when running tests. To run this file in CLion, you need to select `sequence_starter` from the drop-down
 * menu next to the Build (hammer) icon.
 */

#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include "Sequence.h"
#include <gtest/gtest.h>

// -----------------------------------------------------------------------------
// Change this typedef to switch test type (int, double, std::string, etc.)
// -----------------------------------------------------------------------------
typedef Sequence::ElementType value_type;
// typedef int value_type;
// typedef double value_type;

#define INDEP
#define STREAM_INSERTION

#define PUSH_FRONT
#define PUSH_BACK
#define INSERT
#define INSERT_HEAD
#define INSERT_TAIL
#define INSERT_INVALID

#define POP_BACK
#define POP_BACK_EMPTY
#define POP_FRONT
#define POP_FRONT_EMPTY
#define ERASE
#define ERASE_HEAD
#define ERASE_TAIL
#define ERASE_INVALID

#define FRONT
#define FRONT_EMPTY
#define BACK
#define BACK_EMPTY
#define GET
#define GET_INVALID

#define EMPTY
#define SIZE

#define CLEAR


#define ASSIGNMENT
#define COPY_CONSTRUCTOR

#define MEMORY_LEAK_TEST

#define NUM_MEM_TESTS 10000
#define MEM_TEST_SIZE 10

// macro for when code should run without exceptions
#define EXPECT_OK(stmt) \
do { \
try { \
stmt; \
} catch (const std::exception& e) { \
FAIL() << "Unexpected exception: " << e.what(); \
} catch (...) { \
FAIL() << "Unexpected non-std exception"; \
} \
} while (0)

// macro for when code is expected to throw some expression, can provide a specific exception or just std::exception
#define EXPECT_FAIL(stmt, exType) \
EXPECT_THROW(stmt, exType)


// -----------------------------------------------------------------------------
// Conversion helper to generate values from integer indices.
// -----------------------------------------------------------------------------
inline value_type make_value(int i);

// Overload for string-like types
inline std::string make_value_string(int i) {
    return std::string(1, static_cast<char>('A' + i % 26));
}

// Generic template fallback for numeric or trivially convertible types
template<typename T>
inline T make_value_generic(int i) {
    return static_cast<T>(i + 1);
}

// Dispatcher
inline value_type make_value(int i) {
    if constexpr (std::is_same_v<value_type, std::string>)
        return make_value_string(i);
    else
        return make_value_generic<value_type>(i);
}


void insert_items(Sequence& s, std::initializer_list<int> values) {
#if defined(PUSH_FRONT)
    for (int v: std::views::reverse(values)) {
        EXPECT_OK(s.push_front(make_value(v)));
    }
#elif defined(PUSH_BACK)
    for (int v: values) {
        EXPECT_OK(s.push_front(make_value(v)));
    }
#elif defined(INSERT)
    for (int v: values) {
        EXPECT_OK(s.insert(0, make_value(v)));
    }
#else
    FAIL() << "No insertion method implemented (push_back or push_front)";
#endif
}


TEST(SequenceTest, IndependentSeqs) {
#if defined(INDEP)

    std::unique_ptr<Sequence> seq1;
    std::unique_ptr<Sequence> seq2;

    EXPECT_OK(seq1 = std::make_unique<Sequence>());
    ASSERT_NE(seq1, nullptr);

    EXPECT_OK(seq2 = std::make_unique<Sequence>());
    ASSERT_NE(seq2, nullptr);

    EXPECT_NE(seq1, seq2);

    insert_items(*seq1, {1, 3, 5, 7, 9});
    insert_items(*seq2, {2, 4, 6, 8, 10});

#ifndef FRONT
    GTEST_SKIP() << "Skipping testing independent sequences with front()";
#else
    EXPECT_OK(EXPECT_NE(seq1->front(), seq2->front()));
#endif

#ifndef BACK
    GTEST_SKIP() << "Skipping testing independent sequences with back()";
#else
    EXPECT_OK(EXPECT_NE(seq1->back(), seq2->back()));
#endif

#if !defined(STREAM_INSERTION)
    GTEST_SKIP() << "Skipping operator<< test for independent sequences";
#else
    std::stringstream ss1, ss2;
    EXPECT_OK(ss1 << *seq1);
    EXPECT_OK(ss2 << *seq2);
    EXPECT_NE(ss1.str(), ss2.str());
#endif

#else
    FAIL() << "Not testing independent sequences";
#endif
}


TEST(SequenceTest, CreatePrint) {
#if defined(STREAM_INSERTION)

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);

    insert_items(*seq, {0, 1, 2, 3, 4});

    std::stringstream ss;
    EXPECT_OK(ss << *seq);

    EXPECT_EQ(ss.str(), "<A, B, C, D, E>");

#else
    FAIL() << "Not testing create print";
#endif
}


TEST(SequenceTest, PushBack) {
#if defined(PUSH_BACK) && defined(BACK)

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    for (int i = 0; i < 5; i++) {
        EXPECT_OK(seq->push_back(make_value(i)));
        EXPECT_EQ(seq->back(), make_value(i));
    }

#if !defined(STREAM_INSERTION)
    GTEST_SKIP() << "Skipping operator<< test for PushBack";
#else
    std::stringstream ss;
    EXPECT_OK(ss << *seq);

    EXPECT_EQ(ss.str(), "<A, B, C, D, E>");
#endif

#else
    FAIL() << "Not testing push_back";
#endif
}

TEST(SequenceTest, PopBack) {
#if defined(POP_BACK)

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_EQ(seq->pop_back(), make_value(4)));
    EXPECT_OK(EXPECT_EQ(seq->pop_back(), make_value(3)));

#if !defined(STREAM_INSERTION)
    GTEST_SKIP() << "Skipping operator<< test for PushBack";
#else
    std::stringstream ss;
    EXPECT_OK(ss << *seq);

    EXPECT_EQ(ss.str(), "<A, B, C>");
#endif

#else
    FAIL() << "Not testing pop_back";
#endif
}

TEST(SequenceTest, PopBackEmtpy) {
#if defined(POP_BACK_EMPTY) && defined(PUSH_BACK)

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    EXPECT_OK(seq->pop_back());
    EXPECT_OK(seq->pop_back());
    EXPECT_OK(seq->pop_back());

    EXPECT_FAIL(seq->pop_back(), std::exception);
#else
    FAIL() << "Not testing pop_back on empty sequence";
#endif
}

TEST(SequenceTest, PushFront) {
#if defined(PUSH_FRONT)

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    for (int i = 0; i < 5; i++) {
        EXPECT_OK(seq->push_front(make_value(i)));
        EXPECT_OK(EXPECT_EQ(seq->front(), make_value(i)));
    }

#if !defined(STREAM_INSERTION)
    GTEST_SKIP() << "Skipping operator<< test for PushBack";
#else
    std::stringstream ss;
    EXPECT_OK(ss << *seq);

    EXPECT_EQ(ss.str(), "<E, D, C, B, A>");
#endif

#else
    FAIL() << "Not testing pop_back on empty sequence";
#endif
}

TEST(SequenceTest, PopFront) {
#ifdef POP_FRONT

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_EQ(seq->pop_front(), make_value(0)));
    EXPECT_OK(EXPECT_EQ(seq->pop_front(), make_value(1)));

#if !defined(STREAM_INSERTION)
    GTEST_SKIP() << "Skipping operator<< test for PushBack";
#else
    std::stringstream ss;
    EXPECT_OK(ss << *seq);

    EXPECT_EQ(ss.str(), "<C, D, E>");
#endif

#else
    FAIL() << "Not testing pop_front";
#endif
}

TEST(SequenceTest, PopFrontEmpty) {
#ifdef POP_FRONT_EMPTY

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    EXPECT_OK(seq->pop_front());
    EXPECT_OK(seq->pop_front());
    EXPECT_OK(seq->pop_front());

    EXPECT_FAIL(seq->pop_front(), std::exception);

#else
    FAIL() << "Not testing pop_front() on empty sequence";
#endif
}


TEST(SequenceTest, Insert) {
#if defined(INSERT)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    auto to_insert = make_value(99);
    EXPECT_OK(seq->insert(1, to_insert));

    bool hasPrint = false;
    bool hasGet = false;

#if defined(STREAM_INSERTION)
    hasPrint = true;
    std::stringstream ss;
    EXPECT_OK(ss << *seq);
    EXPECT_EQ(ss.str(), "<A, " + to_insert + ", B, C>");

#endif

#if defined(GET)
    hasGet = true;
    EXPECT_OK(EXPECT_EQ(seq->get(0), "A"));
    EXPECT_OK(EXPECT_EQ(seq->get(1), to_insert));
    EXPECT_OK(EXPECT_EQ(seq->get(2), "B"));
    EXPECT_OK(EXPECT_EQ(seq->get(3), "C"));

#endif

    if (!hasPrint && !hasGet) {
        GTEST_SKIP() << "No verification method (operator<< nor get()) available for insert()";
    }

    if (!hasPrint) {
        GTEST_LOG_(INFO) << "operator<< not used to test insert()";
    }
    if (!hasGet) {
        GTEST_LOG_(INFO) << "get() not used to test insert()";
    }

    ASSERT_TRUE(hasPrint || hasGet);

#else
    FAIL() << "Not testing insert";
#endif
}

TEST(SequenceTest, InsertHead) {
#if defined(INSERT_HEAD)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    auto to_insert = make_value(99);
    EXPECT_OK(seq->insert(0, to_insert));

    bool hasPrint = false;
    bool hasFront = false;
#if defined(STREAM_INSERTION)
    hasPrint = true;
    std::stringstream ss;
    EXPECT_OK(ss << *seq);
    EXPECT_EQ(ss.str(), "<" + to_insert + ", A, B, C>");
#endif

#if defined(FRONT)
    hasFront = true;
    EXPECT_OK(EXPECT_EQ(seq->front(), to_insert));
#endif

    if (!hasPrint && !hasFront) {
        GTEST_SKIP() << "No verification method (operator<< nor get()) available for to test InsertHead";
    }

    if (!hasPrint) {
        GTEST_LOG_(INFO) << "operator<< not used to test InsertHead";
    }
    if (!hasFront) {
        GTEST_LOG_(INFO) << "get() not used to test InsertHead";
    }

    ASSERT_TRUE(hasPrint || hasFront);

#else
    FAIL() << "Not testing InsertHead";
#endif
}

TEST(SequenceTest, InsertTail) {
#if defined(INSERT_TAIL)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    auto to_insert = make_value(99);
    EXPECT_OK(seq->insert(3, to_insert));

    bool hasPrint = false;
    bool hasBack = false;
#if defined(STREAM_INSERTION)
    hasPrint = true;
    std::stringstream ss;
    EXPECT_OK(ss << *seq);
    EXPECT_EQ(ss.str(), "<A, B, C, " + to_insert + ">");
#endif

#if defined(BACK)
    hasBack = true;
    EXPECT_OK(EXPECT_EQ(seq->back(), to_insert));
#endif

    if (!hasPrint && !hasBack) {
        GTEST_SKIP() << "No verification method (operator<< nor get()) available to test InsertTail";
    }

    if (!hasPrint) {
        GTEST_LOG_(INFO) << "operator<< not used to test InsertTail";
    }
    if (!hasBack) {
        GTEST_LOG_(INFO) << "get() not used to test InsertTail";
    }

    ASSERT_TRUE(hasPrint || hasBack);

#else
    FAIL() << "Not testing InsertTail";

#endif
}

TEST(SequenceTest, InsertInvalid) {
#ifdef INSERT_INVALID
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2});

    auto to_insert = make_value(99);
    EXPECT_FAIL(seq->insert(4, to_insert), std::exception);
    EXPECT_FAIL(seq->insert(5, to_insert), std::exception);
    EXPECT_FAIL(seq->insert(6, to_insert), std::exception);

#else
    FAIL() << "Not testing insert() with invalid position";
#endif
}

TEST(SequenceTest, Front) {
#ifdef FRONT
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_EQ(seq->front(), make_value(0)));
#else
    FAIL() << "Not testing front()";
#endif
}

TEST(SequenceTest, FrontEmpty) {
#ifdef FRONT_EMPTY
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    EXPECT_FAIL(seq->front(), std::exception);
#else
    FAIL() << "Not testing front() on empty sequence";
#endif
}

TEST(SequenceTest, Back) {
#ifdef BACK
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_EQ(seq->back(), make_value(4)));
#else
    FAIL() << "Not testing back()";
#endif
}

TEST(SequenceTest, BackEmpty) {
#ifdef BACK_EMPTY
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    EXPECT_FAIL(seq->back(), std::exception);
#else
    FAIL() << "Not testing back() on empty sequence";
#endif
}

TEST(SequenceTest, Get) {
#if defined(GET)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {4, 3, 5, 0, 2});

    EXPECT_OK(EXPECT_EQ(seq->get(0), make_value(4)));
    EXPECT_OK(EXPECT_EQ(seq->get(1), make_value(3)));
    EXPECT_OK(EXPECT_EQ(seq->get(2), make_value(5)));
    EXPECT_OK(EXPECT_EQ(seq->get(3), make_value(0)));
    EXPECT_OK(EXPECT_EQ(seq->get(4), make_value(2)));

#else
    FAIL() << "Not testing get()";
#endif
}

TEST(SequenceTest, GetInvalid) {
#if defined(GET_INVALID)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    value_type failed_get;
    EXPECT_FAIL(failed_get = seq->get(0), std::exception);

    insert_items(*seq, {4, 3, 5, 0, 2});

    EXPECT_FAIL(failed_get = seq->get(5), std::exception);
    EXPECT_FAIL(failed_get = seq->get(6), std::exception);
    EXPECT_FAIL(failed_get = seq->get(7), std::exception);

#else
    FAIL() << "Not testing get with invalid position";
#endif
}

TEST(SequenceTest, Empty) {
#ifdef EMPTY
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    EXPECT_OK(EXPECT_TRUE(seq->empty()));

    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_FALSE(seq->empty()));

#if defined(POP_FRONT)
    EXPECT_OK(
        while (!seq->empty()) {
        seq->pop_front();
        });
    EXPECT_OK(EXPECT_TRUE(seq->empty()));
#elif defined(POP_BACK)
    EXPECT_OK(
        while (!seq->empty()) {
        seq->pop_back();
        });
    EXPECT_OK(EXPECT_TRUE(seq->empty()));
#else
    GTEST_SKIP() << "Unable to remove all items with pop_front/back to validate empty() == true"
#endif

#else
    FAIL() << "Not testing empty()";
#endif
}

TEST(SequenceTest, Size) {
#ifdef SIZE
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    EXPECT_OK(EXPECT_EQ(seq->size(), 0));

    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(EXPECT_EQ(seq->size(), 5));

#if defined(POP_FRONT)
    EXPECT_OK(
        while (seq->size() > 0) {
        seq->pop_front();
        });
    EXPECT_OK(EXPECT_EQ(seq->size(), 0));
#elif defined(POP_BACK)
    EXPECT_OK(
        while (seq->size() > 0) {
        seq->pop_back();
        });
    EXPECT_OK(EXPECT_EQ(seq->size(), 0));
#else
    ADD_FAILURE() << "Unable remove all items with pop_front/back to validate size() == 0"
#endif
#else
    FAIL() << "Not testing size()";
#endif
}

TEST(SequenceTest, Clear) {
#ifdef CLEAR
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {0, 1, 2, 3, 4});

    EXPECT_OK(seq->clear());

    bool clearValidated = false;

#if defined(EMPTY)
    clearValidated = true;
    EXPECT_OK(EXPECT_TRUE(seq->empty()));
#else
    GTEST_LOG_(INFO) << "Unable to use empty() to validate clear()"
#endif

#if defined(SIZE)
    clearValidated = true;
    EXPECT_OK(EXPECT_EQ(seq->size(), 0));
#else
    GTEST_LOG_(INFO) << "Unable to use size() to validate clear()"
#endif

    if (!clearValidated) {
        ADD_FAILURE() << "Unable to validate clear with empty/size";
    }

#else
    FAIL() << "Not testing clear()";
#endif
}

TEST(SequenceTest, Erase) {
#ifdef ERASE

    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {4, 3, 5, 0, 2});

    value_type erased_value;

    EXPECT_OK(erased_value = seq->erase(2));
    EXPECT_EQ(erased_value, make_value(5));

#else
    FAIL() << "Not testing erase()";
#endif
}

TEST(SequenceTest, EraseHead) {
#if defined(ERASE_HEAD)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {4, 3, 5, 0, 2});

    value_type erased_value;

    EXPECT_OK(erased_value = seq->erase(0));
    EXPECT_EQ(erased_value, make_value(4));
#else
    FAIL() << "Not testing erase() on head";
#endif
}

TEST(SequenceTest, EraseTail) {
#if defined(ERASE_TAIL)
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {4, 3, 5, 0, 2});

    value_type erased_value;

    EXPECT_OK(erased_value = seq->erase(4));
    EXPECT_EQ(erased_value, make_value(2));
#else
    FAIL() << "Not testing erase() on tail";
#endif
}

TEST(SequenceTest, EraseInvalid) {
#ifdef ERASE_INVALID
    std::unique_ptr<Sequence> seq;

    EXPECT_OK(seq = std::make_unique<Sequence>());
    ASSERT_NE(seq, nullptr);
    insert_items(*seq, {4, 3, 5, 0, 2});

    value_type erased_value;

    EXPECT_FAIL(erased_value = seq->erase(5), std::exception);
    EXPECT_FAIL(erased_value = seq->erase(6), std::exception);
    EXPECT_FAIL(erased_value = seq->erase(7), std::exception);
#else
    FAIL() << "Not testing erase() with invalid position";
#endif
}

// currently these aren't in Project 3
// #ifdef ASSIGNMENT
// TEST(SequenceTest, ) {
//
// }
// #endif
//
// #ifdef COPY_CONSTRUCTOR
// TEST(SequenceTest, ) {
//
// }
// #endif

// this can't really be tested programmatically
TEST(SequenceTest, MemoryLeakTest) {
#ifdef MEMORY_LEAK_TEST
    std::cout << "Pre-memory leak test..." << std::endl;
    std::cout << std::endl; // set break point here
    for (int i = 0; i < NUM_MEM_TESTS; i++) {
        std::unique_ptr<Sequence> seq;
        EXPECT_OK(seq = std::make_unique<Sequence>());
        ASSERT_NE(seq, nullptr);
        insert_items(*seq, {4, 3, 5, 0, 2});
    }
    std::cout << "Post-memory leak test..." << std::endl;
    std::cout << std::endl; // set break point here

#else
    FAIL() << "Not running memory leak test";
#endif
}
