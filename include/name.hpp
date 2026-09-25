#ifndef __NAME_H__
#define __NAME_H__

#include <string>

class Name {
 private:
  std::string last;
  std::string first;

 public:
  Name();
  Name(const Name&);

  std::string getLast() const;
  std::string getFirst() const;

  std::string toString()const;

  void setLast(const std::string&);
  void setFirst(const std::string&);

  Name& operator=(const Name&);
        
  bool operator == (const Name&) const;
  bool operator != (const Name&) const;
  bool operator < (const Name&) const;
  bool operator > (const Name&) const;
  bool operator <= (const Name&) const;
  bool operator >= (const Name&) const;

  int compareTo(const Name&) const;    
  static int compare(const Name&, const Name&);
};
#endif  // __NAME_H__