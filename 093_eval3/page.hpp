#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/**
* Page is a class that holds the contents of an input page
*/
class Page {
  private:
    std::stringstream pageText;
    //pair in vector contains navigation choices in string and next page in 'int'
    std::vector<std::pair<std::string, int> > choices; 
  public:
    Page (char * fileName);
    void printPage () {
      std::cout << pageText.str();
      std::cout << *this;
    }
    friend std::istream & operator>>(std::istream & s, Page & page);
    friend std::ostream & operator<<(std::ostream & s, Page & page);
};

//Are these needed here?
//std::istream & operator>>(std::istream & s, std::vector<std::pair<std::string, int> > & data);
//std::ostream & operator<<(std::ostream & s, std::vector<std::pair<std::string, int> > & data);

#endif
