#include <iostream>
#include <cstdlib>

using namespace std;

void generate_certificate(string input_data){


	int i = system("openssl req -x509 -nodes -days 365 -newkey rsa:1024 -keyout cert/mycert.pem -out cert/mycert.pem < cert/Certificate.txt");
	#ifdef DEBUG
	if(i==0)
		cout << "Certificate created successfully!" << endl;
	else
		cout << "Error in creating certificate!" << endl;
	#endif
}
