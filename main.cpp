#include <iostream>
#include <fstream>
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
cauv(vector<char> & alph, vector<int> & freq, char val)
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

vector<string>
sasc(vector<string> & strings)
{
    vector<string> out;
    for (int i = 0; i < strings.size(); i++)
    {
        out.push_back(strings[i].substr(0, 1));
        out.push_back(strings[i].substr(2, strings[i].length() - 2));
    }
}

int
main(int argc, char** argv) 
{
    string curLine;
    ifstream readfile(*(argv + 1));
    vector<char> alphabet;
    vector<int> frequency;
    while (getline(readfile, curLine))
    {
        char* cur = new char[curLine.length() + 1];
        std::strcpy(cur, curLine.c_str());
        while (*cur != '\0')
        {
            cauv(alphabet, frequency, *cur);
            cur++;
        }
        cauv(alphabet, frequency, '\n');
    }
    readfile.close();
    int output = 0;
    for (int i = 0; i < frequency.size(); i++)
        output += frequency[i];
    cout << "Total frequency: " << output << endl;
    vector<string> hc = codes(alphabet, frequency);
    cout << "List of characters and their codes" << endl;
    vector<string> hc2 = sasc(hc);
    for (int i = 0; i < hc.size(); i += 2)
    {
        if (hc2[i] == "\n")
            cout << "Newline: " << hc2[i+1] << endl;
        else
            cout << hc2[i] << ": " << hc2[i+1] << endl;
    }
    return 0;
}