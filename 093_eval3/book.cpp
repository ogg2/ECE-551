#include "book.hpp"
#include "errors.hpp"
#include <limits>
#include <cmath>

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

void Book::winAndLose() {
  if (!losable) {
    Error ("Story is not losable.");
  }
  if (!winnable) {
    Error ("Story is not winnable.");
  }
}

void Book::readBook () {
  Page * thisPage = pages[0];
  thisPage->printPage();
  while (true) {
    if (thisPage->getChoices()[0].second == 0) {
      freeBookMemory();
      exit (EXIT_SUCCESS);
    }
    //size_t userChoice;
    float userChoice;
    bool invalidInput = true;

    //NEED TO FIGURE OUT DOUBLE/FLOAT INPUTS
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
      
void Book::freeBookMemory() {
  std::vector<Page*>::iterator it = pages.begin();
  while (it != pages.end()) {
    delete *it;
    ++it;
  }
  pages.~vector();
}
