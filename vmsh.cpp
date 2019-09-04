#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
#define max_word_len 20
#define max_words 50
typedef long long ll;

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

/*void input(char **carrptr, string &str, bool &b)
{
    char ch;
    ch = getchar();
    int lv=0;
    while(ch != '\n' && ch != '\0')
    {
        str[lv] = ch;
        ++lv;
    }
    carrptr = new char[str.length()+1];
    int lv1 = 0, lv2 = 0, count=0;
    lv=0;
    while(count < str.length())
    {
        if(str[lv] == '|')
            b = true;
        if(str[lv] != ' ' && str[lv] != '\n' && str[lv] != '\0')
        {
            carrptr[lv1][lv2] = str[lv];
            ++lv2;
        }
        else
        {
            ++lv1;
            lv2=0;
        }
        ++count;
    }
    carrptr[lv+1] = NULL;
}*/ 

void child_handler(char** parr, bool pflag, bool rtflag)
{
    ll lv;
    int fd;
    bool decide;
    char pathh[30];
    getcwd(pathh, 30);
    if(pflag || rtflag)
    {
        if(!pflag && rtflag)
        {
            for(lv=0; parr[lv] != NULL; lv++);
            cout<<"runnin\n";
            lv -= 2;
            cout<<parr[lv+1]<<endl;
            //strcat(pathh, parr[lv+1]);
            //cout<<pathh<<endl;
            
            decide = (strcmp(parr[lv], ">") == 0)?true:false;
            fd = open(parr[lv+1], O_APPEND | O_CREAT | 0640);
            parr[lv] = NULL;
            cout<<"fd "<<fd<<endl;
            close(1);
            dup2(fd, 1);
            
            execvp(parr[0], parr);
            close(fd);
            cout<<"done dana done dan\n";
        }

    }
    else
    {
        int s_f = execvp(parr[0], parr);
        if(s_f == -1)
            cout<<"     error\n";
    }
}

int main()
{
    //char *charr[10];
    char ch;
    int lv = -1;
    bool pipeflag, redirflag;
    while(1)
    {
        pipeflag = false;
        redirflag = false;
        prompt();
        //cout<<"prompted\n";
        char **charr = new char*[max_words];
        //cout<<"allocated memory\n";
        //string str;
        //input(charr, str, &pipeflag);
        lv = -1;
    	do{
    	    ++lv;
    	    charr[lv] = new char[max_word_len];
    	    cin>>charr[lv];
            if(strcmp(charr[lv], "|") == 0)
                pipeflag = true;
            else if(strcmp(charr[lv], ">") == 0 || strcmp(charr[lv], ">>") == 0)
                redirflag = true;
    	    //cout<<lv<<" took inp of "<<charr[lv]<<endl;
    	    ch = getchar();

    	}while(ch != '\n');
    	++lv;
    	charr[lv] = NULL;
        int lv = 0;
        while(charr[lv])
            cout<<charr[lv++]<<endl;
        //cout<<"     lv end "<<lv<<endl;
    	//cout<<"loop done\n";
    	/*while(lv>-1)
    	{
        	cout<<lv<<endl;
        	if(charr[lv])
            	cout<<charr[lv]<<endl;
        	else
            	cout<<"null\n";
            --lv;
    	}*/
        if(strlen(charr[0]) == 0)
            continue;
        if(strcmp(charr[0], "exit") == 0)
        {
            break;
            //delete charr;
        }
        /*if(strcmp(charr[0], "cd") == 0)
        {
            int f = chdir(charr+)
        }*/
        int f = fork();
        if(f)
        {
            //cout<<"     inside parent\n";
            wait(NULL);
            //cout<<"     parent's wait ended\n";
        }
        else
        {
            //cout<<"     inside child\n";
            child_handler(charr, pipeflag, redirflag);
            exit(0);
        }
        //cout<<f<<"      deleting memory\n";
        --lv;
        //cout<<"lv "<<lv<<endl;
        while(lv>-1)
        {
            //cout<<f<<"      deleting "<<charr[lv]<<endl;
            delete charr[lv];
            //cout<<f<<"      deleted\n";
            --lv;
        }
        //cout<<f<<"      deleted indivs\n";
        delete charr;
    }
    
    return 0;
}