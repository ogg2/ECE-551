#include "book.hpp"

int main (int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./program directory" << std::endl;
    return EXIT_FAILURE;
  }

  Book book (argv[1]);
  book.validNextPage();
  book.allPagesReferenced();
  book.winAndLose();
  //book.readBook();
  book.depth();
  book.printDepth();
  return EXIT_SUCCESS;
}
