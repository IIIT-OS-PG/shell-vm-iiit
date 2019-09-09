#include<iostream>
#include<fstream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
typedef long long ll;

void child_handler(char** parr, bool pflag, bool rtflag);

void change_direc(char *cptr[], char pdir[30]);

void eval_pipe(char** ptr, bool rtflag);

char** input(bool& pflag, bool& rflag);

void prompt();

void set_environ();
