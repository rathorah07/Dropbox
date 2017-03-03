#include <cstdlib>
#include "Result.h"
#include "FileObjects.h"
#include <vector>
#include "time_handle.h"


//isdir is 1 if the file is a directory
// function F to get the server time
// function G to get the client time

//WE are doing +1 in Server , here it's a 0-3 range
// 0 : delete the file in the client  -> 0
// 2 : delete the file in the server  -> 1
// 1 : upload the file on the server ->   2
// 3 : download the file from the server to the client -> 3

using namespace std;

vector<result> compare_client(std::vector<FileObject> input, string input_name){
	
	long int time_data = read_time(input_name);
	std::vector<result> output;
	std::vector<FileObject>::iterator iter;

	for (iter = input.begin(); iter != input.end(); iter++){
		
		result temp;

		if ((*iter).ltime > time_data){
			temp.code = 2;
		}  
		else{
			temp.code = 0;
		}
		temp.file_name = (*iter).name;
		temp.file_size = (*iter).file_size;
		temp.path = (*iter).path;
		temp.isDir = (*iter).isDir;
		temp.ltime = (*iter).ltime;
		output.push_back(temp);
		
	} 
	return output;
}

vector<result> compare_server(std::vector<FileObject> input, string input_name){
	
	long int time_data = read_time(input_name);
	std::vector<result> output;
	std::vector<FileObject>::iterator iter;

	for (iter = input.begin(); iter != input.end(); iter++){
		
		result temp;

		if ((*iter).ltime > time_data){
			temp.code = 3;
		}  
		else{
			temp.code = 1;
		}
		temp.file_name = (*iter).name;
		temp.file_size = (*iter).file_size;
		temp.path = (*iter).path;
		temp.isDir = (*iter).isDir;
		temp.ltime = (*iter).ltime;
		output.push_back(temp);
		
	} 
	return output;
}