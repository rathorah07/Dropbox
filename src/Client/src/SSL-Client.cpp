//SSL-Client.c
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "Input_Instance.h"
#include "string_int.h"
#include "fileinfo1.h"
#include "func.h"
#include "filesysmaker.h"
#include "time_handle.h"
#include "stringobject.h"
#include "sharestring.h"
#include"path_handle.h"
#include <vector>

#define FAIL    -1


 using namespace std;

SSL_CTX *ctx;
int server;
SSL *ssl;
char buf[1024];
int bytes;
char *hostname, *portnum;
string server_name;

int OpenConnection(const char *hostname, int port)
{   int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

SSL_CTX* InitCTX(void)
{   const SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = SSLv23_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}

void send_computername()
{
    string computer_name = getenv("HOME");

    computer_name += "/Desktop";

     int len = computer_name.length();
    string temp_len  = convert_to_string(computer_name.length()); // Getting length in Server buffer format



    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, computer_name.c_str(), computer_name.length());

}


string receive_servername()
{
	#ifdef DEBUG
    cout << "Inside receive_servername" << endl ; //Analogous to give username
    #endif

    char buffer[256];
    int bytes=0;

    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string username_length = word_to_string(buffer,18);

    bytes = SSL_read(ssl, buffer, convert_to_int(username_length));
    string username = word_to_string(buffer,convert_to_int(username_length));
    return username;
}

void receive_file()
{

    string file_name,file_path;

    #ifdef DEBUG
    cout << "Inside Receive File on ClientSide" << endl;
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

    file_path.clear();
    file_path = buffer[0];
    for(int i=1;i<bytes;i++)
    file_path += buffer[i];

    file_name = file_path;
    /*file_name = "'";
    file_name += file_path + "'";
    */

    #ifdef DEBUG
    cout << file_name << ":      this is file path"<<endl;
    cout<<file_name.length()<<endl;
    #endif


     bytes=0;
    bytes = SSL_read(ssl,buffer,18);

    string sfile_size = word_to_string(buffer,18);
    long long file_size= convert_to_int(sfile_size);

    long long bytes_read=0;
  //  if(bytes>0)
    //{
        create_path(file_name);
        fout.open(file_name.c_str(),ios::binary|ios::out); // TODO : CHANGE TO FILE PATH
    //}
        if(fout.is_open())
        {
        	#ifdef DEBUG
            cout << "Open" << endl;
            #endif
        }
        else
        {
        	#ifdef DEBUG
            cout << "Closed" << endl;
        	#endif
        }

    //else
      //  ERR_print_errors_fp(stderr);
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






void send_file( string file_path)
{
	#ifdef DEBUG
    cout << "Send_file_called" << endl;
    #endif

    string file_name;
    string temp_name= file_path ;

    input_instance obj(file_path.c_str());
    fileinfo file_obj(file_path);

    temp_name = getenv("HOME");
    temp_name += "/Desktop";

    temp_name = cut_homepath(file_path,temp_name);

    file_name = server_name + temp_name;

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

        string command = " touch -c -a -m -t 200502212234.44 ";
        command += "'" + file_path + "'";   //file name is here filepath
        system(command.c_str());
}

int send_username(string username)
{
    char *data;

    #ifdef DEBUG
    cout << "Inside send_username" << endl;
    #endif

    string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format
     ShowCerts(ssl);
    string code;
    code = convert_to_string(1);

    SSL_write(ssl, code.c_str(), 18);
    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

    char numb[18];

    int bytes=0;
    //while(bytes==0)
    SSL_read(ssl, numb, 1);


    return (numb[0] - '0');

}


int send_credentials(string username,string password)
{
    char *data;

    #ifdef DEBUG
    cout << "Inside send_password" << endl;
    #endif

    ShowCerts(ssl);
    string code;
    code = convert_to_string(2);

    string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format
    cout << "Code is " << code << endl;
    SSL_write(ssl, code.c_str(), 18);
    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

     temp_len  = convert_to_string(password.length()); // Getting length in Server buffer format
    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, password.c_str(), password.length());

    char numb[18];

    int bytes=0;
    //while(bytes==0)
    SSL_read(ssl, numb, 1);


    return (numb[0] - '0');

}

