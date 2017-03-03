#include "fileinfo1.h"


fileinfo::fileinfo(){
			
			filepath = NULL;
			isdir = 0;
			exist = 0;
		 	filesize;      // sys/types.h
			last_modify = 0;   // time.h
			last_access = 0;
			last_statuschange = 0;	
}




fileinfo::fileinfo(string path){
			
			filepath = (char *)path.c_str();

			if(stat(filepath, &info_box)!=0)
			{
				exist = false;		// no such path exist
			}
			else
			{	
				exist = true;
				switch (info_box.st_mode & S_IFMT){
			
				case S_IFDIR: isdir = true;      break;
				default: isdir      = false;     break;			
				}
	
				filesize   	  			= info_box.st_size;
				last_modify 	  		= info_box.st_mtime;
				last_access 	  		= info_box.st_mtime; 
				last_statuschange 		= info_box.st_ctime;
				
			}	
	
}

int fileinfo::setfile(string path){
			
			filepath = (char *)path.c_str();
			return refresh_stat();
}
		
int fileinfo::refresh_stat(void){
		

			if(stat(filepath, &info_box)!=0)
			{
				exist = false;
				return -1;    // no such path exist
			}

			else
			{	
				exist = true;
				switch (info_box.st_mode & S_IFMT){
			
				case S_IFDIR: isdir = true;      break;
				default: isdir      = false;     break;			
				}
	
				filesize   	  	  = info_box.st_size;
				last_modify 	  = info_box.st_mtime;
				last_access 	  = info_box.st_mtime;
				last_statuschange = info_box.st_ctime;
				
			}

			
			
			return 0;
	
}