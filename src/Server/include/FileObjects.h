#ifndef FileObjects_H
#define FileObjects_H

#include <string>
using namespace std;

class FileObject
{

public:
	string name;
	string path;
	int isDir;
	int file_size;
	long long ltime;

};

#endif