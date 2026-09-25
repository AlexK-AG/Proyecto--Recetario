#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>
#include <string>
#include "listDoublyLinked.hpp"
#include "listSimpleLinked.hpp"
#include "recipe.hpp"
#include "name.hpp"
#include "ingredients.hpp"

class Menu {
    private:
    ListDoubly<Recipe>* listRecipeBook;
    string filterCategory; //Para los filtros de la lista
    
    public:
    Menu(ListDoubly<Recipe>&);

};

#endif // __MENU_H__