#include "page.hpp"
#include <fstream>
#include <sstream>
#include "errors.hpp"

/**
* Constructor that reads an input file and separates the navigation section
*   from the story text section

* input: fileName is the file that is being read
*/
Page::Page (char * fileName) {
  std::ifstream file (fileName);
  if (!file) {
    Error ("Could not open file!");
  }
  file >> choices;
  file.close ();
  std::cout << choices;
}

std::istream & operator>>(std::istream & s, std::vector<std::pair<std::string, int> > & data) {
  std::string line;
  while (std::getline (s, line)) {
    if (line.substr(0,1).compare("#") != 0) {
      size_t colon = line.find_first_of(':');
      char * extraNumbers = NULL;
      int nextPage = 0;
      //Handle win/lose in here? Or further checks if line without page number
      //Navigation section error checking
      if ((colon != std::string::npos || data.size() > 0) && 
         ((nextPage = strtol (line.substr(0, colon).c_str(), &extraNumbers, 10)) <= 0 || 
         *extraNumbers != '\0')) {
        Error ("Page number must be integer greater than 0.");
      }
      std::pair<std::string, int> pair (line.substr (colon + 1, line.length()), nextPage);
      data.push_back (pair);
    } else {
      break;
    }
  }

  if (data.size() == 0) {
    Error ("No navigation choices.");
  }

  while (std::getline (s, line)) {
    std::cout << line << std::endl;
  }
  std::cout << std::endl;
  return s;
}

std::ostream & operator<<(std::ostream & s, std::vector<std::pair<std::string, int> > & data) {
  std::vector<std::pair<std::string, int> >::iterator it = data.begin();
  int index = 1;
  if (it->second == 0) {
    if (it->first.compare ("WIN") == 0 && data.size() == 1) {
      s << "Congratulations! You have won. Hooray!" << std::endl;
    } else if (it->first.compare ("LOSE") == 0 && data.size() == 1) {
      s << "Sorry, you have lost. Better luck next time!" << std::endl;
    } else {
      Error ("Navigation choices must include page number.");
    }  
  } else {
      s << "What would you like to do?\n" << std::endl;
    while (it != data.end()) {
      s << " " << index << ". " << it->first << std::endl;
      //s << "\t" << it->second << std::endl; //FOR TESTING - DELETE
      ++it;
      index++;
    }
  }
  return s;
}
