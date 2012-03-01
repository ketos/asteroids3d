#ifndef READTEXT_
#define READTEXT_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
class ReadTXT
{
public:
    /*
     * @brief constructs a reader and writer for .txt files
     */
	ReadTXT();
    /*
     * @brief reads a .txt file
     * @return vector<string> a vector, which contains the text of the file
     */
    vector<string> read();
    /*
     * @brief writes the given name and points in the highscore
     * @param string the name of the player
     * @param int points of the player
     */
    void write(string s,int punkte);

private:

    fstream datei;
    QString filename;
    char line[256];
    stringstream sstr;	   
};

#endif 