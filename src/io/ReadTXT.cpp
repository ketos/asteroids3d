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
        tmp.push_back(line);        
    }

    return tmp;
    datei.close();
}

void ReadTXT::write(string s, int punkte)
{
    vector<string> tmp;
    vector<pair<int, string> > vecpair;
    string highscore;
    string name;
    int pts;
    tmp = read();
    vector<string>::iterator iter;
    iter = tmp.begin();

    while(iter != tmp.end())
    {
        highscore = (*iter);
        sstr << highscore;
        sstr >> name;
        sstr >> pts;
        pair<int, string> temp(pts, name);
        vecpair.push_back(temp); 
        iter++;
        sstr.clear(); 
    }
    
    vecpair.push_back(make_pair(punkte,s));

    sort(vecpair.begin(), vecpair.end());
    vector<pair<int,string> >::reverse_iterator iters;
    iters = vecpair.rbegin();
    fstream datei1;
    datei1.open("res/score/highscore.txt", ios::out);
    int i = 0; 

    while(iters != vecpair.rend() && i < 10)
    {
        pair<int,string> pairs = (*iters);
        datei1 << pairs.second << " " << pairs.first << endl;
        iters++;
        i++;
    }
    datei1.close(); 
}


