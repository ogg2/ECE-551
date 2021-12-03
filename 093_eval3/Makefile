CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3

cyoa-step1: page.cpp cyoa-step1.cpp page.hpp
	g++ $(CPPFLAGS) -o cyoa-step1 page.cpp cyoa-step1.cpp

cyoa-step2: page.cpp book.cpp cyoa-step2.cpp page.hpp book.hpp
	g++ $(CPPFLAGS) -o cyoa-step2 page.cpp book.cpp cyoa-step2.cpp

cyoa-step3: page.cpp book.cpp cyoa-step3.cpp page.hpp book.hpp
	g++ $(CPPFLAGS) -o cyoa-step3 page.cpp book.cpp cyoa-step3.cpp

cyoa-step4: page.cpp book.cpp cyoa-step4.cpp page.hpp book.hpp
	g++ $(CPPFLAGS) -o cyoa-step4 page.cpp book.cpp cyoa-step4.cpp

clean:
	rm -f cyoa-step?
