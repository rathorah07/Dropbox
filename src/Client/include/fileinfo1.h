#ifndef FILEINFO_H
#define FILEINFO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

using namespace std;

class fileinfo{
	
	private:
		
		struct stat info_box;
	
	public:
		char* filepath;
		bool isdir;
		bool exist;
		off_t filesize;      // sys/types.h
		time_t last_modify;   // time.h
		time_t last_access;
		time_t last_statuschange;
		
		fileinfo();

		fileinfo(string path);
 
		int setfile(string path);
		
		int refresh_stat(void);
};

#endif
