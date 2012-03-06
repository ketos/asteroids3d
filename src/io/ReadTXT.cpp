#include "ReadTXT.hpp"

ReadTXT::ReadTXT()
{
	//file directory
    filename="res/score/highscore.txt";
}

vector<string> ReadTXT::read()
{
	//vector for the lines, that shall be read
    vector<string> tmp;
    //open file
    datei.open("res/score/highscore.txt", ios::in);
    //write every line in the vector
    while (datei.getline (line, 256))
    {
        tmp.push_back(line);        
    }

    //return vector
    return tmp;
    
    //close file
    datei.close();
}

void ReadTXT::write(string s, int punkte)
{
    //vector for the actual highscore
    vector<string> tmp;
    //vector containing the names and points of the highscore
    vector<pair<int, string> > vecpair;
    
    string highscore;
    
    //name and points of the actual player
    string name;
    int pts;
    
    //read the actual highscore
    tmp = read();
    
    //iterator for 
    vector<string>::iterator iter;
    iter = tmp.begin();

    //get the 'old' highscore from the highscore-file
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
    
    //pushs the actual name and points of the player in the vector
    vecpair.push_back(make_pair(punkte,s));
    //sorts the whole vector by points
    sort(vecpair.begin(), vecpair.end());
    //reverse iterator to get the correct output
    vector<pair<int,string> >::reverse_iterator iters;
    iters = vecpair.rbegin();

    fstream datei1;
    //open file in that should be written
    datei1.open("res/score/highscore.txt", ios::out);
    
	//write only the first ten entries in the highscore-file   
    int i = 0;
    while(iters != vecpair.rend() && i < 10)
    {
        pair<int,string> pairs = (*iters);
        datei1 << pairs.second << " " << pairs.first << endl;
        iters++;
        i++;
    }
    //close file
    datei1.close();
}