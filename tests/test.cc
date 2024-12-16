#include <iostream>
#include "gtest/gtest.h"
#include <stddef.h>
#include "../sources/solid/single_responsible.hxx"
#include "../sources/solid/open_close.hxx"
#include "../sources/solid/liskov.hxx"

TEST(tests1, srp) {
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

TEST(tests2, oc_principle) {
    using namespace solid;
    Product apple   {"Apple",   Color::green,   Size::small};
    Product tree    {"Tree",    Color::green,   Size::large};
    Product house   {"House",   Color::blue,    Size::large};
    std::vector<Product*> items { &apple, &tree, &house };

    By_color by_color(Color::green);
    By_size by_size(Size::small);
    And_specification<Product> and_spec(by_color, by_size);
    Product_filter pf;
    const auto result = pf.filter(items, and_spec);
    ASSERT_EQ(1, result.size());
    ASSERT_EQ("Apple", result.at(0)->name);
}

TEST(tests3, liskov_substitution_principle) {
    using namespace solid;
    Rectangle rect(2,3);
    ASSERT_EQ(process(rect), 20); //2*10
    Square sqr(4);
    ASSERT_EQ(process(sqr), 100); //10*10

    auto rect2 = factory::create_rectangle(2,3);
    ASSERT_EQ(process(rect2), 20); //2*10
    auto sqr2 = factory::create_square(4);
    ASSERT_EQ(process(sqr2), 40); //4*10
}
