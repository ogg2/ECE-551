#include "book.hpp"

Book::Book (char * directoryName) {
  int index = 1;
  bool lastPage = false;
  while (!lastPage) {
    std::stringstream s;
    s << directoryName << "/page" << index << ".txt";
    //std::cout << s.str();
    try {
      Page * page = new Page(s.str().c_str()); 
      pages.push_back(page);
    } catch (std::invalid_argument & e) {
      std::cout << "Last Page\n";
      lastPage = true;
    }
    index++;
  }
}

void Book::printBook () {
  std::vector<Page*>::iterator it = pages.begin();
  while (it != pages.end()) {
    (*it)->printPage();
    ++it;
  }
}
