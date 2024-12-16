#include <iostream>
#include "gtest/gtest.h"
#include <stddef.h>
#include "../sources/solid/single_responsible.hxx"

TEST(tests, single_responsible) {
    using namespace solid;
    Journal journal("Diary");
    journal.add_new_entry("I ate bug today!");
    journal.add_new_entry("I cried today!");
    //write data to diary.txt
    persistence_manager::save("diary.txt", journal);
    //read data from diary.txt
    std::ifstream ifs("diary.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }

    ASSERT_EQ("<Diary>", lines.at(0));
    ASSERT_EQ("1) I ate bug today!", lines.at(1));
    ASSERT_EQ("2) I cried today!", lines.at(2));
    ASSERT_EQ(3, lines.size());
}

