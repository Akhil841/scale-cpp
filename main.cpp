#include <iostream>
#include "encrypt.h"

int
main(int argc, char** argv)
{
    if (argc < 3) 
    {
        cout << "Not enough arguments" << endl;
        cout << "Format: " << endl;
        cout << "./scale <-e | -d> <filename/filedir>" << endl;
        cout << "Ending" << endl;
        return 1;
    }
    if (string(*(argv + 1)) == "-e")
    {
        string filename = string(*(argv + 2));
        return encrypt(filename);
    }
    if (string(*(argv + 1)) == "-d")
    {

    }
    else
    {
        cout << "Invalid option" << endl;
        cout << "Use the -e flag to encrypt a file";
        cout << " and the -d flag to decrypt one" << endl;
        cout << "Ending" << endl;
        return 1;
    }
    return 0;
}
