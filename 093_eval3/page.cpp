#include "page.hpp"
#include <fstream>

/**
* Constructor that reads an input file and separates the navigation section
*   from the story text section

* input: fileName is the file that is being read
*/
Page::Page (char * fileName) {
  std::ifstream file (fileName);
  if (!file) {
    std::cerr << "Error: Could not open file!" << std::endl;
    exit (EXIT_FAILURE);
  }
  
  file >> choices;
  file.close ();
  std::cout << choices;

}

std::istream & operator>>(std::istream & s, std::vector<std::string> & data) {
  std::string line;
  while (std::getline (s, line)) {
    if (line.compare("#") != 0) { //change to starts with # instead of only "#"
      data.push_back(line);
    } else {
      break;
    }
  }

  while (std::getline (s, line)) {
    std::cout << line << std::endl;
  }

  std::cout << "\nWhat would you like to do?\n" << std::endl;
  return s;
}

std::ostream & operator<<(std::ostream & s, std::vector<std::string> & data) {
  std::vector<std::string>::iterator it = data.begin();
  while (it != data.end()) {
    s << *it << std::endl;
    ++it;
  }
  return s;
}

