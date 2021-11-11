#include "book.hpp"

int main (int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./program directory" << std::endl;
  }

  Book book (argv[1]);
  book.printBook();
  return EXIT_SUCCESS;
}
