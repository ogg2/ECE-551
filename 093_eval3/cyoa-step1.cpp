#include "page.hpp"

int main (int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./program input.txt" << std::endl;
  }

  Page page (argv[1]);
  page.printPage();
  return EXIT_SUCCESS;
}
