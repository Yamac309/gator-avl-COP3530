/*
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <string>
#include "AVL.h"

using namespace std;

TEST_CASE("Incorrect AVL operations") {

    {
        AVL tree;
        REQUIRE(tree.insert("A", "12345678"));
        REQUIRE_FALSE(tree.insert("B", "12345678"));
    }

    {
        AVL tree;
        REQUIRE_FALSE(tree.removeID("87654321"));
    }

    {
        AVL tree;
        REQUIRE_FALSE(tree.removeInorder(0));
    }

    {
        AVL tree;
        tree.insert("C", "11111111");
        REQUIRE_FALSE(tree.removeInorder(5));
    }

    {
        AVL tree;
        string out;
        REQUIRE_FALSE(tree.searchID("99999999", out));
    }
}

TEST_CASE("Edge cases") {
    AVL tree;

    REQUIRE_FALSE(tree.removeID("12345678"));

    REQUIRE(tree.insert("A", "22222222"));
    REQUIRE(tree.removeID("22222222"));
    REQUIRE(tree.printInorder().empty());

    string out;
    REQUIRE_FALSE(tree.searchID("22222222", out));
}

TEST_CASE("AVL rotations") {

    {
        AVL tree;
        tree.insert("A", "30");
        tree.insert("B", "20");
        tree.insert("C", "10");
        REQUIRE(tree.printInorder() == vector<string>{"C", "B", "A"});
    }

    {
        AVL tree;
        tree.insert("A", "10");
        tree.insert("B", "20");
        tree.insert("C", "30");
        REQUIRE(tree.printInorder() == vector<string>{"A", "B", "C"});
    }

    {
        AVL tree;
        tree.insert("A", "30");
        tree.insert("B", "10");
        tree.insert("C", "20");
        REQUIRE(tree.printInorder() == vector<string>{"B", "C", "A"});
    }

    {
        AVL tree;
        tree.insert("A", "10");
        tree.insert("B", "30");
        tree.insert("C", "20");
        REQUIRE(tree.printInorder() == vector<string>{"A", "C", "B"});
    }
}

TEST_CASE("Deletion cases") {
    AVL tree;

    tree.insert("A", "10");
    REQUIRE(tree.removeID("10"));

    tree.insert("B", "20");
    tree.insert("C", "15");
    REQUIRE(tree.removeID("20"));

    tree.insert("D", "30");
    tree.insert("E", "25");
    tree.insert("F", "35");
    REQUIRE(tree.removeID("30"));
}


TEST_CASE("Bulk insert and delete") {
    AVL tree;

    for (int i = 0; i < 100; i++) {
        tree.insert("N", to_string(10000000 + i));
    }

    REQUIRE(tree.printInorder().size() == 100);

    for (int i = 0; i < 10; i++) {
        tree.removeID(to_string(10000000 + i * 3));
    }

    REQUIRE(tree.printInorder().size() == 90);
}
*/