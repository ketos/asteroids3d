#include <iostream>
#include <fstream>
#include <stdexcept>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <vector>

using namespace std;
class ReadTXT
{
public:
	
	ReadTXT();
	vector<string> read();
	//void write(string s);

private:
	
	   ifstream datei;
	   QString filename;
	   char line[256];
};