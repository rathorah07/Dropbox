//SSL-Server.cpp
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include <algorithm>
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "string_int.h"
#include "fileinfo1.h"
#include "login_table.h"
#include "func.h"
#include "syncbox.h"
#include "Result.h"
#include "Input_Instance.h"
#include "filesysmaker.h"
#include "SharingDatabase.h"
#include "time_handle.h"
#include "path_handle.h"
#include <queue>
#include "Gen_cert.h"
#define FAIL    -1


 using namespace std;

 extern  vector<result> clientcode;
 extern  vector<result> servercode;

string computer_name;
string username;

int OpenListener(int port)
{   int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        perror("can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 )
    {
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}

SSL_CTX* InitServerCTX(void)
{
  const SSL_METHOD *method;
    SSL_CTX *ctx;
    SSL_library_init();
    SSL_load_error_strings();   /* load all error messages */
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    method = SSLv23_server_method();  /* create new server-method instance */
    ctx = SSL_CTX_new(method);   /* create new context from method */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
    	#ifdef DEBUG
        fprintf(stderr, "Private key does not match the public certificate\n");
        #endif
        abort();
    }
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL )
    {
    	#ifdef DEBUG
        printf("Server certificates:\n");
        #endif

        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);

        #ifdef DEBUG
        printf("Subject: %s\n", line);
        #endif

        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);

        #ifdef DEBUG
        printf("Issuer: %s\n", line);
        #endif

        free(line);
        X509_free(cert);
    }
    else
    {
    	#ifdef DEBUG
        printf("No certificates.\n");
        #endif
    }
}


string receive_compname(SSL * ssl)
{

    char buffer[256];
    int bytes=0;

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string compname_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(compname_length));
    string compname = word_to_string(buffer,convert_to_int(compname_length));
    return compname;

}

string give_username(SSL *ssl)
{

	#ifdef DEBUG
    cout << "Inside give_username" << endl;
    #endif
    char buffer[256];
    int bytes;

    bytes = SSL_read(ssl, buffer, 18);
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));
    return username;

    //Read Username
}

void send_myname(SSL *ssl)
{
    #ifdef DEBUG
    cout << "Inside send_myname" << endl;
    #endif

    string username = getenv("HOME");
    username += "/Desktop/VDesktop";
    string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format



    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

    //Server Name Sent
}


