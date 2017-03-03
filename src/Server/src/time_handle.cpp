#include "time_handle.h"

void write_time(string path,int flag)
{
	ofstream file;
	file.open(path.c_str());
    if(flag==0)
    {
        file << "0";
    }
    else
        file << time(0);

	file.close();
}


long int read_time(string path)
{
	
	long int output=0;

	ifstream file;
	file.open(path.c_str());
	
	string time = "\0";
	std::getline(file,time);
	
	for(int i=0;i<time.length();i++)
	{
		output = output*10 + time[i] - '0';
	}

	return output;
}
