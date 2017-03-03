#ifndef FILEOBJECT_H
#define FILEOBJECT_H
#include <string>
using namespace std;

class FileObject
{

public:
	string name;
	string path;
	int isDir;
    int filesize;
	long long ltime;

};
#endif
