#ifndef __Recipe_H__
#define __Recipe_H__

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include "name.hpp"
#include "listSimpleLinked.hpp"
#include "ingredients.hpp"

class Recipe {
  private:
    std::string recipeName;
    int preparationTime;
    ListSimple<Ingredients> ingredientsList;
    std::string procedure;
    std::string category;
    Name chefAuthorName;

  public:

  Recipe();
  Recipe(const Recipe&);

  std::string getRecipeName() const;
  int getPreparationTime() const;
  std::string getProcedure() const;
  std::string getCategory() const;
  Name getChefAuthorName() const;
  ListSimple<Ingredients>& getIngredientList(); // Método para obtener la lista de ingredientes

  std::string toString() const;

  void setRecipeName(const std::string&);
  void setPreparationTime(const int&);
  void setProcedure(const std::string&);
  void setCategory(const int&);
  void setChefAuthorName(const Name&);
  void setIngredienteList(const ListSimple<Ingredients> &);

  Recipe& operator=(const Recipe&);

  bool operator == (const Recipe&) const;
  bool operator != (const Recipe&) const;
  bool operator < (const Recipe&) const;
  bool operator > (const Recipe&) const;
  bool operator <= (const Recipe&) const;
  bool operator >= (const Recipe&) const;

  int compareTo(const Recipe&);
  
  static int compare(const Recipe&, const Recipe&);

  static int compareNameRecipe(const Recipe&, const Recipe&);

  static int compareCategory(const Recipe&, const Recipe&); 

  static int comparePrepTime(const Recipe&, const Recipe&);
  
  friend std::ostream& operator<<(std::ostream& os, const Recipe& recipe);
  friend std::istream& operator>>(std::istream& is, Recipe& recipe);
};

#endif // __Recipe_H__