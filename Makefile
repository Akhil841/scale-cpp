all: main.cpp treebuilder.cpp heapbuilder.cpp
	g++ -o scale main.cpp treebuilder.cpp heapbuilder.cpp

clean:
	rm scale

test: scale
	echo "Testing Program"
	./scale test/testfile.txt