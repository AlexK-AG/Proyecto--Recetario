#include "ingredients.hpp"
using namespace std;

Ingredients::Ingredients() {}

Ingredients::Ingredients(const Ingredients& s) : ingredient(s.ingredient), amount(s.amount){}


std::string Ingredients::getIngredients() const {
  return this->ingredient;
}

std::string Ingredients::getAmount() {
  return this->amount;
}

string Ingredients::toString() const {
  ostringstream oss;
    oss << ingredient << ", " << "Cantidad - " << amount;
    return oss.str();
}

void Ingredients::setIngredients(const string& ing) {
  this->ingredient = ing;
}

void Ingredients::setAmount(const string& am) {
    this->amount = am;
}

Ingredients& Ingredients::operator=(const Ingredients s)
{
    this->ingredient=s.ingredient;
    this->amount=s.amount;

    return *this;
}

bool Ingredients::operator == (const Ingredients& e) const
{
  return this->ingredient == e.ingredient;
}

bool Ingredients::operator != (const Ingredients& e) const
{
  //return this->code != e.code;
  return !(*this == e);
}

bool Ingredients::operator < (const Ingredients& e) const
{
  return this->ingredient < e.ingredient; 
}

bool Ingredients::operator > (const Ingredients& e) const
{
  //return this->code > e.code; 
 return !(*this <= e);
}

bool Ingredients::operator <= (const Ingredients& e) const
{
 // return this->code <= e.code; 
 return *this < e or *this == e;
}

bool Ingredients::operator >= (const Ingredients& e) const
{
 // return this->code >= e.code; 
 return !(*this < e);
}

int Ingredients::compareTo(const Ingredients& e)
{
  return this->ingredient.compare(e.ingredient);
}

int Ingredients::compare(const Ingredients& a, const Ingredients& b)
{
  return a.ingredient.compare(b.ingredient);
}

int Ingredients::compareIngredients(const Ingredients& a, const Ingredients& b)
{
  return a.ingredient.compare(b.ingredient);
}

// Implementación de operadores de serialización
std::ostream& operator<<(std::ostream& os, const Ingredients& ing) {
  os << ing.ingredient << "|" << ing.amount;
  return os;
}

std::istream& operator>>(std::istream& is, Ingredients& ing) {
  std::getline(is, ing.ingredient, '|');
  std::getline(is, ing.amount, '#');
  return is;
}