#include "filesysmaker.h"

static int callback2(void *NotUsed, int argc=0, char **argv=NULL, char **azColName=NULL)
{
   int i;
   #ifdef DEBUG
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   printf("\n");
   #endif

   return 0;
}


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


int initialize_files_database(string path)
{
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string dbname = path;
   dbname += "/clientdb.db";
   char *ptr = (char *)dbname.c_str();
   rc = sqlite3_open(ptr, &db);  // TODO : MAKE IT USERNAME DEPENDENT

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


   sql = "CREATE TABLE FILESYSTEM("  \
         "Filename      TEXT PRIMARY KEY    NOT NULL," \
         "IsDirectory   INTEGER NOT NULL," \
         "Path   TEXT NOT NULL," \
         "Filesize INTEGER NOT NULL," \
         "Ltime      INTEGER    NOT NULL );";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   	if( rc != SQLITE_OK )
   	{	
   		#ifdef DEBUG
   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      	sqlite3_free(zErrMsg);
      	#endif
   	}

   	else
   	{
   	  #ifdef DEBUG
      fprintf(stdout, "Table created successfully\n");
      #endif
    }


   sqlite3_close(db);
   return 0;
}

int create_new_entry(string path,string oFilename,int oIsDirectory,string oPath,int oFilesize, int oLtime)
{
   #ifdef DEBUG
   cout << "create_new_entry called" << endl;
   #endif

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   string query;

   string dbname = path;
   dbname += "/clientdb.db";
   char *ptr = (char *)dbname.c_str();



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

    query = "INSERT INTO FILESYSTEM(Filename,IsDirectory,Path,Filesize,Ltime)" \
          " VALUES ('" + oFilename + "','" + to_string(oIsDirectory) + "','" + oPath + "','" + to_string(oFilesize) + "','"  + to_string(oLtime) +  "');";
    
    #ifdef DEBUG
    cout << query  << endl;
    #endif

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback2, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
   	  #ifdef DEBUG
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      #endif
      sqlite3_free(zErrMsg);
   }
   else
   {
   	  #ifdef DEBUG
      fprintf(stdout, "Records created successfully\n");
  	  #endif
   }

   sqlite3_close(db);
   return 0;
}


int drop_table(string path)
{
   int count=0;
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char* sql;
   const char* data = "Callback function called";
   string query;

   string dbname = path;
   dbname += "/clientdb.db";
   char *ptr = (char *)dbname.c_str();


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

  

   query = "DROP TABLE FILESYSTEM";
   
   
           
    cout << query  << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, query.c_str(), callback2, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK )
   {  
   	  #ifdef DEBUG
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      #endif

      sqlite3_free(zErrMsg);
   }
   else
   {
   	  #ifdef DEBUG
      fprintf(stdout, "Operation done successfully\n");
      #endif
   }

   sqlite3_close(db);
   return 0;
}