int check_credentials(string username,string password)
{
    char *data;

    #ifdef DEBUG
    cout << "Inside check_credentials" << endl;
    #endif

     ShowCerts(ssl);
    string code;
    code = convert_to_string(4); // 4 is the error code

    string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format


    SSL_write(ssl, code.c_str(), 18);
    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

     temp_len  = convert_to_string(password.length()); // Getting length in Server buffer format
    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, password.c_str(), password.length());


    char numb[18];

    int bytes=0;
    //while(bytes==0)
    SSL_read(ssl, numb, 1);

    if(numb[0]=='1')
    {

            //give_username(username);
            server_name = receive_servername();
            send_computername();

    }


    return (numb[0] - '0');

}



void give_username(string username)
{
    string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format



    SSL_write(ssl, temp_len.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

    //Username Sent
}


void handle_code1()
{
	#ifdef DEBUG
    cout << "Inside Handle_Code1" << endl;
    #endif

    char buffer[256];
    int bytes=0;
     while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string spath_length = word_to_string(buffer,18);
    int path_length = convert_to_int(spath_length);

    bytes=0;
    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, path_length);
    }
     string path = word_to_string(buffer,path_length);

    string command = "rm '";
    command +=  getenv("HOME") ;
    command += "/Desktop" + path +"'";
    system(command.c_str());

}

void handle_code2()
{
	#ifdef DEBUG
    cout << "Inside Handle_Code2" << endl;
    #endif

    return; // FILE DELETED ON SERVER - CLIENT DOES NOT HAVE TO DO ANYTHING
}

void handle_code3()
{
	#ifdef DEBUG
    cout << "Inside Handle_Code3" << endl;
    #endif

    char buffer[256];
    int bytes=0;
     while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string spath_length = word_to_string(buffer,18);
    int path_length = convert_to_int(spath_length);



    bytes=0;
    while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, path_length);
    }
     string path = word_to_string(buffer,path_length);
     string temp_path = getenv("HOME");
     temp_path += "/Desktop" ;
     path = temp_path +path;

    send_file(path);

}

void handle_code4()
{
	#ifdef DEBUG
    cout << "Inside Handle_Code4" << endl;
    #endif

    receive_file();
}


void handledownload(string path,string sharername) // Receives Partial Path
{


    string full_path =  server_name + path;

    string slen;
    slen = convert_to_string(full_path.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, full_path.c_str(), full_path.length());

    slen = convert_to_string(sharername.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, sharername.c_str(), sharername.length());


    receive_file();
    #ifdef DEBUG
    cout  << "File DOWNLOADED" <<  endl;
    #endif

}

void  handleupload(string path) // Receives Partial Path
{
    string full_path = getenv("HOME");
    full_path +="/Desktop/";
    full_path += path;
    send_file(full_path);
}

void calldownload(string path,string sharername)
{
    string code;
    code = convert_to_string(8); // T
    SSL_write(ssl, code.c_str(), 18);
    handledownload(path,sharername);
}

void callupload(string path)
{
    string code;
    code = convert_to_string(9); // T
    SSL_write(ssl, code.c_str(), 18);
    handleupload(path);
}




void handle_codes() //HANDLES CLIENT-SERVER SYNC COMMUNICATION
{
    int bytes;
    bytes=0;
    char buffer[256];



     while(bytes==0)
    {
        usleep(100000);
        bytes = SSL_read(ssl, buffer, 18);
    }
    string scode_num = word_to_string(buffer,18);
    int code_number = convert_to_int(scode_num);



    for(int it=0;it<code_number;it++)
    {
        bytes=0;
         while(bytes==0)
        {
            usleep(100000);
            bytes = SSL_read(ssl, buffer, 18);
        }
        string code_name = word_to_string(buffer,18);
        int code = convert_to_int(code_name);
        switch(code)
        {
            case 1: handle_code1();
            break;
            case 2: handle_code2();
            break;
            case 3: handle_code3();
            break;
            case 4: handle_code4();
            break;
        }
    }

    /*string code_name;
    int code;
    bytes=0;
    while(bytes==0)
   {
       usleep(100000);
       bytes = SSL_read(ssl, buffer, 18);
   }
    scode_num = word_to_string(buffer,18);
   code_number = convert_to_int(scode_num);



   for(int it=0;it<code_number;it++)
   {
       bytes=0;
        while(bytes==0)
       {
           usleep(100000);
           bytes = SSL_read(ssl, buffer, 18);
       }
        code_name = word_to_string(buffer,18);
        code = convert_to_int(code_name);
       switch(code)
       {
           case 1: handle_code1();
           break;
           case 2: handle_code2();
           break;
           case 3: handle_code3();
           break;
           case 4: handle_code4();
           break;
           case 5 :
           break;
       }
   }

 */




}




