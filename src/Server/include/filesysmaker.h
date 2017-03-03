//#ifndef FILESYSMAKER_H
//#define FILESYSMAKER_H

#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int initialize_files_database(string path);
int create_new_entry(string path,string oFilename,int oIsDirectory,string oPath,int oFilesize, int oLtime);
int drop_table(string path);

//#endif
