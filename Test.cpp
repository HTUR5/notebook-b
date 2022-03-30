#include "doctest.h"
#include "Notebook.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace ariel;
using ariel::Direction;

TEST_CASE("Write function - Horizontal") { //3 tests
    Notebook emptyNotebook;
    emptyNotebook.write(98, 55, 55, Direction::Horizontal, "HODAYA");                           
    emptyNotebook.write(99, 23, 52, Direction::Horizontal, "TURGEMAN");
    //sentence with spaces                             
    emptyNotebook.write(100, 44, 12, Direction::Horizontal, "THIS IS SENTENCE WITH SPACES");                            
   
    CHECK(emptyNotebook.read(98, 55, 55, Direction::Horizontal, 6) == "HODAYA"); 
    CHECK(emptyNotebook.read(99, 23, 52, Direction::Horizontal, 8) == "TURGEMAN"); 
    CHECK(emptyNotebook.read(100, 44, 12, Direction::Horizontal, 28) == "THIS IS SENTENCE WITH SPACES"); 
}   

TEST_CASE("Write function - Vertical"){ //3 tests
    Notebook emptyNotebook;
    emptyNotebook.write(50, 55, 55, Direction::Vertical, "HODAYA");                           
    emptyNotebook.write(50, 55, 56, Direction::Vertical, "TURGEMAN");
    //sentence with spaces                           
    emptyNotebook.write(50, 55, 57, Direction::Vertical, "THIS IS SENTENCE WITH SPACES");                            
   
    CHECK(emptyNotebook.read(50, 55, 55, Direction::Vertical, 6) == "HODAYA"); 
    CHECK(emptyNotebook.read(50, 55, 56, Direction::Vertical, 8) == "TURGEMAN"); 
    CHECK(emptyNotebook.read(50, 55, 57, Direction::Vertical, 28) == "THIS IS SENTENCE WITH SPACES"); 
} 

TEST_CASE("Write function - special places"){ //4 tests
    Notebook emptyNotebook;
    //write in the left up corner
    emptyNotebook.write(0, 0, 0, Direction::Horizontal, "HODAYA"); 
    emptyNotebook.write(0, 1, 0, Direction::Vertical, "HODAYA"); 
    
    CHECK(emptyNotebook.read(0, 0, 0, Direction::Vertical, 6) == "HODAYA");
    CHECK(emptyNotebook.read(0, 1, 0, Direction::Horizontal, 6) == "HODAYA");

    //write in the same row
    emptyNotebook.write(98, 54, 55, Direction::Horizontal, "ab");                           
    emptyNotebook.write(98, 54, 52, Direction::Horizontal, "cd"); 

    CHECK(emptyNotebook.read(98, 54, 52, Direction::Vertical, 5) == "cd_ab");

    //write in the same column
    emptyNotebook.write(7, 54, 10, Direction::Vertical, "ab");                           
    emptyNotebook.write(7, 57, 10, Direction::Vertical, "cd"); 

    CHECK(emptyNotebook.read(7, 54, 10, Direction::Vertical, 5) == "ab_cd");


}

TEST_CASE("read function - empty places"){ //2 tests
    Notebook emptyNotebook;
    CHECK(emptyNotebook.read(7, 54, 10, Direction::Vertical, 5) == "_____");
    CHECK(emptyNotebook.read(0, 0, 0, Direction::Vertical, 6) == "______");
}

TEST_CASE("Erase function"){ //4 tests
    Notebook emptyNotebook;
    //eraze where we already write
    //Horizontal test
    emptyNotebook.write(7, 7, 7, Direction::Horizontal, "shalom");
    emptyNotebook.erase(7, 7, 7, Direction::Horizontal, 2);
    CHECK(emptyNotebook.read(7, 7, 7, Direction::Horizontal, 4) == "~~~~om");

    //Vertical test
    emptyNotebook.write(7, 7, 7, Direction::Vertical, "shalom");
    emptyNotebook.erase(7, 7, 7, Direction::Vertical, 2);
    CHECK(emptyNotebook.read(7, 7, 7, Direction::Vertical, 4) == "~~~~om");

    //eraze in empty space
    emptyNotebook.erase(7, 0, 0, Direction::Horizontal, 2);
    CHECK(emptyNotebook.read(7, 0, 0, Direction::Horizontal, 4) == "~~__");

    //eraze where we already erazed
    emptyNotebook.erase(7, 7, 7, Direction::Horizontal, 2);
    CHECK(emptyNotebook.read(7, 7, 7, Direction::Horizontal, 4) == "~~~~om");
}

TEST_CASE("not valid amount of chars"){ //4 tests
    Notebook emptyNotebook;
    string char_more_then_100 = "--------------------------------------------------------------------------------------------------------------";
    CHECK_THROWS(emptyNotebook.write(1, 1, 1, Direction::Horizontal, char_more_then_100));
    CHECK_THROWS(emptyNotebook.read(7, 7, 7, Direction::Vertical, 101));
    CHECK_THROWS(emptyNotebook.erase(7, 7, 7, Direction::Vertical, 101));
    CHECK_THROWS(emptyNotebook.write(1, 1, 99, Direction::Horizontal, "---"));
}

TEST_CASE("not valid chars"){ //2 tests
    Notebook emptyNotebook;
    CHECK_THROWS(emptyNotebook.write(1, 1, 1, Direction::Horizontal, "~ "));
    CHECK_THROWS(emptyNotebook.write(7, 7, 7, Direction::Vertical, "\n "));
}

TEST_CASE("writing where we already eraze"){ //2 tests
    Notebook emptyNotebook;
    emptyNotebook.erase(7, 7, 7, Direction::Horizontal, 2);
    CHECK_THROWS(emptyNotebook.write(7, 7, 7, Direction::Horizontal, "aa"));
    emptyNotebook.erase(8, 7, 7, Direction::Horizontal, 2);
    CHECK_THROWS(emptyNotebook.write(8, 7, 7, Direction::Horizontal, "aaa"));
}

TEST_CASE("some caces with the char '_' "){ //2 tests
    //write again where we alredy write '_'
    Notebook emptyNotebook;
    emptyNotebook.write(7, 7, 7, Direction::Horizontal, "__");
    CHECK(emptyNotebook.read(7, 7, 7, Direction::Horizontal, 2) == "__");
    emptyNotebook.write(7, 7, 7, Direction::Horizontal, "_w");
    CHECK(emptyNotebook.read(7, 7, 7, Direction::Horizontal, 2) == "_w");

}

TEST_CASE("Negative numbers"){ //3 tests
    Notebook emptyNotebook;
    CHECK_THROWS(emptyNotebook.write(-1, 55, 55, Direction::Horizontal, "HODAYA"));
    CHECK_THROWS(emptyNotebook.erase(7, -5, 7, Direction::Horizontal, 2));
    CHECK_THROWS(emptyNotebook.read(-99, 7, 7, Direction::Vertical, 101));
    CHECK_THROWS(emptyNotebook.show(-3));
}

TEST_CASE("write, eraze and read for 10 pages"){ //10 tests
    Notebook emptyNotebook;
    for(int i= 0; i < 10; i++) {
        emptyNotebook.write(i, i, i, Direction::Horizontal, "abcd");
        CHECK(emptyNotebook.read(i, i, i, Direction::Horizontal, 5) == "abcd_");
        emptyNotebook.erase(i, i, i, Direction::Horizontal, 2);
        CHECK(emptyNotebook.read(i, i, i, Direction::Horizontal, 5) == "~~cd_");

    }
}