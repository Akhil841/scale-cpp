#include "util.h"
#include "treelib.h"
#include "encrypt.h"
#include "decrypt.h"

int main(int argc, char** argv)
{
    //argument checking
    if (argc != 4)
        error("Input must have 3 arguments");
    //input file stream
    IStreamWrapper in(*(argv + 2));
    //output file stream
    OStreamWrapper out(*(argv + 3));
    //compress/decompress
    std::string option = std::string(*(argv + 1));
    //check file integrity
    if (!in.good())
        error("Bad input file");
    //encrypt or decrypt based on input
    if (option == "-c")
        encrypt(in, out);
    else if (option == "-d")
        decrypt(in, out);
    else
        error("Bad option");
    return 0;
}