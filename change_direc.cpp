#include"header.h"

void change_direc(char *cptr[], char pdir[30])
{
    char *path = cptr[1];
    char prevpath2[30];
    //cout<<"prev start "<<pdir<<endl;
    if(path == NULL || strlen(path) == 0 || strcmp(path, "~") == 0)
    {
        //cout<<"homepath\n";
        getcwd(pdir, 30);
        chdir(getenv("HOME"));
    }
    else if(strcmp(path, "-") == 0)
    {
        //cout<<"prevpath\n";
        getcwd(prevpath2, 30);
        chdir(pdir);
        strcpy(pdir, prevpath2);
    }
    else
    {
        //cout<<"normpath\n";
        getcwd(pdir, 30);
        int f = chdir(path);
        if(f == -1)
            cout<<"\t\tInvalid path\n";
    }
    //cout<<"prev end "<<pdir<<endl;
}