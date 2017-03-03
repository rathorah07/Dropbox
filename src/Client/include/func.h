#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

void generate_database(string path,string path_to_cut,string database_path);
string cut_homepath(string path,string path_to_cut);

#endif