void receive_file(SSL* ssl)
{

    string file_name,file_path;

    #ifdef DEBUG
    cout << "Inside Receive File" << endl;
    #endif

    ofstream fout;
    char buffer[256];

    int bytes=0;

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }

    string temp_len = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(temp_len));

    file_path = buffer[0];
    for(int i=1;i<bytes;i++)
    file_path += buffer[i];

    file_name = file_path;
    /*file_name = "'";
    file_name += file_path + "'";
    */


    bytes = SSL_read(ssl,buffer,18);

    string sfile_size = word_to_string(buffer,18);
    long long file_size= convert_to_int(sfile_size);

    long long bytes_read=0;

        create_path(file_name);
        fout.open(file_name.c_str(),ios::binary|ios::out);

        if(fout.is_open())
        {
        	#ifdef DEBUG
            cout << "Open " << endl;
            #endif
        }
        else
        {
        	#ifdef DEBUG
            cout << "Closed" << endl;
            #endif
        }

    while(bytes_read < file_size)
    {
        int arg3;
        if( (file_size - bytes_read)<256)
          arg3 = file_size - bytes_read;
        else
            arg3 = 256;
        bytes = SSL_read(ssl, buffer, arg3);
        //cout << bytes << endl;
        bytes_read += bytes;
        fout.write(buffer,bytes);

    }

    cout << bytes_read << " " << file_size <<  endl;
    fout.close();

    string command = " touch -c -a -m -t 200502212234.44 ";
    command += "'" + file_name + "'";
    system(command.c_str());


}


 void receive_username(SSL* ssl)
 {

 	#ifdef DEBUG
    cout << "Inside receive_username" << endl;
    #endif

    char buffer[256];
    int bytes;

    bytes = SSL_read(ssl, buffer, 18);
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));

    int count = check_username_collision(username);

    //char ch = count - '0';
    string result;
    if(count==0)
    {
        result = "0";
    }
    else
        result="1";

    #ifdef DEBUG
    cout << "Receive_username returning " << result << endl;
    #endif

    SSL_write(ssl, result.c_str(),1 );

 }

  void receive_credentials(SSL* ssl)
 {

 	#ifdef DEBUG
    cout << "Inside receive_credentials" << endl;
    #endif

    char buffer[256];
    int bytes;

    bytes = SSL_read(ssl, buffer, 18);
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));

    bytes = SSL_read(ssl, buffer, 18);
    string password_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(password_length));
    string password = word_to_string(buffer,convert_to_int(password_length));

    string temp_folder_path = "\0";

    int count = register_new_user(username,password);

    #ifdef DEBUG
    cout << "New User" << count << endl;
    #endif

    //char ch = count - '0';
    string result;
    if(count==0)
    {
        result = "0";
        string folder_path = getenv("HOME");
        folder_path += "/Desktop/VDesktop/" + username;
        temp_folder_path = folder_path + "_temp";

        folder_path = "mkdir '" + folder_path + "'";
        system(folder_path.c_str());
        folder_path = "mkdir '" + temp_folder_path + "'";
        system(folder_path.c_str());

        temp_folder_path = temp_folder_path + "/server_time.txt";

        //cout << temp_folder_path <<"  this is the path  " << temp_folder_path.length()<<endl;;

        write_time(temp_folder_path,0);

    }
    else
        result="1";

    #ifdef DEBUG
    cout << "receive_credentials returning " << result << endl;
    #endif

    SSL_write(ssl, result.c_str(),1 );

 }

  void receive_idpass(SSL* ssl)
 {
 	#ifdef DEBUG
    cout << "Inside receive_idpass" << endl;
    #endif

    char buffer[256];
    int bytes;

    bytes = SSL_read(ssl, buffer, 18);
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));

    bytes = SSL_read(ssl, buffer, 18);
    string password_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(password_length));
    string password = word_to_string(buffer,convert_to_int(password_length));



    int count = check_credentials(username, password);

    #ifdef DEBUG
    cout << "Valid Pass " << count << endl;
    #endif

    //char ch = count - '0';
    string result;
    if(count==0)
    {
        result = "0";
    }
    else
        result="1";

    #ifdef DEBUG
    cout << "receive_idpass returning " << result << endl;
    #endif

    SSL_write(ssl, result.c_str(),1 );

    if(result=="1")
    {
    	    ::username=username;
    	    //give_username(username);
    	   send_myname(ssl);
    	  computer_name=receive_compname(ssl);

    }
 }


void send_file(SSL* ssl, string file_path,string sharername="\0")
{
	#ifdef DEBUG
    cout << "Send_file_called with path   "<<file_path << endl;
    #endif

    string file_name;
    string temp_name= file_path ;

    input_instance obj(file_path.c_str());
    fileinfo file_obj(file_path);

    temp_name = getenv("HOME");
    temp_name += "/Desktop/VDesktop";


    if(sharername!="\0")
    {	temp_name += "/";
		temp_name += sharername;
	}

    temp_name = cut_homepath(file_path,temp_name);

 	#ifdef DEBUG
    cout<< temp_name << "   this is the temp name"<<endl;
    cout<<computer_name << "    this is the client compuer name"<<endl;
    #endif

     if(sharername=="\0")
     file_name = computer_name + temp_name;
    	else
       {
       		file_name =computer_name + "/" + username;
       		file_name += temp_name;
       }


    long long file_size= file_obj.filesize;
    char *data;

    string temp_len  = convert_to_string(file_name.length()); // Getting length in Server buffer format
    string sfile_len = convert_to_string(file_size);


    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, file_name.c_str(), file_name.length());


    SSL_write(ssl, sfile_len.c_str(), 18);
    // cout << "Filename sent "  << (char *)file_name.c_str() << endl;

    while(obj.send_again==true)
    {

        //cout << "Inside Send File loop" << endl;
        data=obj.send_data();

        SSL_write(ssl, data, obj.packet_size);

    }

    #ifdef DEBUG
    cout << "File Sent";
    #endif

    string command = " touch -c -a -m -t 200502212234.44 ";
    command += "'" + file_path+ "'";      // rahul filename is filepath here
    system(command.c_str());
}


