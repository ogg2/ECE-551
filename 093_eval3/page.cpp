#include "page.hpp"
#include <fstream>
#include "errors.hpp"
#include <exception>

/**
* Constructor that reads an input file and separates the navigation section
*   from the story text section

* input: fileName is the file that is being read
*/
Page::Page (const char * fileName) {
  std::ifstream file (fileName);
  if (!file) {
    throw std::invalid_argument ("Bad");
    //Error ("Could not open file!");
  }
  possibleWin = false;
  possibleLoss = false;
  file >> *this;
  file.close ();
}

void Page::validChoices() {
  if (choices.size() == 0) {
    Error ("No navigation choices.");
  }
  
  std::pair<std::string, int> firstPair = choices.front();

  if (firstPair.second == 0) {
    if (firstPair.first.compare ("WIN") == 0 && choices.size() == 1) {
      choices.front().first = "Congratulations! You have won. Hooray!";
      possibleWin = true;
    } else if (firstPair.first.compare ("LOSE") == 0 && choices.size() == 1) {
      choices.front().first = "Sorry, you have lost. Better luck next time!";
      possibleLoss = true;
    } else {
      Error ("Navigation choices must include page number.");
    }
  }
}

/**
* printPage prints page.pageText to the terminal and calls operator<< to print page.choices
*/
void Page::printPage () {
  std::cout << pageText.str();
  std::cout << *this;
}

/**
* Overloaded operator>> takes an input file and writes the contents to a page
*   navigation choices are written to page.choices
*   story text is written to page.pageText
*/
std::istream & operator>>(std::istream & s, Page & page) {
  std::string line;
  while (std::getline (s, line)) {
    if (line.substr(0,1).compare("#") != 0) {
      size_t colon = line.find_first_of(':');
      char * extraNumbers = NULL;
      int nextPage = 0;
      //Navigation section error checking
      if ((colon != std::string::npos || page.choices.size() > 0) && 
         ((nextPage = strtol (line.substr(0, colon).c_str(), &extraNumbers, 10)) <= 0 || 
         *extraNumbers != '\0')) {
        Error ("Page number must be integer greater than 0.");
      }
      std::pair<std::string, int> pair (line.substr (colon + 1, line.length()), nextPage);
      page.choices.push_back (pair);
    } else {
      break;
    }
  }

  page.validChoices ();

  while (std::getline (s, line)) {
    page.pageText << line << "\n";
  }
  page.pageText << "\n";
  return s;
}

/**
* Overloaded operator<< prints page.choices to terminal
*/
std::ostream & operator<<(std::ostream & s, const Page & page) {
  std::vector<std::pair<std::string, int> >::const_iterator it = page.choices.begin();
  int index = 1;
  if (it->second == 0) {
    s << it->first << std::endl;
    return s;
  }
  s << "What would you like to do?\n" << std::endl;
  while (it != page.choices.end()) {
    s << " " << index << ". " << it->first << std::endl;
    //s << "\t" << it->second << std::endl; //FOR TESTING - DELETE
    ++it;
    index++;
  }
  return s;
}
