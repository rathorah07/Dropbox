#ifndef LOGINTABLE_H
#define LOGINTABLE_H
int initialize_user_database();

int register_new_user(string new_username,string new_password);

// int check_credentials(string new_username,string new_password);

int check_username_collision(string new_username);
#endif
