#include "book.hpp"
#include "errors.hpp"
#include <limits>
#include <cmath>
#include <queue>
#include <stack>

/**
* Constructor to add all the pages in directoryName to a book
*
* input: directoryName is the directory that contains all of the page files
*/
Book::Book (char * directoryName) {
  size_t index = 1;
  bool lastPage = false;
  while (!lastPage) {
    std::stringstream s;
    s << directoryName << "/page" << index << ".txt";
    try {
      Page * page = new Page(s.str().c_str()); 
      page->setPageNum(index);
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
    if ((*it)->getChoices()[0].first.compare("WIN") == 0) {
      winnable = true;
    }
    if ((*it)->getChoices()[0].first.compare("LOSE") == 0) {
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

    if (thisPage->getChoices()[0].first.compare("WIN") != 0 && 
        thisPage->getChoices()[0].first.compare("LOSE") != 0) {

      for (size_t i = 0; i < thisPage->getChoices().size(); i++) {
        size_t nextPage = thisPage->getChoices()[i].second;
        //add to queue if not yet visited
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
* cycleFreeWins usees DFS to find all possible, cycle-free, paths from page1
*   to any win page
*/
void Book::cycleFreeWins() {
  bool unwinnable = true;
  //mark as not visited when popping?, "avoid revisiting node on same path"
  //DFS using stack?
  //track explored paths with extra vector after marking as unvisited
    //this is local variable so we can still reuse page in a separate path
  std::stack<Page*> pageStack;
  pageStack.push(pages[0]);
  
  std::vector<Page*> currentPath;
  //std::vector<size_t> choices;
  //currentPath.push_back(pair);
  //bool popping = false;
  //bool addedPage = true;

  while (!pageStack.empty()) {
    Page * thisPage = pageStack.top();
    pageStack.pop();
    //thisPage->setVisited(true);

    /*if (addedPage) {
      thisPage->setVisited(false);
    }*/

    //currentPath.push_back(thisPage);
    //std::cout << "Vector Size: " << thisPage->getChoices().size() << std::endl;
    /*while (popping) {
      size_t currentChoice = choices.back();
      choices.pop_back();
      if (currentChoice <= 1) {
        currentPath.back()->setVisited(false);
        currentPath.pop_back();
      } else {
        //while (pages[thisPage->getChoices()[currentChoice - 1].second]->getVisited()) {
        //  currentChoice--;
        //  if (currentChoice == 0) {
        //    break;
        //  }
        //}
        choices.push_back(currentChoice - 1);
        popping = false;
      }
    }
    size_t index = thisPage->getChoices().size();
    //while (pages[thisPage->getChoices()[index - 1].second]->getVisited()) {
    //  index--;
    //  if (index == 0) {
    //    break;
    //  }
    //}
    currentPath.push_back(thisPage);
    //choices.push_back(thisPage->getChoices().size());
    choices.push_back(index);*/

    if (thisPage->getChoices()[0].first.compare("WIN") == 0) {
      printWins(thisPage);
      unwinnable = false;
      //addedPage = false;
      //printWins(currentPath, choices);
      //popping = true; 
      //pageStack.pop();
      //break;
    } else if (thisPage->getChoices()[0].first.compare("LOSE") == 0) {
      //popping = true; 
      //addedPage = false;
    } else {
      for (size_t i = 0; i < thisPage->getChoices().size(); i++) {
        size_t nextPage = thisPage->getChoices()[i].second;
        bool visited = false;
        Page * prevPage = thisPage->getPrev();
        while (prevPage != NULL) {
          if (prevPage->getPageNum() == nextPage ||
              thisPage->getPageNum() == nextPage) {
            visited = true;
          }
          //std::cout << "Page Num: " << prevPage->getPageNum() << std::endl;
          prevPage = prevPage->getPrev();
        }
        //if (!pages[nextPage - 1]->getVisited()) {
        if (!visited) {
          pages[nextPage - 1]->setPrev(thisPage);
          pageStack.push(pages[nextPage - 1]); 
          //addedPage = true;
          //popping = false;
        }
      }
    }
  }
  if (unwinnable) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}

/**
* printWins prints the page numbers and corresponding choices required to reach 
*   a winning page
*
* input: thisPage is the win page that we will be printing the winning path to
*/
void Book::printWins(Page * thisPage) {//, std::vector<size_t> choices) {
  std::vector<std::pair<size_t, size_t> > path;

  Page * prevPage = thisPage->getPrev();
  std::pair<size_t, size_t> pair (thisPage->getPageNum(), 0);
  path.push_back(pair);

  //reconstruct path by looking at prev pages
  while (prevPage != NULL) {
    size_t choice;
    for (size_t i = 0; i < prevPage->getChoices().size(); i++) { // what if diff choice goes to same page?
      if (prevPage->getChoices()[i].second == thisPage->getPageNum()) {
        choice = i + 1;
        break;
      }
    }
    pair = std::make_pair(prevPage->getPageNum(), choice);
    path.push_back(pair); 

    thisPage = prevPage;
    prevPage = prevPage->getPrev();
  }

  std::vector<std::pair<size_t, size_t> >::reverse_iterator rit = path.rbegin();
  while (rit != path.rend()) {
    std::cout << rit->first << "(";
    if (rit->second == 0) {
      std::cout << "win)";
    } else {
      std::cout << rit->second << "),";
    }
    ++rit;
  }
  std::cout << std::endl;
  /*for (size_t i = path.size() - 1; i > 0; i--) {
    std::cout << path[i].first << "(";
    if (path[i].second == 0) {
      std::cout << "win)";
    } else {
      std::cout << path[i].second << "),";
    }
  }
  std::cout << std::endl;*/


  /*for (size_t i = 0; i < path.size(); i++) {
    std::cout << path[i]->getPageNum() << "(";
    if (path[i]->getChoices()[0].second == 0) {
      std::cout << "win)";
    } else {
      std::cout << choices[i] << "),";
    }
  }
  std::cout << std::endl;*/
}

/**
* readBook allows a user to play the CYOA, playing involves printing pageText
*   for the current page, displaying the page's navigations choices, prompting
*   the user to select which choice they would like to make, and navigating to page
*   corresponding to user's choice
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
