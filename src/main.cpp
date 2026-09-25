#include <iostream>
#include <cassert>
#include "menu.hpp"
#include "listDoublyLinked.hpp"
#include "recipe.hpp"

int main()
{
    ListDoubly<Recipe> recipBook;

    Menu mainMN(recipBook);
}