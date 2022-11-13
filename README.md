# scale-cpp
SCALE (Simple Compression Algorithm that's Lossless and sometimes Efficient) is a file format based on Huffman encryption. For details on what a `.sca` file entails, see [the documentation](./ccf.md).

This repository also contains a SCALE codec as per the specifications, written in C++.

Because SCALE uses a Huffman tree for compression, it carries the strengths and weaknesses of Huffman trees. What this means is that SCALE compresses text files well, because they only use the 99 printable ASCII characters. Binaries, on the other hand, use all 256 ASCII characters and that tends to result with every code being at least 8 bits long and some being 9 or even 10 bits long, which guarantees a compressed file **larger** than the original file.

Hence the name saying **sometimes** efficient. The more unique characters your file uses, the less efficiently it will compress. (This is just a rule of thumb, it doesn't always apply, since Huffman trees are also affected by the *frequency* of characters in a file.)
