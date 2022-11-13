all: main.cpp encrypt.cpp decrypt.cpp treelib.cpp util.cpp
	g++ -o scale -std=c++20 main.cpp encrypt.cpp decrypt.cpp treelib.cpp util.cpp

scale:
	make

clear:
	make clean

clean:
	rm -f scale
	rm -rf out/*
	rm test/gigabin.bin

gb: gigatest.cpp
	g++ -o giga -std=C++20 gigatest.cpp

gigatest: scale
	make
	./giga
	echo "Testing binary gigabyte"
	./scale -c test/gigatest.bin out/gigatest.sca
	./scale -d out/gigatest.sca out/gigatest.dcs
	echo "Binary gigabyte diff below:"
	diff test/gigatest.bin out/gigatest.dcs
	make clean

test: scale
	make
	echo "Testing Hello"
	./scale -c test/hello.txt out/hello.sca
	./scale -d out/hello.sca out/hello.dcs
	echo "Hello diff below:"
	diff test/hello.txt out/hello.dcs
	echo "Testing Opcodes"
	./scale -c test/opcodes.json out/opcodes.sca
	./scale -d out/opcodes.sca out/opcodes.dcs
	echo "Opcodes diff below:"
	diff test/opcodes.json out/opcodes.dcs
	echo "Testing 2 MB"
	./scale -c test/2mboftext.txt out/2mb.sca
	./scale -d out/2mb.sca out/2mb.dcs
	echo "2 MB diff below:"
	diff test/2mboftext.txt out/2mb.dcs
	echo "Testing testfile"
	./scale -c test/testfile.txt out/testfile.sca
	./scale -d out/testfile.sca out/testfile.dcs
	echo "Testfile diff below:"
	diff test/testfile.txt out/testfile.dcs
	echo "Testing binary"
	./scale -c test/binary.bin out/binary.sca
	./scale -d out/binary.sca out/binary.dcs
	echo "Binary diff below:"
	diff test/binary.bin out/binary.dcs
	make clean