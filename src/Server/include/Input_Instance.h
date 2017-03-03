#include <string>
#include <fstream>

using namespace std;

class input_instance
{
	private :
		string file_name;
		ifstream fin;
		ofstream fout;
		fstream file;
		int file_size;

		ofstream copy;
		
		char buffer[256]; 


	public :
		int packet_size;
		bool send_again; // If more data can be sent from the file.

		input_instance(string input);
		
		string send_file_name();
		char * send_data();
		~input_instance()
		{
			fin.close();
		}

};
