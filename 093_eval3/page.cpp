#include "page.hpp"
#include <fstream>
#include <sstream>

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

std::istream & operator>>(std::istream & s, std::vector<std::pair<std::string, int> > & data) {
  std::string line;
  while (std::getline (s, line)) {
    if (line.substr(0,1).compare("#") != 0) {
      size_t colon = line.find_first_of(":");
      //std::string::size_type sz;
      int nextPage; // = atoi (line.substr(0, colon));
      std::istringstream (line.substr(0, colon)) >> nextPage;
      std::pair<std::string, int> pair (line.substr (colon + 1, line.length()), nextPage);
      //pair.first = line.substr(colon + 1, line.length());
      //pair.second = line.substr(0, colon);
      //pair.second = 2;
      data.push_back (pair);
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

std::ostream & operator<<(std::ostream & s, std::vector<std::pair<std::string, int> > & data) {
  std::vector<std::pair<std::string, int> >::iterator it = data.begin();
  int index = 1;
  while (it != data.end()) {
    s << " " << index << ". " << it->first << std::endl;
    s << " " << index << ". " << it->second << std::endl;
    ++it;
    index++;
  }
  return s;
}