void handledownload(SSL *ssl)
{
    string file_name,file_path;

    #ifdef DEBUG
    cout << "Inside Handle Downlod" << endl;
    #endif

    ofstream fout;
    char buffer[256];

    int bytes=0;

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }

    string temp_len = word_to_string(buffer,18);

    bytes=0;
    bytes = SSL_read(ssl, buffer, convert_to_int(temp_len));

    file_path = buffer[0];
    for(int i=1;i<bytes;i++)
    file_path += buffer[i];

    file_name = file_path; // full file path.

    bytes=0;
    bytes = SSL_read(ssl, buffer, convert_to_int(temp_len));
    string sharername_length = word_to_string(buffer,18);

	bytes=0;
    bytes = SSL_read(ssl, buffer, convert_to_int(temp_len));
    string sharername = word_to_string(buffer, convert_to_int(sharername_length));



    send_file(ssl,file_name,sharername);

}

void handleupload(SSL *ssl)
{

	#ifdef DEBUG
    cout << "Inside Handle Upload" << endl;
  	#endif

    receive_file(ssl);

}



void handle_code1(SSL* ssl,string path)
{
    int path_length = path.length();
    string spath_length  = convert_to_string(path_length); // Getting length in Server buffer format
    SSL_write(ssl, spath_length.c_str(), 18); //Sending Path Length

    SSL_write(ssl,path.c_str(),path.length()); // Send Path


}

void handle_code2(SSL *ssl,string path)
{
    string temp_path = getenv("HOME");

    temp_path = " rm '" + temp_path + "/Desktop/VDesktop" + path + "'";

    system(temp_path.c_str());
}



void handle_code3(SSL* ssl,string path)
{
    int path_length = path.length();
    string spath_length  = convert_to_string(path_length); // Getting length in Server buffer format
    SSL_write(ssl, spath_length.c_str(), 18); //Sending Path Length

    SSL_write(ssl,path.c_str(),path.length()); // Send Path

    receive_file(ssl);

}

void handle_code4(SSL* ssl,string path)
{

  string file_path = getenv("HOME");
  file_path += "/Desktop/VDesktop"+path;

    send_file(ssl,file_path);

}




