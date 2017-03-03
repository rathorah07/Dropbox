#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int count_records;

static int callback2(void *NotUsed, int argc=0, char **argv=NULL, char **azColName=NULL)
{

		   int i;
		   #ifdef DEBUG
		   for(i=0; i<argc; i++){
		      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		   }
		   printf("\n");
		   #endif
		   count_records = atoi(argv[0]) ;



   return 0;
}


static int callback(void *data, int argc, char **argv, char **azColName)
{

	      int i;
	      #ifdef DEBUG
	      fprintf(stderr, "%s: ", (const char*)data);

	      cout << argc << endl;

	      for(i=0; i<argc; i++)
	      {
	         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	      }
	      printf("\n");
	      #endif

	      count_records = atoi(argv[0]) ;


      return 0;
}


int initialize_user_database()
{
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;

   rc = sqlite3_open("db/Users.db", &db);

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

   sql = "CREATE TABLE USERS("  \
         "Username      TEXT PRIMARY KEY    NOT NULL," \
         "Password      TEXT     NOT NULL );";

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

int register_new_user(string new_username,string new_password)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string query;

   rc = sqlite3_open("db/Users.db", &db);

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

 	query = "INSERT INTO USERS(Username,Password)" \
          " VALUES ('" + new_username + "','" + new_password + "');";
    cout << query  << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback2, 0, &zErrMsg);

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

int check_credentials(string new_username,string new_password)
{

   int count=0;
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   const char* data = "Callback function called";
   string query;

   rc = sqlite3_open("db/Users.db", &db);


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



 	query = "SELECT COUNT(*) FROM USERS WHERE" \
          " Username='" + new_username + "' AND Password='" + new_password + "';";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback, (void*)data, &zErrMsg);

	   ////#ifdef DEBUG
	   if( rc != SQLITE_OK )
	   {
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }
	   else
	   {
	      fprintf(stdout, "Operation done successfully\n");
	   }
	   //#endif

   count=count_records;
   sqlite3_close(db);
   return count;
}




int check_username_collision(string new_username)
{
   int count=0;
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
    const char* data = "Callback function called";
   string query;

   rc = sqlite3_open("db/Users.db", &db);

	   ////#ifdef DEBUG
	   if( rc )
	   {
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      return 0;
	   }
	   else
	   {
	      fprintf(stderr, "Opened Users database successfully\n");
	   }
	   //#endif



   query = "SELECT COUNT(*) FROM USERS WHERE" \
          " Username='" + new_username +"';";


    cout << query  << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback, (void*)data, &zErrMsg);

	   ////#ifdef DEBUG
	   if( rc != SQLITE_OK )
	   {
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }
	   else
	   {
	      fprintf(stdout, "Operation done successfully\n");
	   }
	   //#endif

   count=count_records;
   sqlite3_close(db);
   return count;
}
