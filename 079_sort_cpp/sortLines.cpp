#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::istream & operator>>(std::istream & s, std::vector<std::string> & data) {
  std::string line;
  while (std::getline (s, line)) {
    data.push_back(line);
  }
  return s;
}

std::ostream & operator<<(std::ostream & s, std::vector<std::string> & data) {
  /*if (data.size() > 0) {
    for (size_t i = 0; i < data.size() - 1; i++) {
      s << data[i] << "\n";
    }
    s << data[data.size() - 1];
  }*/

  std::vector<std::string>::iterator it = data.begin();
  while (it != data.end()) {
    s << *it << "\n";
    ++it;
  }

  return s;
}

int main (int argc, char ** argv) {
  std::vector<std::string> v1;
  if (argc == 1) {
    std::cin >> v1;
  } else {
    for (int i = 1; i < argc; i++) {
      std::ifstream file (argv[i]);
      if (!file) {
        std::cerr << "Could not open file!" << std::endl;
        return EXIT_FAILURE;
      }
      file >> v1;
      file.close (); 
    }
  }

  std::sort (v1.begin(), v1.end());
  std::cout << v1;
  return EXIT_SUCCESS;
}
