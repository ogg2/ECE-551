#include "book.hpp"

/**
* main for cyoa-step3
*/
int main (int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./program directory" << std::endl;
    return EXIT_FAILURE;
  }

  Book book (argv[1]);
  book.validNextPage();
  book.allPagesReferenced();
  book.winAndLose();
  book.depth();
  book.printDepth();
  book.freeBookMemory();
  return EXIT_SUCCESS;
}
