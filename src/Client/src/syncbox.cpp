#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "FileObjects.h"

using namespace std;


vector <FileObject> diffar;

 static int callback(void *data, int argc, char **argv, char **azColName)
 {
      
      int i;
      FileObject x;
      
      #ifdef DEBUG
      fprintf(stderr, "%s: ", (const char*)data);
      cout << argc << endl;
      #endif
      
      x.name  = argv[0];
      x.path  = argv[2];
      x.isDir = atoi(argv[1]);
      x.ltime = atoi(argv[2]);
      diffar.push_back(x);
        
      return 0;
   }

int blackbox()
{
	sqlite3 *db;
	int rc;
	char *zErrMsg = 0;
    char* sql;
  
	
	string query = "ATTACH ";
	string path = "'";
	path += getenv("HOME");
   string path1 = getenv("HOME");
   path1+= "/Desktop/anm/xyz.db";
   char *ptr2 = (char *)path1.c_str();
   rc = sqlite3_open(ptr2, &db);
	path += "/Desktop/anm/client_files_database.db";
	query += path;
	query += "' AS A";
   cout << query << endl;
	char *qptr=(char *)query.c_str();

   if( rc )
   {  
   	  #ifdef DEBUG
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      #endif

      return 0;
   }
   else
   {
   	  #ifdef DEBUG
      fprintf(stderr, "Opened Users database successfully\n");
      #endif
   }
   rc = sqlite3_exec(db, qptr,callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK )
   {
   	  #ifdef DEBUG
      fprintf(stderr, "Can't attach database: %s\n", sqlite3_errmsg(db));
      #endif

      return 0;
   }
   else
   {
      fprintf(stderr, "Attached Users database successfully\n");
   }
   string newquery = "SELECT * FROM FILESYSTEM EXCEPT SELECT * FROM A.FILESYSTEM";
    cout << newquery << endl;
   //string newquery = "SELECT * FROM " + path1 + ".FILESYSTEM INTERSECT SELECT * FROM mytmp.FILESYSTEM;";
   char *ptr= (char *)newquery.c_str();
   sqlite3_exec(db, ptr,callback,0, &zErrMsg);
   
   if( rc != SQLITE_OK )
   {  
   	  #ifdef DEBUG
      fprintf(stderr, "CQuery didn't work: %s\n", sqlite3_errmsg(db));
      #endif

      return 0;
   }
   else
   {	
   	  #ifdef DEBUG
      fprintf(stderr, "Query worked\n");
   	  #endif
   }

}
