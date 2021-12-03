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
    bool referenced;            //bool to make sure page in story is referenced
    int depth;                  //minimum page depth from page1
    size_t pageNum;             //page number as described in file name
    std::stringstream pageText; //remainder of text after "#" line

    //previous page used to backtrack winning path solution after DFS
    Page * prev;
    //array of all possible navigation choices associated with page
    //pair.first = text associated with navigation choice
    //pair.second = page number associated with navigation choice
    std::vector<std::pair<std::string, size_t> > choices; 
  public:
    Page(const char * fileName);
    void validChoices();
    const std::vector<std::pair<std::string, size_t> > getChoices() const {return choices;}
    bool getReferenced() const {return referenced;}
    void setReferenced(bool r) {referenced = r;}
    int getDepth() const {return depth;}
    void setDepth(int d) {depth = d;}
    size_t getPageNum() const {return pageNum;}
    void setPageNum(size_t pn) {pageNum = pn;}
    Page * getPrev() const {return prev;}
    void setPrev(Page * p) {prev = p;}
    void printPage() const;
    friend std::istream & operator>>(std::istream & s, Page & page);
    friend std::ostream & operator<<(std::ostream & s, const Page & page);
};

#endif
