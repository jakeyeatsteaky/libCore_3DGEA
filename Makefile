build:
	g++ -std=c++17 -Wall -Werror -IInclude Src/*.cpp -g main.cpp -o libCore

build_and_run:
	g++ -std=c++17 -Wall -Werror -IInclude Src/*.cpp -g main.cpp -o libCore
	./libCore

clean:
	rm libCore
