#ifndef __INGREDIENTS_H__
#define __INGREDIENTS_H__

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "listSimpleLinked.hpp"

class Ingredients {
  private:
    std::string ingredient;
    std::string amount;

 public:

  Ingredients();
  Ingredients(const Ingredients&);

  std::string getIngredients() const;
  std::string getAmount();

  std::string toString() const;

  void setIngredients(const std::string&);
  void setAmount(const std::string&);


  Ingredients& operator=(const Ingredients);

  bool operator == (const Ingredients&) const;
  bool operator != (const Ingredients&) const;
  bool operator < (const Ingredients&) const;
  bool operator > (const Ingredients&) const;
  bool operator <= (const Ingredients&) const;
  bool operator >= (const Ingredients&) const;

  int compareTo(const Ingredients&);
  
  static int compare(const Ingredients&, const Ingredients&);

  static int compareIngredients(const Ingredients&, const Ingredients&);

  friend std::ostream& operator<<(std::ostream& os, const Ingredients& ing);
  friend std::istream& operator>>(std::istream& is, Ingredients& ing);
};

#endif // __INGREDIENTS_H__