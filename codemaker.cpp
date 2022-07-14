#include "codemaker.h"

//Bit String to Character Array
char*
bstoca(std::string bs, char* size, char* offset)
{
    //calculate offset size and total string size
    int ss = bs.length();
    //get offset (this is the number of '0's that must be added to the code to
    //make it fit into a group of bytes)
    int osize = (8 - (ss % 8)) % 8;
    //get the total size of the bitstring
    int tsize = ss + osize;
    //write these values to their pointers
    *offset = osize;
    *size = tsize;
    //create output char array
    char* ca = new char[(tsize/8)];
    //offset string for writing purposes
    for (int i = 0; i < osize; i++)
        bs += "0";
    //write all 1s to the char array
    for (int i = 0; i < bs.length(); i++)
    {
        //get which index
        int wc = i/8;
        //and which bit in the selected character to edit
        int charind = i % 8;
        //write a 1 or a 0 to the current character
        if (bs[i] == '1')
            *(ca + wc) |= 1 << (7 - charind);
        else
            *(ca + wc) &= ~(1 << (7 - charind));
    }
    //return the character buffer
    return ca;
}

//for converting large strings to bitstrings
char*
bstoca(std::string & bs, int* size, unsigned char* offset)
{
    //calculate offset size and total string size
    int ss = bs.length();
    //get offset (this is the number of '0's that must be added to the code to
    //make it fit into a group of bytes)
    int osize = (8 - (ss % 8)) % 8;
    //get the total size of the bitstring
    int tsize = ss + osize;
    //write these values to their pointers
    *offset = osize;
    *size = tsize;
    //create output char array
    char* ca = new char[(tsize/8)];
    //offset string for writing purposes
    for (int i = 0; i < osize; i++)
        bs += "0";
    //write all 1s to the char array
    for (int i = 0; i < bs.length(); i++)
    {
        //get which index
        int wc = i/8;
        //and which bit in the selected character to edit
        int charind = i % 8;
        //write a 1 or a 0 to the current character
        if (bs[i] == '1')
            *(ca + wc) |= 1 << (7 - charind);
        else
            *(ca + wc) &= ~(1 << (7 - charind));
    }
    //return the character buffer
    return ca;
}

//unsigned long to character array
char* ultoca(unsigned long l)
{
    char* out = new char[8];
    for (int i = 0; i < 64; i++)
    {
        char wc = i/8;
        char wb = i % 8;
        if (((l >> (63 - i)) & 1))
            *(out + wc) |= (1 << (7 - wb));
        else
            *(out + wc) &= ~(1 << (7 - wb));
    }
    return out;
}

//rotate left
char rotl(char n, unsigned char d)
{
    d %= 8;
    return (n << d)|(n >> (7 - d));
}

//rotate right
char rotr(char n, unsigned char d)
{
    d %= 8;
    return (n >> d)|(n << (7 - d));
}

//Shift Character Array by N
void
sftcabyn(char* ca, int casz, unsigned char n)
{
    if (n > 7) throw 1;
    for (int i = 0; i < casz - 1; i++)
    {
        //shift current character by n
        *(ca + i) <<= n;
        //create n-long bitmask from left
        char bitmask = 0;
        for (int i = 0; i < n; i++)
            bitmask |= (1 << (7 - i));
        //get next n bits from the next character
        char next = *(ca + i + 1) & bitmask;
        //rotate right by (7-n) so it's 0s followed by 1s
        next = rotr(next, 7 - n);
        //write parts of next character with bitwise or
        *(ca + i) |= next;
    }
    //shift last character by n
    *(ca + (casz - 1)) <<= n;
}