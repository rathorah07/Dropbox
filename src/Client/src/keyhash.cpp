#include "keyhash.h"
#include <iostream>

string keyencrypt (string s){

    unsigned char digest[SHA_DIGEST_LENGTH];

     SHA1((unsigned char*)s.c_str(), s.length(), (unsigned char*)&digest);

     char mdString[SHA_DIGEST_LENGTH*2+1];

     for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
     {
             sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
     }

   string out = mdString;
   return out;
}

int validate_username(string name){

   // invalid character
   if(name.length()==0)
       return 1;

   for (int i=0 ;i<name.length();i++)
   {
       if((name[i] >= 48 && name[i] <=57) || (name[i] >=65 && name[i] <=90) || (name[i]==95) || (name[i] >= 97 && name[i] <=122))
       {}

       else return 1;
   }

   return 0;
}

