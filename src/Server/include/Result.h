#ifndef RESULT_H
#define RESULT_H

#include <string>

using namespace std;


struct result{
	int code;
	string file_name;
	string path;
	int isDir;
	int file_size;
	long long ltime;
	    bool operator<(result other) const
    {
        return code < other.code ;
    }
};

#endif
