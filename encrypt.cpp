#include <iostream>
#include <fstream>
#include <cstdio>
#include "encrypt.h"
#include "treebuilder.h"
#include <memory>

/*
CAUV (Check And Update Vectors) updates the
alphabet and frequency vectors passed to it with
the provided character.
If the character is in the alphabet, its corresponding
frequency is updated.
Otherwise, a new entry is made in both vectors. The
alphabet entry contains val, and the frequency entry contains 1.
*/
void
cauv(vector<char>& alph, vector<int>& freq, char val)
{
    for (int i = 0; i < alph.size(); i++)
    {
        if (alph[i] == val)
        {
            freq[i]++;
            return;
        }
    }
    alph.push_back(val);
    freq.push_back(1);
}

/*
SASC (Separate At Second Character) separates each string in a string vector
into two pieces, at the second character. Each piece is returned, with the 
first character following the rest of the string, for an arbitrary string.
*/
vector<string>*
sasc(vector<string>* strings)
{
    vector<string>* out = new vector<string>;
    for (int i = 0; i < strings->size(); i++)
    {
        out->push_back(strings->at(i).substr(0, 1));
        out->push_back(strings->at(i).substr(2, strings->at(i).length() - 2));
    }
    return out;
}

int 
encrypt(string pn)
{
    string curLine;
    ifstream readfile(pn);
    if (!readfile)
    {
        cout << "Invalid file or directory\nending" << endl;
        return 1;
    }
    vector<char> alphabet;
    vector<int> frequency;
    //1GB buffer
    const streamsize BUFSZ = 1024 * 1024 * 1024;
    char* buf = new char[BUFSZ];
    int bufcnt = 0;
    int gc;
    do
    {
        readfile.read(buf, BUFSZ);
        gc = readfile.gcount();
        if (gc <= 0)
            break;
        for (int i = 0; i < gc; i++)
            cauv(alphabet, frequency, *(buf + i));
        bufcnt++;
    }
    while (readfile);
    delete[] buf;
    readfile.close();
    vector<string>* hc = sasc(codes(alphabet, frequency));
    vector<char> alph;
    vector<string> code;
    for (int i = 0; i < hc->size(); i += 2)
    {
        alph.push_back(hc->at(i)[0]);
        code.push_back(hc->at(i+1));
    }
    return 0;
}