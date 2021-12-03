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
    bool referenced;
//    bool visited;
    int depth;
    size_t pageNum;
    Page * prev; //previous page used to backtrack solution after DFS
    std::stringstream pageText;
    //pair in vector contains navigation choices in string and next page in 'size_t'
    std::vector<std::pair<std::string, size_t> > choices; 
  public:
    Page(const char * fileName);
    void validChoices();
    const std::vector<std::pair<std::string, size_t> > getChoices() {return choices;}
    bool getReferenced() {return referenced;}
    void setReferenced(bool r) {referenced = r;}
  //  bool getVisited() {return visited;}
  //  void setVisited(bool v) {visited = v;}
    int getDepth() {return depth;}
    void setDepth(int d) {depth = d;}
    size_t getPageNum() {return pageNum;}
    void setPageNum(size_t pn) {pageNum = pn;}
    Page * getPrev() {return prev;}
    void setPrev(Page * p) {prev = p;}
    void printPage();
    friend std::istream & operator>>(std::istream & s, Page & page);
    friend std::ostream & operator<<(std::ostream & s, const Page & page);
};

#endif
