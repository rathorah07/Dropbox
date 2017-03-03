#ifndef COMPARE_H
#define COMPARE_H

#include <vector>
#include "FileObjects.h"
#include "Result.h"
#include <string>

vector<result> compare_server(std::vector<FileObject> input, string input_name);
vector<result> compare_client(std::vector<FileObject> input, string input_name);

#endif
