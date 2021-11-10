#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Page {
  private:
    std::string pageText;
    std::vector<std::pair<std::string, int> > choices; 
    //std::vector<int> nextPage;
  public:
    Page (char * fileName);

};

//Are these needed here?
std::istream & operator>>(std::istream & s, std::vector<std::pair<std::string, int> > & data);
std::ostream & operator<<(std::ostream & s, std::vector<std::pair<std::string, int> > & data);


#endif
