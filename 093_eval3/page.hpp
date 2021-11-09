#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Page {
  private:
    std::string pageText;
    std::vector<std::string> choices; 
  public:
    Page (char * fileName);

};

//Are these needed here?
std::istream & operator>>(std::istream & s, std::vector<std::string> & data);
std::ostream & operator<<(std::ostream & s, std::vector<std::string> & data);


#endif
