# scale-cpp
## Introduction
SCALE (Simple Compression Algorithm that's Lossless and sometimes Efficient) is a file format based on Huffman encryption. For details on what a compressed file entails, see [the documentation](./ccf.md).

This repository also contains a SCALE codec as per the specifications, written in C++.

Because SCALE uses a Huffman tree for compression, it carries the strengths and weaknesses of Huffman trees. What this means is that SCALE compresses text files well, because they only use the 99 printable ASCII characters. Binaries, on the other hand, use all 256 ASCII characters and that tends to result with every code being at least 8 bits long and some being 9 or even 10 bits long, which guarantees a compressed file **larger** than the original file.

Hence the name saying **sometimes** efficient. The more unique characters your file uses, the less efficiently it will compress. (This is just a rule of thumb, it doesn't always apply, since Huffman trees are also affected by the *frequency* of characters in a file.)

## Compiling SCALE
If you have at least `C++17`, you should be fine. If you have a lower version, you will need to edit `IStreamWrapper::size()` and `OStreamWrapper::size()` in `util.cpp` to use `std::ifstream::tellg()` or `std::ofstream::tellg()` rather than `std::filesystem::file_size()`.

### Dependencies
If your compiler has the `std` namespace, you should be fine. Otherwise, you need `std::filesystem`, `std::algorithm`, `std::iostream`, `std::string`, `std::fstream`, `std::queue`, `std::vector`, and `std::unordered_map`.

You will also need `cstdlib` to generate a 1 GB binary file for testing purposes via `gigatest.cpp` or the `make gigatest` command.

To compile SCALE, enter `make` in the repository's root directory.

## Running SCALE

The syntax for using SCALE is as follows:

`./scale <-c|-d> <input_file> <output_file>`

Using the `-c` flag compresses `input_file` and writes it into `output_file`, and the `-d` flag decompressses `input_file` and writes it to `output_file`.

## Theoretical and practical limits

Because SCALE stores data such as filesize as an unsigned 64-bit integer, it is theoretically capable of operating on up to files of up to 16 EiB in size. In practice, given that the program is run in a single thread and the hardware limitations of today, it should probably not be used for files larger than 50 MiB. (I tried compressing a 1 GiB file on my laptop with this program, and it took nearly an hour.). This program was made merely for practice with C++ and implementing Huffman coding. If you actually want efficient, fast compression, use [7zip](https://www.7-zip.org/)!
