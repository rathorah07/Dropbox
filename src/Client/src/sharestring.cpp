#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "stringobject.h"

using namespace std;

vector<stringobject> vec;

  static int callback(void *data, int argc, char **argv, char **azColName)
  {
      int i;
      
      #ifdef DEBUG
      fprintf(stderr, "%s: ", (const char*)data);
      cout << argc << endl;
      for(i=0; i<argc; i++){
         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      }
      printf("\n");
      #endif
      //	count_records = atoi(argv[0]) ;
   
   		stringobject x;
   		x.path = argv[0];
   		x.name = argv[1];
   		x.owner = argv[2];

      
   		
   		vec.push_back(x);   	
      
      return 0;
  }


int sharebox(string username)
{
    vec.clear();
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string temp = getenv("HOME");
   temp += "/Desktop/";
   temp += username;
   temp += "_temp/sharedb.db";
   char *ptr = (char *)temp.c_str();
   rc = sqlite3_open(ptr, &db);

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

   sql = "SELECT * FROM SHARED";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
}
