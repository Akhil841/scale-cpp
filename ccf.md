# Contents of a `.sca` File
## Signature 1
The first 40 bits of a `.sca` file are always `SCALE`. A SCALE codec checks this to ensure that the input file is a valid `.sca` file.
## Key count
The next 8 bits contain the number of Huffman keys, minus one. This is becuase there are 256 ASCII characters (thus, up to 256 keys) and in 8 bits, we can store any value between 0 and 255. 
## LUT section
The next segment contains a lookup table containing each key, as well as other data necessary to tokenize and decode it. The Huffman key is padded because it is rarely exactly a multiple of 8 bits long. The value used to pad is `0`.<br><br>
Each row of the lookup table looks like this:
|`Character` | `Size of padded Huffman key` | `Number of padded bits`| `Huffman key, padded to modulo 8 bits`
|:---|:---|:---|:---|

## Signature 2
The next 40 bits of the file are always `CDATA`. This is short for "compressed data", and like the first signature, a SCALE codec checks this to ensure that the input file is a valid `.sca` file. The presence of two signatures coupled with a varying number of bits between them ensures that it is very unlikely for an invalid `.sca` file to make it past this stage.

## Data section

The data section contains all the compressed data, without delimiters to optimize compression. The file is padded with `0`s to contain modulo 8 bits.