#include "page.hpp"
#include <fstream>
#include "errors.hpp"
#include <exception>

/**
* Constructor that reads an input file and separates the navigation section
*   from the story text section
*
* input: fileName is the file that is being read
*/
Page::Page (const char * fileName) {
  std::ifstream file (fileName);
  if (!file) {
    throw std::invalid_argument ("File does not exist.");
  }
  referenced = false;
  depth = -1;
  prev = NULL;
  file >> *this;
  file.close ();
}
    
/**
* validChoices ensures a page's navigation choices are legal
*/
void Page::validChoices() {
  if (choices.size() == 0) {
    Error ("No navigation choices.");
  }
  
  std::pair<std::string, size_t> firstPair = choices.front();
  
  //if not a WIN/LOSE page, navigation choice must include page number
  if (firstPair.second == 0 && firstPair.first.compare ("WIN") != 0 
      && firstPair.first.compare ("LOSE") != 0) {
      Error ("Navigation choices must include page number.");
  }
}

/**
* printPage prints page.pageText to the terminal and calls operator<< to print page.choices
*/
void Page::printPage () const {
  std::cout << pageText.str();
  std::cout << *this;
}

/**
* Overloaded operator>> takes an input file and writes the contents to a page
*   navigation choices are written to page.choices
*   story text is written to page.pageText
*
* input: s is an input stream, file, that is being read from
* input: page is the object that is being created
*
* return: std::istream is the input file stream, return is unused
*/
std::istream & operator>>(std::istream & s, Page & page) {
  std::string line;
  while (std::getline (s, line)) {
    if (line.substr(0,1).compare("#") != 0) {
      size_t colon = line.find_first_of(':');
      char * extraNumbers = NULL;
      size_t nextPage = 0;
      //Navigation section error checking
      //Citation: based on code from /060_eval2
      if ((colon != std::string::npos || page.choices.size() > 0) && 
         ((nextPage = strtol (line.substr(0, colon).c_str(), &extraNumbers, 10)) <= 0 || 
         *extraNumbers != '\0')) {
        Error ("Page number must be integer greater than 0.");
      }

      //pair.first = text associated with navigation choice
      //pair.second = page number associated with navigation choice
      std::pair<std::string, size_t> pair (line.substr (colon + 1, line.length()), nextPage);
      page.choices.push_back (pair);
    } else {
      break;
    }
  }

  page.validChoices ();

  //read every line after line with "#" and add to pageText
  while (std::getline (s, line)) {
    page.pageText << line << "\n";
  }
  page.pageText << "\n";
  return s;
}

/**
* Overloaded operator<< prints page.choices to terminal
*
* input: s is the output stream to be printed
* input: page is a page that will have it's choices printed
*
* return: std::ostream is the output stream to be printed
*/
std::ostream & operator<<(std::ostream & s, const Page & page) {
  std::vector<std::pair<std::string, size_t> >::const_iterator it = page.choices.begin();

  //check if this page is a WIN/LOSE page
  if (it->second == 0) {
    if (it->first.compare ("WIN") == 0) {
      s << "Congratulations! You have won. Hooray!" << std::endl;
    } else {
      s << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    return s;
  }

  s << "What would you like to do?\n" << std::endl;
  int index = 1;
  while (it != page.choices.end()) {
    s << " " << index << ". " << it->first << std::endl;
    ++it;
    index++;
  }
  return s;
}
