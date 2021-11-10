#ifndef __ERRORS_HPP__
#define __ERRORS_HPP__
#include <string>

class Error {
  private:
    std::string message;
  public: 
  Error (std::string m) : message (m) {
    printError ();
  }

  void printError () {
    std::cerr << "Error: " <<message << std::endl;
    exit (EXIT_FAILURE);
  }
};

#endif
