#include "name.hpp"
using namespace std;

Name::Name() {}

Name::Name(const Name& other) : last(other.last), first(other.first) {}

string Name::getLast() const {
  return this->last;
}

string Name::getFirst() const {
  return this->first;
}

string Name::toString() const {
    return " " + this->first + " " + this->last;
}

void Name::setLast(const string& l) {
    this->last = l;
}

void Name::setFirst(const string& f) {
    this->first = f;
}

Name& Name::operator=(const Name& n){
  this-> last=n.last;
  this->first=n.first;
  return *this;
}

bool Name::operator == (const Name& e) const
{
  return this->toString() == e.toString();
}

bool Name::operator != (const Name& e) const
{
 return !(*this == e); 
}

bool Name::operator < (const Name& e) const
{
  return this->toString() < e.toString(); 
}

bool Name::operator > (const Name& e) const
{
  return !(*this <= e); 
}

bool Name::operator <= (const Name& e) const
{
  return *this < e or *this == e; 
}

bool Name::operator >= (const Name& e) const
{
  return !(*this < e); 
}

int Name::compareTo(const Name& e) const
{
  return this->toString().compare(e.toString());
}

int Name::compare(const Name& a, const Name& b)
{
  return a.toString().compare(b.toString());
}