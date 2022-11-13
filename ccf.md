# Contents of a `.sca` File
## Preorder traversal of the Huffman tree
The first 10(2n-1) bits, where *n* is the number of unique characters in the uncompressed file, of a `.sca` file contain a preorder traversal of the Huffman tree used to encode the file. 

## 11 signature
The next 2 bits are always `11`, which can be used as a method to verify file integrity.

## Data pad
The next 8 - n bits of data contain a padding to make the data structured as bytes again.

## Uncompressed file size
The next 64 bits of data contain the number of bytes that the uncompressed data takes up.

## Data section
The data section contains all the compressed data, Huffman encoded. The file is padded with `0`s to contain modulo 8 bits.