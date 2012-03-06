/**
 * @file ReadTXT.hpp
 *
 * @author gruppe3
 */

#ifndef READTEXT_
#define READTEXT_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <vector>

using namespace std;
class ReadTXT
{
public:
    /**
     * @brief constructs a reader and writer for .txt files
     */
    ReadTXT();

    /**
     * @brief reads a .txt file
     * @return vector<string> a vector, which contains the text of the file
     */
    vector<string> read();

    /**
     * @brief writes the given name and points in the highscore
     * @param s the name of the player
     * @param punkte points of the player
     */
    void write(string s,int punkte);

private:

    fstream datei;
    QString filename;
    char line[256];
    stringstream sstr;
};

#endif 
