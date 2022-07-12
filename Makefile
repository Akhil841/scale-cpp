all: main.cpp encrypt.cpp treebuilder.cpp
	g++ -o scale main.cpp encrypt.cpp treebuilder.cpp

scale:
	make

clean:
	rm scale

test: scale
	make
	echo "Testing Program"
	cd test
	./scale testfile.txt >> output.txt
	diff expected.txt output.txt
	echo "Difference (If you see nothing then it works!)"
	echo "Cleaning"
	make clean