void GLOBAL_SYNCHRONIZE(string username,string temp_path)
{




    char *data;

    #ifdef DEBUG
    cout << "Inside GLOBAL_SYNCHRONIZE" << endl;
    #endif

    string code;
    code = convert_to_string(5); // T
    //string temp_len  = convert_to_string(username.length()); // Getting length in Server buffer format
    SSL_write(ssl, code.c_str(), 18);
    //Sever ready to accept syncs

    //give_username(username);
    //server_name = receive_servername();
    //send_computername();

    cout << server_name << endl;

    string user_dir = getenv("HOME");
    user_dir += "/Desktop/";
    user_dir += username;

    string path_to_cut = getenv("HOME");
    path_to_cut += "/Desktop";
    //Generating Database
     drop_table(temp_path);
     initialize_files_database(temp_path);
     generate_database(user_dir,path_to_cut,temp_path);

    //Genrated Database
     cout << "RETURNED " << endl;
     string dbpath = temp_path + "/clientdb.db";
     string timepath = temp_path + "/client_time.txt";
     send_file(dbpath);
     send_file(timepath);
     //SENT DATABASE

     handle_codes();

    // WAIT FOR SYNCBOX TO OCCUR : NOW SERVER BECOMES THE ONE TO SEND SIGNALS
    write_time(timepath,1);// TODO : UPDATE SERVER/CLIENT TIME

}


void handle_sharing(string filename, string filepath,string ownername,string sharedwith)
{
    char *data;

    #ifdef DEBUG
    cout << "Inside Handle_Sharing" << endl;
    #endif

    string code;
    code = convert_to_string(6); // T
    SSL_write(ssl, code.c_str(), 18);

    //Sever side handle sharing called.
    handleupload(filepath);

    string slen;
    slen = convert_to_string(filename.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, filename.c_str(), filename.length());

    slen = convert_to_string(filepath.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, filepath.c_str(), filepath.length());

    slen = convert_to_string(ownername.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, ownername.c_str(), ownername.length());

    slen = convert_to_string(sharedwith.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, sharedwith.c_str(), sharedwith.length());
}

vector<stringobject> sharedwithme(string username) // INCLUDE IN SSL-Client
{
    char *data;

    #ifdef DEBUG
    cout << "Inside Shared with me" << endl;
    #endif

    string code;
    code = convert_to_string(7); // T
    SSL_write(ssl, code.c_str(), 18);

    //Sever side handle sharing called.

    string slen;
    slen = convert_to_string(username.length());
    SSL_write(ssl, slen.c_str(), 18);
    SSL_write(ssl, username.c_str(), username.length());

    receive_file();
    sharebox(username);
    extern vector<stringobject> vec;
    return vec;

}



int ServerConnect(int count, char *strings[])
{
    SSL_CTX *ctx;
        int server;

        char buf[1024];
        int bytes;
        char *hostname, *portnum;

        if ( count != 3 )
        {
            printf("usage: %s <hostname> <portnum>\n", strings[0]);
            exit(0);
        }
        SSL_library_init();
        hostname=strings[1];
        portnum=strings[2];

        ctx = InitCTX();
        server = OpenConnection(hostname, atoi(portnum));
        ssl = SSL_new(ctx);      // create new SSL connection state //
        SSL_set_fd(ssl, server);    // attach the socket descriptor //

        if ( SSL_connect(ssl) == FAIL )   // perform the connection //
            ERR_print_errors_fp(stderr);
        else
        {   char *msg = "Yo";

            printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
            ShowCerts(ssl);        // get any certs //
            //send_file(ssl);
            //send_file(ssl,(string)"dropbox.png");
            //SSL_write(ssl, msg, strlen(msg));   // encrypt & send message //
            //bytes = SSL_read(ssl, buf, sizeof(buf)); // get reply & decrypt //
            //buf[bytes] = 0;
            printf("Received: \"%s\"\n", buf);
            //SSL_free(ssl);        // release connection state //
        }

        //GLOBAL_SYNCHRONIZE();

        return 0;

}

int CloseConnection()
{
    SSL_free(ssl);
    close(server);         // close socket //
    SSL_CTX_free(ctx);        // release context
    return 0;
}
