#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

  static int callback(void *data, int argc, char **argv, char **azColName){
      
	      
	      int i;
	      #ifdef DEBUG
	      fprintf(stderr, "%s: ", (const char*)data);
	      cout << argc << endl;
	      for(i=0; i<argc; i++){
	         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	      }
	      printf("\n");
	      #endif
    
      return 0;
   }

static int callback2(void *NotUsed, int argc=0, char **argv=NULL, char **azColName=NULL)
{	
	   
	   int i;
	   #ifdef DEBUG
	   for(i=0; i<argc; i++)
	   {
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
   	   printf("\n");
   	   #endif
   
   return 0;
}

int initialize_share_database(string username) // TO BE CALLED ON SIGNUP 
{
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string temp = getenv("HOME");
   temp += "/Desktop/VDesktop/";
   temp += username;
   temp += "_temp/sharedb.db";
   char *ptr = (char *)temp.c_str();
   rc = sqlite3_open(ptr, &db);

	   #ifdef DEBUG
	   if( rc )
	   {
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   else
	   {
	      fprintf(stderr, "Opened Users database successfully\n");
	   }
	   #endif

   sql = "CREATE TABLE SHARED("  \
         "FilePath     TEXT     UNIQUE," \  
         "FileName     TEXT     NOT NULL," \  
         "FileOwner      TEXT     NOT NULL );";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		#ifdef DEBUG
	   	if( rc != SQLITE_OK )
	   	{
	   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      	sqlite3_free(zErrMsg);
	   	}
	   	else
	   	{
	      fprintf(stdout, "Table created successfully\n");
	    }
	    #endif


   sqlite3_close(db);
   return 0;
}


int add_new_entry(string path, string filename, string ownername,string username)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string query;

   string temp = getenv("HOME");
   temp += "/Desktop/VDesktop/";
   temp += username;
   temp += "_temp/sharedb.db";
   

   char *ptr = (char *)temp.c_str();
   rc = sqlite3_open(ptr, &db);
	   
	   #ifdef DEBUG
	   if( rc )
	   {
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   else
	   {
	      fprintf(stderr, "Opened Sharing database successfully\n");
	   }
	   #endif

 	query = "INSERT INTO SHARED(FilePath,FileName,FileOwner)" \
          " VALUES ('" + path + "','" + filename + "','" + ownername + "')";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);
   
   #ifdef DEBUG
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Records created successfully\n");
   }
   #endif
   
   sqlite3_close(db);
   return 0;
}