void handle_codes(SSL* ssl)
{



    queue<result>  clientq,serverq;
    result obj1,obj2;
    vector<result> total_codes;

    for(int i=0;i<clientcode.size();i++)
    {
        if(clientcode[i].isDir==0)
        total_codes.push_back(clientcode[i]);
        else
        clientq.push(clientcode[i]);
    }

    for(int i=0;i<servercode.size();i++)
    {
        if(servercode[i].isDir==0)
        total_codes.push_back(servercode[i]);
        else
        serverq.push(servercode[i]);

    }
    sort(total_codes.begin(),total_codes.end());



    int i;
    int num_codes = total_codes.size();
    string snum_code  = convert_to_string(num_codes); // Getting length in Server buffer format
    SSL_write(ssl, snum_code.c_str(), 18);





    for(i=0;i<total_codes.size();i++)
    {
        int code = total_codes[i].code+1;
        string code_number  = convert_to_string(code); // Getting length in Server buffer format
        SSL_write(ssl, code_number.c_str(), 18);
        string path = total_codes[i].path;



        switch(code)
        {
            case 1: handle_code1(ssl,path);
            break;
            case 2: handle_code2(ssl,path);
            break;
            case 3: handle_code3(ssl,path);
            break;
            case 4: handle_code4(ssl,path);
            break;
        }
        //SSL_write(ssl, username.c_str(), username.length());


    }

    /*num_codes = clientq.size() + serverq.size();
    snum_code  = convert_to_string(num_codes); // Getting length in Server buffer format
    SSL_write(ssl, snum_code.c_str(), 18);

    while(!clientq.empty() || !serverq.empty())
    {
        if(!clientq.empty() && !serverq.empty())
        {
            obj1 = clientq.front();
            obj2 = serverq.front();
            if(obj1.path == obj2.path)
            {
                 string code_number  = convert_to_string(5); // Getting length in Server buffer format
                SSL_write(ssl, code_number.c_str(), 18);

                clientq.pop();
                serverq.pop();
            }
            else if(obj1.path < obj2.path)
            {
                   int code = obj1.code+1;
                   string code_number  = convert_to_string(code); // Getting length in Server buffer format
                    SSL_write(ssl, code_number.c_str(), 18);
                    string path = obj1.path;



                switch(code)
                {
                    case 1: handle_code1(ssl,path);
                    break;
                    case 2: handle_code2(ssl,path);
                    break;
                   case 3: handle_code3(ssl,path);
                   break;
                   case 4: handle_code4(ssl,path);
                   break;
                 }


                clientq.pop();
            }
            else
            {

                   int code = obj2.code+1;
                   string code_number  = convert_to_string(code); // Getting length in Server buffer format
                    SSL_write(ssl, code_number.c_str(), 18);
                    string path = obj2.path;



                switch(code)
                {
                    case 1: handle_code1(ssl,path);
                    break;
                    case 2: handle_code2(ssl,path);
                    break;
                   case 3: handle_code3(ssl,path);
                   break;
                   case 4: handle_code4(ssl,path);
                   break;
                 }

                serverq.pop();
            }
        }
        else if(!clientq.empty())
        {
            obj1 = clientq.front();
            int code = obj1.code+1;
                   string code_number  = convert_to_string(code); // Getting length in Server buffer format
                    SSL_write(ssl, code_number.c_str(), 18);
                    string path = obj1.path;



                switch(code)
                {
                    case 1: handle_code1(ssl,path);
                    break;
                    case 2: handle_code2(ssl,path);
                    break;
                   case 3: handle_code3(ssl,path);
                   break;
                   case 4: handle_code4(ssl,path);
                   break;
                 }


                clientq.pop();
        }
        else if(!serverq.empty())
        {
                    obj2 = serverq.front();
                   int code = obj2.code+1;
                   string code_number  = convert_to_string(code); // Getting length in Server buffer format
                    SSL_write(ssl, code_number.c_str(), 18);
                    string path = obj2.path;



                switch(code)
                {
                    case 1: handle_code1(ssl,path);
                    break;
                    case 2: handle_code2(ssl,path);
                    break;
                   case 3: handle_code3(ssl,path);
                   break;
                   case 4: handle_code4(ssl,path);
                   break;
                 }

                serverq.pop();
            }

        }
       */

}



 void server_sync(SSL* ssl)
 {
 	#ifdef DEBUG
    cout << "Inside server_sync" << endl;
 	#endif

    string temp_folder_path = getenv("HOME");
    string path_to_cut = getenv("HOME");
    path_to_cut += "/Desktop/VDesktop";
    temp_folder_path +="/Desktop/VDesktop/";

    temp_folder_path +=username;


    string folder_path = temp_folder_path;
    temp_folder_path +="_temp";

     cout << folder_path << endl;
     cout << path_to_cut << endl;
     cout << temp_folder_path << endl;

     #ifdef DEBUG
     cout << "DROP TABLE CALLED " << endl;
   	 #endif

     drop_table(temp_folder_path);

     #ifdef DEBUG
     cout << "INITIALIZE CALLED" << endl;
     #endif

     initialize_files_database(temp_folder_path);
     generate_database(folder_path,path_to_cut,temp_folder_path);

    receive_file(ssl);//DB FILE
    receive_file(ssl);//TIME FILE

    #ifdef DEBUG
    cout << "FILES RECEIVED" << endl;
    #endif

    string S1= temp_folder_path+"/clientdb.db";
    string S2= temp_folder_path+"/serverdb.db";
    string S3 = temp_folder_path + "/server_time.txt";
    string S4 = temp_folder_path + "/client_time.txt";
    blackbox(S2,S1,S3,S4,username);


    handle_codes(ssl);
    write_time(S3,1);

    #ifdef DEBUG
    cout << "RETURNED FROM HANDLE_SYNC";
    #endif

 }



void handle_sharing(SSL* ssl)
{
	handleupload(ssl);
    char buffer[256];
    int bytes=0;

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string filename_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(filename_length));
    string filename = word_to_string(buffer,convert_to_int(filename_length));

    bytes=0;
    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string filepath_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(filepath_length));
    string filepath = word_to_string(buffer,convert_to_int(filepath_length));

    bytes=0;
    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string  ownername_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(ownername_length));
    string ownername = word_to_string(buffer,convert_to_int(ownername_length));

    bytes=0;
    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string  sharedwith_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(sharedwith_length));
    string sharedwith = word_to_string(buffer,convert_to_int(sharedwith_length));

    initialize_share_database(sharedwith);
    add_new_entry(filepath,filename,ownername,sharedwith);

}

void sharedwithme(SSL* ssl)
{
  	char buffer[256];
    int bytes=0;

    #ifdef DEBUG
    cout<< "Inside Share with Me";
    #endif

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));

    initialize_share_database(username);

    string path = getenv("HOME");
    path += "/Desktop/VDesktop/";
    path +=  username;
    path += "_temp/sharedb.db";

    send_file(ssl,path);


}

