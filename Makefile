all: main.cpp treebuilder.cpp heapbuilder.cpp
	g++ -o scale main.cpp treebuilder.cpp heapbuilder.cpp

scale:
	make

clean:
	rm scale

test: scale
	echo "Testing Program"
	./scale test/testfile.txt
	echo "Cleaning"
	make clean