#include "filehandle.h"

void create_dir(string path)
{
	fileinfo temp(path);

	string command = "\0";

	command  = "'" + path + "'";
	
	if(temp.exist)
	{
		system(("rm -r"+command).c_str());
	}
		command = "mkdir " + command;

		system(command.c_str());

        cout<<"folder created\n";

}
void remove_file_dir(string path)
{
	fileinfo temp(path);

	if(!temp.exist)
	{
		return;
	}

	string command = "\0";

	command  = "rm -r '" + path + "'";
	system(command.c_str());
	return;
}

bool exist_path(string path)
{
	fileinfo temp(path);

	if(!temp.exist)
	{
		return 0;
	}

	return 1;	
}
