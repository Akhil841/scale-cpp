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
	cd test
	./scale testfile.txt >> output.txt
	diff expected.txt output.txt
	echo "Difference (If you see nothing then it works!)"
	echo "Cleaning"
	make clean