#include "recipe.hpp"
using namespace std;

Recipe::Recipe() {}

Recipe::Recipe(const Recipe& s) : recipeName(s.recipeName), preparationTime(s.preparationTime), procedure(s.procedure), category(s.category), chefAuthorName(s.chefAuthorName), ingredientsList(s.ingredientsList) {}

std::string Recipe::getRecipeName() const {
  return this->recipeName;
}

int Recipe::getPreparationTime() const {
  return this->preparationTime;
}

std::string Recipe::getProcedure() const {
  return this->procedure;
}

std::string Recipe::getCategory() const
{
  return this-> category;
}

Name Recipe::getChefAuthorName() const
{
  return this-> chefAuthorName;
}

ListSimple<Ingredients>& Recipe::getIngredientList() {
  return this->ingredientsList;
}

string Recipe::toString() const {
  ostringstream oss;

  int hours = preparationTime / 60;
  int minutes = preparationTime % 60;

  oss << "-------------------------------------------------------------------------------------------------------------\n"
      << "Nombre de la receta: " << recipeName << "\n"
      << "\nTiempo de preparacion: " << hours << " hora/s " << "con " << (minutes < 10 ? "0" : "") << minutes << " minutos" << "\n"
      << "\nIngredientes: \n" << ingredientsList.toString() << "\n"
      << "Categoria: " << category << "\n"
      << "\nChef: " << chefAuthorName.toString() << "\n"
      << "\nProcedimiento: " << procedure << "\n";

  return oss.str();
}

void Recipe::setRecipeName(const string& rn) {
  this->recipeName = rn;
}

void Recipe::setPreparationTime(const int& pt) {
  this->preparationTime = pt;
}

void Recipe::setProcedure(const string& pd) {
  this->procedure = pd;
}

void Recipe::setCategory(const int& ct)
{
  if(ct == 1){
    this->category = "Desayuno";
  }else if(ct == 2){
    this->category = "Comida";
  }else if(ct == 3){
    this->category = "Cena";
  }else{
    this->category = "Navideno";
  }
}

void Recipe::setChefAuthorName(const Name& can) {
  this-> chefAuthorName = can;
}

void Recipe::setIngredienteList(const ListSimple<Ingredients>& igl)
{
  this->ingredientsList = igl;
}


Recipe& Recipe::operator=(const Recipe& s)
{
    this->recipeName=s.recipeName;
    this->preparationTime=s.preparationTime;
    this->procedure=s.procedure;
    this->category=s.category;
    this->chefAuthorName=s.chefAuthorName;
    this->ingredientsList = s.ingredientsList;

    return *this;
}

bool Recipe::operator == (const Recipe& e) const
{
  return this->recipeName == e.recipeName;
}

bool Recipe::operator != (const Recipe& e) const
{
  //return this->code != e.code;
  return !(*this == e);
}

bool Recipe::operator < (const Recipe& e) const
{
  return this->recipeName < e.recipeName; 
}

bool Recipe::operator > (const Recipe& e) const
{
  //return this->code > e.code; 
 return !(*this <= e);
}

bool Recipe::operator <= (const Recipe& e) const
{
 // return this->code <= e.code; 
 return *this < e or *this == e;
}

bool Recipe::operator >= (const Recipe& e) const
{
 // return this->code >= e.code; 
 return !(*this < e);
}

int Recipe::compareTo(const Recipe& e)
{
  return this->recipeName.compare(e.recipeName);
}

int Recipe::compare(const Recipe& a, const Recipe& b)
{
  return a.recipeName.compare(b.recipeName);
}

int Recipe::compareNameRecipe(const Recipe& a, const Recipe& b)
{
  return a.recipeName.compare(b.recipeName);
}

int Recipe::compareCategory(const Recipe& a, const Recipe& b)
{
 return a.category.compare(b.category);
}

int Recipe::comparePrepTime(const Recipe& a, const Recipe& b)
{
 return a.preparationTime - b.preparationTime;
}


std::ostream& operator<<(std::ostream& os, const Recipe& recipe) {
  int ingredientCount = 0;
    ListSimple<Ingredients>::Position pos0 = recipe.ingredientsList.getFirstPos();
    while (pos0 != nullptr) {
        ingredientCount++;
        pos0 = recipe.ingredientsList.getNextPos(pos0);
    }

  os << recipe.recipeName << "|"
     << recipe.preparationTime << "|"
     << recipe.procedure << "|"
     << recipe.category << "|"
     << recipe.chefAuthorName.getFirst() << "|"
     << recipe.chefAuthorName.getLast() << "|"
     << ingredientCount << "|";
  
  ListSimple<Ingredients>::Position pos = recipe.ingredientsList.getFirstPos();             
  while (pos != nullptr) {
      os << recipe.ingredientsList.retrieve2(pos) << "#";
      pos = recipe.ingredientsList.getNextPos(pos);
  }
  os << '#';
  return os;
}

std::istream& operator>>(std::istream& is, Recipe& recipe) {
    std::string line;
    // Leer toda la línea para mejor control
    if (!std::getline(is, line)) {
        return is;
    }
    
    std::istringstream iss(line);
    std::string token;
    
    // Leer datos básicos
    std::getline(iss, recipe.recipeName, '|');
    
    std::getline(iss, token, '|');
    recipe.preparationTime = std::stoi(token);
    
    std::getline(iss, recipe.procedure, '|');
    std::getline(iss, recipe.category, '|');
    
    // Leer nombre del chef
    Name chef;
    std::string first, last;
    std::getline(iss, first, '|');
    std::getline(iss, last, '|');
    chef.setFirst(first);
    chef.setLast(last);
    recipe.setChefAuthorName(chef);
    
    // Leer número de ingredientes
    std::string ingCountStr;
    std::getline(iss, ingCountStr, '|');
    int ingCount = 0;
    if (!ingCountStr.empty() && ingCountStr != "0") {
        ingCount = std::stoi(ingCountStr);
    }

    // Limpiar lista existente
    recipe.ingredientsList.deleteAll();

    // Leer ingredientes
    for (int i = 0; i < ingCount; ++i) {
        Ingredients ing;
        std::string ingredientStr;
        std::getline(iss, ingredientStr, '#');
        
        // Parsear ingrediente (formato: "ingrediente|cantidad")
        std::istringstream ingStream(ingredientStr);
        std::string name, amount;
        std::getline(ingStream, name, '|');
        std::getline(ingStream, amount);
        
        ing.setIngredients(name);
        ing.setAmount(amount);
        recipe.ingredientsList.insertData(recipe.ingredientsList.getLastPos(), ing);
    }

    // Consumir los ## finales si existen
    if (iss.peek() == '#') {
        iss.ignore(2, '#');
    }

    return is;
}