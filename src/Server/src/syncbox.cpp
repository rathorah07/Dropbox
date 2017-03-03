#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Compare.h"

using namespace std;


vector <FileObject> diffcr,diffsr; // DiffCR is Different Records on Server, Diffsr is Different records on client

 static int callback(void *data, int argc, char **argv, char **azColName){
      int i;
      FileObject x;
      
      #ifdef DEBUG
      cout << argc << endl;
      #endif

      x.name  = argv[0];
      x.path  = argv[2];
      x.isDir = atoi(argv[1]);
      x.file_size = atoi(argv[3]);
      x.ltime = atoi(argv[4]);

     diffcr.push_back(x);
    
      return 0;
   }


 static int callback2(void *data, int argc, char **argv, char **azColName){

      #ifdef DEBUG
      cout << "START OF CALLBACK2" << endl;
      #endif

      int i;
      FileObject x;
      //fprintf(stderr, "%s: ", (const char*)data);
     
      #ifdef DEBUG
	  cout << argc << endl;
      #endif

      x.name  = argv[0];
      x.path  = argv[2];
      x.isDir = atoi(argv[1]);
      x.file_size = atoi(argv[3]);
      x.ltime = atoi(argv[4]);

      diffsr.push_back(x);
      return 0;
   }



int smallbox(string path1,string path2)
{

   sqlite3 *db;
   int rc;
   char *zErrMsg = 0;
    char* sql;
  
   
   string query = "ATTACH ";
   string path = "'";
   char *ptr2 = (char *)path1.c_str();
   rc = sqlite3_open(ptr2, &db);
   path += path2;
   query += path;
   query += "' AS Client";
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
   	  #ifdef DEBUG
      fprintf(stderr, "Attached Users database successfully\n");
      #endif
   }
   //ATTACHED


   //Query1
    string newquery = "SELECT * FROM FILESYSTEM  EXCEPT SELECT * FROM Client.FILESYSTEM ";

   //string newquery = "(SELECT * FROM FILESYSTEM WHERE FILESYSTEM.IsDirectory=0) EXCEPT (SELECT * FROM Client.FILESYSTEM WHERE Client.FILESYSTEM.IsDirectory=0)";
    #ifdef DEBUG
    cout << newquery << endl;
    #endif

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
   //Query1-End

   //Query2

/*
   newquery.clear();
   newquery = "SELECT * FROM FILESYSTEM WHERE FILESYSTEM.IsDirectory=1 AND FILESYSTEM.Path NOT IN SELECT Client.FILESYSTEM.Path FROM Client.FILESYSTEM WHERE Client.FILESYSTEM.IsDirectory=1";
    cout << newquery << endl;
   //string newquery = "SELECT * FROM " + path1 + ".FILESYSTEM INTERSECT SELECT * FROM mytmp.FILESYSTEM;";
    ptr= (char *)newquery.c_str();
   sqlite3_exec(db, ptr,callback,0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "CQuery didn't work: %s\n", sqlite3_errmsg(db));
      return 0;
   }
   else
   {
      fprintf(stderr, "Query worked\n");
   }

*/


   //Query2-End


   //Query3


   newquery.clear();
   newquery = "SELECT * FROM Client.FILESYSTEM  EXCEPT SELECT * FROM FILESYSTEM ";
    cout << newquery << endl;
   //string newquery = "SELECT * FROM " + path1 + ".FILESYSTEM INTERSECT SELECT * FROM mytmp.FILESYSTEM;";
    ptr= (char *)newquery.c_str();
   sqlite3_exec(db, ptr,callback2,0, &zErrMsg);
   
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

   //Query3-END

   //Query4

 
   /*newquery.clear();
   newquery = "SELECT * FROM Client.FILESYSTEM WHERE Client.FILESYSTEM.IsDirectory=1 " ;//AND Client.FILESYSTEM.Path NOT IN SELECT FILESYSTEM.Path FROM FILESYSTEM WHERE FILESYSTEM.IsDirectory=1";
    cout << newquery << endl;
   //string newquery = "SELECT * FROM " + path1 + ".FILESYSTEM INTERSECT SELECT * FROM mytmp.FILESYSTEM;";
    ptr= (char *)newquery.c_str();
   sqlite3_exec(db, ptr,callback2,0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "CQuery didn't work: %s\n", sqlite3_errmsg(db));
      return 0;
   }
   else
   {
      fprintf(stderr, "Query worked\n");
   }
   */
   

   //Query4-END


}

 vector<result> clientcode;
 vector<result> servercode;


int blackbox(string path1,string path2,string servertimepath,string clienttimepath,string username) // Path1 is Path till Server db file , Path 2 till client db file
{
   #ifdef DEBUG
   cout << "BLACKBOX CALLED" << endl;
   #endif

   diffsr.clear();
   diffcr.clear();
   smallbox(path1,path2);
  
   clientcode.clear();
   servercode.clear();

   clientcode = compare_client(diffsr,servertimepath);
   servercode = compare_server(diffcr,clienttimepath);
   
   #ifdef DEBUG
   cout << "PRINTING CLIENTCODE " << endl;
  
   for(int i=0;i<clientcode.size();i++)
   cout << clientcode[i].code << " " << clientcode[i].file_name << " " << clientcode[i].path << " " << clientcode[i].isDir << " " << endl;
   cout << "PRINTING SERVERCODE " << endl;
 

   for(int i=0;i<servercode.size();i++)
   cout << servercode[i].code << " " << servercode[i].file_name << " " << servercode[i].path << " " << servercode[i].isDir << " " << endl;
   #endif

}

