#include <iostream>
#include <fstream>
#include "encrypt.h"
#include "treebuilder.h"

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
    string thetext;
    while (getline(readfile, curLine))
    {
        thetext += curLine;
        thetext += "\n";
        for (int i = 0; i < curLine.size(); i++)
            cauv(alphabet, frequency, curLine[i]);
        //every file should end with a newline anyway
        cauv(alphabet, frequency, '\n');
    }
    readfile.close();
    cout << "Size: " << alphabet.size() << endl;
    vector<string>* hc = sasc(codes(alphabet, frequency));
    cout << "List of characters and their codes" << endl;
    vector<char> alph;
    vector<string> code;
    for (int i = 0; i < hc->size(); i += 2)
    {
        alph.push_back(hc->at(i)[0]);
        code.push_back(hc->at(i+1));
        if (hc->at(i) == "\n")
            cout << "Newline: " << hc->at(i+1) << endl;
        else
        {
            cout << hc->at(i) << ": " << hc->at(i+1) << endl;
        }
    }
}