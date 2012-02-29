#include "ReadTXT.hpp"


ReadTXT::ReadTXT()
{
    filename="res/score/highscore.txt";
}

vector<string> ReadTXT::read()
{
    vector<string> tmp;
    datei.open("res/score/highscore.txt", ios::in);
    while (datei.getline (line, 256))
    {
        // mach was mit der zeile
        tmp.push_back(line);
        
    }
    return tmp;
}
/*
void ReadTXT::write(string s)
{
    datei.open(filename.c_str, ios::out);
    datei << s << endl;
    datei.close();
    
}*/


