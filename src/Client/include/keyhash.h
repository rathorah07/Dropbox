#ifndef KEYHASH
#define KEYHASH

#include <stdio.h>
#include <openssl/sha.h>
#include <string>
#include <cstdlib>
#include <pthread.h>

using namespace std;

string keyencrypt (string);

int validate_username(string);
#endif // KEYHASH

