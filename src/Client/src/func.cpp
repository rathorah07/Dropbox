#include "func.h"
#include "fileinfo1.h"
#include "filesysmaker.h"


string cut_homepath(string path,string path_to_cut)

{

    int cut_length = path_to_cut.length();

    string out = path.erase(0,cut_length);

	return out;
}


void generate_database(string folder_path,string path_to_cut,string database_path){


	string command = folder_path;

	string home_folder_name = "\0";

	for(int i = folder_path.length()-1;i>=0;i--)
	{
		char c = folder_path[i];
		if(c == '/')
			break;
		else
		{
			home_folder_name = c + home_folder_name;
		}
	}

    string temp_database_path = database_path;
	
    temp_database_path += "/temp_database.txt";

	command = "ls -B -R '" + folder_path +"' > '" + temp_database_path + "'";

	system(command.c_str());
	
	fileinfo stat_object;

	string temp ="\0";

	string path_to_node = "\0";
	string path_to_files = "\0";

	ifstream fin(temp_database_path.c_str());

 int n=0;
	while(std::getline(fin,temp))
	{
		if(temp[temp.length()-1] == ':')
		{	

			path_to_node = temp.erase(temp.length()-1,1);
			if(n==0){

				stat_object.setfile(path_to_node);			// this is a folder path
                create_new_entry(database_path,home_folder_name,stat_object.isdir,cut_homepath(path_to_node,path_to_cut),stat_object.filesize,stat_object.last_access);
			}
		}

		else if(temp == "\0")
			{
					// nothing to done just changing directory now
			}

		else
		{	
			path_to_files = path_to_node;
			path_to_files = path_to_files +"/" +temp;
			stat_object.setfile(path_to_files);
            create_new_entry(database_path,temp,stat_object.isdir,cut_homepath(path_to_files,path_to_cut),stat_object.filesize,stat_object.last_access);
		}

		n++;
	}

	fin.close();


	command = "rm '" + temp_database_path +"'";

    system(command.c_str());
	return ;
}
