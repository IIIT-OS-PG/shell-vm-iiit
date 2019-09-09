#include"header.h"

void prompt()
{
    char hostname[50];
    char direc[50];
    getcwd(direc, 50);
    gethostname(hostname, 50);
    cout<<endl<<getenv("USER")<<'@';
    int id = getuid();
    cout<<hostname;
    cout<<" "<<direc<<' ';
    if(!id)
        cout<<"(#)";
    else
        cout<<"($)";
    cout<<" :";
}