#pragma once
#include <string>
char* bstoca(std::string bs, char* size, char* offset);
char* bstoca(std::string & bs, int* size, unsigned char* offset);
char* ultoca(unsigned long l);
char rotl(char n, unsigned char d);
char rotr(char n, unsigned char d);
void sftcabyn(char* ca, int casz, unsigned char n);