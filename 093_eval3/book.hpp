#ifndef __BOOK_HPP__
#define __BOOK_HPP__

#include "page.hpp"

/**
* Book is a class that holds a collection of pages
*/
class Book {
  private:
    std::vector<Page*> pages; //array of all pages in book
    bool winnable;            //at least one win page in book
    bool losable;             //at least one lose page in book
  public:
    Book(char * directoryName);
    void validNextPage();
    void allPagesReferenced();
    void winAndLose() const;
    void depth();
    void printDepth() const;
    void cycleFreeWins();
    void printWins(const Page * thisPage) const;
    void readBook() const;
    void freeBookMemory();
};

#endif
