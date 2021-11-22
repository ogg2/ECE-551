#include "book.hpp"
#include "errors.hpp"
#include <limits>
#include <cmath>
#include <queue>

/**
* Constructor to add all the pages in directoryName to a book
*
* input: directoryName is the directory that contains all of the page files
*/
Book::Book (char * directoryName) {
  int index = 1;
  bool lastPage = false;
  while (!lastPage) {
    std::stringstream s;
    s << directoryName << "/page" << index << ".txt";
    try {
      Page * page = new Page(s.str().c_str()); 
      pages.push_back(page);
    } catch (std::invalid_argument & e) {
      if (index == 1) {
        Error ("page1.txt does not exist.");
      }
      lastPage = true;
    }
    index++;
  }
  winnable = false;
  losable = false;
}

/**
* validNextPage ensures each next page choice is a page that exists
*   within the book, each page is then marked as referenced
*/
void Book::validNextPage () {
  for (size_t i = 0; i < pages.size(); i++) {
    for (size_t j = 0; j < pages[i]->getChoices().size(); j++) {
      size_t nextPage = pages[i]->getChoices()[j].second;
      if (nextPage > pages.size()) {
        Error ("Page reference out of bounds.");
      } else {
        //Mark pages as referenced
        if (nextPage != 0) {
          pages[nextPage - 1]->setReferenced (true);
        }
      }
    }
  }
}

/**
* allPagesReferenced ensures each page is referenced by checking it's
*    referenced field, if page is a win or lose page the book's  winnable or losable
*    field in is updated accordingly
*/
void Book::allPagesReferenced () {
  std::vector<Page*>::iterator it = pages.begin();
  ++it; //page1 does not need to be referenced  
  while (it != pages.end()) {
    if (!(*it)->getReferenced()) {
      Error ("Not every page is referenced.");
    }
    //CHECK THERE IS BOTH A WIN PAGE AND LOSE PAGE
    if ((*it)->getChoices()[0].first.compare("Congratulations! You have won. Hooray!") == 0) {
      winnable = true;
    }
    if ((*it)->getChoices()[0].first.compare("Sorry, you have lost. Better luck next time!") == 0) {
      losable = true;
    }
    ++it;
  }
}

/**
* winAndLose ensures a CYOA is winnable and losable by checkings it's
*   winnable and losable field accordingly
*/
void Book::winAndLose() {
  if (!losable) {
    Error ("Story is not losable.");
  }
  if (!winnable) {
    Error ("Story is not winnable.");
  }
}

/**
* depth prints the story depth for each page in the book in numerical order
*/
void Book::depth() {
  std::queue<Page*> pageQueue;
  pages[0]->setDepth(0);
  pageQueue.push(pages[0]);
  
  while (!pageQueue.empty()) {
    Page * thisPage = pageQueue.front();
    pageQueue.pop();
    int pageDepth = thisPage->getDepth();

    if (thisPage->getChoices()[0].first.compare("Congratulations! You have won. Hooray!") != 0 && 
        thisPage->getChoices()[0].first.compare("Sorry, you have lost. Better luck next time!") != 0) {

      for (size_t i = 0; i < thisPage->getChoices().size(); i++) {
        size_t nextPage = thisPage->getChoices()[i].second;
        //do not add to queue if already visited
        //change choices to just WIN/LOSE
        if (pages[nextPage - 1]->getDepth() == -1) {
          pages[nextPage - 1]->setDepth(pageDepth + 1);
          pageQueue.push(pages[nextPage - 1]);
        }
      }
    }
  }
}

/**
* printDepth prints the minimum depth of each page in the book
*/
void Book::printDepth() {
  for (size_t i = 0; i < pages.size(); i++) {
    std::cout << "Page " << i + 1;
    if (pages[i]->getDepth() > -1) {
      std::cout << ":" << pages[i]->getDepth() << std::endl;
    } else {
      std::cout << " is not reachable" << std::endl;
    }
  }
}

/**
* readBook allows a user to play the CYOA, playing involves printing pageText
*   for the current page, displaying the page's navigations choices, prompting
*   the user to select which choice they would like to make 
SIMPLIFY COMMENT?????
*/
void Book::readBook() {
  Page * thisPage = pages[0];
  thisPage->printPage();
  while (true) {
    if (thisPage->getChoices()[0].second == 0) {
      return;
    }
    //size_t userChoice;
    float userChoice;
    bool invalidInput = true;

    //NEED TO FIGURE OUT DOUBLE/FLOAT INPUTS
    //error checking user input
    while (invalidInput) {
      std::cin >> userChoice;
      if (std::cin.good() && (size_t) userChoice <= thisPage->getChoices().size() 
          && (size_t) userChoice > 0 && fmod(userChoice, 1.0) == 0.0) {
        invalidInput = false;
      } else {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    userChoice = thisPage->getChoices()[userChoice - 1].second;

    thisPage = pages[userChoice - 1];
    thisPage->printPage();
  }
}
      
/**
* freeBookMemory deletes each page within the book
*/
void Book::freeBookMemory() {
  std::vector<Page*>::iterator it = pages.begin();
  while (it != pages.end()) {
    delete *it;
    ++it;
  }
}
