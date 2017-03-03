#ifndef SSLCLIENT_H
#define SSLCLIENT_H
#include "stringobject.h"

int ServerConnect(int count, char *strings[]);
int send_username(string username);
int send_credentials(string username,string password);
int check_credentials(string username,string password);
void GLOBAL_SYNCHRONIZE(string username,string temp_path);
int sharebox(string username);
vector<stringobject> sharedwithme(string username);
void handle_sharing(string filename, string filepath,string ownername,string sharedwith);
void  handleupload(string path) ;
void calldownload(string path,string sharer);
void handledownload(string path,string sharer);
void callupload(string path);


#endif // SSLCLIENT_H

