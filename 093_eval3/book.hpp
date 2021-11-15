#ifndef __BOOK_HPP__
#define __BOOK_HPP__

#include "page.hpp"

/**
* Book is a class that holds a collection of pages
*/
class Book {
  private:
    std::vector<Page*> pages; 
  public:
    Book (char * directoryName);
    void printBook ();
    friend std::istream & operator>>(std::istream & s, Book & book);
    friend std::ostream & operator<<(std::ostream & s, Book & book);
};

#endif
