all: main.cpp encrypt.cpp treebuilder.cpp codemaker.cpp
	g++ -o scale main.cpp encrypt.cpp treebuilder.cpp codemaker.cpp

scale:
	make

clean:
	rm -f scale
	rm -f *.sca

test: scale
	make
	echo "Testing Program"
	./scale -e test/testfile.txt 