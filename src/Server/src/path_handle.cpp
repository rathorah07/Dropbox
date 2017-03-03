#include "path_handle.h"
void create_path(string path)
{	

	fileinfo temp;
	
	string temp_path ;

	int required_length  = path.find_last_of('/',path.length());

	temp_path = path.erase(required_length);

	temp.setfile(temp_path);

	if(temp.exist)	
	{	
		#ifdef DEBUG
		cout<<"path already exist "<<endl;
		#endif

		return;
	}

	
	string create_dir = "mkdir --parents " ;

	create_dir += temp_path;

	system(create_dir.c_str());
}
