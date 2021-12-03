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
    void depth();
    void printDepth();
    void cycleFreeWins();
    void printWins(Page * thisPage);
    //void printWins(std::vector<Page*> path, std::vector<size_t> choices);
    void readBook();
    void freeBookMemory(); //make this destructor?
    //write copy constructor and assignment operator?
    friend std::istream & operator>>(std::istream & s, Book & book);
    friend std::ostream & operator<<(std::ostream & s, Book & book);
};

#endif
