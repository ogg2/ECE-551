#ifndef __BOOK_HPP__
#define __BOOK_HPP__

#include "page.hpp"

/**
* Book is a class that holds a collection of pages
*/
class Book {
  private:
    std::vector<Page*> pages; 
    bool winnable;
    bool losable;
  public:
    Book(char * directoryName);
    void validNextPage();
    void allPagesReferenced();
    void winAndLose();
    void readBook();
    void freeBookMemory();
    friend std::istream & operator>>(std::istream & s, Book & book);
    friend std::ostream & operator<<(std::ostream & s, Book & book);
};

#endif