void handle(SSL* ssl,int num)
{
    #ifdef DEBUG
    cout << "Inside handle" << endl;
    #endif

    switch(num)
    {
        case 1 :  receive_username(ssl);
        break;
        case 2 :  receive_credentials(ssl);
        break;
        case 3 :  receive_file(ssl);
        break;
        case 4 : receive_idpass(ssl);
        break;
        case 5 : server_sync(ssl);
        break;
        case 6 : handle_sharing(ssl);
        break;
        case 7 : sharedwithme(ssl);
        break;
        case 8 : handledownload(ssl);
        break;
        case 9: handleupload(ssl);
        break;
        //break;
    }

}

void Servlet(SSL* ssl) /* Serve the connection -- threadable */
{   char buf[1024];
    char reply[1024];
    int sd, bytes=0;
    const char* HTMLecho="<html><body><pre>%s</pre></body></html>\n\n";

    if ( SSL_accept(ssl) == FAIL )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else
    {
        ShowCerts(ssl);        /* get any certificates */

    	#ifdef DEBUG
        cout << "Inside_Servlet" << endl;
        #endif

        while(1)
        {
            while(bytes==0)
            {
                cout << "in" << endl;
                usleep(100000);
                bytes = SSL_read(ssl, buf, 18);
                cout << "out" << endl;
            }

          cout << bytes << endl;

        #ifdef DEBUG
        cout << "Outside_Bytes_Loop" << endl;
        #endif

        bytes=0;
        string temp_string = word_to_string(buf,18);
        int handler_num = convert_to_int(temp_string);
        handle(ssl,handler_num);

        }
        #ifdef DEBUG
        cout << "OutSide_Continuous_EventLoop" << endl;
        #endif

         /*bytes = SSL_read(ssl, buf, 18);

         cout << bytes << endl;

         cout << "Outside_Bytes_Loop" << endl;

         bytes=0;
         temp_string = word_to_string(buf,18);
         handler_num = convert_to_int(temp_string);
          handle(ssl,handler_num);
         */

         //receive_file(ssl);
        // receive_file(ssl);
        //bytes = SSL_read(ssl, buf, sizeof(buf)); /* get request */
        if ( bytes > 0 )
        {
            buf[bytes] = 0;

            #ifdef DEBUG
            printf("Client msg: \"%s\"\n", buf);
           	#endif

            sprintf(reply, HTMLecho, buf);   /* construct reply */
            SSL_write(ssl, reply, strlen(reply)); /* send reply */
        }
        else
            ERR_print_errors_fp(stderr);
    }
    sd = SSL_get_fd(ssl);       /* get socket connection */
    SSL_free(ssl);         /* release SSL state */
    close(sd);          /* close connection */
}

int main(int count, char *strings[])
{
  SSL_CTX *ctx;
  int server;
  char *portnum;

 	generate_certificate("cert/Certificate.txt");
 	string init = getenv("HOME");
 	init += "/Desktop/VDesktop";

 	fileinfo obj(init);

 	if(obj.exist==false)
 	{
 		string command = "mkdir '";
 		command += init + "'";
 		system(command.c_str());
 	}
    /*if(!isRoot())
    {
        printf("This program must be run as root/sudo user!!");
        exit(0);
    }*/
    if ( count != 2 )
    {
        printf("Usage: %s <portnum>\n", strings[0]);
        exit(0);
    }


    portnum = strings[1];
    ctx = InitServerCTX();        /* initialize SSL */
    LoadCertificates(ctx, "cert/mycert.pem", "cert/mycert.pem"); /* load certs */
    server = OpenListener(atoi(portnum));    /* create server socket */
    initialize_user_database();
    while (1)
    {   struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        int client = accept(server, (struct sockaddr*)&addr, &len);  /* accept connection as usual */
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        int pid = fork();

        if(pid == 0)
        {
         //close(server);
        ssl = SSL_new(ctx);              /* get new SSL state with context */
        SSL_set_fd(ssl, client);      /* set connection socket to SSL state */
        Servlet(ssl);         /* service connection */
        exit(0);
        }
        else
        close(client);

    }
    close(server);          /* close server socket */
    SSL_CTX_free(ctx);         /* release context */
}
