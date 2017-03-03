#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include "Input_Instance.h"

using namespace std;

input_instance::input_instance(string input)
{
			send_again=true;
			file_name = input;
			fin.open(input.c_str(),ios::binary);

			 fin.seekg(0,ios::end);
			file_size = fin.tellg();
			cout << file_size;
		    fin.seekg(0,ios::beg);


			if(!fin.is_open())
			{	
				#ifdef DEBUG
				cout << "ERROR: FIle Not Opened" << endl;	
				#endif
			}
		   
}



string input_instance::send_file_name()
{
	return file_name;
}


char * input_instance::send_data()
{



	int diff = file_size- fin.tellg();
	 packet_size=0;
	
	if(diff<256)
    packet_size = diff;
	else
	packet_size = 256;
	
	 // Max buffer capacity is 256
	//cout << packet_size;
	  //cout << "The packet size is " << file_size  << " " << fin.tellg() << " " << packet_size << endl;
	fin.read(buffer,packet_size);
		if(fin.tellg()==file_size)
		send_again=false;
		
	copy.write(buffer,packet_size);
	
	return buffer;
}


